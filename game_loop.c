/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "game_reader.h"
#include "graphic_engine.h"

/**
 * @brief It initializes the game and graphic engine
 * @author Iker Díaz
 *
 * @param game a pointer to the game pointer
 * @param gengine a pointer to the graphic engine pointer
 * @param file_name path to the game data file
 * @return 0 if OK, 1 if game initialization fails, 2 if graphic engine initialization fails
 */
static int game_loop_init(Game** game, Graphic_engine** gengine, char* file_name);

/**
 * @brief It frees all allocated resources
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param gengine a pointer to the graphic engine
 */
static void game_loop_cleanup(Game* game, Graphic_engine* gengine);

int main(int argc, char* argv[]) {
  Game* game = NULL;
  Graphic_engine* gengine = NULL;
  Command* last_cmd = NULL;
  int result = 0;

  srand((unsigned int)time(NULL));

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  result = game_loop_init(&game, &gengine, argv[1]);
  if (result == 1) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }
  if (result == 2) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    return 1;
  }

  last_cmd = game_get_last_command(game);

  while (command_get_code(last_cmd) != EXIT && game_get_finished(game) == FALSE) {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);
  }

  game_loop_cleanup(game, gengine);
  return 0;
}

static int game_loop_init(Game** game, Graphic_engine** gengine, char* file_name) {
  *game = game_reader_create_from_file(file_name);
  if (!*game) {
    return 1;
  }

  *gengine = graphic_engine_create();
  if (!*gengine) {
    game_destroy(*game);
    *game = NULL;
    return 2;
  }

  return 0;
}

static void game_loop_cleanup(Game* game, Graphic_engine* gengine) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
