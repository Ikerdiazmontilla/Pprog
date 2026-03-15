/**
 * @brief It defines space unit tests
 *
 * @file space_test.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>

#include "space.h"

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
  Space* space = NULL;
  Id* ids = NULL;

  space = space_create(11);
  print_test_result(space != NULL);
  print_test_result(space_create(NO_ID) == NULL);

  print_test_result(space_set_name(space, "Entry") == OK);
  print_test_result(strcmp(space_get_name(space), "Entry") == 0);

  print_test_result(space_set_north(space, 1) == OK);
  print_test_result(space_get_north(space) == 1);
  print_test_result(space_set_south(space, 2) == OK);
  print_test_result(space_get_south(space) == 2);
  print_test_result(space_set_east(space, 3) == OK);
  print_test_result(space_get_east(space) == 3);
  print_test_result(space_set_west(space, 4) == OK);
  print_test_result(space_get_west(space) == 4);

  print_test_result(space_is_empty_of_objects(space) == TRUE);
  print_test_result(space_add_object(space, 21) == OK);
  print_test_result(space_add_object(space, 22) == OK);
  print_test_result(space_has_object(space, 21) == TRUE);
  print_test_result(space_get_n_objects(space) == 2);

  ids = space_get_objects_ids(space);
  print_test_result(ids != NULL);
  print_test_result(ids[0] == 21 && ids[1] == 22);

  print_test_result(space_remove_object(space, 21) == OK);
  print_test_result(space_remove_object(space, 99) == ERROR);
  print_test_result(space_is_empty_of_objects(space) == FALSE);

  print_test_result(space_set_character(space, 31) == OK);
  print_test_result(space_get_character(space) == 31);
  print_test_result(space_set_character(space, NO_ID) == OK);
  print_test_result(space_get_character(space) == NO_ID);

  print_test_result(space_set_gdesc(space, 0, "abcdefghi") == OK);
  print_test_result(strcmp(space_get_gdesc(space, 0), "abcdefghi") == 0);
  print_test_result(space_set_gdesc(space, 5, "bad") == ERROR);
  print_test_result(space_get_gdesc(space, 5) == NULL);

  print_test_result(space_print(space) == OK);
  print_test_result(space_print(NULL) == ERROR);

  print_test_result(space_destroy(space) == OK);
  print_test_result(space_destroy(NULL) == ERROR);

  printf("\nPassed: %d\nFailed: %d\n", tests_passed, tests_failed);

  return (tests_failed == 0) ? 0 : 1;
}
