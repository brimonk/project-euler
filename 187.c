// Brian Chrzanowski
//
// Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0, where each "_"
// is a single digit.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

// #define LIMIT 30
#define LIMIT 100000000

int main(int argc, char **argv)
{
    fprintf(stderr, "computing primes table\n");

    uint8_t *primes = calloc(LIMIT, sizeof(*primes));
    int *factors = calloc(LIMIT, sizeof(*factors));
    int *p_factors = calloc(LIMIT, sizeof(*factors));

    memset(primes, 0xff, LIMIT * sizeof(*primes));

    primes[0] = false;
    primes[1] = false;

    for (int i = 2; i < LIMIT; i++) {
        for (int j = i * 2; j < LIMIT; j += i) {
            primes[j] = false;
        }
    }

    fprintf(stderr, "counting factors\n");

    for (int i = 2; i < LIMIT; i++) {
        for (int j = i * 2; j < LIMIT; j += i) {
            if (i * i == j)
                factors[j]++;
            factors[j]++;
        }
    }

    for (int i = 2; i < LIMIT; i++) {
        if (primes[i]) {
            for (int j = i * 2; j < LIMIT; j += i) {
                if (i * i == j)
                    p_factors[j]++;
                p_factors[j]++;
            }
        }
    }

    int count = 0;
    for (int i = 2; i < LIMIT; i++) {
        // printf("%d\t%d\t%d%s\n", i, factors[i], p_factors[i], factors[i] == 2 && p_factors[i] == 2 ? "*" : "");
        if (factors[i] == 2 && p_factors[i] == 2)
            count++;
    }
    printf("count of numbers with precisely two prime factors: %d\n", count);

    free(primes);
    free(factors);

    return 0;
}
