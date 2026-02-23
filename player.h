/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Iker Díaz
 * @version 0
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

/**
 * @brief Maximum length for the player graphic description
 * @author Iker Díaz
 */
#define PLAYER_GDESC_SIZE 6

typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Iker Díaz
 *
 * @param id the identification number for the new player
 * @return a new player, initialized
 */
Player* player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Iker Díaz
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player* player);

/**
 * @brief It gets the id of a player
 * @author Iker Díaz
 *
 * @param player a pointer to the Player
 * @return the id of the player
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the name of a player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the name of a player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @return  a string with the name of the player
 */
const char* player_get_name(Player* player);

/**
 * @brief It sets the id of the object carried by the player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @param object_id the id of the carried object (or NO_ID if none)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object(Player* player, Id object_id);

/**
 * @brief It gets the id of the object carried by the player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @return the id of the object (or NO_ID if none)
 */
Id player_get_object(Player* player);

/**
 * @brief It sets the location of the player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @param location_id the id of the space where the player is
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status player_set_location(Player* player, Id location_id);

/**
 * @brief It gets the player location
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @return the id of the location of the player
 */
Id player_get_location(Player* player);

/**
 * @brief It sets the health points of a player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @param health current health points
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_health(Player* player, int health);

/**
 * @brief It gets the health points of a player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @return current health points
 */
int player_get_health(Player* player);

/**
 * @brief It sets the graphic description of a player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @param gdesc a string with the graphic description to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_gdesc(Player* player, char* gdesc);

/**
 * @brief It gets the graphic description of a player
 * @author Iker Díaz
 *
 * @param player a pointer to the player
 * @return a string with the graphic description of the player
 */
const char* player_get_gdesc(Player* player);

/**
 * @brief It prints the player information
 * @author Iker Díaz
 *
 * This function shows the id, name, object, location, health and gdesc of the player.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player* player);

#endif
