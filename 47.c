// The first two consecutive numbers to have two distinct prime factors are:
//
//   14 = 2 * 7
//   15 = 3 * 5
//
// The first three consecutive numbers to have three distinct prime factors are:
//
//   644 = 2^2 *  7 * 23
//   645 = 3   *  5 * 43
//   646 = 2   * 17 * 19
//
// Find the first four consecutive integers to have four distinct prime factors each. What is the
// first of these numbers?

#include "common.h"

#define LIMIT 1000000

u8 *primes = NULL;

void compute_primes(void)
{
    primes = calloc(LIMIT, sizeof(*primes));
    memset(primes, 0xff, sizeof(*primes) * LIMIT);

    primes[0] = false;
    primes[1] = false;

    for (int i = 2; i < LIMIT; i++) {
        for (int j = i * 2; j < LIMIT; j += i) {
            primes[j] = false;
        }
    }
}

// returns the prime factorization, with each prime factor presented independently
i32 *prime_factors(i32 n)
{
    i32 *factors = NULL;

    while (n >= 1) {
        i32 lim = n / 2;
        bool found = false;
        for (i32 i = 2; i <= lim; i++) {
            if (primes[i] && n % i == 0) {
                arrput(factors, i);
                n /= i;
                found = true;
                break;
            }
        }

        if (!found) { // number must be prime?
            arrput(factors, n);
            break;
        }
    }

    i32 last = -1;

    qsort(factors, arrlen(factors), sizeof(*factors), comp_i32);

    for (i32 i = 0; i < arrlen(factors); i++) {
        if (last == factors[i]) {
            arrdel(factors, i);
            i--;
        }
        last = factors[i];
    }

    return factors;
}

void print_i32s(i32 *list)
{
    for (i32 i = 0; i < arrlen(list); i++) {
        printf("%d%s", list[i], i == arrlen(list) - 1 ? "\n" : ", ");
    }
}

int main(int argc, char **argv)
{
    i32 answer = 0;

    compute_primes();

    for (i32 i = 3; i < 1000000; i++) {
        autofreearr i32 *i0 = prime_factors(i);
        if (arrlen(i0) == 4) {
            autofreearr i32 *i1 = prime_factors(i + 1);
            if (arrlen(i1) != 4)
                continue;

            autofreearr i32 *i2 = prime_factors(i + 2);
            if (arrlen(i2) != 4)
                continue;

            autofreearr i32 *i3 = prime_factors(i + 3);
            if (arrlen(i3) != 4)
                continue;

            print_i32s(i0);
            print_i32s(i1);
            print_i32s(i2);
            print_i32s(i3);

            answer = i;
            break;
        }
    }

    printf("%d\n", answer);
}
