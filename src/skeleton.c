
#include "skeleton.h"

int IsEqual(float *A, float *B, int m, int n){
    
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(!(fabs(A[i*n + j]-B[i*n + j])<0.000000001))
                return 0;
    
    return 1;
}

void Matrix_Multiply(float *A, float *B, float *C, int m, int n, int p){
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < p; j++){
			C[i*p + j] = 0;
			for (int k = 0; k < n; k++)
				C[i*p + j] += A[i*n + k] * B[k*p + j];
		}
    }
}

int main(){
    int N = 3;
    float *A = (float *)malloc(sizeof(float *)*(N*N));
    float *B = (float *)malloc(sizeof(float *)*(N*N));
    float *C = (float *)malloc(sizeof(float *)*(N*N));

    for(int i = 0; i < N*N; i++){
        A[i] = drand48();
        B[i] = drand48();
        printf("%f %f \n", A[i], B[i]);
    }

    Matrix_Multiply(A, B, C, N, N, N);

    for(int i = 0; i < N*N; i++)
        printf("%f \n", C[i]);
        
    printf("ISEQUAL %d\n",IsEqual(C, C, N, N));
}