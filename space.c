/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Iker Díaz
 * @version 0
 * @date 24-01-2026
 * @copyright GNU Public License
 */

#include "set.h"
#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Id north;                 /*!< Id of the space at the north */
  Id south;                 /*!< Id of the space at the south */
  Id east;                  /*!< Id of the space at the east */
  Id west;                  /*!< Id of the space at the west */
  Set *objects;                /*!< Id of the object in the space (or NO_ID) */
  Id character;             /*!< Id of the character in the space (or NO_ID) */
  char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1]; /*!< Graphical description lines */
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space* space_create(Id id) {
  Space* newSpace = NULL;
  int i = 0;

  /* Error control */
  if (id == NO_ID) return NULL;

  newSpace = (Space*)calloc(1, sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = NULL;
  newSpace->character = NO_ID;
  for (i = 0; i < SPACE_GDESC_LINES; i++) {
    newSpace->gdesc[i][0] = '\0';
  }

  return newSpace;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

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

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
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
  if (!space || id == NO_ID) {
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
  if (!space || id == NO_ID) {
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
  if (!space || id == NO_ID) {
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

Status space_set_object(Space* space, Id object_id) {
  if (!space) {
    return ERROR;
  }
  if ((set_add_id(space->objects,object_id)) == ERROR)
  {
    return ERROR;
  }
  
  
  return OK;
}



Id space_get_object(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->objects;
}

Status space_add_object(Space *space, Id object_Id)
{
  if (!(space) || object_Id == NO_ID)
  {
      return ERROR;
  }
  
  if ((set_find_id(space->objects, object_Id)) == TRUE)
  {
      return ERROR;
  }else
  {
   if ((set_add_id(space->objects, object_Id)) == ERROR)
   {
      return ERROR;
   }
      return OK;
  }
  
}



Status space_del_object(Space *space, Id id)
{
  if (!(space) || id == NO_ID)
  {
    return ERROR;
  }
  
  if ((set_find_id(space->objects, id)) == FALSE)
  {
   return ERROR;
  }

  if ((set_del_id(space->objects, id)) == ERROR)
  {
    return ERROR;
  }
  
  return OK;

}

Bool space_find_object_id(Space *space, Id object_id)
{
  if (!(space) || object_id == NO_ID)
  {
    return FALSE;
  }
  
  if ((set_find_id(space->objects, object_id)) == TRUE)
  {
   return ERROR;
  }

  return TRUE;
}


int space_get_obects_n_ids(Space *space)
{
  if (!(space))
  {
    return -1;
  }
  return set_get_n_ids(space->objects);
  
  
}

Id *space_get_objects_ids(Space *space)
{
  if (!(space))
  {
    return NO_ID;
  }
  return set_get_ids(space->objects);
  
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

Status space_print(Space* space) {
  Id idaux = NO_ID;
  int i = 0;

  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  if (space_get_object(space) != NO_ID) {
    fprintf(stdout, "---> Object in the space (Id: %ld).\n", space->objects);
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  if (space_get_character(space) != NO_ID) {
    fprintf(stdout, "---> Character in the space (Id: %ld).\n", space->character);
  } else {
    fprintf(stdout, "---> No character in the space.\n");
  }

  for (i = 0; i < SPACE_GDESC_LINES; i++) {
    fprintf(stdout, "---> Gdesc line %d: %s\n", i, space->gdesc[i]);
  }

  return OK;
}
