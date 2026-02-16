/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Iker Díaz
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stddef.h>

/**
   Private functions
*/

/**
 * @brief It handles an unknown command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_unknown(Game* game);

/**
 * @brief It handles the exit command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_exit(Game* game);

/**
 * @brief It handles the next command (move south)
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_next(Game* game);

/**
 * @brief It handles the back command (move north)
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_back(Game* game);

/**
 * @brief It handles the take command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_take(Game* game);

/**
 * @brief It handles the drop command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_drop(Game* game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;

    case TAKE:
      game_actions_take(game);
      break;

    case DROP:
      game_actions_drop(game);
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

static void game_actions_unknown(Game* game) {
  (void)game;
}

static void game_actions_exit(Game* game) {
  if (!game) {
    return;
  }

  game_set_finished(game, TRUE);
}

static void game_actions_next(Game* game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

static void game_actions_back(Game* game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

static void game_actions_take(Game* game) {
  Player* player = NULL;
  Space* space = NULL;
  Id space_id = NO_ID;
  Id space_object = NO_ID;
  Id object_id = NO_ID;

  if (!game) {
    return;
  }

  player = game_get_player(game);
  if (!player) {
    return;
  }

  if (player_get_object(player) != NO_ID) {
    return;
  }

  object_id = object_get_id(game_get_object(game));
  if (object_id == NO_ID) {
    return;
  }

  space_id = game_get_player_location(game);
  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

  space_object = space_get_object(space);
  if (space_object != object_id) {
    return;
  }

  player_set_object(player, object_id);
  space_set_object(space, NO_ID);
}

static void game_actions_drop(Game* game) {
  Player* player = NULL;
  Space* space = NULL;
  Id space_id = NO_ID;
  Id player_object = NO_ID;

  if (!game) {
    return;
  }

  player = game_get_player(game);
  if (!player) {
    return;
  }

  player_object = player_get_object(player);
  if (player_object == NO_ID) {
    return;
  }

  space_id = game_get_player_location(game);
  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

  if (space_get_object(space) != NO_ID) {
    return;
  }

  space_set_object(space, player_object);
  player_set_object(player, NO_ID);
}
