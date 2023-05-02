/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include <cblas.h>
#include "utils.h"

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	double *Result = (double *) calloc(N * N, sizeof(double));
	// Result = B
	cblas_dcopy(N * N, B, 1, Result, 1);
	// Result = A * B
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, Result, N);
	// Result = Result * A_t
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.0, A, N, Result, N);
	// Result += B_t * B_t
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, N, N, N, 1.0, B, N, B, N, 1.0, Result, N);
	return Result;
}
