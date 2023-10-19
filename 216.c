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

void t(mpz_t k, int64_t n)
{
    mpz_t z;
    mpz_init(z);

    mpz_set_si(z, n);
    mpz_mul_si(z, z, n);
    mpz_mul_si(z, z, 2);
    mpz_sub_ui(z, z, 1);

    mpz_set(k, z);
    mpz_clear(z);
}

int main(int argc, char **argv)
{
    mpz_t k;

    int count = 0;
    for (int i = 1; i <= 50000000; i++) {
        mpz_init(k);
        t(k, i);
        if (mpz_probab_prime_p(k, 55)) {
            count++;
        }
        mpz_clear(k);
    }

    printf("primes <= 50000000: %d\n", count);

    return 0;
}
