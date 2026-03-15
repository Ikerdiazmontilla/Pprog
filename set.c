/**
 * @brief It implements the set module
 *
 * @file set.c
 * @author Fernando Pina
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "set.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Set
 * @author Fernando Pina
 *
 * This struct stores the ids currently inserted in the set.
 */
struct _Set {
  Id ids[SET_MAX_IDS]; /*!< Stored ids */
  int n_ids;           /*!< Number of valid ids */
};

Set* set_create(void) {
  Set* new_set = NULL;
  int i = 0;

  new_set = (Set*)calloc(1, sizeof(Set));
  if (!new_set) {
    return NULL;
  }

  new_set->n_ids = 0;
  for (i = 0; i < SET_MAX_IDS; i++) {
    new_set->ids[i] = NO_ID;
  }

  return new_set;
}

Status set_destroy(Set* set) {
  if (!set) {
    return ERROR;
  }

  free(set);
  return OK;
}

Status set_add_id(Set* set, Id id) {
  if (!set || id == NO_ID || set->n_ids >= SET_MAX_IDS) {
    return ERROR;
  }

  if (set_find_id(set, id) == TRUE) {
    return ERROR;
  }

  set->ids[set->n_ids] = id;
  set->n_ids++;
  return OK;
}

Status set_del_id(Set* set, Id id) {
  int i = 0;
  int position = -1;

  if (!set || id == NO_ID || set->n_ids <= 0) {
    return ERROR;
  }

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      position = i;
      break;
    }
  }

  if (position < 0) {
    return ERROR;
  }

  for (i = position; i < set->n_ids - 1; i++) {
    set->ids[i] = set->ids[i + 1];
  }

  set->n_ids--;
  set->ids[set->n_ids] = NO_ID;

  return OK;
}

Bool set_find_id(Set* set, Id id) {
  int i = 0;

  if (!set || id == NO_ID) {
    return FALSE;
  }

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      return TRUE;
    }
  }

  return FALSE;
}

Status set_print(Set* set) {
  int i = 0;

  if (!set) {
    return ERROR;
  }

  fprintf(stdout, "--> Set (%d ids):", set->n_ids);
  for (i = 0; i < set->n_ids; i++) {
    fprintf(stdout, " %ld", set->ids[i]);
  }
  fprintf(stdout, "\n");

  return OK;
}

int set_get_n_ids(Set* set) {
  if (!set) {
    return -1;
  }

  return set->n_ids;
}

Id* set_get_ids(Set* set) {
  if (!set) {
    return NULL;
  }

  return set->ids;
}
