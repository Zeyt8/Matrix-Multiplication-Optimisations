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

I am using block matrix multiplication for all the multiplications. In addition, I am working with pointers instead of accessing the matrix elements with the index operator. Also, I am storing the sums in a temporary variable instead of directly adding them to the result matrix.

The transpositions are not necessary, I can just acces elements from the matrix in a different order.

Since I am working with blocks, to optimise for upper triangular matrices, instead of skipping to the i-th column, I only skip to it if it is part of the current block.

For the second multiplication (the one with A<sup>t</sup>), I need a temporary matrix to store the result. This happens because of the partial sums made by the block matrix algorithm.

I also use loop unrolling. For B<sup>t</sup>xB<sup>t</sup> I unroll the loop by 4 and the procedure is trivial. Considering that k_max - kk is always equal to the block_size, that loop could be removed entirely and the computation manually repeated 40 times to further improve the performance.

For the multiplications that include A, I also did loop unrolling, but the optimisation for upper triangular matrix caused me some problems. Hence I treated sepparately the case when k_min is not divisible by 2(I don't unroll), is divisible by 4(unroll by 4) and is divisible by 2(unroll by 2). A more general solution surely exists, but I couldn't find it.

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

### Time

As we can see from the graphs, the naive implementation is the slowest. A manual computation of the data in the graph shows that M_size[i+1]/M_size[i]=cubic_root(time[i+1])/cubic_root(time[i]). That means that the time complexity is O(n<sup>3</sup>).

The optimised version is faster by a significant amount, but the blas implementation is the fastest by far. These result are to be expected. Again, a manual computation of the data shows that the complexity is still O(n<sup>3</sup>).

Memory is the main bottle neck, so my optimisations are very effective, but there is only so much I can do without changing the algorithm. A manual computation reveals that the complexity is, I think, still O(n<sup>3</sup>).

Blas is the fastest because it is a highly optimised library that uses vectorial operations. It probably uses all the optimisations the compiler with O3 would use, but it also has a lot of other manual optimisations.

### Cachegrind

As expected neopt has a lot of cache misses.

The optimised version has a lot less. That happens because the main optimisation used is block matrix multiplication which is designed to reduce the number of cache misses.

I noticed that if I tried to do the addition with B<sup>t</sup>×B<sup>t</sup> and A<sup>t</sup> × B<sup>t</sup> in the same loop, the time to run increased, which is probably caused by a lot of extra cache misses.

Surprinzigly, the blas implementation has a bit less data accesses, a bit less first level cache misses, but a bit more last level cache misses. The conclusion that can be drawn is that the first 2 are more important and increase the performance.

I can also see that blass has a lot less branch misspredicts and branches over all. This fact dramatically improves the performance. Also the number of instruction cache references is a lot lower.