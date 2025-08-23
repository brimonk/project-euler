#include "common.h"

// This problem is actually just math. In a 2x2 grid, there are 6 choices, as per the problem.
//
// At any one spot, you can either go up, or down. This is like, a binomial coefficient kind of
// thing.

i64 binomial_coeff_form(i64 n, i64 k)
{
    if (k > n - k) {
        k = n - k;
    }

    i64 product = 1;
    for (i64 i = 1; i <= k; i++) {
        product *= (n - k + i) / i;
    }
    return product;
}

int main(int argc, char **argv)
{
    for (i32 i = 1; i <= 20; i++)
        printf("answer: %d, %ld\n", i, binomial_coeff_form(2 * i, i));
}
