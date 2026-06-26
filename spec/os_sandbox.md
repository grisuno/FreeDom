# Especificación: `os_sandbox`

> Hito 4 — Endurecimiento del SO (confinamiento de syscalls). Estado: **SPEC + TEST (rojo)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_os_sandbox.c` debe fallar hasta
> que exista `src/os_sandbox.c` (estado rojo).

## 1. Propósito

`os_sandbox` confina el proceso a nivel del **kernel** con **seccomp-bpf**: instala una lista
blanca de syscalls que **falla cerrado** (todo lo no permitido se deniega). Es la última frontera
Zero Trust: aunque el parser, el motor JS o el bridge fueran comprometidos, el proceso no puede
abrir archivos, abrir sockets, ejecutar binarios, hacer `ptrace`, etc. Convierte una ejecución
arbitraria de código en, a lo sumo, cómputo inerte.

Cubre la parte de endurecimiento del SO del Hito 4 (la UI Cairo+Wayland se especifica aparte: no
es testeable sin display). En BSD el equivalente será `pledge`/`unveil` (fuera de alcance aquí).

## 2. Decisión de stack (sin dependencia nueva)

seccomp-bpf **crudo** vía `prctl(PR_SET_NO_NEW_PRIVS)` + `prctl(PR_SET_SECCOMP,
SECCOMP_MODE_FILTER, ...)` con un programa BPF clásico construido a mano. **No** se usa
`libseccomp` (aunque esté disponible): el filtro es pequeño, auditable y elimina una dependencia.
Verificado en este host: modo KILL ⇒ `SIGSYS` en una syscall denegada; modo ERRNO ⇒ `EPERM`.

## 3. Modelo de la política

- **Única fuente de verdad:** un array de números de syscall permitidos. La función pura
  `os_policy_allows` y el constructor del BPF lo recorren ambos, así la política es
  **directamente testeable** sin instalar nada (doctrina: la lógica de seguridad en funciones
  puras).
- **Comprobación de arquitectura:** el BPF rechaza cualquier `arch` distinto de `AUDIT_ARCH_X86_64`
  (defensa frente a confusión de ABI x32/i386). En arquitecturas no soportadas `os_harden`
  devuelve `OS_ERR_UNSUPPORTED` (no instala una política incompleta — falla cerrado).
- **Acción ante violación:** `OS_VIOLATION_KILL` (por defecto) mata el proceso con `SIGSYS`
  (fail-closed duro). `OS_VIOLATION_ERRNO` deniega con `EPERM` (diagnóstico / compatibilidad con
  librerías que sondean syscalls). El camino por defecto es el seguro.
- **Irreversible:** una vez instalado el filtro, no se puede quitar ni relajar (`NO_NEW_PRIVS`
  impide recuperar privilegios). Se instala tras la inicialización, antes de tocar contenido no
  confiable.

La lista blanca es la de un trabajador ya inicializado (renderer / worker JS): I/O sobre
descriptores ya abiertos y cómputo, **no** apertura de recursos nuevos. Excluye explícitamente
`open`/`openat`, `socket`/`connect`, `execve`, `ptrace`, `clone`/`fork`, etc.

## 4. Contrato de la API

Definida en `include/os_sandbox.h`.

```c
typedef enum os_status {
    OS_OK = 0,
    OS_ERR_UNSUPPORTED, /* no Linux/x86_64, o seccomp no disponible */
    OS_ERR_PRCTL        /* fallo de prctl(NO_NEW_PRIVS) o de la instalacion */
} os_status;

typedef enum os_violation {
    OS_VIOLATION_KILL = 0, /* por defecto: SIGSYS-mata el proceso */
    OS_VIOLATION_ERRNO     /* deniega con EPERM (diagnostico) */
} os_violation;

/* Funciones puras (sin efectos): la superficie de prueba de la politica. */
int    os_policy_allows(long syscall_nr);
size_t os_policy_size(void);

/* Espejo puro de la decision REAL del BPF para los syscalls de memoria: 1 si una
 * llamada a syscall_nr con esos flags de proteccion se permitiria. Para syscalls
 * que no son de memoria equivale a os_policy_allows; para mmap/mprotect es ademas
 * falso cuando prot pide PROT_EXEC (W^X, ver seccion 11). */
int os_prot_allowed(long syscall_nr, unsigned long prot);

/* Anti-volcado (defensa en profundidad): prctl(PR_SET_DUMPABLE,0) + RLIMIT_CORE=0
 * para que ni un core dump ni un ptrace de un proceso ajeno puedan exfiltrar los
 * secretos del worker. Mejor-esfuerzo; se llama antes de os_harden (seccion 12). */
os_status os_no_dump(void);

/* Instala el filtro fail-closed en el proceso llamante. Irreversible. */
os_status os_harden(os_violation action);
```

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `OS_OK` | Filtro instalado (o consulta pura correcta). |
| `OS_ERR_UNSUPPORTED` | Plataforma sin seccomp-bpf x86_64. |
| `OS_ERR_PRCTL` | `prctl(PR_SET_NO_NEW_PRIVS)` o `PR_SET_SECCOMP` falló. |

## 6. Semántica

- `os_policy_allows(nr)`: `1` si `nr` está en la lista blanca, `0` si no. Sin efectos.
- `os_policy_size()`: número de syscalls permitidas (introspección/pruebas).
- `os_harden(action)`: `PR_SET_NO_NEW_PRIVS=1`, luego instala el BPF (guard de arch + lista
  blanca + acción por defecto). Devuelve `OS_OK` o un error; en error **no** deja una política
  parcial peligrosa (si `NO_NEW_PRIVS` o el filtro fallan, no se instala nada utilizable).

## 7. Matriz de pruebas

`tests/test_os_sandbox.c` (cmocka):
- **Puras:** `os_policy_allows` acepta `read`/`write`/`exit_group`/`getpid`; rechaza
  `socket`/`openat`/`execve`/`ptrace`. `os_policy_size() > 0`.
- **Integración (fork):** el padre bifurca; el hijo llama a `os_harden` y sondea, comunicando por
  código de salida (no usa cmocka tras endurecerse):
  - KILL: una syscall permitida (`getpid`) sobrevive; `socket` ⇒ el hijo muere por `SIGSYS`.
  - ERRNO: `socket` ⇒ `EPERM` (el hijo sale con un código marcador).

> Las pruebas de integración bifurcan porque `os_harden` es irreversible y afecta a todo el
> proceso; el hijo usa `syscall(2)` directo y `_exit` para no disparar syscalls del runtime.

## 8. Confinamiento del sistema de ficheros (Landlock) — Hito 5

Complemento a seccomp: **Landlock** (LSM del kernel Linux ≥ 5.13) confina el acceso al sistema de
ficheros por **rutas**, no por syscall. seccomp ya deniega `open`/`openat`, pero Landlock añade
defensa en profundidad y, sobre todo, un modelo más rico: una pestaña puede tener permitido leer
**solo** un directorio (p.ej. una caché) y nada más; todo lo demás se deniega. **Fail-closed**: lo
no cubierto por una regla se deniega; sin reglas se deniega **todo** el FS.

Verificado en este host: kernel 6.19, LSM `landlock` activo, ABI disponible vía
`landlock_create_ruleset(NULL, 0, LANDLOCK_CREATE_RULESET_VERSION)`.

```c
typedef enum os_fs_access {
    OS_FS_NONE = 0,        /* sin acceso (no se usa en reglas; documenta intención) */
    OS_FS_READ = 1,        /* leer ficheros, listar directorios, ejecutar */
    OS_FS_READ_WRITE = 2   /* lo anterior + crear/escribir/borrar/truncar */
} os_fs_access;

typedef struct os_fs_rule {
    const char  *path;     /* fichero o directorio (jerarquía "beneath") */
    os_fs_access access;    /* qué se permite en/bajo esa ruta */
} os_fs_rule;

/* Versión de ABI de Landlock del kernel (>=1), 0 si no hay soporte, <0 error. */
int os_landlock_abi(void);

/* Confina el proceso llamante a las reglas dadas: todo acceso al FS no cubierto
 * por una regla se deniega. rules==NULL o n==0 ⇒ se deniega TODO el FS.
 * Irreversible. Debe llamarse ANTES de seccomp (usa syscalls de Landlock y, con
 * reglas, open(O_PATH), que seccomp bloquea). Fail-closed. */
os_status os_landlock_restrict(const os_fs_rule *rules, size_t n);
```

- **Selección de derechos por ABI:** `os_landlock_restrict` consulta la ABI y enmascara los
  derechos `handled_access_fs` a los que el kernel soporta (REFER en ABI≥2, TRUNCATE en ABI≥3,
  IOCTL_DEV en ABI≥5), de modo que `landlock_create_ruleset` no falle con `EINVAL` en kernels más
  antiguos. Se manejan **todos** los derechos de FS soportados (denegación total por defecto) y
  cada regla concede su subconjunto (`OS_FS_READ` = EXECUTE|READ_FILE|READ_DIR;
  `OS_FS_READ_WRITE` = además WRITE_FILE|REMOVE_*|MAKE_*|REFER|TRUNCATE).
- **Errores:** `OS_ERR_UNSUPPORTED` si el kernel no tiene Landlock; `OS_ERR_LANDLOCK` ante
  cualquier fallo de creación/regla/`restrict_self`; nunca se deja un confinamiento parcial.
- **Orden en el hijo del renderer:** primero `os_landlock_restrict(...)`, luego `os_harden(KILL)`.

### Matriz de pruebas (Landlock, fork-based)
- **Pura:** `os_landlock_abi() > 0` en este host.
- **Deny-all:** hijo llama `os_landlock_restrict(NULL,0)`; `open("/etc/hostname",O_RDONLY)` ⇒
  falla con `EACCES`; sale con código marcador. El padre lo verifica.
- **Allow-read:** hijo confina con una regla `OS_FS_READ` sobre un directorio temporal; leer un
  fichero dentro **funciona**, leer fuera (`/etc/hostname`) **falla**.
- **Args NULL / n>0 con rules NULL** ⇒ `OS_ERR_*` apropiado sin confinar a medias.

## 9. Aislamiento por namespaces (Linux) — defensa en profundidad por pestaña

Tercera capa bajo seccomp y Landlock: el worker de cada pestaña se **desacopla** en namespaces
propios con `unshare(2)` antes de tocar contenido. seccomp ya prohíbe `socket`/`connect`, pero un
bypass por bug del kernel del filtro no encontraría **red** que alcanzar, ni IPC compartida, ni la
identidad del host.

```c
/* Conjunto puro de flags CLONE_* que el worker aísla (espejo testeable de lo aplicado). */
int       os_namespace_flags(void);
/* Aplica unshare(os_namespace_flags()) sobre el proceso llamante. */
os_status os_isolate_namespaces(void);
```

- **Flags:** `CLONE_NEWUSER` (habilitador no privilegiado del resto) `| CLONE_NEWNET` (el worker
  **nunca** usa la red —el padre hace el fetch y pasa los bytes—, así que recibe una pila vacía) `|
  CLONE_NEWIPC | CLONE_NEWUTS`. **Fuera de alcance:** mount y PID namespaces (exigen remontar
  `/proc` y un `fork` posterior al `unshare`).
- **Best-effort (como Landlock), no fatal:** seccomp sigue siendo la frontera **obligatoria**; si
  `unshare` falla (userns no privilegiado deshabilitado), el worker continúa igual de protegido por
  seccomp. `OS_ERR_UNSUPPORTED` (EPERM/EINVAL/ENOSYS) vs `OS_ERR_NAMESPACE` (otro fallo).
- **Contexto monohilo:** debe llamarse recién forkeado, antes de cualquier hilo o contenido
  (`unshare(CLONE_NEWUSER)` lo exige). **No** escribe mapas uid/gid (al worker no le importa su uid
  dentro del namespace) ⇒ cero escrituras a `/proc`. Los fds de pipe heredados siguen funcionando.
- **Orden en el hijo del worker:** `os_isolate_namespaces()` → `os_landlock_restrict(NULL,0)` →
  `os_harden(KILL)`.

### Matriz de pruebas (namespaces)
- **Pura:** `os_namespace_flags()` incluye `CLONE_NEWNET`/`NEWUSER`/`NEWIPC`/`NEWUTS`.
- **Enforcement (fork-based):** el hijo aísla y debe quedar en un **net namespace distinto** que el
  padre (inode de `/proc/self/ns/net` cambia); en hosts con userns deshabilitado reporta *skip*
  (ambos resultados aceptables: es defensa en profundidad).

## 10. Fuera de alcance

- UI Cairo + Wayland (spec aparte; requiere display).
- `pledge`/`unveil` (OpenBSD) y equivalentes no-Linux.
- Mount/PID namespaces; reglas Landlock de red/IPC (ABI≥4/≥6; aquí FS + namespaces).
- **`RLIMIT_AS`** (tope de memoria virtual): **diferido**. Choca con la enorme reserva de
  espacio virtual del *shadow memory* de AddressSanitizer (rompería `make asan`), y el heap del
  motor JS ya está acotado por su asignador propio (`js_sandbox`) y las imágenes por el tope de
  dimensiones **antes** de decodificar. Reintroducir con `#if !defined(__SANITIZE_ADDRESS__)` y un
  valor justificado cuando haya un caso de uso medido.
- **`RLIMIT_CPU`** (tope de segundos de CPU): **diferido**. Mata todo el worker (no solo el script)
  y el valor es una política de tiempo de render / presupuesto de interrupción del intérprete JS;
  va atado a un mecanismo de *interrupt handler* de QuickJS, no a un número mágico aquí.
- `ppoll`/`epoll`/`pselect6`: **deliberadamente NO** se agregan al allowlist. El worker hace I/O
  **bloqueante** sobre fds de pipe ya abiertos (`read`/`write`); añadirlos violaría el privilegio
  mínimo (ensanchar la superficie sin necesidad es lo contrario de endurecer).
- ARM64 (`AUDIT_ARCH_AARCH64`): el guard de arquitectura sigue siendo x86_64 (este host); en otra
  arquitectura `os_harden` falla cerrado con `OS_ERR_UNSUPPORTED`.

## 11. W^X — sin memoria ejecutable (filtrado por argumento de syscall)

seccomp v1 filtra por número de syscall, pero el programa BPF clásico **también puede inspeccionar
los argumentos** (`seccomp_data.args[]`). El worker es un **intérprete** (QuickJS interpreta
bytecode, **sin JIT**) sobre código ya mapeado, más parser (`lexbor`) y decoders (`libpng`/
`libjpeg`); con `-z relro -z now` hasta el PLT/GOT se resuelve y queda de solo-lectura al arrancar,
**antes** del `fork`. Por lo tanto, tras confinarse, **ninguna** operación legítima necesita crear
ni convertir una página a ejecutable.

Por eso `os_harden` saca `mmap` y `mprotect` del allowlist genérico y los maneja con un bloque que
inspecciona su argumento de protección (`args[2]`, índice 2 en ambas): si pide `PROT_EXEC`, **se
deniega** (KILL/ERRNO según la acción); si no, se permite. Así, aunque una corrupción de memoria
secuestre el control del worker, **no puede montar shellcode nativo** (W^X / no-dyncode): se cierra
el último paso de la inyección de código.

- `mremap` se mantiene permitido sin filtrar: **no** toma argumento de protección (preserva la del
  área), así que no puede elevar a ejecutable.
- `pkey_mprotect` sigue **denegado por completo** (el worker no lo usa; privilegio mínimo).
- **Espejo puro:** `os_prot_allowed(nr, prot)` replica la decisión del BPF y es la superficie de
  prueba directa. `os_policy_allows` sigue siendo la **pertenencia** (mmap/mprotect siguen en la
  lista); `os_prot_allowed` es la **decisión efectiva** (pertenencia ∧ ¬PROT_EXEC para mmap/mprotect).

### Matriz de pruebas (W^X)
- **Pura:** `os_prot_allowed(mmap, READ|WRITE)`=1; `os_prot_allowed(mmap, READ|EXEC)`=0;
  `os_prot_allowed(mprotect, EXEC)`=0; `os_prot_allowed(read, *)`=1; `os_prot_allowed(socket, *)`=0.
- **Enforcement (fork, KILL):** el hijo se endurece; `mmap(...,PROT_READ|PROT_WRITE,...)` sobrevive;
  `mmap(...,PROT_READ|PROT_EXEC,...)` ⇒ `SIGSYS`; `mprotect(pagina, len, PROT_READ|PROT_EXEC)` ⇒
  `SIGSYS`.

## 12. Anti-volcado — no exfiltrar secretos del worker

`os_no_dump()` aplica `prctl(PR_SET_DUMPABLE, 0)` y `setrlimit(RLIMIT_CORE, {0,0})`: un crash del
worker **no** deja un core file y un proceso ajeno (no el padre) **no** puede `ptrace`-adjuntarse ni
leer `/proc/<pid>/mem`. Así, tras un compromiso o un fallo, no se filtran los secretos del worker
(la clave de sesión que envenena el readback de canvas/audio, los bytes de la página descifrada).
Mejor-esfuerzo (defensa en profundidad, como Landlock/namespaces); el orden en el hijo del worker es
`os_isolate_namespaces()` → `os_no_dump()` → `os_landlock_restrict(NULL,0)` → `os_harden(KILL)`.

### Matriz de pruebas (anti-volcado, fork-based)
- El hijo llama `os_no_dump()` (antes de seccomp, así `prctl`/`getrlimit` siguen disponibles):
  `prctl(PR_GET_DUMPABLE)` ⇒ 0 y `getrlimit(RLIMIT_CORE).rlim_cur` ⇒ 0; sale con código marcador.
