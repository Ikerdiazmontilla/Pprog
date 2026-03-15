/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "command.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Maximum input length for command parsing
 * @author Iker Díaz
 */
#define CMD_LENGTH 128

/**
 * @brief It compares two tokens ignoring case
 * @author Iker Díaz
 *
 * @param first first string
 * @param second second string
 * @return TRUE if both strings match, FALSE otherwise
 */
static Bool command_token_equals(const char* first, const char* second);

/**
 * @brief It trims leading and trailing blank characters
 * @author Iker Díaz
 *
 * @param text text to trim in place
 * @return pointer to the trimmed text
 */
static char* command_trim(char* text);

/**
 * @brief Command token table (short and long)
 * @author Iker Díaz
 */
char* cmd_to_str[N_CMD][N_CMDT] = {
  {"", "no command"},
  {"", "unknown"},
  {"e", "exit"},
  {"n", "next"},
  {"b", "back"},
  {"l", "left"},
  {"r", "right"},
  {"t", "take"},
  {"d", "drop"},
  {"a", "attack"},
  {"c", "chat"}
};

/**
 * @brief Command data
 * @author Iker Díaz
 *
 * This struct stores the command code and its optional argument.
 */
struct _Command {
  CommandCode code;                 /*!< Current command code */
  char argument[WORD_SIZE + 1];     /*!< Optional command argument */
};

Command* command_create(void) {
  Command* new_command = NULL;

  new_command = (Command*)calloc(1, sizeof(Command));
  if (!new_command) {
    return NULL;
  }

  new_command->code = NO_CMD;
  new_command->argument[0] = '\0';

  return new_command;
}

Status command_destroy(Command* command) {
  if (!command) {
    return ERROR;
  }

  free(command);
  return OK;
}

Status command_set_code(Command* command, CommandCode code) {
  if (!command) {
    return ERROR;
  }

  command->code = code;
  return OK;
}

CommandCode command_get_code(Command* command) {
  if (!command) {
    return NO_CMD;
  }

  return command->code;
}

Status command_set_argument(Command* command, const char* argument) {
  char buffer[WORD_SIZE + 1];

  if (!command || !argument) {
    return ERROR;
  }

  strncpy(buffer, argument, WORD_SIZE);
  buffer[WORD_SIZE] = '\0';

  strncpy(command->argument, buffer, WORD_SIZE);
  command->argument[WORD_SIZE] = '\0';
  return OK;
}

const char* command_get_argument(Command* command) {
  if (!command) {
    return NULL;
  }

  return command->argument;
}

Status command_get_user_input(Command* command) {
  char input[CMD_LENGTH];
  char* token = NULL;
  char* rest = NULL;
  char* trimmed_argument = NULL;
  int i = 0;
  CommandCode code = UNKNOWN;

  if (!command) {
    return ERROR;
  }

  if (!fgets(input, CMD_LENGTH, stdin)) {
    command_set_argument(command, "");
    return command_set_code(command, EXIT);
  }

  token = strtok(input, " \t\n");
  if (!token) {
    command_set_argument(command, "");
    return command_set_code(command, UNKNOWN);
  }

  for (i = 1; i < N_CMD; i++) {
    if (command_token_equals(token, cmd_to_str[i][CMDS]) == TRUE ||
        command_token_equals(token, cmd_to_str[i][CMDL]) == TRUE) {
      code = (CommandCode)(i + NO_CMD);
      break;
    }
  }

  rest = strtok(NULL, "");
  if (rest) {
    trimmed_argument = command_trim(rest);
    command_set_argument(command, trimmed_argument);
  } else {
    command_set_argument(command, "");
  }

  return command_set_code(command, code);
}

static Bool command_token_equals(const char* first, const char* second) {
  unsigned char first_char = '\0';
  unsigned char second_char = '\0';

  if (!first || !second) {
    return FALSE;
  }

  while (*first != '\0' && *second != '\0') {
    first_char = (unsigned char)tolower((unsigned char)*first);
    second_char = (unsigned char)tolower((unsigned char)*second);

    if (first_char != second_char) {
      return FALSE;
    }

    first++;
    second++;
  }

  return (*first == '\0' && *second == '\0') ? TRUE : FALSE;
}

static char* command_trim(char* text) {
  char* end = NULL;

  if (!text) {
    return NULL;
  }

  while (*text != '\0' && isspace((unsigned char)*text)) {
    text++;
  }

  if (*text == '\0') {
    return text;
  }

  end = text + strlen(text) - 1;
  while (end >= text && isspace((unsigned char)*end)) {
    *end = '\0';
    end--;
  }

  return text;
}
