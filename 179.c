// Brian Chrzanowski
//
// Find the number of integers 1 < n < 10**7, for which n and n + 1 have the same number of positive
// divisors. For example, 14 has the positive divisors 1, 2, 7, 14, while 15 has 1, 3, 5, 15.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#define LIMIT 10000000

int16_t *DIVISORS = NULL;

// Returns the number of divisors for the given number 'n'.
int get_divisors(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++) { // compute number of divisors
        if (n % i == 0) {
            sum++;
        }
    }
    return sum;
}

int main(int argc, char **argv)
{
    DIVISORS = calloc((LIMIT + 1), sizeof(*DIVISORS));

    for (int i = 1; i <= LIMIT / 2; i++) {
        for (int j = i; j <= LIMIT; j += i) {
            DIVISORS[j]++;
        }
    }

    int sum = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (DIVISORS[i] == DIVISORS[i - 1]) {
            sum++;
        }
    }

    printf("1 < n < %d, st divisors(n) == divisors(n + 1): %d\n", LIMIT, sum);

    free(DIVISORS);

    return 0;
}
