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
	int block_size = 40;

	double *Result = (double *) calloc(N * N, sizeof(double));
	double *Result2 = (double *) calloc(N * N, sizeof(double));
	// Result = A * B
	for (int ii = 0; ii < N; ii += block_size) {
    	for (int kk = 0; kk < N; kk += block_size) {
        	for (int jj = 0; jj < N; jj += block_size) {
            	int i_max = ii + block_size;
            	int j_max = jj + block_size;
            	int k_max = kk + block_size;
            	for (int i = ii; i < i_max; i++) {
					int k_min = kk > i ? kk : i;
					double *A_i_orig = A + i * N + k_min;
                	for (int j = jj; j < j_max; j++) {
                    	register double sum = 0;
						double *A_i = A_i_orig;
						double *B_i = B + k_min * N + j;
						if (k_min % 2 == 1)
                    		for (int k = k_min; k < k_max; k++) {
                        		sum += (*A_i) * (*B_i);
								A_i++;
								B_i += N;
                    		}
						else if (k_min % 4 == 0)
							for (int k = k_min / 4; k < k_max / 4; k++) {
                        		sum += (*A_i) * (*B_i);
								A_i++;
								B_i += N;
								sum += (*A_i) * (*B_i);
								A_i++;
								B_i += N;
								sum += (*A_i) * (*B_i);
								A_i++;
								B_i += N;
								sum += (*A_i) * (*B_i);
								A_i++;
								B_i += N;
                    		}
						else
							for (int k = k_min / 2; k < k_max / 2; k++) {
                        		sum += (*A_i) * (*B_i);
								A_i++;
								B_i += N;
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
    	for (int kk = 0; kk < N; kk += block_size) {
        	for (int jj = 0; jj < N; jj += block_size) {
            	int i_max = ii + block_size;
            	int j_max = jj + block_size;
            	int k_max = kk + block_size;
            	for (int i = ii; i < i_max; i++) {
                	for (int j = jj; j < j_max; j++) {
						int k_min = kk > j ? kk : j;
                    	register double sum = 0;
						double *R_i = Result + i * N + k_min;
						double *A_t_i = A + j * N + k_min;
						if (k_min % 2 == 1)
                    		for (int k = k_min; k < k_max; k++) {
                        		sum += (*R_i) * (*A_t_i);
								R_i++;
								A_t_i++;
                    		}
						else if (k_min % 4 == 0)
							for (int k = k_min / 4; k < k_max / 4; k++) {
                        		sum += (*R_i) * (*A_t_i);
								R_i++;
								A_t_i++;
								sum += (*R_i) * (*A_t_i);
								R_i++;
								A_t_i++;
								sum += (*R_i) * (*A_t_i);
								R_i++;
								A_t_i++;
								sum += (*R_i) * (*A_t_i);
								R_i++;
								A_t_i++;
                    		}
						else
							for (int k = k_min / 2; k < k_max / 2; k++) {
                        		sum += (*R_i) * (*A_t_i);
								R_i++;
								A_t_i++;
								sum += (*R_i) * (*A_t_i);
								R_i++;
								A_t_i++;
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
    	for (int kk = 0; kk < N; kk += block_size) {
        	for (int jj = 0; jj < N; jj += block_size) {
            	int i_max = ii + block_size;
            	int j_max = jj + block_size;
            	int k_max = kk + block_size;
            	for (int i = ii; i < i_max; i++) {
					double *B_t_i_orig = B + kk * N + i;
                	for (int j = jj; j < j_max; j++) {
                    	register double sum = 0;
						double *B_t_i = B_t_i_orig;
						double *B_t_i2 = B + j * N + kk;
                    	for (int k = kk / 4; k < k_max / 4; k++) {
                        	sum += (*B_t_i) * (*B_t_i2);
							B_t_i += N;
							B_t_i2++;
							sum += (*B_t_i) * (*B_t_i2);
							B_t_i += N;
							B_t_i2++;
							sum += (*B_t_i) * (*B_t_i2);
							B_t_i += N;
							B_t_i2++;
							sum += (*B_t_i) * (*B_t_i2);
							B_t_i += N;
							B_t_i2++;
                    	}
                    	Result[i * N + j] += sum;
                	}
            	}
        	}
    	}
	}
	
	return Result;
}
