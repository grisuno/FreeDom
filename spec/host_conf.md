# host_conf (`hcf_`) — la UNICA fuente de las listas de hosts del usuario

> Doctrina (dueño, 2026-10-20): una cosa, una fuente de verdad. La GUI y el modo headless
> cargaban `block.conf`/`allow.conf`/`js.conf` cada uno con su propia función y orden de
> búsqueda; el headless leía solo `allow.conf`. El benchmark medía entonces un perfil que el
> navegador real no tiene.

## Contrato

- `hcf_search_dirs(env, home, out)` — pura. Orden: `$FREEDOM_HOSTS_DIR` (si no vacío),
  `$HOME/.config/freedom` (si `home` no vacío), `./config`. Acumulativa; un directorio repetido
  se cuenta una vez. Nunca desborda `HCF_MAX_DIRS`.
- `hcf_search_dirs_from_env(out)` — el mismo cálculo leyendo el entorno real.
- `hcf_load_filter(dirs)` — `hb_set` con `block.conf` (lista BLOCK) y `allow.conf` (lista ALLOW)
  de cada directorio; la blanca gana (`hostblock`).
- `hcf_load_allowlist(dirs, fname)` — `hb_set` con un solo archivo (`js.conf`, `allow.conf`) como
  lista ALLOW.
- Un archivo ausente o ilegible NO es error: falla ABIERTO (nunca bloquea de más). Un archivo
  mayor que `HCF_MAX_FILE_BYTES` se ignora entero (anti-DoS), no se trunca a media línea.
- Devuelven `NULL` solo ante OOM o argumento nulo.

## Dado-Cuando-Entonces

- Dado `block.conf` con `ads.example` en el directorio del entorno y `allow.conf` con
  `ok.ads.example` en `~/.config/freedom`, cuando se carga el filtro, entonces `ads.example` se
  bloquea y `ok.ads.example` se permite (la blanca gana, aunque venga de otro directorio).
- Dado `js.conf` solo en `./config`, cuando se carga la lista, entonces su host figura en
  `hb_is_allowlisted`.
- Dado ningún archivo, cuando se carga, entonces el conjunto está vacío y todo host se permite.
- Dado `env` vacío y `home` nulo, entonces solo `./config` se busca.

## Fuera de alcance

Escritura de las listas (`hostedit`), y la decisión de qué capacidades recibe cada página
(`webcaps`).
