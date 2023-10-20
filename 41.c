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

int get_digit(int64_t x, int digit)
{
    return x / (int)(pow(10, digit)) % 10;
}

int get_len(int64_t x)
{
    return (int)(log(x) / log(10)) + 1;
}

int is_n_digital(int n, int x)
{
    int digits[10] = {0};
    for (int i = 0; i <= n; i++) {
        digits[get_digit(x, i)]++;
    }
    for (int i = 0; i <= n; i++) {
        if (digits[i] > 1) {
            return false;
        }
        if (digits[i] == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
#define PRIMES 1000000000

    uint8_t *primes = calloc(PRIMES, sizeof(*primes));
    memset(primes, 0xff, PRIMES * sizeof(*primes));

    primes[0] = false;
    primes[1] = false;

    for (int i = 2; i < PRIMES; i++) {
        for (int j = i * 2; j < PRIMES; j += i) {
            primes[j] = false;
        }
    }

    assert(is_n_digital(4, 2143) && primes[2143]);
    assert(is_n_digital(9, 987654321));
    assert(get_len(2143) == 4);
    assert(!is_n_digital(8, 987654323));

    int max = -1;
    for (int i = 0; i < PRIMES; i++) {
        if (primes[i] && is_n_digital(get_len(i), i)) {
            max = i;
        }
    }

    printf("%d\n", max);

    free(primes);

    return 0;
}
