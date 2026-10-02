# Recipe: Fix a Dependency Cycle

Target cycle: `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`

1. Read the imports between these files: `grep -n '^import\|^from\|#include' include/js_dom.h`, `grep -n '^import\|^from\|#include' include/js_location.h`
2. Move the shared symbols into a new leaf module both sides import
3. Verify: `readmenator . && grep -c 'Dependency Cycles' readmenator-agent/GOTCHAS.md`
