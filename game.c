/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Game data
 * @author Iker Díaz
 *
 * This struct stores all entities and runtime state of the game.
 */
struct _Game {
  Player* player;                         /*!< Game player */
  Space* spaces[MAX_SPACES];              /*!< Space list */
  int n_spaces;                           /*!< Number of loaded spaces */
  Object* objects[MAX_OBJECTS];           /*!< Object list */
  Id object_locations[MAX_OBJECTS];       /*!< Cached object locations */
  int n_objects;                          /*!< Number of loaded objects */
  Character* characters[MAX_CHARACTERS];  /*!< Character list */
  int n_characters;                       /*!< Number of loaded characters */
  Command* last_cmd;                      /*!< Last command introduced by the user */
  Status last_cmd_status;                 /*!< Result of the last executed command */
  char message[GAME_MESSAGE_SIZE + 1];    /*!< Informational message for the interface */
  Bool finished;                          /*!< Whether the game is finished */
};

/**
 * @brief It gets the index of an object in the object array
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param object_id object id to locate
 * @return object index, or -1 if not found
 */
static int game_get_object_index(Game* game, Id object_id);

/**
 * @brief It gets the index of a character in the character array
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param character_id character id to locate
 * @return character index, or -1 if not found
 */
static int game_get_character_index(Game* game, Id character_id);

Game* game_create(void) {
  Game* game = NULL;
  int i = 0;

  game = (Game*)calloc(1, sizeof(Game));
  if (!game) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  for (i = 0; i < MAX_OBJECTS; i++) {
    game->objects[i] = NULL;
    game->object_locations[i] = NO_ID;
  }
  for (i = 0; i < MAX_CHARACTERS; i++) {
    game->characters[i] = NULL;
  }

  game->player = player_create(PLAYER_ID);
  if (!game->player) {
    free(game);
    return NULL;
  }

  if (player_set_name(game->player, "Knight") == ERROR ||
      player_set_health(game->player, PLAYER_INITIAL_HEALTH) == ERROR ||
      player_set_gdesc(game->player, PLAYER_INITIAL_GDESC) == ERROR) {
    player_destroy(game->player);
    free(game);
    return NULL;
  }

  game->last_cmd = command_create();
  if (!game->last_cmd) {
    player_destroy(game->player);
    free(game);
    return NULL;
  }

  game->n_spaces = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->last_cmd_status = OK;
  game->message[0] = '\0';
  game->finished = FALSE;

  return game;
}

Status game_destroy(Game* game) {
  int i = 0;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; i < game->n_objects; i++) {
    object_destroy(game->objects[i]);
  }

  for (i = 0; i < game->n_characters; i++) {
    character_destroy(game->characters[i]);
  }

  command_destroy(game->last_cmd);
  player_destroy(game->player);
  free(game);

  return OK;
}

Status game_add_space(Game* game, Space* space) {
  if (!game || !space || game->n_spaces >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;
  return OK;
}

Space* game_get_space(Game* game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_id(game->spaces[i]) == id) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_space_id_at(Game* game, int position) {
  if (!game || position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Id game_get_player_location(Game* game) {
  if (!game || !game->player) {
    return NO_ID;
  }

  return player_get_location(game->player);
}

Status game_set_player_location(Game* game, Id id) {
  if (!game || !game->player || !game_get_space(game, id)) {
    return ERROR;
  }

  return player_set_location(game->player, id);
}

Player* game_get_player(Game* game) {
  if (!game) {
    return NULL;
  }

  return game->player;
}

Status game_add_object(Game* game, Object* object, Id location_id) {
  int index = 0;
  Space* space = NULL;
  Id object_id = NO_ID;

  if (!game || !object || location_id == NO_ID || game->n_objects >= MAX_OBJECTS) {
    return ERROR;
  }

  object_id = object_get_id(object);
  if (object_id == NO_ID || game_get_object_by_id(game, object_id) != NULL) {
    return ERROR;
  }

  space = game_get_space(game, location_id);
  if (!space) {
    return ERROR;
  }

  index = game->n_objects;
  game->objects[index] = object;
  game->object_locations[index] = location_id;
  game->n_objects++;

  return space_add_object(space, object_id);
}

Object* game_get_object(Game* game) {
  if (!game || game->n_objects <= 0) {
    return NULL;
  }

  return game->objects[0];
}

Object* game_get_object_by_id(Game* game, Id id) {
  int index = -1;

  if (!game || id == NO_ID) {
    return NULL;
  }

  index = game_get_object_index(game, id);
  if (index < 0) {
    return NULL;
  }

  return game->objects[index];
}

Id game_get_object_location(Game* game) {
  Object* object = NULL;

  object = game_get_object(game);
  if (!object) {
    return NO_ID;
  }

  return game_get_object_location_by_id(game, object_get_id(object));
}

Id game_get_object_location_by_id(Game* game, Id object_id) {
  int index = -1;

  if (!game || object_id == NO_ID) {
    return NO_ID;
  }

  if (game->player && player_get_object(game->player) == object_id) {
    return NO_ID;
  }

  index = game_get_object_index(game, object_id);
  if (index < 0) {
    return NO_ID;
  }

  return game->object_locations[index];
}

Status game_set_object_location(Game* game, Id id) {
  Object* object = NULL;

  object = game_get_object(game);
  if (!object) {
    return ERROR;
  }

  return game_set_object_location_by_id(game, object_get_id(object), id);
}

Status game_set_object_location_by_id(Game* game, Id object_id, Id id) {
  int i = 0;
  int index = -1;
  Space* destination = NULL;

  if (!game || object_id == NO_ID) {
    return ERROR;
  }

  index = game_get_object_index(game, object_id);
  if (index < 0) {
    return ERROR;
  }

  if (id != NO_ID) {
    destination = game_get_space(game, id);
    if (!destination) {
      return ERROR;
    }
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_has_object(game->spaces[i], object_id) == TRUE) {
      space_remove_object(game->spaces[i], object_id);
      break;
    }
  }

  if (id != NO_ID) {
    if (space_add_object(destination, object_id) == ERROR) {
      return ERROR;
    }
  }

  game->object_locations[index] = id;
  return OK;
}

Id game_get_object_id_at(Game* game, int position) {
  if (!game || position < 0 || position >= game->n_objects) {
    return NO_ID;
  }

  return object_get_id(game->objects[position]);
}

int game_get_n_objects(Game* game) {
  if (!game) {
    return -1;
  }

  return game->n_objects;
}

Status game_add_character(Game* game, Character* character, Id location_id) {
  Space* space = NULL;
  Id character_id = NO_ID;

  if (!game || !character || location_id == NO_ID || game->n_characters >= MAX_CHARACTERS) {
    return ERROR;
  }

  character_id = character_get_id(character);
  if (character_id == NO_ID || game_get_character(game, character_id) != NULL) {
    return ERROR;
  }

  space = game_get_space(game, location_id);
  if (!space || space_get_character(space) != NO_ID) {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

  return space_set_character(space, character_id);
}

Character* game_get_character(Game* game, Id id) {
  int index = -1;

  if (!game || id == NO_ID) {
    return NULL;
  }

  index = game_get_character_index(game, id);
  if (index < 0) {
    return NULL;
  }

  return game->characters[index];
}

Id game_get_character_location(Game* game, Id character_id) {
  int i = 0;

  if (!game || character_id == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_character(game->spaces[i]) == character_id) {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

Status game_set_character_location(Game* game, Id character_id, Id location_id) {
  int i = 0;
  Space* destination = NULL;

  if (!game || character_id == NO_ID || location_id == NO_ID) {
    return ERROR;
  }

  if (!game_get_character(game, character_id)) {
    return ERROR;
  }

  destination = game_get_space(game, location_id);
  if (!destination || space_get_character(destination) != NO_ID) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_character(game->spaces[i]) == character_id) {
      space_set_character(game->spaces[i], NO_ID);
      break;
    }
  }

  return space_set_character(destination, character_id);
}

Id game_get_character_id_at(Game* game, int position) {
  if (!game || position < 0 || position >= game->n_characters) {
    return NO_ID;
  }

  return character_get_id(game->characters[position]);
}

int game_get_n_characters(Game* game) {
  if (!game) {
    return -1;
  }

  return game->n_characters;
}

Command* game_get_last_command(Game* game) {
  if (!game) {
    return NULL;
  }

  return game->last_cmd;
}

Status game_set_last_command(Game* game, Command* command) {
  if (!game || !command || !game->last_cmd) {
    return ERROR;
  }

  if (command_set_code(game->last_cmd, command_get_code(command)) == ERROR) {
    return ERROR;
  }

  if (command_set_argument(game->last_cmd, command_get_argument(command)) == ERROR) {
    return ERROR;
  }

  return OK;
}

Status game_get_last_command_status(Game* game) {
  if (!game) {
    return ERROR;
  }

  return game->last_cmd_status;
}

Status game_set_last_command_status(Game* game, Status status) {
  if (!game) {
    return ERROR;
  }

  game->last_cmd_status = status;
  return OK;
}

const char* game_get_message(Game* game) {
  if (!game) {
    return NULL;
  }

  return game->message;
}

Status game_set_message(Game* game, const char* message) {
  if (!game || !message) {
    return ERROR;
  }

  strncpy(game->message, message, GAME_MESSAGE_SIZE);
  game->message[GAME_MESSAGE_SIZE] = '\0';
  return OK;
}

Status game_clear_message(Game* game) {
  if (!game) {
    return ERROR;
  }

  game->message[0] = '\0';
  return OK;
}

Bool game_get_finished(Game* game) {
  if (!game) {
    return TRUE;
  }

  return game->finished;
}

Status game_set_finished(Game* game, Bool finished) {
  if (!game) {
    return ERROR;
  }

  game->finished = finished;
  return OK;
}

void game_print(Game* game) {
  int i = 0;

  if (!game) {
    return;
  }

  fprintf(stdout, "\n\n-------------\n\n");
  fprintf(stdout, "=> Spaces:\n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  fprintf(stdout, "=> Objects:\n");
  for (i = 0; i < game->n_objects; i++) {
    object_print(game->objects[i]);
    fprintf(stdout, "---> Location: %ld\n",
            game_get_object_location_by_id(game, object_get_id(game->objects[i])));
  }

  fprintf(stdout, "=> Characters:\n");
  for (i = 0; i < game->n_characters; i++) {
    character_print(game->characters[i]);
    fprintf(stdout, "---> Location: %ld\n",
            game_get_character_location(game, character_get_id(game->characters[i])));
  }

  fprintf(stdout, "=> Player:\n");
  player_print(game->player);
}

static int game_get_object_index(Game* game, Id object_id) {
  int i = 0;

  if (!game || object_id == NO_ID) {
    return -1;
  }

  for (i = 0; i < game->n_objects; i++) {
    if (object_get_id(game->objects[i]) == object_id) {
      return i;
    }
  }

  return -1;
}

static int game_get_character_index(Game* game, Id character_id) {
  int i = 0;

  if (!game || character_id == NO_ID) {
    return -1;
  }

  for (i = 0; i < game->n_characters; i++) {
    if (character_get_id(game->characters[i]) == character_id) {
      return i;
    }
  }

  return -1;
}
