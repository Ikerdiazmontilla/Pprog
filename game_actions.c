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
#include <time.h>
#include <stdlib.h>
#include <string.h>



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
 * @brief It handles the next command (move west)
 * @author Fernando Pina
 *
 * @param game a pointer to the game
 */
static void game_actions_left(Game* game);

/**
 * @brief It handles the next command (move east)
 * @author Fernando Pina
 *
 * @param game a pointer to the game
 */
static void game_actions_right(Game* game);


/**
 * @brief It handles the drop command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_drop(Game* game);

/**
 * @brief It handles the drop command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_attack(Game* game);

/**
 * @brief It handles the drop command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_take_sword(Game* game);
/**
 * @brief It handles the drop command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_take_candelabra(Game* game);
/**
 * @brief It handles the drop command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_take_tapestry(Game* game);
/**
 * @brief It handles the drop command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
static void game_actions_take_parchment(Game* game);


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

    case LEFT:
      game_actions_left(game);
      break;

    case RIGHT:
      game_actions_right(game);
      break;

    case DROP:
      game_actions_drop(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;

    case TAKE_SWORD:
      game_actions_attack(game);
      break;

    case TAKE_CANDELABRA:
    game_actions_attack(game);
    break;

    case TAKE_TAPESTRY:
    game_actions_attack(game);
    break;

    case TAKE_PARCHMENT:
    game_actions_attack(game);
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

static void game_actions_left(Game* game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

static void game_actions_right(Game* game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
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

  space_set_object(space, player_object);
  player_set_object(player, NO_ID);
}


static void game_actions_attack(Game* game){
  
  Player* player = NULL;
  Space* space = NULL;
  Character* character = NULL;
  Id space_id = NO_ID;
  Id character_id = NO_ID;
  int player_health = 0;
  int character_health = 0;
  int random_number = 0;

  if (!game) {
    
    return;
  }
  
  player = game_get_player(game);
  if (!player) {
    return;
  }

  space_id = game_get_player_location(game);
  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }
  character_id = space_get_character(space);
  if (character_id == NO_ID)
  {
    return;  //solo hay un jugador, no puedes atacara la nada
  }
  
  character = game_get_character(game,character_id);
  if (!character)
  {
    return;
  }

  if (character_get_friendly(character) == TRUE)
  {
    return;
  }
  
  
  player_health = player_get_health(player);
  
  if (player_health == 0)
  {
    return;
  }
  character_health = character_get_health(character);
  
  if (character_health == 0)
  {
    return;
  
  }
  random_number = (rand()%10);

  if (random_number >= 0 && random_number <= 4)
  {
    player_health--;
    player_set_health(player,player_health);
    if (player_health == 0)
    {
      game_actions_exit(game);
    }
      
  }else
  {
    character_health--;
    character_set_health(character,character_health);
  }

  return;
}

static void game_actions_chat(Game* game) {
  Player* player = NULL;
  Space* space = NULL;
  Character* character = NULL;
  Id character_id = NO_ID;
  Id space_id = NO_ID;
  char* message;

  if (!game) {
    return;
  }

  player = game_get_player(game);
  if (!player) {
    return;
  }

  space_id = game_get_player_location(game);
  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

    character_id = space_get_character(space);
  if (character_id == NO_ID)
  {
    return;  //solo hay un jugador, no puedes atacara la nada
  }
  
  character = game_get_character(game,character_id);
  if (!character)
  {
    return;
  }

  if (character_get_friendly(character) == FALSE)
  {
    return;
  }

  message = "Hola!! me alegro de verte";
  character_set_message(character, message);

  return;
}

static void game_actions_take_sword(Game* game)
{

  Player* player = NULL;
  Space* space = NULL;
  Object* object = NULL;
  Id space_id = NO_ID;
  Id buffer = NO_ID;
  int n_objects = 0;

  

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
  
  space_id = game_get_player_location(game);
  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

  n_objects = game_get_n_objects(game);

  if (n_objects == 0)
  {
    return;
  }
  
  for (int i = 0; i < n_objects; i++)
  {
    buffer = game_get_object_id_at(game, i);
    if (buffer == NO_ID)
    {
      return;
    }
    
    object = game_get_object_by_id(game,buffer);
    if (!object)
    {
      return;
    }
    
    if ((strcmp(object_get_name(object), "Sword")) == 0)
    {
      if (space_find_object_id(space,buffer) == FALSE)
      {
        return;
      }

      player_set_object(player, buffer);
      space_del_object(space, buffer);
      
    }
    
  }
  
  return;  

}

static void game_actions_take_candelabra(Game* game)
{

  Player* player = NULL;
  Space* space = NULL;
  Object* object = NULL;
  Id space_id = NO_ID;
  Id buffer = NO_ID;
  int n_objects = 0;

  

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
  
  space_id = game_get_player_location(game);
  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

  n_objects = game_get_n_objects(game);

  if (n_objects == 0)
  {
    return;
  }
  
  for (int i = 0; i < n_objects; i++)
  {
    buffer = game_get_object_id_at(game, i);
    if (buffer == NO_ID)
    {
      return;
    }
    
    object = game_get_object_by_id(game,buffer);
    if (!object)
    {
      return;
    }
    
    if ((strcmp(object_get_name(object), "Candelabra")) == 0)
    {
      if (space_find_object_id(space,buffer) == FALSE)
      {
        return;
      }

      player_set_object(player, buffer);
      space_del_object(space, buffer);
      
    }
    
  }
  
  return;  

}

static void game_actions_take_tapestry(Game* game)
{

  Player* player = NULL;
  Space* space = NULL;
  Object* object = NULL;
  Id space_id = NO_ID;
  Id buffer = NO_ID;
  int n_objects = 0;

  

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
  
  space_id = game_get_player_location(game);
  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

  n_objects = game_get_n_objects(game);

  if (n_objects == 0)
  {
    return;
  }
  
  for (int i = 0; i < n_objects; i++)
  {
    buffer = game_get_object_id_at(game, i);
    if (buffer == NO_ID)
    {
      return;
    }
    
    object = game_get_object_by_id(game,buffer);
    if (!object)
    {
      return;
    }
    
    if ((strcmp(object_get_name(object), "Tapestry")) == 0)
    {
      if (space_find_object_id(space,buffer) == FALSE)
      {
        return;
      }

      player_set_object(player, buffer);
      space_del_object(space, buffer);
      
    }
    
  }
  
  return;  

}

static void game_actions_take_parchment(Game* game)
{

  Player* player = NULL;
  Space* space = NULL;
  Object* object = NULL;
  Id space_id = NO_ID;
  Id buffer = NO_ID;
  int n_objects = 0;

  

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
  
  space_id = game_get_player_location(game);
  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

  n_objects = game_get_n_objects(game);

  if (n_objects == 0)
  {
    return;
  }
  
  for (int i = 0; i < n_objects; i++)
  {
    buffer = game_get_object_id_at(game, i);
    if (buffer == NO_ID)
    {
      return;
    }
    
    object = game_get_object_by_id(game,buffer);
    if (!object)
    {
      return;
    }
    
    if ((strcmp(object_get_name(object), "Parchment")) == 0)
    {
      if (space_find_object_id(space,buffer) == FALSE)
      {
        return;
      }

      player_set_object(player, buffer);
      space_del_object(space, buffer);
      
    }
    
  }
  
  return;  

}