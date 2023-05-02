/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	// calculate A transposed
	double *A_t = (double *) calloc(N * N, sizeof(double));
	for (int i = 0; i < N; i++) {
		double *A_t_i = A_t + i * N + i;
		double *A_i = A + i * N + i;
		for (int j = i; j < N; j++) {
			*A_t_i = *A_i;
			A_t_i += N;
			A_i++;
		}
	}
		
	// calculate B transposed
	double *B_t = (double *) calloc(N * N, sizeof(double));
	for (int i = 0; i < N; i++) {
		double *B_t_i = B_t + i;
		double *B_i = B + i * N;
		for (int j = 0; j < N; j++) {
			*B_t_i = *B_i;
			B_t_i += N;
			B_i++;
		}
	}

	int block_size = 40;

	double *Result = (double *) calloc(N * N, sizeof(double));
	double *Result2 = (double *) calloc(N * N, sizeof(double));
	// Result = A * B
	for (int ii = 0; ii < N; ii += block_size) {
    	for (int jj = 0; jj < N; jj += block_size) {
        	for (int kk = 0; kk < N; kk += block_size) {
            	int i_max = ii + block_size;
            	int j_max = jj + block_size;
            	int k_max = kk + block_size;

            	for (int i = ii; i < i_max; i++) {
					int k_min = kk > i ? kk : i;
                	for (int j = jj; j < j_max; j++) {
                    	register double sum = 0;
						double *A_i = A + i * N + k_min;
						double *B_i = B + k_min * N + j;
                    	for (int k = k_min; k < k_max; k++) {
                        	sum += (*A_i) * (*B_i);
							A_i++;
							B_i += N;
                    	}
                    	Result[i * N + j] += sum;
                	}
            	}
        	}
    	}
	}
	// Result *= A_t
	for (int ii = 0; ii < N; ii += block_size) {
    	for (int jj = 0; jj < N; jj += block_size) {
        	for (int kk = 0; kk < N; kk += block_size) {
            	int i_max = ii + block_size;
            	int j_max = jj + block_size;
            	int k_max = kk + block_size;

            	for (int i = ii; i < i_max; i++) {
                	for (int j = jj; j < j_max; j++) {
						int k_min = kk > j ? kk : j;
                    	register double sum = 0;
						double *R_i = Result + i * N + k_min;
						double *A_t_i = A_t + k_min * N + j;
                    	for (int k = k_min; k < k_max; k++) {
                        	sum += (*R_i) * (*A_t_i);
							R_i++;
							A_t_i += N;
                    	}
                    	Result2[i * N + j] += sum;
                	}
            	}
        	}
    	}
	}
	free(Result);
	Result = Result2;
	// Result += B_t * B_t
	for (int ii = 0; ii < N; ii += block_size) {
    	for (int jj = 0; jj < N; jj += block_size) {
        	for (int kk = 0; kk < N; kk += block_size) {
            	int i_max = ii + block_size;
            	int j_max = jj + block_size;
            	int k_max = kk + block_size;

            	for (int i = ii; i < i_max; i++) {
                	for (int j = jj; j < j_max; j++) {
                    	register double sum = 0;
						double *B_t_i = B_t + i * N + kk;
						double *B_t_i2 = B_t + kk * N + j;
                    	for (int k = kk; k < k_max; k++) {
                        	sum += (*B_t_i) * (*B_t_i2);
							B_t_i++;
							B_t_i2 += N;
                    	}
                    	Result[i * N + j] += sum;
                	}
            	}
        	}
    	}
	}
	
	free(A_t);
	free(B_t);

	return Result;
}
