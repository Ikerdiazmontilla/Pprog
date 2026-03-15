# Contributions And Commit Authorship

This document groups the existing Git history by author and records the current finishing pass in the working tree.

## Fernando Pina

- `4f206ce` - `Modulo de player terminado`
- `d52493e` - `Merge branch 'main' of github.com:Ikerdiazmontilla/Pprog`
- `1e715d0` - `Eliminar warnings de game.c`
- `52fcc2a` - `Makefile añadido`
- `318b102` - `Modulo object añadido`
- `2b3d4c0` - `Archivos .o eliminados`
- `1a6b2dc` - `diagrama Gantt añadido`
- `663d917` - `Game opaco, intro de modulo set`
- `bb88c18` - `modulo set acabado`
- `7107482` - `pseudocodigo terminado`
- `17c9d65` - `Space modificado`
- `9bef8b1` - `space y comandos right left`
- `4de25aa` - `todos los comandos hechos`
- `ee85b3f` - `makefile hecho`

## Iker

- `6a53d3f` - `Initial commit`
- `65c28d4` - `First Commit, basic code`
- `e1306f8` - `Merge branch 'main' of github.com:Ikerdiazmontilla`
- `3315f26` - `Add gamerader and move game load functions`
- `ba43d22` - `commit de prueba`
- `dd97f04` - `Add game_reader_create_file to game reader and`
- `7c25803` - `Añadir archivo de estilos y enunciado a la codebase`
- `618a811` - `Add F6,F7 and F8, document changes`
- `7cd39ef` - `Put all documentation in english`
- `c2366e7` - `Tidy up directory`
- `0158cc6` - `Cambiar nombres documentacion`
- `d25362e` - `Arreglar ciertas funciones q no estaban documenta`
- `87eafa4` - `Merge branch 'main' of Ikerdiazmontilla/Pprog`
- `cc96ef6` - `Añadir archivos extra y entrega 1`
- `c9d46bb` - `Reorganizar archivos`
- `bf7b623` - `I2: add Character module/tests and extend Game/Space/Player for object and gdesc loading`

## Current Working Tree Finalization

Author: `Iker Díaz`

Main changes in the current uncommitted finishing pass:

- Rebuilt `Game` as an opaque module and updated the loading flow around it.
- Reworked command parsing to support `take <object>` with arguments instead of hardcoded object-specific commands.
- Fixed `Set` and `Space` so multiple objects and character placement work correctly.
- Corrected object ownership semantics so carried objects disappear from visible spaces.
- Added character loading from `castle.dat` so `attack` and `chat` are functional in the playable game.
- Expanded the graphic engine to show the cross-shaped map, ASCII room descriptions, objects, characters, player health, chat message and last command result.
- Added and enabled `set_test` and `space_test`, and updated the build to use `-Wall -ansi -pedantic` with clean linking rules.
- Updated both Gantt spreadsheets, including the final I2 schedule adjustments across the last week.
