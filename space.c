/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 * @author Iker Díaz
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                                           /*!< Id number of the space */
  char name[WORD_SIZE + 1];                        /*!< Space name */
  Id north;                                        /*!< Northern space id */
  Id south;                                        /*!< Southern space id */
  Id east;                                         /*!< Eastern space id */
  Id west;                                         /*!< Western space id */
  Set* objects;                                    /*!< Set with the ids of the objects in the space */
  Id character;                                    /*!< Character id in the space */
  char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1]; /*!< ASCII representation */
};

Space* space_create(Id id) {
  Space* new_space = NULL;
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  new_space = (Space*)calloc(1, sizeof(Space));
  if (!new_space) {
    return NULL;
  }

  new_space->objects = set_create();
  if (!new_space->objects) {
    free(new_space);
    return NULL;
  }

  new_space->id = id;
  new_space->name[0] = '\0';
  new_space->north = NO_ID;
  new_space->south = NO_ID;
  new_space->east = NO_ID;
  new_space->west = NO_ID;
  new_space->character = NO_ID;

  for (i = 0; i < SPACE_GDESC_LINES; i++) {
    new_space->gdesc[i][0] = '\0';
  }

  return new_space;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);
  free(space);
  return OK;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }

  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  strncpy(space->name, name, WORD_SIZE);
  space->name[WORD_SIZE] = '\0';
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }

  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }

  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }

  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }

  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }

  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }

  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }

  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }

  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }

  return space->west;
}

Status space_set_character(Space* space, Id character_id) {
  if (!space) {
    return ERROR;
  }

  space->character = character_id;
  return OK;
}

Id space_get_character(Space* space) {
  if (!space) {
    return NO_ID;
  }

  return space->character;
}

Status space_set_gdesc(Space* space, int line, char* gdesc) {
  if (!space || !gdesc || line < 0 || line >= SPACE_GDESC_LINES) {
    return ERROR;
  }

  strncpy(space->gdesc[line], gdesc, SPACE_GDESC_LENGTH);
  space->gdesc[line][SPACE_GDESC_LENGTH] = '\0';
  return OK;
}

const char* space_get_gdesc(Space* space, int line) {
  if (!space || line < 0 || line >= SPACE_GDESC_LINES) {
    return NULL;
  }

  return space->gdesc[line];
}

Status space_add_object(Space* space, Id object_id) {
  if (!space || object_id == NO_ID) {
    return ERROR;
  }

  return set_add_id(space->objects, object_id);
}

Status space_remove_object(Space* space, Id object_id) {
  if (!space || object_id == NO_ID) {
    return ERROR;
  }

  return set_del_id(space->objects, object_id);
}

Bool space_has_object(Space* space, Id object_id) {
  if (!space || object_id == NO_ID) {
    return FALSE;
  }

  return set_find_id(space->objects, object_id);
}

int space_get_n_objects(Space* space) {
  if (!space) {
    return -1;
  }

  return set_get_n_ids(space->objects);
}

Id* space_get_objects_ids(Space* space) {
  if (!space) {
    return NULL;
  }

  return set_get_ids(space->objects);
}

Bool space_is_empty_of_objects(Space* space) {
  if (!space) {
    return FALSE;
  }

  return (space_get_n_objects(space) == 0) ? TRUE : FALSE;
}

Status space_print(Space* space) {
  int i = 0;
  Id* object_ids = NULL;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);
  fprintf(stdout, "---> North: %ld\n", space->north);
  fprintf(stdout, "---> South: %ld\n", space->south);
  fprintf(stdout, "---> East: %ld\n", space->east);
  fprintf(stdout, "---> West: %ld\n", space->west);
  fprintf(stdout, "---> Character: %ld\n", space->character);

  fprintf(stdout, "---> Objects:");
  object_ids = space_get_objects_ids(space);
  for (i = 0; i < space_get_n_objects(space); i++) {
    fprintf(stdout, " %ld", object_ids[i]);
  }
  fprintf(stdout, "\n");

  for (i = 0; i < SPACE_GDESC_LINES; i++) {
    fprintf(stdout, "---> Gdesc line %d: %s\n", i, space->gdesc[i]);
  }

  return OK;
}
