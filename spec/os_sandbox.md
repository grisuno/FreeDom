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

## 9. Fuera de alcance

- UI Cairo + Wayland (spec aparte; requiere display).
- `pledge`/`unveil` (OpenBSD) y equivalentes no-Linux.
- Aislamiento por `namespaces`; reglas Landlock de red/IPC (ABI≥4/≥6; aquí solo FS).
- Argumentos de syscall (la v1 de seccomp filtra por número de syscall, no por argumentos).
