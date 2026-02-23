/**
 * @brief It implements the character module
 *
 * @file character.c
 * @author Iker Díaz
 * @version 0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Character
 *
 * This struct stores all the information of a character.
 */
struct _Character {
  Id id;                              /*!< Id number of the character, it must be unique */
  char name[WORD_SIZE + 1];           /*!< Name of the character */
  char gdesc[CHARACTER_GDESC_SIZE + 1]; /*!< Graphic description of the character */
  int health;                         /*!< Health points of the character */
  Bool friendly;                      /*!< TRUE if character is friendly */
  char message[WORD_SIZE + 1];        /*!< Character message */
};

Character* character_create(Id id) {
  Character* new_character = NULL;

  if (id == NO_ID) {
    return NULL;
  }

  new_character = (Character*)calloc(1, sizeof(Character));
  if (!new_character) {
    return NULL;
  }

  new_character->id = id;
  new_character->name[0] = '\0';
  new_character->gdesc[0] = '\0';
  new_character->health = 0;
  new_character->friendly = FALSE;
  new_character->message[0] = '\0';

  return new_character;
}

Status character_destroy(Character* character) {
  if (!character) {
    return ERROR;
  }

  free(character);
  return OK;
}

Id character_get_id(Character* character) {
  if (!character) {
    return NO_ID;
  }

  return character->id;
}

Status character_set_name(Character* character, char* name) {
  if (!character || !name) {
    return ERROR;
  }

  strncpy(character->name, name, WORD_SIZE);
  character->name[WORD_SIZE] = '\0';
  return OK;
}

const char* character_get_name(Character* character) {
  if (!character) {
    return NULL;
  }

  return character->name;
}

Status character_set_gdesc(Character* character, char* gdesc) {
  if (!character || !gdesc) {
    return ERROR;
  }

  strncpy(character->gdesc, gdesc, CHARACTER_GDESC_SIZE);
  character->gdesc[CHARACTER_GDESC_SIZE] = '\0';
  return OK;
}

const char* character_get_gdesc(Character* character) {
  if (!character) {
    return NULL;
  }

  return character->gdesc;
}

Status character_set_health(Character* character, int health) {
  if (!character || health < 0) {
    return ERROR;
  }

  character->health = health;
  return OK;
}

int character_get_health(Character* character) {
  if (!character) {
    return -1;
  }

  return character->health;
}

Status character_set_friendly(Character* character, Bool friendly) {
  if (!character) {
    return ERROR;
  }

  character->friendly = friendly;
  return OK;
}

Bool character_get_friendly(Character* character) {
  if (!character) {
    return FALSE;
  }

  return character->friendly;
}

Status character_set_message(Character* character, char* message) {
  if (!character || !message) {
    return ERROR;
  }

  strncpy(character->message, message, WORD_SIZE);
  character->message[WORD_SIZE] = '\0';
  return OK;
}

const char* character_get_message(Character* character) {
  if (!character) {
    return NULL;
  }

  return character->message;
}

Status character_print(Character* character) {
  if (!character) {
    return ERROR;
  }

  fprintf(stdout, "--> Character (Id: %ld; Name: %s)\n", character->id, character->name);
  fprintf(stdout, "---> Gdesc: %s\n", character->gdesc);
  fprintf(stdout, "---> Health: %d\n", character->health);
  fprintf(stdout, "---> Friendly: %s\n", character->friendly == TRUE ? "yes" : "no");
  fprintf(stdout, "---> Message: %s\n", character->message);

  return OK;
}
