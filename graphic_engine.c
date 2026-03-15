/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libscreen.h"

/**
 * @brief Width of the map area in characters
 * @author Iker Díaz
 */
#define WIDTH_MAP 59

/**
 * @brief Width of the description area in characters
 * @author Iker Díaz
 */
#define WIDTH_DES 57

/**
 * @brief Width of the banner area in characters
 * @author Iker Díaz
 */
#define WIDTH_BAN 29

/**
 * @brief Height of the map area in rows
 * @author Iker Díaz
 */
#define HEIGHT_MAP 29

/**
 * @brief Height of the banner area in rows
 * @author Iker Díaz
 */
#define HEIGHT_BAN 1

/**
 * @brief Height of the help area in rows
 * @author Iker Díaz
 */
#define HEIGHT_HLP 2

/**
 * @brief Height of the feedback area in rows
 * @author Iker Díaz
 */
#define HEIGHT_FDB 3

/**
 * @brief Width of each space box drawn on the map
 * @author Iker Díaz
 */
#define BOX_WIDTH 17

/**
 * @brief Height of each space box drawn on the map
 * @author Iker Díaz
 */
#define BOX_HEIGHT 9

/**
 * @brief Inner width of each space box
 * @author Iker Díaz
 */
#define BOX_INNER_WIDTH (BOX_WIDTH - 2)

/**
 * @brief Vertical start row for the top visible space
 * @author Iker Díaz
 */
#define TOP_ROW 0

/**
 * @brief Vertical start row for the middle visible spaces
 * @author Iker Díaz
 */
#define MIDDLE_ROW 10

/**
 * @brief Vertical start row for the bottom visible space
 * @author Iker Díaz
 */
#define BOTTOM_ROW 20

/**
 * @brief Horizontal start column for the western visible space
 * @author Iker Díaz
 */
#define LEFT_COL 0

/**
 * @brief Horizontal start column for the current and vertical visible spaces
 * @author Iker Díaz
 */
#define CENTER_COL 21

/**
 * @brief Horizontal start column for the eastern visible space
 * @author Iker Díaz
 */
#define RIGHT_COL 42

/**
 * @brief Graphic engine data
 * @author Iker Díaz
 *
 * This struct stores all screen areas used to render the game interface.
 */
struct _Graphic_engine {
  Area* map;      /*!< Map area */
  Area* descript; /*!< Description area */
  Area* banner;   /*!< Banner area */
  Area* help;     /*!< Help area */
  Area* feedback; /*!< Feedback area */
};

/**
 * @brief It clears the map canvas
 * @author Iker Díaz
 *
 * @param canvas map canvas to clear
 */
static void graphic_engine_clear_canvas(char canvas[HEIGHT_MAP][WIDTH_MAP + 1]);

/**
 * @brief It copies a string into the map canvas at a given position
 * @author Iker Díaz
 *
 * @param canvas map canvas
 * @param row destination row
 * @param col destination column
 * @param text text to copy
 */
static void graphic_engine_put_text(char canvas[HEIGHT_MAP][WIDTH_MAP + 1],
                                    int row, int col, const char* text);

/**
 * @brief It draws a visible space box on the map canvas
 * @author Iker Díaz
 *
 * @param canvas map canvas
 * @param game a pointer to the game
 * @param space_id id of the space to draw
 * @param start_row top row of the box
 * @param start_col left column of the box
 * @param is_current TRUE if the box is the current player space
 */
static void graphic_engine_draw_space_box(char canvas[HEIGHT_MAP][WIDTH_MAP + 1],
                                          Game* game, Id space_id, int start_row,
                                          int start_col, Bool is_current);

/**
 * @brief It builds the header line of a space box
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param space a pointer to the space
 * @param is_current TRUE if the player is in the space
 * @param buffer destination buffer
 */
static void graphic_engine_build_space_header(Game* game, Space* space,
                                              Bool is_current, char* buffer);

/**
 * @brief It builds the object line of a space box
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param space a pointer to the space
 * @param buffer destination buffer
 */
static void graphic_engine_build_space_objects(Game* game, Space* space, char* buffer);

/**
 * @brief It appends a string to a fixed-size buffer, truncating safely
 * @author Iker Díaz
 *
 * @param destination destination buffer
 * @param source string to append
 * @param max_size maximum buffer size
 */
static void graphic_engine_safe_append(char* destination, const char* source, int max_size);

/**
 * @brief It formats the last executed command for the feedback area
 * @author Iker Díaz
 *
 * @param game a pointer to the game
 * @param buffer destination buffer
 */
static void graphic_engine_build_feedback(Game* game, char* buffer);

Graphic_engine* graphic_engine_create(void) {
  static Graphic_engine* ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4,
              WIDTH_MAP + WIDTH_DES + 3);

  ge = (Graphic_engine*)calloc(1, sizeof(Graphic_engine));
  if (!ge) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2,
                                HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2,
                              WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3,
                                  WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine* ge) {
  if (!ge) {
    return;
  }

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine* ge, Game* game) {
  char map_canvas[HEIGHT_MAP][WIDTH_MAP + 1];
  char text_line[GAME_MESSAGE_SIZE + 1];
  Space* current_space = NULL;
  Player* player = NULL;
  Object* object = NULL;
  Character* character = NULL;
  Id current_space_id = NO_ID;
  Id north_id = NO_ID;
  Id south_id = NO_ID;
  Id east_id = NO_ID;
  Id west_id = NO_ID;
  Id object_id = NO_ID;
  Id character_id = NO_ID;
  int i = 0;
  int n_objects = 0;
  int n_characters = 0;

  if (!ge || !game) {
    return;
  }

  current_space_id = game_get_player_location(game);
  current_space = game_get_space(game, current_space_id);
  player = game_get_player(game);

  if (current_space) {
    north_id = space_get_north(current_space);
    south_id = space_get_south(current_space);
    east_id = space_get_east(current_space);
    west_id = space_get_west(current_space);
  }

  screen_area_clear(ge->map);
  screen_area_reset_cursor(ge->map);
  graphic_engine_clear_canvas(map_canvas);

  graphic_engine_draw_space_box(map_canvas, game, north_id, TOP_ROW, CENTER_COL, FALSE);
  graphic_engine_draw_space_box(map_canvas, game, west_id, MIDDLE_ROW, LEFT_COL, FALSE);
  graphic_engine_draw_space_box(map_canvas, game, current_space_id, MIDDLE_ROW, CENTER_COL, TRUE);
  graphic_engine_draw_space_box(map_canvas, game, east_id, MIDDLE_ROW, RIGHT_COL, FALSE);
  graphic_engine_draw_space_box(map_canvas, game, south_id, BOTTOM_ROW, CENTER_COL, FALSE);

  if (north_id != NO_ID) {
    graphic_engine_put_text(map_canvas, TOP_ROW + BOX_HEIGHT, CENTER_COL + 8, "^");
  }
  if (south_id != NO_ID) {
    graphic_engine_put_text(map_canvas, BOTTOM_ROW - 1, CENTER_COL + 8, "v");
  }
  if (west_id != NO_ID) {
    graphic_engine_put_text(map_canvas, MIDDLE_ROW + 4, CENTER_COL - 2, "<");
  }
  if (east_id != NO_ID) {
    graphic_engine_put_text(map_canvas, MIDDLE_ROW + 4, CENTER_COL + BOX_WIDTH + 1, ">");
  }

  for (i = 0; i < HEIGHT_MAP; i++) {
    screen_area_puts(ge->map, map_canvas[i]);
  }

  screen_area_clear(ge->descript);
  screen_area_reset_cursor(ge->descript);

  screen_area_puts(ge->descript, " Objects:");
  n_objects = game_get_n_objects(game);
  for (i = 0; i < n_objects; i++) {
    object_id = game_get_object_id_at(game, i);
    object = game_get_object_by_id(game, object_id);
    if (!object) {
      continue;
    }

    if (player && player_get_object(player) == object_id) {
      sprintf(text_line, "  %-10s: player", object_get_name(object));
    } else {
      sprintf(text_line, "  %-10s: %ld", object_get_name(object),
              game_get_object_location_by_id(game, object_id));
    }
    screen_area_puts(ge->descript, text_line);
  }

  screen_area_puts(ge->descript, " ");
  screen_area_puts(ge->descript, " Characters:");
  n_characters = game_get_n_characters(game);
  for (i = 0; i < n_characters; i++) {
    character_id = game_get_character_id_at(game, i);
    character = game_get_character(game, character_id);
    if (!character) {
      continue;
    }

    sprintf(text_line, "  %-6s: %ld (%d)", character_get_gdesc(character),
            game_get_character_location(game, character_id),
            character_get_health(character));
    screen_area_puts(ge->descript, text_line);
  }

  screen_area_puts(ge->descript, " ");
  if (player) {
    sprintf(text_line, " Player      : %ld (%d)", game_get_player_location(game),
            player_get_health(player));
    screen_area_puts(ge->descript, text_line);

    if (player_get_object(player) == NO_ID) {
      screen_area_puts(ge->descript, " Player has no objects");
    } else {
      object = game_get_object_by_id(game, player_get_object(player));
      if (object) {
        sprintf(text_line, " Player has  : %s", object_get_name(object));
        screen_area_puts(ge->descript, text_line);
      }
    }
  }

  if (game_get_message(game) && game_get_message(game)[0] != '\0') {
    screen_area_puts(ge->descript, " ");
    sprintf(text_line, " Message: %s", game_get_message(game));
    screen_area_puts(ge->descript, text_line);
  }

  screen_area_clear(ge->banner);
  screen_area_reset_cursor(ge->banner);
  screen_area_puts(ge->banner, " The haunted castle game ");

  screen_area_clear(ge->help);
  screen_area_reset_cursor(ge->help);
  screen_area_puts(ge->help,
                   " The commands you can use are:");
  screen_area_puts(ge->help,
                   " next, back, left, right, take <object>, drop, attack, chat, exit");

  screen_area_clear(ge->feedback);
  screen_area_reset_cursor(ge->feedback);
  graphic_engine_build_feedback(game, text_line);
  screen_area_puts(ge->feedback, text_line);
  if (game_get_message(game) && game_get_message(game)[0] != '\0') {
    sprintf(text_line, " Message: %s", game_get_message(game));
    screen_area_puts(ge->feedback, text_line);
  } else {
    screen_area_puts(ge->feedback, " ");
  }
  screen_area_puts(ge->feedback, " ");

  screen_paint();
  printf("prompt:> ");
}

static void graphic_engine_clear_canvas(char canvas[HEIGHT_MAP][WIDTH_MAP + 1]) {
  int row = 0;
  int col = 0;

  for (row = 0; row < HEIGHT_MAP; row++) {
    for (col = 0; col < WIDTH_MAP; col++) {
      canvas[row][col] = ' ';
    }
    canvas[row][WIDTH_MAP] = '\0';
  }
}

static void graphic_engine_put_text(char canvas[HEIGHT_MAP][WIDTH_MAP + 1],
                                    int row, int col, const char* text) {
  int i = 0;

  if (!text || row < 0 || row >= HEIGHT_MAP || col >= WIDTH_MAP) {
    return;
  }

  for (i = 0; text[i] != '\0' && (col + i) < WIDTH_MAP; i++) {
    if (col + i >= 0) {
      canvas[row][col + i] = text[i];
    }
  }
}

static void graphic_engine_draw_space_box(char canvas[HEIGHT_MAP][WIDTH_MAP + 1],
                                          Game* game, Id space_id, int start_row,
                                          int start_col, Bool is_current) {
  Space* space = NULL;
  char line[BOX_WIDTH + 1];
  char content[BOX_INNER_WIDTH + 1];
  const char* gdesc = NULL;
  int i = 0;

  if (space_id == NO_ID) {
    return;
  }

  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

  sprintf(line, "+---------------+");
  graphic_engine_put_text(canvas, start_row, start_col, line);

  graphic_engine_build_space_header(game, space, is_current, content);
  sprintf(line, "|%-15s|", content);
  graphic_engine_put_text(canvas, start_row + 1, start_col, line);

  for (i = 0; i < SPACE_GDESC_LINES; i++) {
    gdesc = space_get_gdesc(space, i);
    sprintf(line, "|%-15.15s|", gdesc ? gdesc : "");
    graphic_engine_put_text(canvas, start_row + 2 + i, start_col, line);
  }

  graphic_engine_build_space_objects(game, space, content);
  sprintf(line, "|%-15.15s|", content);
  graphic_engine_put_text(canvas, start_row + 7, start_col, line);

  sprintf(line, "+---------------+");
  graphic_engine_put_text(canvas, start_row + 8, start_col, line);
}

static void graphic_engine_build_space_header(Game* game, Space* space,
                                              Bool is_current, char* buffer) {
  Player* player = NULL;
  Character* character = NULL;
  Id character_id = NO_ID;
  char occupants[BOX_INNER_WIDTH + 1];

  occupants[0] = '\0';
  buffer[0] = '\0';

  if (is_current == TRUE) {
    player = game_get_player(game);
    if (player && player_get_gdesc(player)) {
      graphic_engine_safe_append(occupants, player_get_gdesc(player), BOX_INNER_WIDTH + 1);
    }
  }

  character_id = space_get_character(space);
  if (character_id != NO_ID) {
    character = game_get_character(game, character_id);
    if (character && character_get_gdesc(character)) {
      if (occupants[0] != '\0') {
        graphic_engine_safe_append(occupants, " ", BOX_INNER_WIDTH + 1);
      }
      graphic_engine_safe_append(occupants, character_get_gdesc(character), BOX_INNER_WIDTH + 1);
    }
  }

  sprintf(buffer, "%-11.11s%4ld", occupants, space_get_id(space));
}

static void graphic_engine_build_space_objects(Game* game, Space* space, char* buffer) {
  Object* object = NULL;
  Id* object_ids = NULL;
  int i = 0;
  int n_objects = 0;

  buffer[0] = '\0';

  if (!game || !space) {
    return;
  }

  object_ids = space_get_objects_ids(space);
  n_objects = space_get_n_objects(space);
  for (i = 0; i < n_objects; i++) {
    object = game_get_object_by_id(game, object_ids[i]);
    if (!object) {
      continue;
    }

    if (buffer[0] != '\0') {
      graphic_engine_safe_append(buffer, ", ", BOX_INNER_WIDTH + 1);
    }
    graphic_engine_safe_append(buffer, object_get_name(object), BOX_INNER_WIDTH + 1);
  }
}

static void graphic_engine_safe_append(char* destination, const char* source, int max_size) {
  int length = 0;
  int i = 0;

  if (!destination || !source || max_size <= 0) {
    return;
  }

  length = (int)strlen(destination);
  if (length >= max_size - 1) {
    return;
  }

  for (i = 0; source[i] != '\0' && length < max_size - 1; i++) {
    destination[length] = source[i];
    length++;
  }

  destination[length] = '\0';
}

static void graphic_engine_build_feedback(Game* game, char* buffer) {
  Command* command = NULL;
  CommandCode code = NO_CMD;
  const char* long_name = NULL;
  const char* short_name = NULL;
  char command_text[WORD_SIZE + 1];

  if (!game || !buffer) {
    return;
  }

  command = game_get_last_command(game);
  code = command ? command_get_code(command) : NO_CMD;
  long_name = cmd_to_str[code - NO_CMD][CMDL];
  short_name = cmd_to_str[code - NO_CMD][CMDS];

  command_text[0] = '\0';
  if (code == NO_CMD) {
    strcpy(buffer, " Awaiting command");
    return;
  }

  if (long_name && long_name[0] != '\0') {
    strncpy(command_text, long_name, WORD_SIZE);
    command_text[WORD_SIZE] = '\0';
    command_text[0] = (char)toupper((unsigned char)command_text[0]);
  } else {
    strcpy(command_text, "No command");
  }

  if (code == TAKE && command_get_argument(command) &&
      command_get_argument(command)[0] != '\0') {
    graphic_engine_safe_append(command_text, " ", WORD_SIZE + 1);
    graphic_engine_safe_append(command_text, command_get_argument(command), WORD_SIZE + 1);
  }

  sprintf(buffer, " %s (%s): %s", command_text,
          (short_name && short_name[0] != '\0') ? short_name : "-",
          (game_get_last_command_status(game) == OK) ? "OK" : "ERROR");
}
