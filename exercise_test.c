/* File:     exercise_test.c
 *
 * Purpose:  Unit tests for functions defined in exercise.c
 *
 * Compile:  gcc -g -Wall -o exercise exercise.c exercise_test.c
 * Run:      ./exercise
 *
 */
#include "exercise.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-------------------------------------------------------------------
 * Test exchange()
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 */
char *exchange_test(void) {
  /*Your solution*/
  int a, b, dummy;
  int *c = NULL;
  a = 3;
  b = 4;
  mu_assert("failed to identify invalid pointer in a",
            exchange(c, &dummy) == FAIL);
  mu_assert("failed to identify invalid pointer in b",
            exchange(&dummy, c) == FAIL);
  mu_assert("failed to identify valid pointers", exchange(&a, &b) == SUCC);
  mu_assert("failed to swap a and b values", a == 4 && b == 3);
  exchange(&a, &a);
  mu_assert("failed to swap pointer with itself", a == 4);
  return NULL;
}

/*-------------------------------------------------------------------
 * Test reverse_array()
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 */
char *reverse_array_test(void) {
  /*Your solution*/
  int arr[] = {1, 2};
  int even_arr[] = {1, 2, 3, 4};
  int odd_arr[] = {1, 2, 3};

  mu_assert("Failed to detect invalid array pointer",
            reverse_array(NULL, 3) == FAIL);
  mu_assert("Failed to detect 0 length array", reverse_array(arr, 0) == FAIL);
  mu_assert("Failed to successfully sort valid even array",
            reverse_array(even_arr, sizeof(even_arr) / sizeof(int)) == SUCC);
  mu_assert("Failed to successfully sort valid odd array",
            reverse_array(odd_arr, sizeof(odd_arr) / sizeof(int)) == SUCC);
  mu_assert("Failed to reverse even length array",
            even_arr[0] == 4 && even_arr[1] == 3 && even_arr[2] == 2 &&
                even_arr[3] == 1);
  mu_assert("Failed to revere odd length array",
            odd_arr[0] == 3 && odd_arr[1] == 2 && odd_arr[2] == 1);
  return NULL;
}
/*-------------------------------------------------------------------
 * Test match_add()
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 */
char *match_add_test(void) {
  /*Your solution*/
  mu_assert("Failed to detect NULL cmd", match_add(NULL, 2) == 2);
  mu_assert("Failed to return unchanged arg for no matching cmd",
            match_add("add7", 1) == 1);
  mu_assert("Failed to correctly match add1 cmd", match_add("add1", 1) == 2);
  mu_assert("Failed to correctly match add2 cmd", match_add("add2", 1) == 3);
  mu_assert("Failed to correctly match add3 cmd", match_add("add3", 1) == 4);
  return NULL;
}

/*-------------------------------------------------------------------
 * Test set_key_action()
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 */
int del1(int x) { return x - 1; }
int del2(int x) { return x - 2; }

char *set_key_action_test(void) {
  struct key_action *rec =
      (struct key_action *)malloc(sizeof(struct key_action));
  char *key = "del1";
  int ret = set_key_action(rec, key, del1);
  mu_assert("Error in set_key_action with del1 key",
            strcmp(key, rec->cmd) == 0);
  mu_assert("Error in set_key_action with del1 value", rec->func == del1);
  mu_assert("Error in set_key_action with del1 value", ret == SUCC);
  ret = set_key_action(NULL, key, del1);
  mu_assert("Error in set_key_action with NULL value", ret == FAIL);

  /*All comparisons/tests are valid*/
  return NULL;
}

/*-------------------------------------------------------------------
 * Test match_action()
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 */

struct key_action map[] = {{"del1", del1}, {"del2", del2}, {0, 0}};
char *match_action_test(void) {
  /*Your solution*/
  mu_assert("Failed to detect NULL map", match_action(NULL, "del1", 1) == 1);
  mu_assert("Failed to detect NULL cmd", match_action(map, NULL, 1) == 1);
  mu_assert("Failed to detect no matching action",
            match_action(map, "del3", 1) == 1);
  mu_assert("Failed to match del1 cmd", match_action(map, "del1", 1) == 0);
  mu_assert("Failed to match del2 cmd", match_action(map, "del2", 1) == -1);
  return NULL;
}
/*-------------------------------------------------------------------
 * Test if the  matrix-vector multiplicatioon result is expected.
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 * m is number of rows and n is the number of columns
 */
char *test_vect(double y[], int m, int n) {
  int i;
  double expected = n * (n - 1) / 2;
  for (i = 0; i < m; i++) {
#ifdef DEBUG1
    printf("Expected %f actual %f in mat_vect_mult\n", expected, y[i]);
#endif
    mu_assert("Error in mat_vect_mult, one mismatch", y[i] == expected);
  }
  return NULL;
}
/*-------------------------------------------------------------------
 * Test matrix vector multiplciation
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 */
char *mat_vect_mult_test1(int m, int n) {
  int i, j;
  char *msg;
  double *A = malloc(m * n * sizeof(double));
  double *x = malloc(n * sizeof(double));
  double *y = malloc(m * sizeof(double));
  for (j = 0; j < n; j++) {
    x[j] = j;
  }
  for (i = 0; i < m; i++) {
    y[i] = 0;
  }
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++)
      A[i * n + j] = 1;
  }

  int ret = mat_vect_mult(A, x, y, m, n);
  msg = test_vect(y, m, n);
  free(A);
  free(x);
  free(y);
  if (msg != NULL)
    return msg;
  if (ret != SUCC)
    return "Error in mat_vect_mult return value";
  return NULL;
}

/*-------------------------------------------------------------------
 * Test matrix vector multiplication.
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 */
char *mat_vect_mult_test(void) { return mat_vect_mult_test1(2, 4); }

char *mat_vect_mult_test_null(void) {
  double A = 1;
  int n = 1;
  int ret = mat_vect_mult(NULL, NULL, NULL, n, n);
  mu_assert("Error in mat_mat_mult, NULL input", ret == FAIL);
  ret = mat_vect_mult(&A, &A, &A, 0, n);
  mu_assert("Error in mat_mat_mult, NULL input", ret == FAIL);
  return NULL;
}

/*-------------------------------------------------------------------
 * Test matrix matrix multiplication
 * If failed, return a message string showing the failed point
 * If successful, return NULL
 */
char *mat_mat_mult_test(void) {
  /* Your solution*/
  enum { mat_size = 3 }; // constexpr without using preprocessor :D
  int i;
  double A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double B[] = {11, 12, 13, 14, 15, 16, 17, 18, 19};
  double C[mat_size * mat_size] = {0};
  double oracle[] = {90, 96, 102, 216, 231, 246, 342, 366, 390};
  const double tolerance = 0.01;
  mu_assert("Failed to detect NULL A",
            mat_mat_mult(NULL, B, C, mat_size) == FAIL);
  mu_assert("Failed to detect NULL B",
            mat_mat_mult(A, NULL, C, mat_size) == FAIL);
  mu_assert("Failed to detect NULL C",
            mat_mat_mult(A, B, NULL, mat_size) == FAIL);
  mu_assert("Failed to detect non-positive size",
            mat_mat_mult(A, B, C, 0) == FAIL);
  mu_assert("Failed to successfully return for valid input",
            mat_mat_mult(A, B, C, mat_size) == SUCC);
  for (i = 0; i < mat_size * mat_size; ++i) {
    mu_assert("Failed to correctly implement algorithm",
              (C[i] - oracle[i]) < tolerance);
  }
  return NULL;
}
/*-------------------------------------------------------------------
 * Run all tests.  Ignore returned messages.
 */
void run_all_tests(void) {
  /* Call all tests.  You can add more tests*/
  mu_run_test(exchange_test);
  mu_run_test(reverse_array_test);
  mu_run_test(match_add_test);
  mu_run_test(set_key_action_test);
  mu_run_test(match_action_test);
  mu_run_test(mat_vect_mult_test);
  mu_run_test(mat_vect_mult_test_null);
  mu_run_test(mat_mat_mult_test);
}

/*-------------------------------------------------------------------
 * The main entrance to run all tests.
 * If failed, return a message string showing the first failed point
 * Print the test stats
 */
int main(int argc, char *argv[]) {
  run_all_tests();

  mu_print_test_summary("Summary:");
  return 0;
}
