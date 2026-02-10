# Estilo de Codigo y Documentacion (I1 - PPROG)

Este repositorio debe cumplir, por encima de todo, con los requisitos **D1** y **D2** de `RequisitosI1.pdf`:

- Todo el codigo (semilla y nuevo) debe estar documentado.
- El estilo debe ser **homogeneo**, **simple**, **facil de leer** y **facil de mantener**.
- El codigo debe compilar con `-Wall` sin warnings (requisito **C1**).

`space.c` y `space.h` se toman como **referencia canonica** del formato general (cabeceras, Doxygen, prefijos).

## C (formato)

- Indentacion: **2 espacios**, nunca tabs. No mezclar.
- Llaves: **K&R**.
  - `if (cond) { ... }`
  - `switch (x) { case ...: ...; break; }`
- Longitud de linea: objetivo **100** columnas (romper lineas largas con sentido).
- Espacios:
  - `if (x)`, `for (...)`, `while (...)`
  - Operadores binarios con espacios: `a + b`, `x == y`
  - Punteros como en el codigo semilla: `Type* ptr` (no introducir mezclas dentro de un mismo fichero).
- Orden de `#include` en `.c`:
  1. Cabecera del modulo (`#include "modulo.h"`)
  2. System headers (`<stdio.h>`, `<stdlib.h>`, ...)
  3. Otras cabeceras del proyecto
- Privado vs publico:
  - Funciones privadas: `static` en el `.c` y documentadas (D1).
  - No exponer `struct _X` en `.h` (usar `typedef struct _X X;` como en semilla).
- Manejo de errores:
  - Preferir checks simples y retornos tempranos:
    - `if (!ptr) return ERROR;`
  - `create` devuelve puntero o `NULL`.
  - `destroy` devuelve `OK/ERROR`.
  - `getters` devuelven `NO_ID`/`NULL` si hay error.
- Nombres:
  - Funciones: `modulo_verbo_objeto` (ej.: `player_set_location`).
  - Variables: `snake_case` (ej.: `current_id`, `object_id`).
  - Constantes/macros: `MAYUSCULAS_CON_GUIONES_BAJOS` (ej.: `MAX_SPACES`).

## Documentacion (Doxygen / D1)

Regla general: **si alguien que no has sido tu abre el fichero, debe entender rapidamente que hace el modulo y cada funcion**.

### Cabecera de fichero (obligatoria en `.c` y `.h`)

Usar el mismo formato que `space.c` / `space.h`:

```c
/**
 * @brief ...
 *
 * @file nombre_fichero.c
 * @author ...
 * @version 0
 * @date DD-MM-YYYY
 * @copyright GNU Public License
 */
```

### Prototipos y funciones (publicas y privadas)

- Todas las funciones deben tener bloque Doxygen con:
  - `@brief`
  - `@author` (autor **unico** por funcion, como pide D1)
  - `@param` para cada parametro (si aplica)
  - `@return`
- Si la funcion es simple y obvia, el `@brief` puede ser una frase corta.
- Si hay precondiciones, documentarlas en el `@brief` o con `@note`.

Ejemplo (como `space.h`):

```c
/**
 * @brief It sets the location of the player
 * @author Nombre Apellido
 *
 * @param player a pointer to the player
 * @param location_id the id of the space where the player is
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_location(Player* player, Id location_id);
```

### Estructuras, enums, globales

- `struct` privada en `.c`: documentar el `struct` y cada campo.
- Enums publicos (si se introducen): documentar el enum y cada valor.
- Variables globales: evitar; si existen, documentarlas y justificar su necesidad.

Ejemplo de campos:

```c
struct _Player {
  Id id;                    /*!< Unique player id */
  char name[WORD_SIZE + 1]; /*!< Player name */
  Id location;              /*!< Current space id */
  Id object;                /*!< Carried object id (or NO_ID) */
};
```

## Colaboracion (2 personas)

- No reformatear masivamente el codigo semilla si no es necesario. Prioridad: cumplir D1/D2/C1.
- Al modificar una funcion existente:
  - Mantener el estilo del fichero.
  - Actualizar el bloque Doxygen de esa funcion para que tenga `@author` unico y describa el comportamiento real.
- Si dos personas trabajan en la misma funcion, decidir un responsable y usar un solo nombre en `@author` (D1). El resto puede quedar en un `@note` corto si hace falta.

## Checklist rapido antes de entregar/cambiar codigo

- `make clean && make` compila con `-Wall` sin warnings.
- El `Makefile` incluye cualquier `.c` nuevo (C3).
- `.c` y `.h` tienen cabecera completa.
- Prototipos (publicos y privados) documentados.
- Ningun comentario/copypaste apunta a `@file` incorrecto o nombres incorrectos.

