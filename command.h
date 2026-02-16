/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

/**
 * @brief Number of command tokens (short and long)
 * @author Profesores PPROG
 */
#define N_CMDT 2

/**
 * @brief Number of supported commands (including NO_CMD and UNKNOWN)
 * @author Iker Díaz
 */
#define N_CMD 7

typedef enum { CMDS, CMDL } CommandType;

/**
 * @brief Supported command codes
 * @author Iker Díaz
 */
typedef enum { NO_CMD = -1, UNKNOWN, EXIT, NEXT, BACK, TAKE, DROP } CommandCode;

typedef struct _Command Command;

/**
 * @brief Command token table (short and long)
 * @author Iker Díaz
 */
extern char* cmd_to_str[N_CMD][N_CMDT];

/**
 * @brief It creates a new command
 * @author Profesores PPROG
 *
 * @return a new command initialized, or NULL on error
 */
Command* command_create();

/**
 * @brief It destroys a command, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param command a pointer to the command that must be destroyed
 * @return OK if everything goes well, ERROR otherwise
 */
Status command_destroy(Command* command);

/**
 * @brief It sets the code of a command
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @param code command code to set
 * @return OK if everything goes well, ERROR otherwise
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief It gets the code of a command
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @return the command code (or NO_CMD on error)
 */
CommandCode command_get_code(Command* command);

/**
 * @brief It reads user input and updates the command code
 * @author Iker Díaz
 *
 * @param command a pointer to the command
 * @return OK if everything goes well, ERROR otherwise
 */
Status command_get_user_input(Command* command);

#endif
