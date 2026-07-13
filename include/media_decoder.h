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

/* Response tags (decoder → parent). */
enum md_resp {
    MD_STREAM_INFO = 1, /* payload: [codec:int32][w:int32][h:int32][has_audio:int32] */
    MD_FRAME       = 2, /* payload: [pts_s:int64][w:int32][h:int32][dlen:size_t][ARGB data] */
    MD_EOS         = 3, /* no payload — end of stream */
    MD_ERROR       = 4  /* payload: [elen:size_t][msg] — non-fatal error, stream continues */
};

#define MD_MAX_SEGMENT_BYTES ((size_t)(32u << 20)) /* 32 MiB per segment */

/* Entry point for the decoder child process. Called from main() when argv
 * matches "--media-decoder <out_fd> <cmd_fd>". Reads commands from cmd_fd,
 * writes responses to out_fd, never returns (_exit). */
void media_decoder_run(int out_fd, int cmd_fd);

/* Spawns a media decoder child via fork+exec. On success stores child pid in
 * *pid, the read-end of the child's output pipe in *out_fd, and the write-end
 * of the command pipe in *cmd_fd; returns 0. On failure returns -1. */
int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd);

#endif /* FREEDOM_MEDIA_DECODER_H */
