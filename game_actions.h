/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"

/**
 * @brief It updates the game state according to the given command
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param cmd a pointer to the command
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_update(Game* game, Command* cmd);

#endif
