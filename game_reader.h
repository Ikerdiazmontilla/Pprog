/**
 * @brief It defines the game reader module interface
 *
 * @file game_reader.h
 * @author Profesores PPROG
 * @version 0
 * @date 10-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "types.h"

/**
 * @brief It creates a game from a data file
 * @author Profesores PPROG
 *
 * This function initializes the game structure, loads spaces from the file and places
 * the player and the object in the first loaded space.
 *
 * @param game a pointer to the game to initialize
 * @param filename path to the game data file
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_reader_create_from_file(Game* game, char* filename);

#endif
