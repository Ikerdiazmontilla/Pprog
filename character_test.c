/**
 * @brief It defines character unit tests
 *
 * @file character_test.c
 * @author Iker Díaz
 * @version 0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>

#include "character.h"

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

int main() {
  Character* character = NULL;

  character = character_create(1);
  print_test_result(character != NULL);
  print_test_result(character_create(NO_ID) == NULL);

  print_test_result(character_set_name(character, "Ghost") == OK);
  print_test_result(character_set_name(NULL, "Ghost") == ERROR);
  print_test_result(strcmp(character_get_name(character), "Ghost") == 0);
  print_test_result(character_get_name(NULL) == NULL);

  print_test_result(character_set_gdesc(character, "^M*") == OK);
  print_test_result(character_set_gdesc(NULL, "^M*") == ERROR);
  print_test_result(strcmp(character_get_gdesc(character), "^M*") == 0);
  print_test_result(character_get_gdesc(NULL) == NULL);

  print_test_result(character_set_health(character, 5) == OK);
  print_test_result(character_set_health(character, -1) == ERROR);
  print_test_result(character_get_health(character) == 5);
  print_test_result(character_get_health(NULL) == -1);

  print_test_result(character_set_friendly(character, TRUE) == OK);
  print_test_result(character_set_friendly(NULL, TRUE) == ERROR);
  print_test_result(character_get_friendly(character) == TRUE);
  print_test_result(character_get_friendly(NULL) == FALSE);

  print_test_result(character_set_message(character, "Hello adventurer") == OK);
  print_test_result(character_set_message(NULL, "Hello adventurer") == ERROR);
  print_test_result(strcmp(character_get_message(character), "Hello adventurer") == 0);
  print_test_result(character_get_message(NULL) == NULL);

  print_test_result(character_get_id(character) == 1);
  print_test_result(character_get_id(NULL) == NO_ID);

  print_test_result(character_print(character) == OK);
  print_test_result(character_print(NULL) == ERROR);

  print_test_result(character_destroy(character) == OK);
  print_test_result(character_destroy(NULL) == ERROR);

  printf("\nPassed: %d\nFailed: %d\n", tests_passed, tests_failed);

  return tests_failed == 0 ? 0 : 1;
}
