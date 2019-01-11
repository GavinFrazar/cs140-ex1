/* File:     exercise.h
 *
 * Purpose:  Head file for exercise.h and exercise_test.h
 *
 * Compile:  gcc -g -Wall -o exercise exercise.c exercise_test.c
 * Run:      ./exercise
 *
 */


struct key_action {
    char *cmd;
    int (*func)();
};
#define SUCC 1
#define FAIL 0

int exchange(int *, int *);
int reverse_array(int a[], int size);
int match_add(char *cmd, int arg);
int set_key_action(struct key_action *rec, char *cmd, int (*f)());
int match_action(struct key_action *map, char *cmd, int arg);
int mat_vect_mult(double A[], double x[], double y[], int m, int n);
int mat_mat_mult( double * matrix_A, double * matrix_B, double * matrix_C, int matrix_size ); 
