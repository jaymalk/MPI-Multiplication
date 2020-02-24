

#include "outline.h"


// MAIN
int main(int argc, char const *argv[])
{
    // Matrix order
    int N = 1000;

    // rank and size
    int rank, size;
    // matrix containers
    float *A[32], *B[32], **C, **C_S;

    // Starting MPI pipeline
    MPI_Init(NULL, NULL);
    
    // Extracting Rank and Processor Count
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Checking for processor id 0
    if(rank == 0) {
        // Initialising the matrices
        for(int i=0; i<32; i++) {
            A[i] = (float *)malloc(sizeof(float) * N);
            B[i] = (float *)malloc(sizeof(float) * N);
            for(int j=0; j<N; j++) {
                A[i][j] = drand48();
                B[i][j] = drand48();
            }
        }
        // Initialising C and C_S
        C = (float **)malloc(sizeof(float *) * N);
        C_S = (float **)malloc(sizeof(float *) * N);
        for(int i=0; i<N; i++) {
            C[i] = (float *)malloc(sizeof(float) * N);
            C_S[i] = (float *)malloc(sizeof(float) * N);
        }
        printf("Initialised.\n");
        multiply_serial(A, B, C, N);
        printf("Equal: %d\n", equal_matrix(C, C, N));
    }
    // Other processes (id != 0)
    else {
        printf("Process with rank: %d or %d\n", rank, size);
    }

    // Ending MPI pieline
    MPI_Finalize();
    return 0;
}