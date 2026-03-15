/**
 * @brief It implements the game reader module
 *
 * @file game_reader.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
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
 * @brief It removes only line endings from a token while preserving spaces
 * @author Iker Díaz
 *
 * @param token token to normalize
 * @return normalized token pointer
 */
static char* game_reader_clean_gdesc_token(char* token);

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

/**
 * @brief It loads characters from a data file
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param filename path to the data file
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_reader_load_characters(Game* game, char* filename);

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
  while (end > token &&
         (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
    *end = '\0';
    end--;
  }

  return token;
}

static char* game_reader_clean_gdesc_token(char* token) {
  char* end = NULL;

  if (!token) {
    return NULL;
  }

  if (*token == '\0') {
    return token;
  }

  end = token + strlen(token) - 1;
  while (end >= token && (*end == '\n' || *end == '\r')) {
    *end = '\0';
    end--;
  }

  return token;
}

static Status game_reader_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE + 1];
  char name[WORD_SIZE + 1];
  char* token = NULL;
  Id id = NO_ID;
  Id north = NO_ID;
  Id east = NO_ID;
  Id south = NO_ID;
  Id west = NO_ID;
  Space* space = NULL;
  int i = 0;

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
      fclose(file);
      return ERROR;
    }
    id = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    strncpy(name, game_reader_clean_token(token), WORD_SIZE);
    name[WORD_SIZE] = '\0';

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    north = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    east = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    south = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    west = atol(game_reader_clean_token(token));

    space = space_create(id);
    if (!space) {
      fclose(file);
      return ERROR;
    }

    if (space_set_name(space, name) == ERROR ||
        space_set_north(space, north) == ERROR ||
        space_set_east(space, east) == ERROR ||
        space_set_south(space, south) == ERROR ||
        space_set_west(space, west) == ERROR) {
      space_destroy(space);
      fclose(file);
      return ERROR;
    }

    for (i = 0; i < SPACE_GDESC_LINES; i++) {
      token = strtok(NULL, "|");
      if (!token || space_set_gdesc(space, i, game_reader_clean_gdesc_token(token)) == ERROR) {
        space_destroy(space);
        fclose(file);
        return ERROR;
      }
    }

    if (game_add_space(game, space) == ERROR) {
      space_destroy(space);
      fclose(file);
      return ERROR;
    }
  }

  fclose(file);
  return OK;
}

static Status game_reader_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE + 1];
  char name[WORD_SIZE + 1];
  char* token = NULL;
  Id id = NO_ID;
  Id location_id = NO_ID;
  Object* object = NULL;

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
      fclose(file);
      return ERROR;
    }
    id = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    strncpy(name, game_reader_clean_token(token), WORD_SIZE);
    name[WORD_SIZE] = '\0';

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    location_id = atol(game_reader_clean_token(token));

    object = object_create(id);
    if (!object) {
      fclose(file);
      return ERROR;
    }

    if (object_set_name(object, name) == ERROR ||
        game_add_object(game, object, location_id) == ERROR) {
      object_destroy(object);
      fclose(file);
      return ERROR;
    }
  }

  fclose(file);
  return OK;
}

static Status game_reader_load_characters(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE + 1];
  char name[WORD_SIZE + 1];
  char gdesc[WORD_SIZE + 1];
  char message[WORD_SIZE + 1];
  char* token = NULL;
  Id id = NO_ID;
  Id location_id = NO_ID;
  int health = 0;
  Bool friendly = FALSE;
  Character* character = NULL;

  if (!game || !filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (!file) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) != 0) {
      continue;
    }

    token = strtok(line + 3, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    id = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    strncpy(name, game_reader_clean_token(token), WORD_SIZE);
    name[WORD_SIZE] = '\0';

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    location_id = atol(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    strncpy(gdesc, game_reader_clean_token(token), WORD_SIZE);
    gdesc[WORD_SIZE] = '\0';

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    health = atoi(game_reader_clean_token(token));

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    friendly = (atoi(game_reader_clean_token(token)) != 0) ? TRUE : FALSE;

    token = strtok(NULL, "|");
    if (!token) {
      fclose(file);
      return ERROR;
    }
    strncpy(message, game_reader_clean_token(token), WORD_SIZE);
    message[WORD_SIZE] = '\0';

    character = character_create(id);
    if (!character) {
      fclose(file);
      return ERROR;
    }

    if (character_set_name(character, name) == ERROR ||
        character_set_gdesc(character, gdesc) == ERROR ||
        character_set_health(character, health) == ERROR ||
        character_set_friendly(character, friendly) == ERROR ||
        character_set_message(character, message) == ERROR ||
        game_add_character(game, character, location_id) == ERROR) {
      character_destroy(character);
      fclose(file);
      return ERROR;
    }
  }

  fclose(file);
  return OK;
}

Game* game_reader_create_from_file(char* filename) {
  Game* game = NULL;
  Id first_space_id = NO_ID;

  if (!filename) {
    return NULL;
  }

  game = game_create();
  if (!game) {
    return NULL;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  first_space_id = game_get_space_id_at(game, 0);
  if (first_space_id == NO_ID || game_set_player_location(game, first_space_id) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  if (game_reader_load_objects(game, filename) == ERROR ||
      game_reader_load_characters(game, filename) == ERROR) {
    game_destroy(game);
    return NULL;
  }

  return game;
}
