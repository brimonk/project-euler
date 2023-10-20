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

int main(int argc, char **argv)
{
    int64_t max_sum = 0;
    char buf[256] = {0};

    for (int i = 1; i < 100; i++) {
        for (int j = 1; j < 100; j++) {
            int64_t curr_sum = 0;

            mpz_t a;

            mpz_init(a);

            mpz_set_si(a, i);
            mpz_pow_ui(a, a, j);

            gmp_snprintf(buf, sizeof buf, "%Zd", a);

            for (size_t k = 0, len = strlen(buf); k < len; k++) {
                curr_sum += buf[k] - '0';
            }

            if (max_sum < curr_sum) {
                max_sum = curr_sum;
            }

            mpz_clear(a);
        }
    }

    printf("%ld\n", max_sum);

    return 0;
}
