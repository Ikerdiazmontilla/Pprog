/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

/**
 * @brief Maximum number of spaces in the game
 * @author Profesores PPROG
 */
#define MAX_SPACES 100

typedef struct _Game {
  Player* player;            /*!< Game player */
  Object* object;            /*!< Game object */
  Space* spaces[MAX_SPACES]; /*!< Space list */
  int n_spaces;              /*!< Number of loaded spaces */
  Command* last_cmd;         /*!< Last command introduced by the user */
  Bool finished;             /*!< Whether the game is finished */
} Game;

/**
 * @brief It creates a new game, initializing its members
 * @author Profesores PPROG
 *
 * @param game a pointer to the game to initialize
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_create(Game* game);

/**
 * @brief It destroys a game, freeing all allocated resources
 * @author Profesores PPROG
 *
 * @param game a pointer to the game to destroy
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_destroy(Game* game);

/**
 * @brief It returns a pointer to the space with the given id
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id space id
 * @return a pointer to the space, or NULL if it does not exist
 */
Space* game_get_space(Game* game, Id id);

/**
 * @brief It gets the player's current location
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return the id of the current space, or NO_ID on error
 */
Id game_get_player_location(Game* game);

/**
 * @brief It sets the player's location
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of the space where the player is
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_player_location(Game* game, Id id);

/**
 * @brief It gets the current location of the object
 * @author Profesores PPROG
 *
 * If the player carries the object, its location is the player's location.
 *
 * @param game a pointer to the game
 * @return the id of the space where the object is, or NO_ID if not found
 */
Id game_get_object_location(Game* game);

/**
 * @brief It places the object in the given space
 * @author Profesores PPROG
 *
 * This function removes the object from the player and from any space before placing it.
 *
 * @param game a pointer to the game
 * @param id the id of the space where the object will be placed
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_object_location(Game* game, Id id);

/**
 * @brief It returns the game player
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return a pointer to the player, or NULL on error
 */
Player* game_get_player(Game* game);

/**
 * @brief It returns the game object
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return a pointer to the object, or NULL on error
 */
Object* game_get_object(Game* game);

/**
 * @brief It gets the last command
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return a pointer to the last command, or NULL on error
 */
Command* game_get_last_command(Game* game);

/**
 * @brief It sets the last command
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param command a pointer to the command
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_last_command(Game* game, Command* command);

/**
 * @brief It gets whether the game is finished
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return TRUE if finished, FALSE otherwise
 */
Bool game_get_finished(Game* game);

/**
 * @brief It sets whether the game is finished
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param finished finished flag
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_finished(Game* game, Bool finished);

/**
 * @brief It prints the game information (for debugging)
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 */
void game_print(Game* game);

/**
 * @brief It returns the id of the space at a given position
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param position index in the space list
 * @return the space id, or NO_ID if out of range
 */
Id game_get_space_id_at(Game* game, int position);

/**
 * @brief It adds a space to the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param space a pointer to the space to add
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_add_space(Game* game, Space* space);

#endif
