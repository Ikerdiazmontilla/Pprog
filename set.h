/**
 * @brief It defines the set module interface
 *
 * @file set.h
 * @author Fernando Pina
 * @version 0
 * @date 17-02-2026
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"


typedef struct _Set Set;

/**
 * @brief It creates a set, allocating memory and initializing its members
 * @author Fernando Pina
 *
 * @param id array of ids
 * @param n_ids the numbers of ids 
 * @return a new set, initialized
 */
Set* set_create(Id *id, const int n_ids);

/**
 * @brief It destroys a set, freeing the allocated memory
 * @author Fernando Pina
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_destroy(Set *set);







#endif

