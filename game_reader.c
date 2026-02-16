/**
 * @brief It implements the game reader module
 *
 * @file game_reader.c
 * @author Iker Díaz
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief It loads spaces from a data file
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param filename path to the data file
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_reader_load_spaces(Game *game, char *filename);
/**
   Implementation of private functions
*/

static Status game_reader_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  if (!game || !filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      if (!toks) {
        status = ERROR;
        break;
      }
      id = atol(toks);
      toks = strtok(NULL, "|");
      if (!toks) {
        status = ERROR;
        break;
      }
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      if (!toks) {
        status = ERROR;
        break;
      }
      north = atol(toks);
      toks = strtok(NULL, "|");
      if (!toks) {
        status = ERROR;
        break;
      }
      east = atol(toks);
      toks = strtok(NULL, "|");
      if (!toks) {
        status = ERROR;
        break;
      }
      south = atol(toks);
      toks = strtok(NULL, "|");
      if (!toks) {
        status = ERROR;
        break;
      }
      west = atol(toks);
#ifdef DEBUG
      printf("Read: s:%ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        if (north != NO_ID) space_set_north(space, north);
        if (east != NO_ID) space_set_east(space, east);
        if (south != NO_ID) space_set_south(space, south);
        if (west != NO_ID) space_set_west(space, west);
        game_add_space(game, space);
      } else {
        status = ERROR;
        break;
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status game_reader_create_from_file(Game *game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}
