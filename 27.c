// Brian Chrzanowski

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

#define ARRSIZE(x) (sizeof((x))/sizeof((x)[0]))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int is_prime(int64_t number)
{
    mpz_t z;
    mpz_init(z);
    mpz_set_si(z, number);
    int rc = mpz_probab_prime_p(z, 80);
    assert(rc == 2 || rc == 0);
    mpz_clear(z);
    return rc > 0;
}

int64_t comp(int64_t n, int64_t a, int64_t b)
{
    return (n * n) + (n * a) + b;
}

int64_t primes_count(int64_t a, int64_t b)
{
    int64_t count = 0;
    int64_t x;

    for (int64_t i = 0; i < INT_MAX; i++, count++) {
        x = comp(i, a, b);
        if (!is_prime(x)) {
            count--;
            break;
        }
    }

    return count;
}

int main(int argc, char **argv)
{
    int64_t max = -1;
    int64_t product = -1;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            {
                int64_t t = primes_count(i, j);
                if (t > max) {
                    max = t;
                    product = i * j;
                }
            }

            {
                int64_t t = primes_count(-i, j);
                if (t > max) {
                    max = t;
                    product = -i * j;
                }
            }

            {
                int64_t t = primes_count(i, -j);
                if (t > max) {
                    max = t;
                    product = -i * j;
                }
            }

            {
                int64_t t = primes_count(-i, -j);
                if (t > max) {
                    max = t;
                    product = -i * j;
                }
            }

        }
    }

    printf("%ld\n", product);

    return 0;
}
