/**
 * @brief It defines the set module interface
 *
 * @file set.h
 * @author Fernando Pina
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/**
 * @brief Maximum number of ids stored in a set
 * @author Fernando Pina
 */
#define SET_MAX_IDS 100

typedef struct _Set Set;

/**
 * @brief It creates a set, allocating memory and initializing its members
 * @author Fernando Pina
 *
 * @return a new set, initialized
 */
Set* set_create(void);

/**
 * @brief It destroys a set, freeing the allocated memory
 * @author Fernando Pina
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK if everything goes well, ERROR otherwise
 */
Status set_destroy(Set* set);

/**
 * @brief It adds an id to the set
 * @author Fernando Pina
 *
 * @param set a pointer to the set
 * @param id the id to add
 * @return OK if everything goes well, ERROR otherwise
 */
Status set_add_id(Set* set, Id id);

/**
 * @brief It deletes an id from the set
 * @author Fernando Pina
 *
 * @param set a pointer to the set
 * @param id the id to delete
 * @return OK if everything goes well, ERROR otherwise
 */
Status set_del_id(Set* set, Id id);

/**
 * @brief It searches an id inside the set
 * @author Fernando Pina
 *
 * @param set a pointer to the set
 * @param id the id to search
 * @return TRUE if the id exists in the set, FALSE otherwise
 */
Bool set_find_id(Set* set, Id id);

/**
 * @brief It prints the content of a set
 * @author Fernando Pina
 *
 * @param set a pointer to the set
 * @return OK if everything goes well, ERROR otherwise
 */
Status set_print(Set* set);

/**
 * @brief It gets the number of ids stored in a set
 * @author Fernando Pina
 *
 * @param set a pointer to the set
 * @return the number of ids, or -1 on error
 */
int set_get_n_ids(Set* set);

/**
 * @brief It gets the internal id array of a set
 * @author Fernando Pina
 *
 * @param set a pointer to the set
 * @return the id array, or NULL on error
 */
Id* set_get_ids(Set* set);

#endif
