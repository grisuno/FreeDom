#ifndef FREEDOM_DATA_URL_H
#define FREEDOM_DATA_URL_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * data_url — pure RFC 2397 "data:" URL parsing + RFC 4648 base64 decoding.
 *
 * No I/O, no global state. A data: URI embeds bytes directly in the document that
 * already reached the reader, so decoding it never opens a network socket: it
 * cannot leak the reader's IP or serve as a tracking pixel, unlike a remote image.
 * render_policy uses du_is_data_url/du_base64_payload to skip the https/host/
 * tracker checks that exist only to gate a NETWORK fetch, while still requiring
 * caps.images (the one on/off switch for all raster content). See spec/data_url.md.
 *
 * du_base64_payload does no allocation (it only slices the caller's url string);
 * the one real allocation, du_base64_decode, is meant to run inside the confined
 * tab worker (OP_DECODE_IMAGE_B64, spec/tab.md), never the trusted parent -- the
 * bytes it produces are hostile until image_decode's format sniff proves otherwise.
 */

typedef enum du_status {
    DU_OK = 0,
    DU_ERR_NULL_ARG,      /* a required pointer was NULL */
    DU_ERR_NOT_DATA_URL,  /* does not start with "data:" (case-insensitive) */
    DU_ERR_NOT_BASE64,    /* "data:" but no ";base64" flag before the comma, or no
                           * comma at all -- the percent-encoded variant is out of
                           * scope (see spec/data_url.md 5) */
    DU_ERR_BAD_BASE64,    /* length not a multiple of 4, a character outside the
                           * base64 alphabet, or '=' padding in a non-final position */
    DU_ERR_TOO_LARGE,     /* encoded payload exceeds DU_MAX_ENCODED_LEN (anti-DoS) */
    DU_ERR_OOM
} du_status;

/* 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/
 * logo/image, bounding the allocation before decoding a payload whose size a
 * remote, hostile document controls. */
#define DU_MAX_ENCODED_LEN ((size_t)(16u * 1024u * 1024u))

/* Nonzero iff url begins (case-insensitively) with "data:". NULL => 0. */
int du_is_data_url(const char *url);

/* Locates the base64 payload inside a data: URL: validates the "data:" prefix,
 * finds the separating comma and the ";base64" flag immediately before it. Does
 * NOT decode or allocate -- *payload points INTO `url` (same lifetime). Fails
 * closed on any unsupported variant (missing comma, missing ";base64" flag,
 * payload beyond DU_MAX_ENCODED_LEN). url/payload/payload_len == NULL =>
 * DU_ERR_NULL_ARG. */
du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len);

/* Decodes base64 text (RFC 4648 standard alphabet, mandatory '=' padding, length a
 * multiple of 4) into freshly malloc'd bytes; *out is the caller's to free(). Any
 * character outside the alphabet, misplaced padding, or a length not a multiple of
 * 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix.
 * b64/out/out_len == NULL (with b64_len != 0) => DU_ERR_NULL_ARG. */
du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len);

#endif /* FREEDOM_DATA_URL_H */
