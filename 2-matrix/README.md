# Matrix Multiplication Optimization

C = A × B × A<sup>t</sup> + B<sup>t</sup> × B<sup>t</sup>

A is an upper triangular matrix.

## Implementation

### Neopt

This is the naive implementation of the algorithm. I transpose A and B with the simple mathematical formula. Because A is an upper triangular matrix, we can skip to the i-th column, where i is the row index.

First I calculate the product of A and B and store it in *Result*. Again, I can skip columns based on the row since A is upper triangular on the left side.

Afterwards I multiply *Result* with A<sup>t</sup>. Because A is upper triangular, I don't need another matrix to store the result, I can use *Result*. A is to the right in this operation, but it is transposed, so the exact same optimisation as before.

In the end I calculate B<sup>t</sup> × B<sup>t</sup> and add it to *Result*.

### Opt

The overall flow of the program is the same as Neopt with a few changes which I will explain below.

I am using block matrix multiplication for all the multiplications. In addition, I am working with pointers instead of accessing the matrix elements with the index operator. Also, I am storing the sums in a temporary variable instead of directly adding them to the result matrix.

The transpositions are optimised as before.

Since I am working with blocks, to optimise for upper triangular matrices, instead of skipping to the i-th column, I only skip to it if it is part of the current block.

For the second multiplication (the one with A<sup>t</sup>), I need a temporary matrix to store the result. This happens because of the partial sums made by the block matrix algorithm.

### Blas

The blas implementation is straightforward. I use the following operations from blas:

1. B <- alpha * A x B
2. B <- alpha * B x A<sup>t</sup>
3. C <- alpha * B<sup>t</sup> x B<sup>t</sup> + beta * C

Usage:

1. I move B to Result to use it as a sink using a blas function. I usec dtrmm for the computation because A is upper triangular. I mark A as being on the left side and alpha as 1. Also A is not a unit matrix.

2. Same as 1, but I mark A as being on the right side and to use the transpose form of A.

3. I use dgemm since that is the usual matrix multiplication function. Both Bs are marked to use the transposed form and as being normal matrices. alpha and beta are both set as 1.

## Results

