

#ifndef __OUTLINE
#define __OUTLINE


#include "include.h"


// For measuring time
struct timespec start_time, end_time;


/*
 * Comparing two matrices and checking equality.
 * @param A, B: Matrices (Must be of the same order)
 * @param N: The final dimension
 * 
 * [COMMON TO ALL COMMUNICATION TYPES]
 */
int equal_matrix(float **, float **, int);


/*
 * Multiplication of Matrices (Parallelised)
 * @param A.T, B: Matrices to be multiplied (both [32][N])
 * @param C: The final container matrix
 * @param N: The final order
 */
void multiply_parallel(float *[32], float *[32], float **, int);

/*
 * Multiplication of Matrices (Serial)
 * @param A.T, B: Matrices to be multiplied (both [32][N])
 * @param C: The final container matrix
 * @param N: The final order
 */
void multiply_serial(float *[32], float *[32], float **, int);

#endif /*__OUTLINE*/