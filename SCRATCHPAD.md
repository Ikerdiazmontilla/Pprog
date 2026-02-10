# SCRATCHPAD

## 2026-02-10T10:35:16+01:00
- What failed: No existia `SCRATCHPAD.md` y al inicio lo omiti por la instruccion previa de "no modifiques nada".
- Why: Asumi que crear un fichero nuevo contaba como modificacion del proyecto.
- Fix applied: Se crea `SCRATCHPAD.md` y a partir de ahora se crea/lee siempre al empezar, aunque el resto del trabajo sea solo revision.
- Prevention: Si el usuario pide "no tocar nada", aclarar que `SCRATCHPAD.md` es parte del proceso y crear solo eso como excepcion acordada.

## 2026-02-10T10:45:48+01:00
- Lesson: Acordar y centralizar el estilo (D1/D2) en un unico fichero para no mezclar formatos entre codigo semilla y codigo nuevo.
- Fix applied: Se crea `style.md` en la raiz como fuente de verdad de estilo y documentacion, tomando `space.c/.h` como referencia.

## 2026-02-10T11:01:31+01:00
- What failed: `make` fallo en `game_actions.c` por uso de `NULL` sin incluir cabeceras.
- Why: Se eliminaron `#include` no usados y se olvido que `NULL` requiere `stddef.h` (o `stdlib.h`).
- Fix applied: Anadir `#include <stddef.h>` en `game_actions.c`.
- Prevention: Tras tocar includes, compilar siempre con `-Wall` inmediatamente para detectar errores de cabeceras/defines.
