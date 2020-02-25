

#include "outline.h"


// MAIN
int main(int argc, char const *argv[])
{
    // Matrix order
    int N = 8000;

    // rank and size
    int rank, size;
    // matrix containers
    float *A[32], *B[32], **C, **C_S;

    // Starting MPI pipeline
    MPI_Init(NULL, NULL);
    
    // Extracting Rank and Processor Count
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Operations Common to all
    
    // Initialising A and B
    for(int i=0; i<32; i++) {
        A[i] = (float *)malloc(sizeof(float) * N);
        B[i] = (float *)malloc(sizeof(float) * N);
    }
    // Initialising C and C_S
    C = (float **)malloc(sizeof(float *) * N);
    C_S = (float **)malloc(sizeof(float *) * N);
    for(int i=0; i<N; i++) {
        C[i] = (float *)malloc(sizeof(float) * N);
        C_S[i] = (float *)malloc(sizeof(float) * N);
    }

    // Initialisation in A
    if(rank == 0) {
        // Setting the values in matrices A & B
        for(int i=0; i<32; i++) {
            for(int j=0; j<N; j++) {
                A[i][j] = drand48();
                B[i][j] = drand48();
            }
        }
    }

    // BROADCASTING
    for(int i=0; i<32; i++) {
        MPI_Bcast(A[i], N, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Bcast(B[i], N, MPI_FLOAT, 0, MPI_COMM_WORLD);
    }

    // Serial Multiplication in RANK 0
    if(rank == 0) {
        // Calculating C serially
        multiply_serial(A, B, C_S, N);
    }
    // Otherwise segmented multiplication
    else {
        // Calculating boundaries
        int start = (N*(rank-1))/(size-1), end = (N*(rank))/(size-1);
        // Multiplying the respective sections
        for(int i=start; i<end; i++) {
            C[i] = (float *)malloc(sizeof(float)*N);
            for(int j=0; j<N; j++) {
                C[i][j] = 0;
                for(int k=0; k<32; k++)
                    C[i][j] += A[k][i]*B[k][j];
            }
        }
    }

    // Broadcasting multiplied value, from all ranks to rank 0
    for(int p=1; p<size; p++) {
        int start = (N*(p-1))/(size-1), end = (N*(p))/(size-1);
        for(int i=start; i<end; i++) 
            MPI_Bcast(C[i], N, MPI_FLOAT, p, MPI_COMM_WORLD);
    }

    // Comparing in rank = 0
    if(rank == 0) {
        // Checking if both are equal
        fprintf(__stdoutp, "Equal: %d\n", equal_matrix(C_S, C, N));
    }

    // Ending MPI pieline
    MPI_Finalize();
    return 0;
}