# Guia de estudio de la codebase

Este documento esta pensado para que entiendas el proyecto desde cero y lo puedas defender en un examen.

No esta escrito como documentacion de usuario. Esta escrito como guia de estudio:
- primero te da el modelo mental correcto,
- luego te explica el flujo real del programa,
- despues baja modulo a modulo,
- y al final resume lo que deberias saber responder de memoria.

## 1. Que es este proyecto

Es un juego de aventura en terminal hecho en C.

El programa:
- carga un mapa desde `castle.dat`,
- crea un estado de partida,
- muestra una interfaz ASCII,
- lee comandos del usuario,
- actualiza el estado,
- vuelve a pintar la interfaz.

El ciclo base del juego esta en `game_loop.c`.

## 2. La idea mas importante de toda la codebase

La mejor forma de entender el proyecto es esta:

- `Game` guarda la verdad del estado.
- `game_reader` construye ese estado desde el fichero `.dat`.
- `command` interpreta lo que escribe el usuario.
- `game_actions` cambia el estado segun el comando.
- `graphic_engine` pinta el estado en la pantalla.

Si entiendes esa frase, entiendes la arquitectura.

## 3. Mapa mental rapido de archivos

### Archivos fundamentales

- `types.h`: tipos comunes de todo el proyecto.
- `game.h` y `game.c`: estado global de la partida.
- `game_loop.c`: bucle principal.
- `game_reader.h` y `game_reader.c`: carga el juego desde `castle.dat`.
- `command.h` y `command.c`: interpreta los comandos.
- `game_actions.h` y `game_actions.c`: aplica la logica de juego.
- `graphic_engine.h` y `graphic_engine.c`: dibuja la interfaz.

### Entidades del mundo

- `space.h` y `space.c`: salas.
- `player.h` y `player.c`: jugador.
- `object.h` y `object.c`: objetos.
- `character.h` y `character.c`: personajes.
- `set.h` y `set.c`: conjunto de ids, usado para varios objetos por sala.

### Soporte

- `castle.dat`: mundo cargado por el juego.
- `Makefile`: compilacion y tests.
- `*_test.c`: tests unitarios.

## 4. Fundamentos de C que necesitas para entender esta codebase

Antes de meterte en la logica del juego, necesitas manejar estas 8 ideas.

### 4.1 `typedef`

En `types.h` se usan alias de tipos:

```c
typedef long Id;
typedef enum { FALSE, TRUE } Bool;
typedef enum { ERROR, OK } Status;
```

Esto hace el codigo mas legible:
- `Id` en vez de `long`
- `Bool` en vez de usar enteros
- `Status` para decir si una funcion ha ido bien o mal

### 4.2 `NO_ID`

En este proyecto `NO_ID` significa "no hay entidad valida".

```c
#define NO_ID -1
```

Se usa constantemente:
- una sala sin salida tiene `NO_ID` en esa direccion,
- un jugador sin objeto lleva `NO_ID`,
- un personaje inexistente se representa con `NO_ID`.

### 4.3 Struct opaco

Ejemplo en `game.h`:

```c
typedef struct _Game Game;
```

Eso no define el struct completo. Solo dice: "existe un struct `_Game`, y desde fuera lo llamaremos `Game`".

La definicion real esta en `game.c`:

```c
struct _Game {
  ...
};
```

Esto sirve para encapsular. Desde fuera no puedes tocar los campos internos directamente. Solo puedes usar funciones como:
- `game_get_player_location`
- `game_add_space`
- `game_set_message`

Esa es una decision de diseno importante de I2.

### 4.4 Punteros y doble puntero

Si ves:

```c
Game *game;
```

eso es un puntero a un `Game`.

Si ves:

```c
Game **game;
```

eso es un puntero a un puntero a `Game`.

Se usa en `game_loop_init` para poder modificar el puntero original creado en `main`.

Ejemplo:

```c
static int game_loop_init(Game** game, Graphic_engine** gengine, char* file_name);
```

Dentro de la funcion se hace:

```c
*game = game_reader_create_from_file(file_name);
*gengine = graphic_engine_create();
```

Si la funcion recibiera solo `Game *game`, cambiaria una copia local y `main` no veria el resultado.

### 4.5 Cabeceras `.h` y fuentes `.c`

Regla general:
- `.h`: declara tipos y funciones
- `.c`: implementa esas funciones

Por eso en `space.h` ves prototipos como:

```c
Space* space_create(Id id);
Status space_set_name(Space* space, char* name);
```

y en `space.c` ves el codigo real de esas funciones.

### 4.6 `strtok`

`strtok` parte una cadena en tokens usando un delimitador.

Ejemplo:

```c
#o:21|Sword|11
```

si lo partes por `|`, obtienes:
- `21`
- `Sword`
- `11`

Eso es exactamente lo que hace `game_reader.c` al leer el `.dat`.

### 4.7 `\n`, `\r` y finales de linea

- `\n`: salto de linea
- `\r`: retorno de carro

En Linux suele haber `\n`.
En Windows suele haber `\r\n`.

Por eso el parser limpia `\n` y `\r`, para que no queden caracteres basura al final de los strings.

### 4.8 Memoria dinamica

Este proyecto crea casi todas las entidades con `calloc`:
- `game_create`
- `space_create`
- `player_create`
- `object_create`
- `character_create`
- `command_create`
- `set_create`

Y luego las libera con su `destroy` correspondiente.

Esa relacion entre `create` y `destroy` es muy importante en C. Si olvidas destruir, fugas memoria. Si destruyes dos veces, puedes romper el programa.

## 5. Flujo real del programa

Ahora vamos a seguir el juego desde que arrancas hasta que escribes un comando.

### 5.1 `main`

En `game_loop.c`, `main` hace esto:

1. inicializa punteros a `Game` y `Graphic_engine`
2. comprueba que exista argumento de linea de comandos
3. llama a `game_loop_init`
4. recupera el ultimo comando del juego
5. entra en el bucle principal

El bucle principal es:

```c
while (command_get_code(last_cmd) != EXIT && game_get_finished(game) == FALSE) {
  graphic_engine_paint_game(gengine, game);
  command_get_user_input(last_cmd);
  game_actions_update(game, last_cmd);
}
```

Esta es la secuencia fundamental del juego:

- pintar,
- leer,
- actualizar.

### 5.2 `game_loop_init`

`game_loop_init` hace dos cosas:

```c
*game = game_reader_create_from_file(file_name);
*gengine = graphic_engine_create();
```

Traduccion:
- carga el mundo desde el fichero,
- crea el motor grafico.

## 6. El corazon del proyecto: `Game`

`Game` es el estado completo de una partida.

En `game.c`, el struct real contiene:

- `Player* player`
- `Space* spaces[MAX_SPACES]`
- `Object* objects[MAX_OBJECTS]`
- `Id object_locations[MAX_OBJECTS]`
- `Character* characters[MAX_CHARACTERS]`
- `Command* last_cmd`
- `Status last_cmd_status`
- `char message[GAME_MESSAGE_SIZE + 1]`
- `Bool finished`

Esto es importantisimo:

`Game` no es solo el mapa.
`Game` es todo:
- quien eres,
- donde estas,
- que objeto llevas,
- que personajes existen,
- que mensaje debe mostrarse,
- si la partida ha terminado.

### 6.1 Por que `object_locations` esta en `Game`

Aunque una sala ya guarda sus objetos, `Game` tambien guarda un array de localizaciones.

Esto permite:
- consultar rapidamente donde esta un objeto,
- distinguir si el jugador lo lleva,
- mover objetos entre salas manteniendo consistencia.

### 6.2 Correccion clave de I2

En I2 habia una correccion importante:

`game_get_object_location_by_id` debe devolver `NO_ID` si el jugador lleva el objeto.

Eso evita que el objeto siga "apareciendo" en una sala cuando ya lo has cogido.

## 7. Las entidades del mundo

### 7.1 `Space`

Una sala tiene:
- id
- nombre
- conexiones `north`, `south`, `east`, `west`
- un `Set` de objetos
- un personaje
- un `gdesc`

`gdesc` significa `graphical description`.
Es el dibujo ASCII de la sala:

```c
char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1];
```

Y en `space.h` se define:
- 5 lineas
- 9 caracteres por linea

Por eso cada sala en `castle.dat` tiene exactamente 5 trozos de ASCII.

### 7.2 `Player`

El jugador tiene:
- id
- nombre
- objeto que lleva
- localizacion actual
- vida
- `gdesc`

Observa algo importante:
- el jugador no guarda un puntero al objeto,
- guarda el `Id` del objeto.

Eso es un patron general de la codebase: usar ids para desacoplar.

### 7.3 `Object`

Un objeto es deliberadamente simple:
- id
- nombre

La logica de "donde esta" no vive en `Object`, vive en `Game` y `Space`.

### 7.4 `Character`

Un personaje tiene:
- id
- nombre
- `gdesc`
- salud
- `friendly`
- mensaje

Eso permite dos roles distintos:
- personaje amistoso: sirve para `chat`
- personaje hostil: sirve para `attack`

## 8. `Set`: por que existe

Antes una sala podia comportarse como si tuviera un solo objeto.
En I2 eso ya no bastaba.

Por eso existe `Set`.

`Set` es una estructura que guarda varios `Id`, sin duplicados.

En esta codebase sirve para representar:
- los ids de los objetos presentes en una sala.

Funciones importantes:
- `set_add_id`
- `set_del_id`
- `set_find_id`
- `set_get_n_ids`
- `set_get_ids`

Conceptualmente:
- `Space` usa `Set`
- `Game` consulta `Space`
- `graphic_engine` termina mostrando los resultados

## 9. Como se carga el juego desde `castle.dat`

El parser esta en `game_reader.c`.

La funcion grande es `game_reader_create_from_file`.

Hace esto:

1. crea un `Game` vacio
2. carga espacios
3. coloca al jugador en el primer espacio cargado
4. carga objetos
5. carga personajes
6. devuelve el `Game*`

Si algo falla en cualquier paso, destruye el juego y devuelve `NULL`.

### 9.1 Como se leen los espacios

`game_reader_load_spaces` recorre el fichero linea a linea con `fgets`.

Para cada linea:
- si no empieza por `#s:`, la ignora
- si empieza por `#s:`, la divide con `strtok(..., "|")`

Una linea de espacio tiene esta forma:

```txt
#s:<id>|<name>|<north>|<east>|<south>|<west>|<gdesc1>|<gdesc2>|<gdesc3>|<gdesc4>|<gdesc5>
```

Despues:
- crea un `Space`
- rellena nombre y conexiones
- recorre 5 veces para guardar cada linea de `gdesc`
- mete la sala en `Game`

### 9.2 Por que hay dos funciones de limpieza

El parser tiene:
- `game_reader_clean_token`
- `game_reader_clean_gdesc_token`

La segunda existe porque el ASCII necesita conservar espacios.

Si recortaras espacios al principio o al final del dibujo, lo destrozarias visualmente.

### 9.3 Como se leen objetos y personajes

Lo mismo, pero con otros prefijos:

- `#o:` objetos
- `#c:` personajes

Cada pasada recorre otra vez el fichero completo, lo que simplifica el codigo:
- primero aseguras que las salas existen,
- luego metes objetos en salas existentes,
- luego metes personajes en salas existentes.

## 10. `castle.dat`: el mundo canonico

`castle.dat` es el nivel del juego.

Contiene:
- espacios
- objetos
- personajes

### 10.1 Estructura del mapa

Camino principal:
- Entrada
- Pasillo
- Comedor
- Cocina
- Patio interior
- Jardin

Rama este:
- Habitacion
- Bano

Rama oeste:
- Mazmorra

La mazmorra no tiene salidas. Todas sus conexiones estan a `-1`.

### 10.2 Personajes

Hay dos personajes:
- `Butler`, amistoso, en el pasillo
- `Ghost`, hostil, en el comedor

Sirven para demostrar dos mecanicas distintas:
- `chat`
- `attack`

## 11. El parser de comandos

Todo lo que escribe el usuario pasa por `command.c`.

`Command` guarda:
- el codigo del comando
- un argumento opcional

Ejemplo:
- `n` -> comando `NEXT`, sin argumento
- `take Sword` -> comando `TAKE`, argumento `"Sword"`

### 11.1 Como parsea

`command_get_user_input`:
- lee una linea con `fgets`
- extrae el primer token como comando
- extrae el resto como argumento
- compara el token con la tabla `cmd_to_str`

Comandos soportados:
- `exit`
- `next`
- `back`
- `left`
- `right`
- `take`
- `drop`
- `attack`
- `chat`

### 11.2 Detalle importante de memoria

`command_set_argument` copia primero el texto a un buffer temporal y luego al campo interno del struct.

Eso se hace para evitar problemas si el origen y destino se solapan en memoria.

Es una correccion fina, pero muy importante si te preguntan por validacion o robustez.

## 12. La logica del juego: `game_actions`

`game_actions_update` recibe:
- el estado global (`Game`)
- el comando ya parseado (`Command`)

Y hace:

1. guardar el ultimo comando
2. limpiar el mensaje anterior
3. ejecutar un `switch`
4. guardar el resultado del comando en `last_cmd_status`

### 12.1 Movimiento

`game_actions_move`:
- obtiene la sala actual
- mira la conexion en la direccion pedida
- si la conexion es `NO_ID`, falla
- si existe, cambia la localizacion del jugador

### 12.2 `take`

`game_actions_take`:
- comprueba que el jugador no lleve ya un objeto
- busca el objeto por nombre
- comprueba que este en la sala actual
- lo mueve a `NO_ID` como localizacion del mundo
- pone ese id como objeto del jugador

Esto refleja una idea muy importante:
- el objeto deja de estar en una sala,
- y pasa a estar "en manos del jugador".

### 12.3 `drop`

`game_actions_drop`:
- mira que objeto lleva el jugador
- lo deja en la sala actual
- borra el objeto del jugador

### 12.4 `attack`

`game_actions_attack`:
- comprueba que haya personaje en la sala
- comprueba que sea hostil
- usa `rand() % 10`
- si sale 0..4, pierde vida el jugador
- si sale 5..9, pierde vida el enemigo
- si el jugador llega a 0, `game_set_finished(game, TRUE)`

No es un sistema complejo de combate. Es intencionalmente simple.

### 12.5 `chat`

`game_actions_chat`:
- comprueba que haya personaje
- comprueba que sea amistoso
- copia el mensaje del personaje a `game->message`

Ese mensaje luego lo pinta el motor grafico.

## 13. El motor grafico

Aqui "motor grafico" no significa graficos reales.
Significa motor de presentacion textual.

Esta en `graphic_engine.c`.

Su trabajo es:
- crear areas de pantalla,
- decidir que texto va en cada una,
- dibujarlo en la terminal.

No aplica reglas del juego.
Solo representa el estado actual.

### 13.1 Areas de pantalla

El motor crea varias areas:
- `map`
- `descript`
- `banner`
- `help`
- `feedback`

### 13.2 La cruz de salas visibles

El mapa se pinta en forma de cruz:

```txt
        [NORTE]

[OESTE] [ACTUAL] [ESTE]

        [SUR]
```

Eso significa que no solo ves la sala actual, sino tambien las adyacentes.

### 13.3 Que muestra

El motor grafico muestra:
- cajas de salas visibles
- `gdesc` de cada sala
- objetos visibles
- flechas de movimiento
- descripcion de objetos del juego
- descripcion de personajes
- estado del jugador
- ayuda de comandos
- feedback del ultimo comando
- mensajes como el del mayordomo

### 13.4 Idea clave de arquitectura

`graphic_engine` no decide nada.

No interpreta si un ataque es valido.
No mueve al jugador.
No coge objetos.

Solo pregunta a `Game` y dibuja el resultado.

## 14. Tests y validacion

La entrega deja varios tests unitarios:
- `set_test.c`
- `space_test.c`
- `character_test.c`
- `command_test.c`

Y el `Makefile` tiene:
- `make`
- `make tests`
- `make run`
- `make clean`

El proyecto tambien se valido con:
- compilacion estricta (`-Wall -ansi -pedantic`)
- AddressSanitizer
- Valgrind

Eso importa mucho porque en C puedes tener:
- errores de memoria,
- fugas,
- dobles liberaciones,
- accesos invalidos.

## 15. Lo mas importante que se hizo en la entrega 2

Resumen de cambios con valor funcional real:

- `Game` se volvio opaco y mas limpio.
- Se corrigio el sistema de objetos para que una sala pueda tener varios.
- Se anadio `Set` como soporte real de varios objetos.
- Se anadieron personajes.
- Se anadieron `chat` y `attack`.
- Se anadieron `left` y `right`.
- `take` paso a aceptar nombre de objeto.
- Se anadieron `gdesc` por sala.
- Se rehizo el renderizado ASCII para mostrar salas visibles y feedback.
- Se corrigio el bug del objeto que seguia apareciendo en la sala aunque lo llevara el jugador.
- Se dejo la mazmorra como callejon sin salida.
- Se anadieron tests nuevos.

## 16. Como explicarlo bien en un examen oral

Si te dicen "explicame la arquitectura", una muy buena respuesta seria:

"La aplicacion esta separada en capas. `game_reader` construye el estado inicial desde un fichero. `Game` centraliza el estado de la partida. `command` interpreta lo que escribe el usuario. `game_actions` modifica `Game` segun las reglas. `graphic_engine` consulta `Game` y dibuja la interfaz. El bucle principal hace paint-read-update hasta que el jugador sale o la partida termina."

Si te dicen "explicame una accion", por ejemplo `take`:

"El comando se parsea en `command`. Luego `game_actions_take` comprueba si el jugador ya lleva algo, busca el objeto por nombre, verifica que este en la sala actual, actualiza la localizacion del objeto a `NO_ID` y guarda ese id en el jugador."

Si te dicen "por que usais ids en vez de punteros cruzados":

"Porque simplifica la carga desde fichero, desacopla modulos y centraliza la resolucion de entidades en `Game`."

## 17. Preguntas trampa que te pueden hacer

### "Que diferencia hay entre `Game`, `Game*` y `Game**`?"

- `Game`: el tipo
- `Game*`: direccion de una estructura `Game`
- `Game**`: direccion de un puntero a `Game`

### "Que es un token?"

Un trozo de texto obtenido al partir una cadena con un delimitador.

### "Que es `gdesc`?"

La descripcion grafica ASCII de una sala.

### "Por que la mazmorra no tiene salida?"

Porque la correccion de la entrega anterior lo exigia explicitamente.

### "Por que el objeto llevado devuelve `NO_ID`?"

Para que la interfaz no siga mostrandolo en el mapa como si siguiera en una sala.

## 18. Checklist de dominio real

Si quieres ir bien preparado, deberias poder explicar sin mirar:

- que guarda `Game`
- como se crea el juego desde el fichero
- como funciona `strtok`
- como se parsea `take Sword`
- como se mueve el jugador
- como se representa una sala
- por que existe `Set`
- que hace `graphic_engine`
- diferencia entre logica y presentacion
- por que el proyecto usa ids y structs opacos

## 19. Como estudiar esto de verdad

No memorices archivo por archivo.
Estudia en este orden:

1. `types.h`
2. `game_loop.c`
3. `game.h` y `game.c`
4. `space`, `player`, `object`, `character`
5. `game_reader.c`
6. `command.c`
7. `game_actions.c`
8. `graphic_engine.c`
9. `castle.dat`

Ese orden respeta el flujo real del programa.

## 20. Ultima idea importante

La gran diferencia entre entender esta codebase "por encima" y entenderla bien es esta:

No tienes que pensar "hay muchos archivos".
Tienes que pensar:

- quien guarda el estado,
- quien lo crea,
- quien lo cambia,
- quien lo pinta.

En este proyecto la respuesta es:

- estado: `Game`
- creacion: `game_reader`
- cambios: `game_actions`
- representacion: `graphic_engine`

Si controlas eso, ya no estas perdido en la codebase.

## 21. Siguiente uso recomendado de este documento

Lo mejor ahora es usar esta guia de forma activa:

- lee una seccion
- abre el archivo correspondiente
- intenta explicarlo con tus palabras
- luego me preguntas la parte que te chirrie

Yo te recomiendo que lo siguiente que hagamos sea una de estas dos cosas:

1. Repaso oral por preguntas tipo examen.
2. Recorrido completo de una jugada real desde teclado hasta pantalla.

