/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Fernando Pina
 * @version 0
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "object.h"



/**
 * @brief object
 *
 * This struct stores all the information of a object.
 */
struct _Object {
  Id id;                    /*!< Id number of the object, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the object */
};

/**
 * @brief It creates a new object
 * @author Fernando Pina
 *
 * @param id the identification number for the object
 * @return a new object initialized, or NULL on error
 */
Object* object_create(Id id) {
  Object* newObject = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newObject = (Object*)calloc(1, sizeof(Object));
  if (newObject == NULL) {
    return NULL;
  }

  /* Initialization of an empty object */
  newObject->id = id;
  newObject->name[0] = '\0';

  return newObject;
}

/*free the memory of the object*/
Status object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  return OK;
}

/*returns object id*/
Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

/*it sets the object name*/
Status object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  strncpy(object->name, name, WORD_SIZE);
  object->name[WORD_SIZE] = '\0';
  return OK;
}

/*it returns the object name*/
const char* object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}


Status object_print(Object* object) {
  

  /* Error Control */
  if (!object) {
    return ERROR;
  }

  /*  Print the id and the name of the object */
  fprintf(stdout, "--> (Id: %ld; Name: %s)\n", object->id, object->name);


  return OK;
}
