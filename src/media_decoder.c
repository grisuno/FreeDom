/*
 * media_decoder — implementation using FFmpeg's safe C API.
 *
 * A separate sandboxed process that decodes MPEG-TS (H.264/H.265) segments
 * into raw ARGB frames. Communication is over two pipes; no shell, no popen,
 * no file I/O on untrusted paths.
 *
 * Architecture:
 *   Parent forks+execs this binary with --media-decoder <out_fd> <cmd_fd>.
 *   The decoder:
 *     1. Creates an AVFormatContext around an AVIOContext that reads from
 *        an in-memory buffer (the received TS segment).
 *     2. Finds the first video stream, opens its decoder.
 *     3. Reads packets, decodes frames, converts to ARGB via sws_scale.
 *     4. Sends each frame back to the parent over out_fd.
 *     5. Multiple MD_DECODE commands append segments; MD_FLUSH drains them.
 *
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFmpeg's allocator. It does NOT get network, fork, or file
 * writes. See os_sandbox.c OS_PROFILE_MEDIA_DECODER.
 */

#define _POSIX_C_SOURCE 200809L

#include "media_decoder.h"

#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>

/* Pipe I/O helpers (EINTR-safe). */

static int write_full(int fd, const void *buf, size_t n) {
    const uint8_t *p = (const uint8_t *)buf;
    size_t done = 0;
    while (done < n) {
        ssize_t w = write(fd, p + done, n - done);
        if (w < 0) { if (errno == EINTR) continue; return -1; }
        done += (size_t)w;
    }
    return 0;
}

static int read_full(int fd, void *buf, size_t n) {
    uint8_t *p = (uint8_t *)buf;
    size_t got = 0;
    while (got < n) {
        ssize_t r = read(fd, p + got, n - got);
        if (r < 0) { if (errno == EINTR) continue; return -1; }
        if (r == 0) return -1;
        got += (size_t)r;
    }
    return 0;
}

/* Sends an error response to the parent (non-fatal, stream continues). */
static void send_error(int fd, const char *msg) {
    uint8_t tag = MD_ERROR;
    size_t len = strlen(msg);
    write_full(fd, &tag, 1);
    write_full(fd, &len, sizeof len);
    write_full(fd, msg, len);
}

/* --- The decoder context (state lives across segments) --- */

typedef struct decoder_ctx {
    int out_fd;
    int stream_idx;          /* video stream index in the format context */
    int w, h;                /* video dimensions (valid after first MD_DECODE) */
    int stream_inited;       /* nonzero after first successful decode */
    int has_audio;           /* set during init */
    /* FFmpeg objects: created on first segment, reused for subsequent ones. */
    AVFormatContext *fmt_ctx;
    AVCodecContext  *codec_ctx;
    AVFrame         *frame;  /* decoded frame (YUV) */
    AVFrame         *rgb;    /* converted frame (ARGB) */
    struct SwsContext *sws;  /* colour converter */
    AVPacket        *pkt;
    int64_t          pts_offset_us; /* running sum of segment durations */
    int              eos_sent;      /* have we sent MD_EOS after MD_FLUSH? */
} decoder_ctx;

/* Frees all FFmpeg objects inside ctx but NOT ctx itself. Zeros the struct. */
static void decoder_close(decoder_ctx *dc) {
    if (dc->sws) sws_freeContext(dc->sws);
    av_frame_free(&dc->rgb);
    av_frame_free(&dc->frame);
    avcodec_free_context(&dc->codec_ctx);
    avformat_close_input(&dc->fmt_ctx);
    av_packet_free(&dc->pkt);
    memset(dc, 0, sizeof *dc);
    dc->stream_idx = -1;
    dc->out_fd = -1;
}

/* Initialises the decoder from the first TS segment bytes. The caller passes
 * the complete segment data so avformat can probe it. On success the
 * decoder context is ready for decode_segment calls. */
static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len) {
    /* Create an AVIOContext that reads from the in-memory buffer. */
    dc->fmt_ctx = avformat_alloc_context();
    if (dc->fmt_ctx == NULL) { send_error(dc->out_fd, "OOM avformat_alloc"); return -1; }

    /* Custom AVIOContext: no callbacks to the filesystem. The buffer is the
     * data we already have, so we use a simple read-packet callback. */
    unsigned char *avio_buf = (unsigned char *)av_malloc(len + AV_INPUT_BUFFER_PADDING_SIZE);
    if (avio_buf == NULL) { send_error(dc->out_fd, "OOM avio buf"); return -1; }
    memcpy(avio_buf, data, len);
    memset(avio_buf + len, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    /* We use a custom AVIOContext with no seek wrapper for simplicity: the
     * first segment IS the entire stream for probing purposes. For multi-segment
     * HLS, each segment is a separate avformat_open_input/close cycle. */
    dc->fmt_ctx->pb = avio_alloc_context(avio_buf, (int)len, 0, NULL,
                                          NULL, NULL, NULL);
    if (dc->fmt_ctx->pb == NULL) {
        av_free(avio_buf);
        avformat_free_context(dc->fmt_ctx);
        dc->fmt_ctx = NULL;
        send_error(dc->out_fd, "OOM avio_alloc");
        return -1;
    }

    /* Probe and open. */
    if (avformat_open_input(&dc->fmt_ctx, "", NULL, NULL) != 0) {
        /* avformat_open_input may free pb on failure */
        dc->fmt_ctx = NULL;
        send_error(dc->out_fd, "avformat_open_input failed");
        return -1;
    }

    if (avformat_find_stream_info(dc->fmt_ctx, NULL) < 0) {
        send_error(dc->out_fd, "avformat_find_stream_info failed");
        return -1;
    }

    /* Find the first video stream. */
    dc->stream_idx = -1;
    for (unsigned int i = 0; i < dc->fmt_ctx->nb_streams; ++i) {
        if (dc->fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            dc->stream_idx = (int)i;
            break;
        }
        if (dc->fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
            dc->has_audio = 1;
    }
    if (dc->stream_idx < 0) {
        send_error(dc->out_fd, "no video stream found");
        return -1;
    }

    AVCodecParameters *par = dc->fmt_ctx->streams[dc->stream_idx]->codecpar;
    const AVCodec *codec = avcodec_find_decoder(par->codec_id);
    if (codec == NULL) {
        send_error(dc->out_fd, "unsupported video codec");
        return -1;
    }

    dc->codec_ctx = avcodec_alloc_context3(codec);
    if (dc->codec_ctx == NULL) { send_error(dc->out_fd, "OOM codec ctx"); return -1; }
    if (avcodec_parameters_to_context(dc->codec_ctx, par) < 0) {
        send_error(dc->out_fd, "avcodec_parameters_to_context failed");
        return -1;
    }
    if (avcodec_open2(dc->codec_ctx, codec, NULL) < 0) {
        send_error(dc->out_fd, "avcodec_open2 failed");
        return -1;
    }

    dc->w = dc->codec_ctx->width;
    dc->h = dc->codec_ctx->height;
    if (dc->w <= 0 || dc->h <= 0 || dc->w > 8192 || dc->h > 8192) {
        send_error(dc->out_fd, "invalid video dimensions");
        return -1;
    }

    /* Allocate frames. */
    dc->frame = av_frame_alloc();
    dc->rgb   = av_frame_alloc();
    dc->pkt   = av_packet_alloc();
    if (dc->frame == NULL || dc->rgb == NULL || dc->pkt == NULL) {
        send_error(dc->out_fd, "OOM frames");
        return -1;
    }

    /* Allocate the RGB output buffer for sws_scale (ARGB = Cairo-friendly). */
    int rgb_bufsize = av_image_alloc(dc->rgb->data, dc->rgb->linesize,
                                     dc->w, dc->h, AV_PIX_FMT_BGRA, 1);
    if (rgb_bufsize < 0) { send_error(dc->out_fd, "av_image_alloc failed"); return -1; }

    /* Initialise the colour converter (YUV→ARGB). */
    dc->sws = sws_getContext(dc->w, dc->h, dc->codec_ctx->pix_fmt,
                             dc->w, dc->h, AV_PIX_FMT_BGRA,
                             SWS_BILINEAR, NULL, NULL, NULL);
    if (dc->sws == NULL) { send_error(dc->out_fd, "sws_getContext failed"); return -1; }

    dc->stream_inited = 1;
    dc->pts_offset_us = 0;
    return 0;
}

/* Decodes one segment of TS data and sends frames. Returns the number of
 * frames sent, or -1 on fatal error. */
static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len) {
    if (!dc->stream_inited) {
        if (decoder_init(dc, data, len) != 0) return -1;
        /* Send MD_STREAM_INFO to parent. */
        uint8_t tag = MD_STREAM_INFO;
        int32_t codec = (int32_t)dc->codec_ctx->codec_id;
        int32_t w32 = (int32_t)dc->w, h32 = (int32_t)dc->h;
        int32_t ha32 = (int32_t)dc->has_audio;
        write_full(dc->out_fd, &tag, 1);
        write_full(dc->out_fd, &codec, sizeof codec);
        write_full(dc->out_fd, &w32, sizeof w32);
        write_full(dc->out_fd, &h32, sizeof h32);
        write_full(dc->out_fd, &ha32, sizeof ha32);
        return 0; /* frames from this segment come from subsequent decode calls */
    }

    /* We need to re-mux the segment into a new format context (each TS segment
     * is self-contained for HLS). We create a temporary AVFormatContext using
     * the same io buffer pattern. */
    AVFormatContext *seg_fmt = avformat_alloc_context();
    if (seg_fmt == NULL) { send_error(dc->out_fd, "OOM seg fmt"); return -1; }

    unsigned char *buf = (unsigned char *)av_malloc(len + AV_INPUT_BUFFER_PADDING_SIZE);
    if (buf == NULL) { avformat_free_context(seg_fmt); send_error(dc->out_fd, "OOM buf"); return -1; }
    memcpy(buf, data, len);
    memset(buf + len, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    seg_fmt->pb = avio_alloc_context(buf, (int)len, 0, NULL, NULL, NULL, NULL);
    if (seg_fmt->pb == NULL) { av_free(buf); avformat_free_context(seg_fmt); return -1; }

    if (avformat_open_input(&seg_fmt, "", NULL, NULL) != 0) {
        seg_fmt = NULL; /* freed by avformat_open_input on error */
        send_error(dc->out_fd, "segment open failed");
        return -1;
    }

    int nframes = 0;
    int seg_stream = -1;
    /* The stream index in the segment may differ; find video stream. */
    for (unsigned int i = 0; i < seg_fmt->nb_streams; ++i) {
        if (seg_fmt->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            seg_stream = (int)i;
            break;
        }
    }
    if (seg_stream < 0) {
        avformat_close_input(&seg_fmt);
        return 0; /* no video in this segment, not an error */
    }

    /* Use the existing codec context from the first segment (codec params
     * must match across segments in a single stream, which is true for HLS). */

    /* Send queued packets through the decoder. */
    while (av_read_frame(seg_fmt, dc->pkt) >= 0) {
        if (dc->pkt->stream_index != seg_stream) {
            av_packet_unref(dc->pkt);
            continue;
        }

        if (avcodec_send_packet(dc->codec_ctx, dc->pkt) < 0) {
            av_packet_unref(dc->pkt);
            continue;
        }
        av_packet_unref(dc->pkt);

        while (avcodec_receive_frame(dc->codec_ctx, dc->frame) >= 0) {
            int64_t pts_us = (dc->frame->pts != AV_NOPTS_VALUE)
                             ? (int64_t)((double)dc->frame->pts
                                  * av_q2d(dc->fmt_ctx->streams[dc->stream_idx]->time_base)
                                  * 1000000.0)
                             : dc->pts_offset_us;
            dc->pts_offset_us = pts_us + 40000; /* ~1 frame at 25fps */

            /* Convert YUV → ARGB. */
            sws_scale(dc->sws,
                      (const uint8_t *const *)dc->frame->data,
                      dc->frame->linesize, 0, dc->h,
                      dc->rgb->data, dc->rgb->linesize);

            /* Send MD_FRAME to parent. */
            uint8_t tag = MD_FRAME;
            int64_t pts_s = pts_us / 1000000;
            int32_t w32 = (int32_t)dc->w, h32 = (int32_t)dc->h;
            size_t dlen = (size_t)dc->w * (size_t)dc->h * 4u;
            write_full(dc->out_fd, &tag, 1);
            write_full(dc->out_fd, &pts_s, sizeof pts_s);
            write_full(dc->out_fd, &w32, sizeof w32);
            write_full(dc->out_fd, &h32, sizeof h32);
            write_full(dc->out_fd, &dlen, sizeof dlen);
            write_full(dc->out_fd, dc->rgb->data[0], dlen);

            ++nframes;
            av_frame_unref(dc->frame);
        }
    }

    /* Flush remaining frames from the decoder. */
    avcodec_send_packet(dc->codec_ctx, NULL);
    while (avcodec_receive_frame(dc->codec_ctx, dc->frame) >= 0) {
        sws_scale(dc->sws,
                  (const uint8_t *const *)dc->frame->data,
                  dc->frame->linesize, 0, dc->h,
                  dc->rgb->data, dc->rgb->linesize);

        uint8_t tag = MD_FRAME;
        int64_t pts_s = dc->pts_offset_us / 1000000;
        int32_t w32 = (int32_t)dc->w, h32 = (int32_t)dc->h;
        size_t dlen = (size_t)dc->w * (size_t)dc->h * 4u;
        write_full(dc->out_fd, &tag, 1);
        write_full(dc->out_fd, &pts_s, sizeof pts_s);
        write_full(dc->out_fd, &w32, sizeof w32);
        write_full(dc->out_fd, &h32, sizeof h32);
        write_full(dc->out_fd, &dlen, sizeof dlen);
        write_full(dc->out_fd, dc->rgb->data[0], dlen);
        ++nframes;
        av_frame_unref(dc->frame);
    }

    avformat_close_input(&seg_fmt);
    return nframes;
}

/* --- main decoder loop --- */

void media_decoder_run(int out_fd, int cmd_fd) {
    signal(SIGPIPE, SIG_IGN);

    decoder_ctx dc;
    memset(&dc, 0, sizeof dc);
    dc.out_fd = out_fd;
    dc.stream_idx = -1;

    /* Register all FFmpeg muxers/demuxers/codecs once at startup. */
    avformat_network_init(); /* safe: a no-op when built without network, but harmless */

    for (;;) {
        uint8_t cmd;
        if (read_full(cmd_fd, &cmd, 1) != 0) break;

        if (cmd == MD_QUIT) break;

        if (cmd == MD_DECODE) {
            size_t len = 0;
            if (read_full(cmd_fd, &len, sizeof len) != 0) break;
            if (len == 0 || len > MD_MAX_SEGMENT_BYTES) {
                send_error(out_fd, "segment too large");
                continue;
            }

            uint8_t *data = (uint8_t *)malloc(len);
            if (data == NULL) break;
            if (read_full(cmd_fd, data, len) != 0) { free(data); break; }

            int fr = decode_segment(&dc, data, len);
            free(data);
            if (fr < 0) {
                /* Fatal: reset the decoder for the next stream. */
                decoder_close(&dc);
                dc.out_fd = out_fd;
                dc.stream_idx = -1;
            }
            continue;
        }

        if (cmd == MD_FLUSH) {
            /* Flush the decoder (send NULL packet). */
            if (dc.codec_ctx != NULL) {
                avcodec_send_packet(dc.codec_ctx, NULL);
                while (avcodec_receive_frame(dc.codec_ctx, dc.frame) >= 0) {
                    sws_scale(dc.sws,
                              (const uint8_t *const *)dc.frame->data,
                              dc.frame->linesize, 0, dc.h,
                              dc.rgb->data, dc.rgb->linesize);

                    uint8_t tag = MD_FRAME;
                    int64_t pts_s = dc.pts_offset_us / 1000000;
                    int32_t w32 = (int32_t)dc.w, h32 = (int32_t)dc.h;
                    size_t dlen = (size_t)dc.w * (size_t)dc.h * 4u;
                    write_full(out_fd, &tag, 1);
                    write_full(out_fd, &pts_s, sizeof pts_s);
                    write_full(out_fd, &w32, sizeof w32);
                    write_full(out_fd, &h32, sizeof h32);
                    write_full(out_fd, &dlen, sizeof dlen);
                    write_full(out_fd, dc.rgb->data[0], dlen);
                    av_frame_unref(dc.frame);
                }
            }

            uint8_t tag = MD_EOS;
            write_full(out_fd, &tag, 1);
            dc.eos_sent = 1;
            continue;
        }
    }

    decoder_close(&dc);
    _exit(0);
}

int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd) {
    if (pid == NULL || out_fd == NULL || cmd_fd == NULL) return -1;

    int out_pipe[2], cmd_pipe[2];
    if (pipe(out_pipe) != 0 || pipe(cmd_pipe) != 0) return -1;

    pid_t p = fork();
    if (p < 0) {
        close(out_pipe[0]); close(out_pipe[1]);
        close(cmd_pipe[0]); close(cmd_pipe[1]);
        return -1;
    }

    if (p == 0) {
        /* Child: decoder process. */
        close(out_pipe[0]); /* child writes to out_pipe[1] */
        close(cmd_pipe[1]); /* child reads from cmd_pipe[0] */

        /* Build --media-decoder <out_fd> <cmd_fd> argv for re-exec. */
        char out_str[16], cmd_str[16];
        snprintf(out_str, sizeof out_str, "%d", out_pipe[1]);
        snprintf(cmd_str, sizeof cmd_str, "%d", cmd_pipe[0]);

        /* Re-exec ourselves as the decoder. */
        execl("/proc/self/exe", "freedom", "--media-decoder",
              out_str, cmd_str, (char *)NULL);

        /* If exec fails, fall through to run in-process. */
        media_decoder_run(out_pipe[1], cmd_pipe[0]);
        close(out_pipe[1]); close(cmd_pipe[0]);
        _exit(1);
    }

    /* Parent. */
    close(out_pipe[1]);
    close(cmd_pipe[0]);
    *pid = p;
    *out_fd = out_pipe[0];  /* read decoded frames from child */
    *cmd_fd = cmd_pipe[1];  /* write commands to child */
    return 0;
}
