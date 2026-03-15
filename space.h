/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "set.h"
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
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id of the space, or NO_ID on error
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return a string with the name of the space, or NULL on error
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located to the north
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param id the id number of the northern space
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the northern space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id number of the northern space, or NO_ID on error
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located to the south
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param id the id number of the southern space
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the southern space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id number of the southern space, or NO_ID on error
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located to the east
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param id the id number of the eastern space
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It gets the id of the eastern space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id number of the eastern space, or NO_ID on error
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located to the west
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param id the id number of the western space
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the western space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id number of the western space, or NO_ID on error
 */
Id space_get_west(Space* space);

/**
 * @brief It sets the id of the character in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param character_id the id of the character, or NO_ID if there is no character
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_set_character(Space* space, Id character_id);

/**
 * @brief It gets the id of the character in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the character id, or NO_ID on error
 */
Id space_get_character(Space* space);

/**
 * @brief It sets one line of the graphical description of a space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param line line index in range [0, SPACE_GDESC_LINES - 1]
 * @param gdesc a string with the line contents
 * @return OK if everything goes well, ERROR otherwise
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
 * @brief It adds an object to the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param object_id the object id to add
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_add_object(Space* space, Id object_id);

/**
 * @brief It removes an object from the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param object_id the object id to remove
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_remove_object(Space* space, Id object_id);

/**
 * @brief It checks whether an object id exists in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @param object_id the object id to search
 * @return TRUE if the object exists in the space, FALSE otherwise
 */
Bool space_has_object(Space* space, Id object_id);

/**
 * @brief It gets the number of objects in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return number of objects, or -1 on error
 */
int space_get_n_objects(Space* space);

/**
 * @brief It gets the array with the ids of the objects in the space
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return the id array, or NULL on error
 */
Id* space_get_objects_ids(Space* space);

/**
 * @brief It checks if the space has no objects
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return TRUE if the space has no objects, FALSE otherwise
 */
Bool space_is_empty_of_objects(Space* space);

/**
 * @brief It prints the space information
 * @author Iker Díaz
 *
 * @param space a pointer to the space
 * @return OK if everything goes well, ERROR otherwise
 */
Status space_print(Space* space);

#endif
