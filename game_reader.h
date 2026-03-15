/**
 * @brief It defines the game reader module interface
 *
 * @file game_reader.h
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief It creates a game from a data file
 * @author Iker Díaz
 *
 * This function initializes the game structure, loads spaces, objects and characters
 * from the file and places the player in the first loaded space.
 *
 * @param filename path to the game data file
 * @return a pointer to the created game, or NULL on error
 */
Game* game_reader_create_from_file(char* filename);

#endif
