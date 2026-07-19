#ifndef FREEDOM_MEDIA_DECODER_H
#define FREEDOM_MEDIA_DECODER_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * media_decoder — helper process that decodes H.264/H.265 video segments
 * (MPEG-TS) into raw ARGB frames using FFmpeg's safe C API.
 *
 * Communicates with the parent over two pipes:
 *   out_fd: decoder → parent (frames, stream info, errors)
 *   cmd_fd: parent → decoder (commands + segment data)
 *
 * The decoder runs as a separate process (fork+exec, see media_decoder_spawn)
 * and is the ONLY component in Freedom that touches untrusted video content.
 * It keeps a minimal sandbox: no network, no new processes, reads its own
 * shared libraries, writes nothing to the filesystem.
 *
 * See spec/media_decoder.md for the full contract.
 */

/* Remote command tags (parent → decoder). */
enum md_cmd {
    MD_DECODE = 1,    /* payload: [len:size_t][ts_bytes] — decode one TS segment */
    MD_FLUSH  = 2,    /* no payload — flush pending frames, send MD_EOS when done */
    MD_QUIT   = 3     /* no payload — terminate */
};

/* Response tags (decoder → parent). Protocol v2: all PTS travel in
 * MICROSECONDS (int64), computed with the time base of the segment being
 * decoded. v1 sent whole seconds, useless for pacing. */
enum md_resp {
    MD_STREAM_INFO = 1, /* payload: [codec:int32][w:int32][h:int32][has_audio:int32] */
    MD_FRAME       = 2, /* payload: [pts_us:int64][w:int32][h:int32][dlen:size_t][ARGB data] */
    MD_EOS         = 3, /* no payload — end of stream */
    MD_ERROR       = 4, /* payload: [elen:size_t][msg] — non-fatal error, stream continues */
    MD_AUDIO_FRAME = 5  /* payload: [pts_us:int64][rate:int32][ch:int32][dlen:size_t][PCM_S16LE data] */
};

#define MD_MAX_SEGMENT_BYTES ((size_t)(32u << 20)) /* 32 MiB per segment */

/*
 * md_pacer — pure pacing brain (no I/O, no clock reads: the caller passes
 * wall time in). The consumer regulates the whole pipeline: the GUI only
 * reads the next frame from the decoder pipe once wall clock reaches the
 * due instant of the frame already read; pipe backpressure then throttles
 * the decoder and the segment feeder in turn. See spec/media_decoder.md.
 */

/* Consumer more than this far behind schedule re-anchors to "now" instead of
 * replaying the backlog at fast-forward speed. */
#define MD_PACE_MAX_LAG_MS 500u

/* A forward PTS jump larger than this is treated as a discontinuity and
 * re-anchors (a hostile PTS must never schedule a year-long sleep). */
#define MD_PACE_MAX_STEP_MS 5000u

/* Frames drained per event-loop iteration when running behind. */
#define MD_MAX_CATCHUP_READS 4

typedef struct md_pacer {
    uint64_t epoch_ms; /* wall time the anchor frame was displayed */
    int64_t  pts0_us;  /* PTS of the anchor frame */
    int      primed;   /* nonzero once anchored */
} md_pacer;

/* Returns the wall-clock instant (ms) at which the frame carrying pts_us is
 * due for display. First frame (or any discontinuity: backwards PTS, absurd
 * forward jump, or the consumer lagging past MD_PACE_MAX_LAG_MS) re-anchors
 * the epoch to now_ms and is due immediately. NULL pacer fails open to "now".
 * Hostile PTS values never cause UB: the delta is computed in unsigned
 * arithmetic after the backwards-PTS branch has excluded wraparound. */
static inline uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms,
                                      int64_t pts_us) {
    if (p == NULL) return now_ms;
    if (p->primed && pts_us >= p->pts0_us) {
        uint64_t delta_ms = ((uint64_t)pts_us - (uint64_t)p->pts0_us) / 1000u;
        uint64_t due = p->epoch_ms + delta_ms;
        if (due >= p->epoch_ms                                /* no wraparound */
            && due <= now_ms + (uint64_t)MD_PACE_MAX_STEP_MS  /* sane jump */
            && now_ms <= due + (uint64_t)MD_PACE_MAX_LAG_MS)  /* not lagging */
            return due;
    }
    p->epoch_ms = now_ms;
    p->pts0_us = pts_us;
    p->primed = 1;
    return now_ms;
}

/* Entry point for the decoder child process. Called from main() when argv
 * matches "--media-decoder <out_fd> <cmd_fd>". Reads commands from cmd_fd,
 * writes responses to out_fd, never returns (_exit). */
void media_decoder_run(int out_fd, int cmd_fd);

/* Spawns a media decoder child via fork+exec. On success stores child pid in
 * *pid, the read-end of the child's output pipe in *out_fd, and the write-end
 * of the command pipe in *cmd_fd; returns 0. On failure returns -1. */
int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd);

#endif /* FREEDOM_MEDIA_DECODER_H */
