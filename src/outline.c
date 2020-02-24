

#include "outline.h"


/*
 * Comparing two matrices and checking equality.
 * @param A, B: Matrices (Must be of the same order)
 * @param N: The final dimension
 * 
 * [COMMON TO ALL COMMUNICATION TYPES]
 */
int equal_matrix(float ** A, float ** B, int N) {
    for(int j=0; j<N; j++) {
        float *_r1 = A[j], *_r2 = B[j];
        for(int i=0; i<N; i++)
            if(fabs(_r1[i] - _r2[i]) > 1e-5)
                return 0;
    }
    return 1;
}

/*
 * Multiplication of Matrices (Serial)
 * @param AT, B: Matrices to be multiplied (both [32][N])
 * @param C: The final container matrix
 * @param N: The final order
 */
void multiply_serial(float * AT[32], float * B[32], float **C, int N) {
    // Looping multiplication
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            C[i][j] = 0;
            for(int k=0; k<32; k++)
                C[i][j] += (AT[k][i] * B[k][j]);
        }
}