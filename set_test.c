/**
 * @brief It defines set unit tests
 *
 * @file set_test.c
 * @author Iker Díaz
 * @version 0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>

#include "set.h"

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
  Set* set = NULL;
  Set* other_set = NULL;
  Id* ids = NULL;

  set = set_create();
  print_test_result(set != NULL);
  other_set = set_create();
  print_test_result(other_set != NULL);

  print_test_result(set_add_id(set, 11) == OK);
  print_test_result(set_add_id(set, 11) == ERROR);

  print_test_result(set_add_id(set, 12) == OK);
  print_test_result(set_get_n_ids(set) == 2);

  print_test_result(set_find_id(set, 11) == TRUE);
  print_test_result(set_find_id(set, 99) == FALSE);

  ids = set_get_ids(set);
  print_test_result(ids != NULL);
  print_test_result(ids[0] == 11 && ids[1] == 12);

  print_test_result(set_del_id(set, 11) == OK);
  print_test_result(set_del_id(set, 11) == ERROR);

  print_test_result(set_print(set) == OK);
  print_test_result(set_print(NULL) == ERROR);

  print_test_result(set_get_n_ids(NULL) == -1);
  print_test_result(set_get_ids(NULL) == NULL);

  print_test_result(set_destroy(set) == OK);
  print_test_result(set_destroy(other_set) == OK);
  print_test_result(set_destroy(NULL) == ERROR);

  printf("\nPassed: %d\nFailed: %d\n", tests_passed, tests_failed);

  return (tests_failed == 0) ? 0 : 1;
}
