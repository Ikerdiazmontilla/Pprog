/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "command.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

/**
 * @brief Maximum number of spaces in the game
 * @author Iker Díaz
 */
#define MAX_SPACES 100

/**
 * @brief Maximum number of objects in the game
 * @author Iker Díaz
 */
#define MAX_OBJECTS 100

/**
 * @brief Maximum number of characters in the game
 * @author Iker Díaz
 */
#define MAX_CHARACTERS 20

/**
 * @brief Maximum length for informational messages shown by the interface
 * @author Iker Díaz
 */
#define GAME_MESSAGE_SIZE 256

/**
 * @brief Default player id
 * @author Iker Díaz
 */
#define PLAYER_ID 1

/**
 * @brief Default player health
 * @author Iker Díaz
 */
#define PLAYER_INITIAL_HEALTH 5

/**
 * @brief Default player graphic description
 * @author Iker Díaz
 */
#define PLAYER_INITIAL_GDESC "^C>"

typedef struct _Game Game;

/**
 * @brief It creates a new game, allocating memory and initializing its members
 * @author Iker Díaz
 *
 * @return a new game initialized, or NULL on error
 */
Game* game_create(void);

/**
 * @brief It destroys a game, freeing all allocated resources
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_destroy(Game* game);

/**
 * @brief It adds a space to the game
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param space a pointer to the space to add
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_add_space(Game* game, Space* space);

/**
 * @brief It returns a pointer to the space with the given id
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param id space id
 * @return a pointer to the space, or NULL if it does not exist
 */
Space* game_get_space(Game* game, Id id);

/**
 * @brief It returns the id of the space at a given position
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param position index in the space list
 * @return the space id, or NO_ID if out of range
 */
Id game_get_space_id_at(Game* game, int position);

/**
 * @brief It gets the player's current location
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return the id of the current space, or NO_ID on error
 */
Id game_get_player_location(Game* game);

/**
 * @brief It sets the player's location
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param id the id of the space where the player is
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_player_location(Game* game, Id id);

/**
 * @brief It returns the game player
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return a pointer to the player, or NULL on error
 */
Player* game_get_player(Game* game);

/**
 * @brief It adds an object to the game
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param object a pointer to the object to add
 * @param location_id the id of the initial space for the object
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_add_object(Game* game, Object* object, Id location_id);

/**
 * @brief It returns the first loaded object
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return a pointer to the object, or NULL on error
 */
Object* game_get_object(Game* game);

/**
 * @brief It gets an object from the game by id
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param id object id
 * @return a pointer to the object, or NULL if it does not exist
 */
Object* game_get_object_by_id(Game* game, Id id);

/**
 * @brief It gets the current location of the first loaded object
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return the id of the space where the object is, or NO_ID if it is carried or not found
 */
Id game_get_object_location(Game* game);

/**
 * @brief It gets the current location of an object by id
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param object_id object id
 * @return the id of the space where the object is, or NO_ID if it is carried or on error
 */
Id game_get_object_location_by_id(Game* game, Id object_id);

/**
 * @brief It sets the location of the first loaded object
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param id the destination space id, or NO_ID if the player carries it
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_object_location(Game* game, Id id);

/**
 * @brief It sets the location of an object by id
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param object_id object id
 * @param id the destination space id, or NO_ID if the player carries it
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_object_location_by_id(Game* game, Id object_id, Id id);

/**
 * @brief It returns the id of the object at a given position
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param position index in the object list
 * @return the object id, or NO_ID if out of range
 */
Id game_get_object_id_at(Game* game, int position);

/**
 * @brief It gets the number of objects in the game
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return number of objects, or -1 on error
 */
int game_get_n_objects(Game* game);

/**
 * @brief It adds a character to the game and places it in a space
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param character a pointer to the character to add
 * @param location_id initial space id for the character
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_add_character(Game* game, Character* character, Id location_id);

/**
 * @brief It gets a character from the game by id
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param id character id
 * @return a pointer to the character, or NULL if it does not exist
 */
Character* game_get_character(Game* game, Id id);

/**
 * @brief It gets the current location of a character by id
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param character_id character id
 * @return the id of the space where the character is, or NO_ID on error
 */
Id game_get_character_location(Game* game, Id character_id);

/**
 * @brief It sets the location of a character by id
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param character_id character id
 * @param location_id destination space id
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_character_location(Game* game, Id character_id, Id location_id);

/**
 * @brief It returns the id of the character at a given position
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param position index in the character list
 * @return the character id, or NO_ID if out of range
 */
Id game_get_character_id_at(Game* game, int position);

/**
 * @brief It gets the number of characters in the game
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return number of characters, or -1 on error
 */
int game_get_n_characters(Game* game);

/**
 * @brief It gets the last command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return a pointer to the last command, or NULL on error
 */
Command* game_get_last_command(Game* game);

/**
 * @brief It updates the stored last command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param command a pointer to the command
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_last_command(Game* game, Command* command);

/**
 * @brief It gets whether the last executed command succeeded
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return OK or ERROR depending on the last command result
 */
Status game_get_last_command_status(Game* game);

/**
 * @brief It sets whether the last executed command succeeded
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param status command result status
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_last_command_status(Game* game, Status status);

/**
 * @brief It gets the informational message shown in the interface
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return the stored message, or NULL on error
 */
const char* game_get_message(Game* game);

/**
 * @brief It sets the informational message shown in the interface
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param message string to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_message(Game* game, const char* message);

/**
 * @brief It clears the informational message shown in the interface
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_clear_message(Game* game);

/**
 * @brief It gets whether the game is finished
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @return TRUE if finished, FALSE otherwise
 */
Bool game_get_finished(Game* game);

/**
 * @brief It sets whether the game is finished
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param finished finished flag
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_finished(Game* game, Bool finished);

/**
 * @brief It prints the game information for debugging
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 */
void game_print(Game* game);

#endif
