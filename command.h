/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

/**
 * @brief Number of command tokens (short and long)
 * @author Iker Díaz
 */
#define N_CMDT 2

/**
 * @brief Number of supported commands (including NO_CMD and UNKNOWN)
 * @author Iker Díaz
 */
#define N_CMD 11

/**
 * @brief Command token type selector
 * @author Iker Díaz
 */
typedef enum {
  CMDS, /*!< Short command token */
  CMDL  /*!< Long command token */
} CommandType;

/**
 * @brief Supported command codes
 * @author Iker Díaz
 */
typedef enum {
  NO_CMD = -1, /*!< Empty command */
  UNKNOWN,     /*!< Unknown command */
  EXIT,        /*!< Exit command */
  NEXT,        /*!< Move south */
  BACK,        /*!< Move north */
  LEFT,        /*!< Move west */
  RIGHT,       /*!< Move east */
  TAKE,        /*!< Take an object */
  DROP,        /*!< Drop the carried object */
  ATTACK,      /*!< Attack a hostile character */
  CHAT         /*!< Talk to a friendly character */
} CommandCode;

typedef struct _Command Command;

/**
 * @brief Command token table (short and long)
 * @author Iker Díaz
 */
extern char* cmd_to_str[N_CMD][N_CMDT];

/**
 * @brief It creates a new command
 * @author Iker Díaz
 *
 * @return a new command initialized, or NULL on error
 */
Command* command_create(void);

/**
 * @brief It destroys a command, freeing the allocated memory
 * @author Iker Díaz
 *
 * @param command a pointer to the command that must be destroyed
 * @return OK if everything goes well, ERROR otherwise
 */
Status command_destroy(Command* command);

/**
 * @brief It sets the code of a command
 * @author Iker Díaz
 *
 * @param command a pointer to the command
 * @param code command code to set
 * @return OK if everything goes well, ERROR otherwise
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief It gets the code of a command
 * @author Iker Díaz
 *
 * @param command a pointer to the command
 * @return the command code (or NO_CMD on error)
 */
CommandCode command_get_code(Command* command);

/**
 * @brief It sets the argument associated with a command
 * @author Iker Díaz
 *
 * @param command a pointer to the command
 * @param argument string with the argument to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status command_set_argument(Command* command, const char* argument);

/**
 * @brief It gets the argument associated with a command
 * @author Iker Díaz
 *
 * @param command a pointer to the command
 * @return the stored argument, or NULL on error
 */
const char* command_get_argument(Command* command);

/**
 * @brief It reads user input and updates the command code and argument
 * @author Iker Díaz
 *
 * @param command a pointer to the command
 * @return OK if everything goes well, ERROR otherwise
 */
Status command_get_user_input(Command* command);

#endif
