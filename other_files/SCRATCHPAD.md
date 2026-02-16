# SCRATCHPAD

## 2026-02-10T10:35:16+01:00
- What failed: `SCRATCHPAD.md` did not exist and I initially skipped creating it due to an earlier "do not modify anything" request.
- Why: I assumed creating a new file counted as a project modification.
- Fix applied: Created `SCRATCHPAD.md` and from now on it is always created/read at the start, even when the task is only a review.
- Prevention: If the user requests "do not touch anything", clarify that `SCRATCHPAD.md` is part of the workflow and create only that file as an agreed exception.

## 2026-02-10T10:45:48+01:00
- Lesson: Agree on and centralize the style (D1/D2) in a single file to avoid mixing formats between seed code and new code.
- Fix applied: Created `style.md` at the repository root as the single source of truth for style and documentation, using `space.c/.h` as reference.

## 2026-02-10T11:01:31+01:00
- What failed: `make` failed in `game_actions.c` because `NULL` was used without the required header.
- Why: Some `#include`s were removed and we forgot `NULL` needs `stddef.h` (or `stdlib.h`).
- Fix applied: Added `#include <stddef.h>` in `game_actions.c`.
- Prevention: After touching includes, always compile immediately with `-Wall` to catch missing headers/defines early.

## 2026-02-16T10:55:55+01:00
- Lesson: Keep author tags consistent with the project convention requested by the team.
- Fix applied: Updated modified function/module documentation to use `@author Iker Díaz`, changed previous `Equipo PPROG` tags, and kept `Fernando Pina` in `player.*` and `object.*`.
- Prevention: Before finishing any change, run a quick `@author` review to ensure new/edited docs follow the current author policy.

## 2026-02-16T11:00:31+01:00
- What failed: Author replacement was too broad and changed some seed authors that should have stayed as `Profesores PPROG`.
- Why: Replacement was done at file level instead of only on modified functions.
- Fix applied: Restored `Profesores PPROG` in untouched seed sections and kept `Iker Díaz` only on modified parts; kept `Fernando Pina` in `player.*` and `object.*`.
- Prevention: Apply author changes per-function, not with blanket replacements across entire files.
