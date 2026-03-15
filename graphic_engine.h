/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief It creates a new graphic engine
 * @author Iker Díaz
 *
 * @return a pointer to a new graphic engine, or NULL on error
 */
Graphic_engine* graphic_engine_create(void);

/**
 * @brief It destroys a graphic engine
 * @author Iker Díaz
 *
 * @param ge a pointer to the graphic engine
 */
void graphic_engine_destroy(Graphic_engine* ge);

/**
 * @brief It paints the current game state on screen
 * @author Iker Díaz
 *
 * @param ge a pointer to the graphic engine
 * @param game a pointer to the game
 */
void graphic_engine_paint_game(Graphic_engine* ge, Game* game);

#endif
