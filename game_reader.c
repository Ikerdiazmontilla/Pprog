/**
 * @brief It implements the game reader module
 *
 * @file game_reader.c
 * @author Iker Díaz
 * @version 0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief It trims leading and trailing spaces and line endings from a token
 * @author Iker Díaz
 *
 * @param token token to normalize
 * @return normalized token pointer
 */
static char* game_reader_clean_token(char* token);

/**
 * @brief It loads spaces from a data file
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param filename path to the data file
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_reader_load_spaces(Game* game, char* filename);

/**
 * @brief It loads objects from a data file
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param filename path to the data file
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_reader_load_objects(Game* game, char* filename);

static char* game_reader_clean_token(char* token) {
  char* end = NULL;

  if (!token) {
    return NULL;
  }

  while (*token == ' ' || *token == '\t') {
    token++;
  }

  if (*token == '\0') {
    return token;
  }

  end = token + strlen(token) - 1;
  while (end > token && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
    *end = '\0';
    end--;
  }

  return token;
}

static Status game_reader_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* token = NULL;
  Id id = NO_ID;
  Id north = NO_ID;
  Id east = NO_ID;
  Id south = NO_ID;
  Id west = NO_ID;
  Space* space = NULL;
  int i = 0;
  Status status = OK;

  if (!game || !filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (!file) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) != 0) {
      continue;
    }

    token = strtok(line + 3, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    token = game_reader_clean_token(token);
    id = atol(token);

    token = strtok(NULL, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    token = game_reader_clean_token(token);
    strncpy(name, token, WORD_SIZE - 1);
    name[WORD_SIZE - 1] = '\0';

    token = strtok(NULL, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    north = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    east = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    south = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    west = atol(game_reader_clean_token(token));

    space = space_create(id);
    if (!space) {
      status = ERROR;
      break;
    }

    if (space_set_name(space, name) == ERROR) {
      space_destroy(space);
      status = ERROR;
      break;
    }

    if (north != NO_ID && space_set_north(space, north) == ERROR) {
      space_destroy(space);
      status = ERROR;
      break;
    }
    if (east != NO_ID && space_set_east(space, east) == ERROR) {
      space_destroy(space);
      status = ERROR;
      break;
    }
    if (south != NO_ID && space_set_south(space, south) == ERROR) {
      space_destroy(space);
      status = ERROR;
      break;
    }
    if (west != NO_ID && space_set_west(space, west) == ERROR) {
      space_destroy(space);
      status = ERROR;
      break;
    }

    for (i = 0; i < SPACE_GDESC_LINES; i++) {
      token = strtok(NULL, "|");
      if (!token) {
        break;
      }
      token = game_reader_clean_token(token);
      if (space_set_gdesc(space, i, token) == ERROR) {
        space_destroy(space);
        status = ERROR;
        break;
      }
    }
    if (status == ERROR) {
      break;
    }

    if (game_add_space(game, space) == ERROR) {
      space_destroy(space);
      status = ERROR;
      break;
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

static Status game_reader_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* token = NULL;
  Id id = NO_ID;
  Id location_id = NO_ID;
  Object* object = NULL;
  Status status = OK;

  if (!game || !filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (!file) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) != 0) {
      continue;
    }

    token = strtok(line + 3, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    id = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    token = game_reader_clean_token(token);
    strncpy(name, token, WORD_SIZE - 1);
    name[WORD_SIZE - 1] = '\0';

    token = strtok(NULL, "|");
    if (!token) {
      status = ERROR;
      break;
    }
    location_id = atol(game_reader_clean_token(token));

    object = object_create(id);
    if (!object) {
      status = ERROR;
      break;
    }

    if (object_set_name(object, name) == ERROR) {
      object_destroy(object);
      status = ERROR;
      break;
    }

    if (game_add_object(game, object, location_id) == ERROR) {
      object_destroy(object);
      status = ERROR;
      break;
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status game_reader_create_from_file(Game* game, char* filename) {
  Id first_space_id = NO_ID;

  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  first_space_id = game_get_space_id_at(game, 0);
  if (first_space_id == NO_ID || game_set_player_location(game, first_space_id) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  if (game_reader_load_objects(game, filename) == ERROR) {
    game_destroy(game);
    return ERROR;
  }

  return OK;
}
