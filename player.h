/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Fernando Pina
 * @version 0
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Fernando Pina
 *
 * @param id the identification number for the new player
 * @return a new player, initialized
 */
Player* player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Fernando Pina
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player* player);

/**
 * @brief It gets the id of a player
 * @author Fernando Pina
 *
 * @param player a pointer to the Player
 * @return the id of the player
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the name of a player
 * @author Fernando Pina
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the name of a player
 * @author Fernando Pina
 *
 * @param player a pointer to the player
 * @return  a string with the name of the player
 */
const char* player_get_name(Player* player);

/**
 * @brief It sets the id of the object carried by the player
 * @author Fernando Pina
 *
 * @param player a pointer to the player
 * @param object_id the id of the carried object (or NO_ID if none)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object(Player* player, Id object_id);

/**
 * @brief It gets the id of the object carried by the player
 * @author Fernando Pina
 *
 * @param player a pointer to the player
 * @return the id of the object (or NO_ID if none)
 */
Id player_get_object(Player* player);

/**
 * @brief It sets the location of the player
 * @author Fernando Pina
 *
 * @param player a pointer to the player
 * @param location_id the id of the space where the player is
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status player_set_location(Player* player, Id location_id);

/**
 * @brief It gets the player location
 * @author Fernando Pina
 *
 * @param player a pointer to the player
 * @return the id of the location of the player
 */
Id player_get_location(Player* player);

/**
 * @brief It prints the player information
 * @author Fernando Pina
 *
 * This fucntion shows the id and name of the player,and if it has an object or not.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player* player);

#endif
