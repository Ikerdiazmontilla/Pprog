/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Iker Díaz
 * @version 0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief It gets the index of an object in the game object array
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param object_id object id to locate
 * @return object index, or -1 if not found
 */
static int game_get_object_index(Game* game, Id object_id);

/**
 * @brief It gets the index of a character in the game character array
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param character_id character id to locate
 * @return character index, or -1 if not found
 */
static int game_get_character_index(Game* game, Id character_id);

Status game_create(Game* game) {
  int i;

  if (!game) {
    return ERROR;
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

  game->n_spaces = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->player = NULL;
  game->last_cmd = command_create();
  if (!game->last_cmd) {
    return ERROR;
  }

  game->player = player_create(1);
  if (!game->player) {
    command_destroy(game->last_cmd);
    game->last_cmd = NULL;
    return ERROR;
  }

  if (player_set_name(game->player, "Knight") == ERROR ||
      player_set_health(game->player, 5) == ERROR ||
      player_set_gdesc(game->player, "^C>") == ERROR) {
    player_destroy(game->player);
    game->player = NULL;
    command_destroy(game->last_cmd);
    game->last_cmd = NULL;
    return ERROR;
  }

  game->finished = FALSE;

  return OK;
}

Status game_destroy(Game* game) {
  int i = 0;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }
  game->n_spaces = 0;

  for (i = 0; i < game->n_objects; i++) {
    object_destroy(game->objects[i]);
    game->objects[i] = NULL;
    game->object_locations[i] = NO_ID;
  }
  game->n_objects = 0;

  for (i = 0; i < game->n_characters; i++) {
    character_destroy(game->characters[i]);
    game->characters[i] = NULL;
  }
  game->n_characters = 0;

  command_destroy(game->last_cmd);
  game->last_cmd = NULL;

  player_destroy(game->player);
  game->player = NULL;

  return OK;
}

Space* game_get_space(Game* game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Status game_add_space(Game* game, Space* space) {
  if (!game || !space || game->n_spaces >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game* game, int position) {
  if (!game || position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Player* game_get_player(Game* game) {
  if (!game) {
    return NULL;
  }

  return game->player;
}

Id game_get_player_location(Game* game) {
  if (!game || !game->player) {
    return NO_ID;
  }

  return player_get_location(game->player);
}

Status game_set_player_location(Game* game, Id id) {
  if (!game || !game->player || id == NO_ID) {
    return ERROR;
  }

  if (!game_get_space(game, id)) {
    return ERROR;
  }

  return player_set_location(game->player, id);
}

Object* game_get_object(Game* game) {
  if (!game || game->n_objects <= 0) {
    return NULL;
  }

  return game->objects[0];
}

Status game_add_object(Game* game, Object* object, Id location_id) {
  Id object_id = NO_ID;
  Space* space = NULL;

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

  game->objects[game->n_objects] = object;
  game->object_locations[game->n_objects] = location_id;
  game->n_objects++;

  if (space_get_object(space) == NO_ID) {
    space_set_object(space, object_id);
  }

  return OK;
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

Id game_get_object_location_by_id(Game* game, Id object_id) {
  int i = 0;
  int index = -1;

  if (!game || object_id == NO_ID) {
    return NO_ID;
  }

  index = game_get_object_index(game, object_id);
  if (index < 0) {
    return NO_ID;
  }

  if (game->player && player_get_object(game->player) == object_id) {
    return player_get_location(game->player);
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_object(game->spaces[i]) == object_id) {
      return space_get_id(game->spaces[i]);
    }
  }

  return game->object_locations[index];
}

Id game_get_object_location(Game* game) {
  Id object_id = NO_ID;

  if (!game || game->n_objects <= 0) {
    return NO_ID;
  }

  object_id = object_get_id(game->objects[0]);
  return game_get_object_location_by_id(game, object_id);
}

Status game_set_object_location_by_id(Game* game, Id object_id, Id id) {
  int i = 0;
  int index = -1;
  Space* space = NULL;

  if (!game || object_id == NO_ID || id == NO_ID) {
    return ERROR;
  }

  index = game_get_object_index(game, object_id);
  if (index < 0) {
    return ERROR;
  }

  space = game_get_space(game, id);
  if (!space) {
    return ERROR;
  }

  if (game->player && player_get_object(game->player) == object_id) {
    player_set_object(game->player, NO_ID);
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_object(game->spaces[i]) == object_id) {
      space_set_object(game->spaces[i], NO_ID);
    }
  }

  game->object_locations[index] = id;
  if (space_get_object(space) == NO_ID) {
    space_set_object(space, object_id);
  }

  return OK;
}

Status game_set_object_location(Game* game, Id id) {
  Id object_id = NO_ID;

  if (!game || game->n_objects <= 0) {
    return ERROR;
  }

  object_id = object_get_id(game->objects[0]);
  return game_set_object_location_by_id(game, object_id, id);
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

Status game_add_character(Game* game, Character* character) {
  Id character_id = NO_ID;

  if (!game || !character || game->n_characters >= MAX_CHARACTERS) {
    return ERROR;
  }

  character_id = character_get_id(character);
  if (character_id == NO_ID || game_get_character(game, character_id) != NULL) {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

  return OK;
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
  if (!game || !command) {
    return ERROR;
  }

  game->last_cmd = command;

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

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Objects: \n");
  for (i = 0; i < game->n_objects; i++) {
    printf("---> Object id %ld location %ld\n", object_get_id(game->objects[i]),
           game_get_object_location_by_id(game, object_get_id(game->objects[i])));
  }

  printf("=> Characters: %d\n", game->n_characters);
  printf("=> Player location: %ld\n", game_get_player_location(game));
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
