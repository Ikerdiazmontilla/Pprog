/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Iker Díaz
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _Game {
  Player* player;            /*!< Game player */
  Object* object;            /*!< Game object */
  Space* spaces[MAX_SPACES]; /*!< Space list */
  int n_spaces;              /*!< Number of loaded spaces */
  Command* last_cmd;         /*!< Last command introduced by the user */
  Bool finished;             /*!< Whether the game is finished */
} Game;


/**
   Private functions
*/

/**
   Game interface implementation
*/

Status game_create(Game *game) {
  int i;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player = NULL;
  game->object = NULL;
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
  player_set_name(game->player, "Knight");

  game->object = object_create(1);
  if (!game->object) {
    player_destroy(game->player);
    game->player = NULL;
    command_destroy(game->last_cmd);
    game->last_cmd = NULL;
    return ERROR;
  }
  object_set_name(game->object, "Sword");

  game->finished = FALSE;

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }
  game->n_spaces = 0;

  command_destroy(game->last_cmd);
  game->last_cmd = NULL;

  player_destroy(game->player);
  game->player = NULL;

  object_destroy(game->object);
  game->object = NULL;

  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (!game) {
    return NULL;
  }

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Player* game_get_player(Game* game) {
  if (!game) {
    return NULL;
  }
  return game->player;
}

Object* game_get_object(Game* game) {
  if (!game) {
    return NULL;
  }
  return game->object;
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

Id game_get_object_location(Game* game) {
  int i = 0;
  Id object_id = NO_ID;

  if (!game || !game->object) {
    return NO_ID;
  }

  object_id = object_get_id(game->object);

  /* If the player carries the object, its location is the player's location */
  if (game->player && player_get_object(game->player) == object_id) {
    return player_get_location(game->player);
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_object(game->spaces[i]) == object_id) {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

Status game_set_object_location(Game* game, Id id) {
  int i = 0;
  Space* space = NULL;
  Id object_id = NO_ID;

  if (!game || !game->object || id == NO_ID) {
    return ERROR;
  }

  space = game_get_space(game, id);
  if (!space) {
    return ERROR;
  }

  object_id = object_get_id(game->object);

  /* Remove the object from everywhere (spaces and player) */
  if (game->player) {
    player_set_object(game->player, NO_ID);
  }
  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_object(game->spaces[i]) == object_id) {
      space_set_object(game->spaces[i], NO_ID);
    }
  }

  return space_set_object(space, object_id);
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %ld\n", game_get_object_location(game));
  printf("=> Player location: %ld\n", game_get_player_location(game));
}

Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

