/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief It compares two names ignoring case
 * @author Iker Díaz
 *
 * @param first first string
 * @param second second string
 * @return TRUE if both names match, FALSE otherwise
 */
static Bool game_actions_name_equals(const char* first, const char* second);

/**
 * @brief It moves the player in the requested direction
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param direction movement direction
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_actions_move(Game* game, Direction direction);

/**
 * @brief It handles the exit command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_actions_exit(Game* game);

/**
 * @brief It handles the take command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param object_name requested object name
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_actions_take(Game* game, const char* object_name);

/**
 * @brief It handles the drop command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_actions_drop(Game* game);

/**
 * @brief It handles the attack command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_actions_attack(Game* game);

/**
 * @brief It handles the chat command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
static Status game_actions_chat(Game* game);

Status game_actions_update(Game* game, Command* command) {
  Status status = ERROR;

  if (!game || !command) {
    return ERROR;
  }

  game_set_last_command(game, command);
  game_clear_message(game);

  switch (command_get_code(command)) {
    case EXIT:
      status = game_actions_exit(game);
      break;

    case NEXT:
      status = game_actions_move(game, S);
      break;

    case BACK:
      status = game_actions_move(game, N);
      break;

    case LEFT:
      status = game_actions_move(game, W);
      break;

    case RIGHT:
      status = game_actions_move(game, E);
      break;

    case TAKE:
      status = game_actions_take(game, command_get_argument(command));
      break;

    case DROP:
      status = game_actions_drop(game);
      break;

    case ATTACK:
      status = game_actions_attack(game);
      break;

    case CHAT:
      status = game_actions_chat(game);
      break;

    case UNKNOWN:
    case NO_CMD:
    default:
      status = ERROR;
      break;
  }

  game_set_last_command_status(game, status);
  return status;
}

static Bool game_actions_name_equals(const char* first, const char* second) {
  if (!first || !second) {
    return FALSE;
  }

  while (*first != '\0' && *second != '\0') {
    if (tolower((unsigned char)*first) != tolower((unsigned char)*second)) {
      return FALSE;
    }
    first++;
    second++;
  }

  return (*first == '\0' && *second == '\0') ? TRUE : FALSE;
}

static Status game_actions_move(Game* game, Direction direction) {
  Space* current_space = NULL;
  Id current_space_id = NO_ID;
  Id destination_id = NO_ID;

  if (!game) {
    return ERROR;
  }

  current_space_id = game_get_player_location(game);
  current_space = game_get_space(game, current_space_id);
  if (!current_space) {
    return ERROR;
  }

  switch (direction) {
    case N:
      destination_id = space_get_north(current_space);
      break;
    case S:
      destination_id = space_get_south(current_space);
      break;
    case E:
      destination_id = space_get_east(current_space);
      break;
    case W:
      destination_id = space_get_west(current_space);
      break;
    default:
      return ERROR;
  }

  if (destination_id == NO_ID) {
    return ERROR;
  }

  return game_set_player_location(game, destination_id);
}

static Status game_actions_exit(Game* game) {
  if (!game) {
    return ERROR;
  }

  game_set_finished(game, TRUE);
  return OK;
}

static Status game_actions_take(Game* game, const char* object_name) {
  Player* player = NULL;
  Space* current_space = NULL;
  Object* object = NULL;
  Id current_space_id = NO_ID;
  Id object_id = NO_ID;
  int n_objects = 0;
  int i = 0;

  if (!game || !object_name || object_name[0] == '\0') {
    return ERROR;
  }

  player = game_get_player(game);
  if (!player || player_get_object(player) != NO_ID) {
    return ERROR;
  }

  current_space_id = game_get_player_location(game);
  current_space = game_get_space(game, current_space_id);
  if (!current_space) {
    return ERROR;
  }

  n_objects = game_get_n_objects(game);
  for (i = 0; i < n_objects; i++) {
    object_id = game_get_object_id_at(game, i);
    object = game_get_object_by_id(game, object_id);

    if (object && game_actions_name_equals(object_get_name(object), object_name) == TRUE) {
      if (space_has_object(current_space, object_id) == FALSE) {
        return ERROR;
      }

      if (game_set_object_location_by_id(game, object_id, NO_ID) == ERROR) {
        return ERROR;
      }

      return player_set_object(player, object_id);
    }
  }

  return ERROR;
}

static Status game_actions_drop(Game* game) {
  Player* player = NULL;
  Id current_space_id = NO_ID;
  Id object_id = NO_ID;

  if (!game) {
    return ERROR;
  }

  player = game_get_player(game);
  if (!player) {
    return ERROR;
  }

  object_id = player_get_object(player);
  if (object_id == NO_ID) {
    return ERROR;
  }

  current_space_id = game_get_player_location(game);
  if (game_set_object_location_by_id(game, object_id, current_space_id) == ERROR) {
    return ERROR;
  }

  return player_set_object(player, NO_ID);
}

static Status game_actions_attack(Game* game) {
  Player* player = NULL;
  Character* character = NULL;
  Space* space = NULL;
  Id character_id = NO_ID;
  Id current_space_id = NO_ID;
  int player_health = 0;
  int character_health = 0;
  int random_number = 0;

  if (!game) {
    return ERROR;
  }

  player = game_get_player(game);
  if (!player) {
    return ERROR;
  }

  current_space_id = game_get_player_location(game);
  space = game_get_space(game, current_space_id);
  if (!space) {
    return ERROR;
  }

  character_id = space_get_character(space);
  if (character_id == NO_ID) {
    return ERROR;
  }

  character = game_get_character(game, character_id);
  if (!character || character_get_friendly(character) == TRUE) {
    return ERROR;
  }

  player_health = player_get_health(player);
  character_health = character_get_health(character);
  if (player_health <= 0 || character_health <= 0) {
    return ERROR;
  }

  random_number = rand() % 10;
  if (random_number <= 4) {
    player_health--;
    if (player_set_health(player, player_health) == ERROR) {
      return ERROR;
    }
    if (player_health == 0) {
      game_set_finished(game, TRUE);
    }
  } else {
    character_health--;
    if (character_set_health(character, character_health) == ERROR) {
      return ERROR;
    }
  }

  return OK;
}

static Status game_actions_chat(Game* game) {
  Character* character = NULL;
  Space* space = NULL;
  Id current_space_id = NO_ID;
  Id character_id = NO_ID;

  if (!game) {
    return ERROR;
  }

  current_space_id = game_get_player_location(game);
  space = game_get_space(game, current_space_id);
  if (!space) {
    return ERROR;
  }

  character_id = space_get_character(space);
  if (character_id == NO_ID) {
    return ERROR;
  }

  character = game_get_character(game, character_id);
  if (!character || character_get_friendly(character) == FALSE) {
    return ERROR;
  }

  return game_set_message(game, character_get_message(character));
}
