// Brian Chrzanowski
//
// To solve this problem, we won't bother creating real matrices in memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#include <gmp.h>

int64_t f(int64_t x)
{
    assert(x % 2 == 1);

    int64_t sum = 1;
    int64_t counter = 1;

    // Here, 'i' represents the side length.
    // Start at '3' because it's generalized.
    for (size_t i = 3; i <= x; i += 2) {
        for (size_t j = 0; j < 4; j++) {
            counter += (i - 1);
            sum += counter;
        }
        // sum += (i - 1) * 4;
    }

    return sum;
}

int main(int argc, char **argv)
{
    assert(f(1) == 1);
    assert(f(3) == 25);
    assert(f(5) == 101);

    printf("%ld\n", f(1001));

    return 0;
}
