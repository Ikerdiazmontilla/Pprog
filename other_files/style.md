# Code And Documentation Style (I1 - PPROG)

This repository must comply, above all, with **D1** and **D2** from `RequisitosI1.pdf`:

- All code (seed code and new code) must be documented.
- The style must be **consistent**, **simple**, and **easy to read**.
- The code must compile with `-Wall` with **no warnings** (**C1**).

`space.c` and `space.h` are the **canonical reference** for header layout, Doxygen blocks, and naming.

## Language (mandatory)

- **All documentation and code comments must be written in English.**
  - File headers, function docs, struct/field docs, inline comments, and user-facing debug strings (when reasonable).

## C (formatting)

- Indentation: **2 spaces**, never tabs. Do not mix.
- Braces: **K&R**.
  - `if (cond) { ... }`
  - `switch (x) { case ...: ...; break; }`
- Line length: target **100** columns (wrap long lines intentionally).
- Spacing:
  - `if (x)`, `for (...)`, `while (...)`
  - Binary operators with spaces: `a + b`, `x == y`
  - Pointers like the seed code: `Type* ptr` (do not mix styles inside the same file).
- `#include` order in `.c`:
  1. Module header (`#include "module.h"`)
  2. System headers (`<stdio.h>`, `<stdlib.h>`, ...)
  3. Project headers
- Public vs private:
  - Private functions: `static` in the `.c` and documented (D1).
  - Do not expose `struct _X` in `.h` (use `typedef struct _X X;`).
- Error handling:
  - Prefer simple checks and early returns:
    - `if (!ptr) return ERROR;`
  - `create` returns pointer or `NULL`.
  - `destroy` returns `OK/ERROR`.
  - Getters return `NO_ID`/`NULL` on error.
- Names:
  - Functions: `module_verb_object` (e.g., `player_set_location`).
  - Variables: `snake_case` (e.g., `current_id`, `object_id`).
  - Constants/macros: `UPPER_SNAKE_CASE` (e.g., `MAX_SPACES`).

## Documentation (Doxygen / D1)

Rule of thumb: if someone who is not you opens a file, they should understand quickly what the module does and what each function does.

### File header (required in `.c` and `.h`)

Use the same format as `space.c` / `space.h`:

```c
/**
 * @brief ...
 *
 * @file filename.c
 * @author ...
 * @version 0
 * @date DD-MM-YYYY
 * @copyright GNU Public License
 */
```

### Prototypes and functions (public and private)

- Every function must have a Doxygen block with:
  - `@brief`
  - `@author` (a **single** author per function, as required by D1)
  - `@param` for each parameter (if any)
  - `@return`
- Project-specific author policy:
  - Keep the original author for untouched seed functions (e.g., **Profesores PPROG**).
  - For modified seed functions, set the function author to **Iker Díaz**.
  - Keep **Fernando Pina** as author for functions in modules he implemented (`player.*` and `object.*`) and directly related updates there.
- Keep `@brief` short but precise. Add `@note` only when it improves clarity.

Example (as in `space.h`):

```c
/**
 * @brief It sets the location of the player
 * @author Name Surname
 *
 * @param player a pointer to the player
 * @param location_id the id of the space where the player is
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_location(Player* player, Id location_id);
```

### Structs, enums, globals

- Private `struct` in `.c`: document the `struct` and each field.
- Public enums (if added): document the enum and each value.
- Global variables: avoid; if needed, document and justify.

Field example:

```c
struct _Player {
  Id id;                    /*!< Unique player id */
  char name[WORD_SIZE + 1]; /*!< Player name */
  Id location;              /*!< Current space id */
  Id object;                /*!< Carried object id (or NO_ID) */
};
```

## Collaboration (2 people)

- Do not reformat the entire seed code unless necessary. Priority: D1/D2/C1 compliance.
- When modifying an existing function:
  - Keep the file's established style.
  - Update that function's Doxygen block so it matches the real behavior and has a single `@author`.
- If two people worked on the same function, pick one responsible author for `@author`. If needed, add a short `@note`.

## Quick checklist before pushing

- `make clean && make` builds with `-Wall` and no warnings.
- `Makefile` includes any new `.c` files (C3).
- `.c` and `.h` files have complete file headers.
- Public and private function docs are present and correct.
- No copy/paste mistakes in `@file`, function names, or parameter names.
