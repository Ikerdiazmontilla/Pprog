/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Fernando Pina
 * @version 0
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "player.h"



/**
 * @brief player
 *
 * This struct stores all the information of a player.
 */
struct _Player {
  Id id;                    /*!< Id number of the player, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the player */
  Id object;                /*!< Carried object id (or NO_ID) */
  Id location;              /*!< Current space id */
};

/** player_create allocates memory for a new player
 *  and initializes its members
 */
Player* player_create(Id id) {
  Player* newPlayer = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newPlayer = (Player*)calloc(1, sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->object = NO_ID;
  newPlayer->location = NO_ID;

  return newPlayer;
}
/*free the memory of the player*/
Status player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player); 
  return OK;
}

/*returns player id*/
Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

/*it sets the player name*/
Status player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  strncpy(player->name, name, WORD_SIZE);
  player->name[WORD_SIZE] = '\0';
  return OK;
}

/*it returns the player name*/
const char* player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}


/*set the object id*/
Status player_set_object(Player* player, Id object_id) {
  if (!player) {
    return ERROR;
  }
  player->object = object_id;
  return OK;
}

/*it returns the id of the object */
Id player_get_object(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->object;
}

/*it sets the player location*/
Status player_set_location(Player* player, Id location_id) {
  if (!player) {
    return ERROR;
  }
  player->location = location_id;
  return OK;
}

/*it returns the player id location*/
Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}


Status player_print(Player* player) {
  

  /* Error Control */
  if (!player) {
    return ERROR;
  }

  /* 1. Print the id and the name of the player */
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  
  /* 3. Print the object id if it exists else print a message if not */
  if (player_get_object(player) != NO_ID) {
    fprintf(stdout, "---> Object of the player (Id: %ld).\n", player->object);
  } else {
    fprintf(stdout, "---> The player has no object.\n");
  }

  if (player_get_location(player) != NO_ID) {
    fprintf(stdout, "---> Location of the player (Id: %ld).\n", player->location);
  } else {
    fprintf(stdout, "---> no location.\n");
  }


  return OK;
}
