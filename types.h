/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Maximum word size for strings in the project
 * @author Profesores PPROG
 */
#define WORD_SIZE 1000

/**
 * @brief Invalid id constant
 * @author Profesores PPROG
 */
#define NO_ID -1

/**
 * @brief Identifier type for game entities
 * @author Profesores PPROG
 */
typedef long Id;

/**
 * @brief Boolean type
 * @author Profesores PPROG
 */
typedef enum { FALSE, TRUE } Bool;

/**
 * @brief Function return status
 * @author Profesores PPROG
 */
typedef enum { ERROR, OK } Status;

/**
 * @brief Cardinal directions
 * @author Profesores PPROG
 */
typedef enum { N, S, E, W } Direction;

#endif
