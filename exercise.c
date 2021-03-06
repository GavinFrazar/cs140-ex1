/* File:     exercise.c
 *
 * Purpose:  Exercises to get familiar with C  programming
 *
 * Compile:  gcc -g -Wall -o exercise exercise.c exercse_test.c
 * Run:      ./exercise
 *
 */
#include "exercise.h"
#include <stdlib.h>
#include <string.h>

/*-------------------------------------------------------------------
 *Function: exchange
 * Purpose: exchange two parameters a and b.
 * 	Conduct a checkup for invalid input.
 * In/out args: 	a : first parameter.  It cannot be NULL.
 * 			b : second parameter.  It cannot be NULL.
 * Return SUCC (namely 1) if successful, otherwise FAIL (namely 0)
 * Example:  a=1; b=2; exchange(&a, &b)
 *	The above code leads a=2 and b=1.
 *
 *
 */
int exchange(int *a, int *b) {
  /*Your solution*/
  if (a && b) {
    if (*a == *b) {
      return SUCC;
    } else {
      *a ^= *b;
      *b ^= *a;
      *a ^= *b;
      return SUCC;
    }
  }
  return FAIL;
}

/*-------------------------------------------------------------------
 *Function: reverse_array
 * Purpose: Reverse an integer array. Conduct a check up for invalid inputs.
 * 		Do nothing with invalid input.
 *
 * In/out arg: 	a : array of integers.  It cannot be NULL.
 * In arg: 		size : array size.  It has to be positive (namely
 *size>0). Return SUCC (namely 1) if successful, otherwise FAIL (namely 0)
 *
 * Example:  int a[]={1,2}; reverse_array(a,2);
 *	The above code leads a[0]=2 and a[1]=1.
 */
int reverse_array(int a[], int size) {
  /*Your solution*/
  if (a && size > 0) {
    int i;
    for (i = 0; i < size / 2; ++i) {
      if (exchange(&a[i], &a[size - i - 1]) == FAIL) {
        return FAIL;
      };
    }
    return SUCC;
  } else {
    return FAIL;
  }
}
/*-------------------------------------------------------------------
 *Function: add1, add2, add3
 * Purpose: functions to increase a parameter  by  one, two, or three
 * In arg: 	x : input number
 * Return: the result of addition
 */

int add1(int x) { return x + 1; }
int add2(int x) { return x + 2; }
int add3(int x) { return x + 3; }
/*-------------------------------------------------------------------
 *Function: match_add
 * Purpose: call  add1, add2, or add3 when the input command is "add1", "add2",
 *or "add3". Conduct a checkup for invalid input. In args: 	cmd : command
 *string. It cannot be NULL. arg : input number Return: the result of addition.
 *If there is no match or its input is not valid, return the orignal value of
 *input number arg. Example:  match_add("add2", 3) returns 5.
 */
int match_add(char *cmd, int arg) {
  /*Your solution*/
  if (cmd) {
    if (strcmp("add1", cmd) == 0)
      return arg + 1;
    else if (strcmp("add2", cmd) == 0)
      return arg + 2;
    else if (strcmp("add3", cmd) == 0)
      return arg + 3;
    else
      return arg;
  } else {
    return arg;
  }
}

/*-------------------------------------------------------------------
 *Function: set_key_action
 * Purpose: Set the value of a key-action structure.
 * In/out args: rec : a key-action structure pointer.
 * In args	cmd : string key
 * 		f : funtion pointer
 * Return SUCC (namely 1) if successful, otherwise FAIL (namely 0)
 *	    If input rec is NULL or the function pointer is NULL, return FAIL
 */
int set_key_action(struct key_action *rec, char *cmd, int (*f)()) {
  if (rec != NULL || f == NULL) {
    rec->cmd = cmd;
    rec->func = f;
    return SUCC;
  }
  return FAIL;
}

/*-------------------------------------------------------------------
 *Function: match_action
 * Purpose: call  a corresponding function with the matched command.
 * 	Conduct a checkup for invalid input.
 * In args: 	map : a null-terminated array of key-action structures. It
 *cannot be NULL. cmd : command string. It cannot be NULL. arg : input number
 * Return: the result of addition. If input is not valid or there is no command
 *matched, return the input number arg. Example: struct key_action map[] = { {
 *"add1", add1 }, { "add2", add2 }, { "add3", add3 }, { 0, 0 }
 * };
 * Calling map_action(map, "add3", 1) will return 4.
 * When the cmd key does not match any entry in the table, just return the
 *original input argumment For example, calling map_action(map, "add4", 1) will
 *return 2.
 *
 */

int match_action(struct key_action map[], char *cmd, int arg) {
  /*Your solution*/
  if (map && cmd) {
    int i;
    for (i = 0; map[i].cmd != NULL; ++i) {
      if (strcmp(map[i].cmd, cmd) == 0)
        return map[i].func(arg);
    }
  }
  return arg;
}

/*-------------------------------------------------------------------
 * Function:   mat_vect_mult
 * Purpose:    Multiply a matrix by a vector. Do nothing with invalid input.
 * In args:    matrix_A: the input matrix A. It cannot be NULL.
 *             x: the vector being multiplied by A. It cannot be NULL.
 *             m: the number of rows in A and components in y. It has to be
 * positive. n: the number of columns in A components in x. It has to be
 * positive. Out args:   y: the product vector y=y+Ax.  It cannot be NULL.
 * Return SUCC (namely 1) if successful, otherwise 0
 *
 * Matrix vector multiplication algorithm
 * for i=0 to m-1
 *   for j=0 to n-1
 *      y[i]=y[i] + A[i][j]*x[j]
 * Matrix format: Row-wise linerized format. A[i][j] is stored in
 * matrix_A[i*n+j] Return SUCC (namely 1) if successful, otherwise 0
 */
int mat_vect_mult(double matrix_A[] /* in  */, double x[] /* in  */,
                  double y[] /* out */, int m /* in  */, int n /* in  */) {
  int i, j;
  if (matrix_A == NULL || x == NULL || y == NULL || m <= 0 || n <= 0)
    return FAIL;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      y[i] += matrix_A[i * n + j] * x[j];
    }
  }
  return SUCC;
}

/*-------------------------------------------------------------------
 * Function: mat_mat_mult
 * Purpose: Multiply square matrices and add product to existing result matrix
 * 	Conduct a checkup for invalid input and do nothing with invalid input.
 * In args: 	matrix_A : first matrix A. It cannot be NULL.
 * 		matrix_B : second matrix B. It cannot be NULL.
 *  		matrix_size : number of rows (same as number of columns). It has
 * to be positive. Out args: 	marix_C: result matrix C= C+ A*B. It cannot be
 * NULL. Return SUCC (namely 1) if successful, otherwise 0
 *
 * Matrix format: Row-wise linearized format. A[i][j] is stored in
 * matrix_A[i*matrix_size+j]
 *
 * Square matrix matrix multiplication algorithm with dimension n
 * for i=0 to n-1
 *   for j=0 to n-1
 *      for k=0 to n-1
 *      	C[i][j]=C[i][j] + A[i][k]*B[k][j]
 */

int mat_mat_mult(double *matrix_A, double *matrix_B, double *matrix_C,
                 int matrix_size) {
  /*Your solution*/
  int i, j, k;
  if (matrix_A && matrix_B && matrix_C && matrix_size > 0) {
    for (i = 0; i < matrix_size; ++i) {
      for (j = 0; j < matrix_size; ++j) {
        for (k = 0; k < matrix_size; ++k) {
          matrix_C[i * matrix_size + j] +=
              matrix_A[i * matrix_size + k] * matrix_B[k * matrix_size + j];
        }
      }
    }
    return SUCC;
  } else {
    return FAIL;
  }
}
