/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Iker Díaz
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"

/**
 * @brief Number of text rows used by the graphical description of a space
 * @author Iker Díaz
 */
#define SPACE_GDESC_LINES 5

/**
 * @brief Maximum length of each text row used by a space graphical description
 * @author Iker Díaz
 */
#define SPACE_GDESC_LENGTH 9

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Iker Díaz
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Iker Díaz
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located at the north
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located at the south
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located at the east
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located at the west
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space* space);

/**
 * @brief It sets the id of the object in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param object_id the id of the object in the space (or NO_ID if there is no object)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_object(Space* space, Id object_id);

/**
 * @brief It gets the id of the object in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id of the object in the space (or NO_ID if there is no object)
 */
Id space_get_object(Space* space);

/**
 * @brief It sets the id of the character in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param character_id the id of the character in the space (or NO_ID if there is no character)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_character(Space* space, Id character_id);

/**
 * @brief It gets the id of the character in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id of the character in the space (or NO_ID if there is no character)
 */
Id space_get_character(Space* space);

/**
 * @brief It sets one line of the graphical description of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param line line index in range [0, SPACE_GDESC_LINES - 1]
 * @param gdesc a string with the line contents
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_gdesc(Space* space, int line, char* gdesc);

/**
 * @brief It gets one line of the graphical description of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param line line index in range [0, SPACE_GDESC_LINES - 1]
 * @return a string with the selected line, or NULL on error
 */
const char* space_get_gdesc(Space* space, int line);

/**
 * @brief It prints the space information
 * @author Iker Díaz
 *
 * This function shows ids and names, links, object, character and graphical description lines.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

Status space_add_object(Space *space, Id object_Id);

Status space_del_object(Space *space, Id id);

Bool space_find_object_id(Space *space, Id object_id);

int space_get_obects_n_ids(Space *space);

Id *set_get_ids(Set *set);
#endif
