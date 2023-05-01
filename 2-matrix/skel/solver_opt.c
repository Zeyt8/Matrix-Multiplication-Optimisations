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
	double *A_t = (double *) malloc(N * N * sizeof(double));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N - i; j++)
			A_t[i * N + j] = A[j * N + i];
	// calculate B transposed
	double *B_t = (double *) malloc(N * N * sizeof(double));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N - i; j++)
			B_t[i * N + j] = B[j * N + i];

	double *Result = (double *) malloc(N * N * sizeof(double));
	// Result = A*B
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Result[i * N + j] = 0;
			for (int k = 0; k <= N - i && k <= N - j; k++) {
				Result[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}
	// Result *= A_t
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double sum = 0;
			for (int k = 0; k <= N - i && k <= N - j; k++) {
				sum += Result[i * N + k] * A_t[k * N + j];
			}
			Result[i * N + j] = sum;
		}
	}
	// Result += B_t * B_t
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			double sum = 0;
			for (int k = 0; k <= N - i && k <= N - j; k++) {
				sum += B_t[i * N + k] * B_t[j * N + k];
			}
			Result[i * N + j] += sum;
		}
	}

	return Result;
}
