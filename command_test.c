/**
 * @brief It defines command unit tests
 *
 * @file command_test.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>

#include "command.h"

int tests_passed = 0;
int tests_failed = 0;
int test_number = 1;

/**
 * @brief It prints the result of a test case
 * @author Iker Díaz
 *
 * @param result TRUE if the test passed, FALSE otherwise
 */
void print_test_result(Bool result) {
  if (result == TRUE) {
    tests_passed++;
    printf("TEST %d: OK\n", test_number);
  } else {
    tests_failed++;
    printf("TEST %d: ERROR\n", test_number);
  }

  test_number++;
}

int main(void) {
  Command* command = NULL;

  command = command_create();
  print_test_result(command != NULL);

  print_test_result(command_set_code(command, TAKE) == OK);
  print_test_result(command_get_code(command) == TAKE);

  print_test_result(command_set_argument(command, "Sword") == OK);
  print_test_result(strcmp(command_get_argument(command), "Sword") == 0);

  print_test_result(command_set_argument(command, command_get_argument(command)) == OK);
  print_test_result(strcmp(command_get_argument(command), "Sword") == 0);

  print_test_result(command_set_argument(NULL, "Sword") == ERROR);
  print_test_result(command_set_argument(command, NULL) == ERROR);
  print_test_result(command_get_argument(NULL) == NULL);

  print_test_result(command_destroy(command) == OK);
  print_test_result(command_destroy(NULL) == ERROR);

  printf("\nPassed: %d\nFailed: %d\n", tests_passed, tests_failed);

  return (tests_failed == 0) ? 0 : 1;
}
