

#include "outline.h"


// MAIN
int main(int argc, char const *argv[])
{
    // Matrix order
    int N = 4000;

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
        // request values for sending
        MPI_Request send_req[64*(size-1)];
        int req_index = 0;

        // Initialising the matrices
        for(int i=0; i<32; i++) {
            A[i] = (float *)malloc(sizeof(float) * N);
            B[i] = (float *)malloc(sizeof(float) * N);
            for(int j=0; j<N; j++) {
                A[i][j] = drand48();
                B[i][j] = drand48();
            }
            for(int p=1; p<size; p++) {
                MPI_Isend(A[i], N, MPI_FLOAT, p, 0, MPI_COMM_WORLD, &send_req[req_index++]);
                MPI_Isend(B[i], N, MPI_FLOAT, p, 0, MPI_COMM_WORLD, &send_req[req_index++]);
            }
        }

        // Initialising C and C_S
        C = (float **)malloc(sizeof(float *) * N);
        C_S = (float **)malloc(sizeof(float *) * N);
        for(int i=0; i<N; i++) {
            C[i] = (float *)malloc(sizeof(float) * N);
            C_S[i] = (float *)malloc(sizeof(float) * N);
        }

        // Calculating C serially
        multiply_serial(A, B, C_S, N);

        // Waiting that all the data has been sent
        MPI_Waitall(64*(size-1), send_req, MPI_STATUS_IGNORE);

        // request values for sending
        MPI_Request recv_req[N];
        req_index = 0;

        // Getting C from other values
        for(int p=1; p<size; p++) {
            int start = (N*(p-1))/(size-1), end = (N*(p))/(size-1);
            for(int i=start; i<end; i++) 
                MPI_Irecv(C[i], N, MPI_FLOAT, p, 0, MPI_COMM_WORLD, &recv_req[req_index++]);
        }

        // Waiting that all the data has been sent
        MPI_Waitall(N, recv_req, MPI_STATUS_IGNORE);

        // Checking if both are equal
        fprintf(__stdoutp, "Equal: %d\n", equal_matrix(C_S, C, N));
    }
    // Other processes (id != 0)
    else {

        // request values for recieving
        MPI_Request recv_req[64];
        int req_index = 0;

        // Initialising the matrices and getting the values
        for(int i=0; i<32; i++) {
            A[i] = (float *)malloc(sizeof(float) * N);
            B[i] = (float *)malloc(sizeof(float) * N);
            MPI_Irecv(A[i], N, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &recv_req[req_index++]);
            MPI_Irecv(B[i], N, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &recv_req[req_index++]);
        }

        // Calculating boundaries
        int start = (N*(rank-1))/(size-1), end = (N*(rank))/(size-1);

        // Initialising the respective matrix
        C = (float **)malloc(sizeof(float *) * (end-start));

        // Waiting that all the data has been recieved
        MPI_Waitall(64, recv_req, MPI_STATUS_IGNORE);

        // Multiplying the respective sections
        for(int i=start; i<end; i++) {
            C[i-start] = (float *)malloc(sizeof(float)*N);
            for(int j=0; j<N; j++) {
                C[i-start][j] = 0;
                for(int k=0; k<32; k++)
                    C[i-start][j] += A[k][i]*B[k][j];
            }
        }

        // request values for sending
        MPI_Request send_req[end-start];
        req_index = 0;

        // Sending all the calculated values
        for(int i=start; i<end; i++)
            MPI_Isend(C[i-start], N, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &send_req[req_index++]);

        // Waiting for all the data to be sent
        MPI_Waitall(end-start, send_req, MPI_STATUS_IGNORE);
    }

    // Ending MPI pieline
    MPI_Finalize();
    return 0;
}