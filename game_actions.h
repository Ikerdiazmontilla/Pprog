/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"

/**
 * @brief It updates the game state according to the given command
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param cmd a pointer to the command
 * @return OK if the command succeeds, ERROR otherwise
 */
Status game_actions_update(Game* game, Command* cmd);

#endif
