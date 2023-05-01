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
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			A_t[j * N + i] = A[i * N + j];
	// calculate B transposed
	double *B_t = (double *) calloc(N * N, sizeof(double));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			B_t[j * N + i] = B[i * N + j];

	double *Result = (double *) calloc(N * N, sizeof(double));
	// Result = A * B
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = i; k < N; k++) {
				Result[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}
	// Result *= A_t
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double sum = 0;
			for (int k = j; k < N; k++) {
				sum += Result[i * N + k] * A_t[k * N + j];
			}
			Result[i * N + j] = sum;
		}
	}
	// Result += B_t * B_t
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double sum = 0;
			for (int k = 0; k < N; k++) {
				sum += B_t[i * N + k] * B_t[k * N + j];
			}
			Result[i * N + j] += sum;
		}
	}

	return Result;
}
