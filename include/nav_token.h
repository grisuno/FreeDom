#ifndef FREEDOM_NAV_TOKEN_H
#define FREEDOM_NAV_TOKEN_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * nav_token (nt_) -- identity of ONE network navigation of ONE tab, shared by reference
 * between the GUI thread and the fetch thread, so a tab keeps loading while parked and a
 * result is routed to the tab that asked for it. Contract: spec/nav_token.md.
 */

#include <stdint.h>

typedef struct nt_token nt_token;

typedef enum nt_route_kind { NT_DROP = 0, NT_DELIVER, NT_PARK } nt_route_kind;

nt_token *nt_new(void);
nt_token *nt_ref(nt_token *t);
void      nt_unref(nt_token **t);
void      nt_cancel(nt_token *t);
int       nt_cancelled(const nt_token *t);
void      nt_set_foreground(nt_token *t, int on);
int       nt_foreground(const nt_token *t);
uint64_t  nt_id(const nt_token *t);

/* Where a result tagged with `job` goes; *slot gets the parked index for NT_PARK, else -1.
 * parked may hold NULL entries; slot may be NULL. */
nt_route_kind nt_route(const nt_token *job, const nt_token *active, nt_token *const *parked,
                       int n, int *slot);

#endif /* FREEDOM_NAV_TOKEN_H */
