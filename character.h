/**
 * @brief It defines the character module interface
 *
 * @file character.h
 * @author Iker Díaz
 * @version 0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

/**
 * @brief Maximum length for the character graphic description
 * @author Iker Díaz
 */
#define CHARACTER_GDESC_SIZE 6

typedef struct _Character Character;

/**
 * @brief It creates a new character, allocating memory and initializing its members
 * @author Iker Díaz
 *
 * @param id the identification number for the new character
 * @return a new character, initialized
 */
Character* character_create(Id id);

/**
 * @brief It destroys a character, freeing the allocated memory
 * @author Iker Díaz
 *
 * @param character a pointer to the character that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_destroy(Character* character);

/**
 * @brief It gets the id of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @return the id of the character
 */
Id character_get_id(Character* character);

/**
 * @brief It sets the name of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_name(Character* character, char* name);

/**
 * @brief It gets the name of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @return a string with the name of the character
 */
const char* character_get_name(Character* character);

/**
 * @brief It sets the graphic description of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @param gdesc a string with the graphic description to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_gdesc(Character* character, char* gdesc);

/**
 * @brief It gets the graphic description of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @return a string with the graphic description of the character
 */
const char* character_get_gdesc(Character* character);

/**
 * @brief It sets the health points of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @param health current health points
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_health(Character* character, int health);

/**
 * @brief It gets the health points of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @return current health points
 */
int character_get_health(Character* character);

/**
 * @brief It sets whether the character is friendly
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @param friendly TRUE if friendly, FALSE otherwise
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_friendly(Character* character, Bool friendly);

/**
 * @brief It gets whether the character is friendly
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @return TRUE if friendly, FALSE otherwise
 */
Bool character_get_friendly(Character* character);

/**
 * @brief It sets the message of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @param message a string with the message to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_message(Character* character, char* message);

/**
 * @brief It gets the message of a character
 * @author Iker Díaz
 *
 * @param character a pointer to the character
 * @return a string with the character message
 */
const char* character_get_message(Character* character);

/**
 * @brief It prints the character information
 * @author Iker Díaz
 *
 * This function shows the id, name and status of the character.
 * @param character a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_print(Character* character);

#endif
