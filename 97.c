// The first known prime found to exceed one million digits was discovered in 1999, and is a
// Mersenne prime of the form 2^6972593 - 1; it contains exactly 2,098,960 digits. Subsequently
// other Mersenne primes, of the form 2^p - 1, have been found which contains more digits.
//
// However, in 2004 there was found a massive non-Mersenne prime which contains 2,357,207 digits:
// 28433 * 2^7830457 + 1.
//
// Find the last 10 digits of this prime number.

#include "common.h"

int main(int argc, char **argv)
{
    mpz_t a, b;

    mpz_inits(a, b, NULL);

    mpz_set_ui(a, 28433);

    mpz_ui_pow_ui(b, 2, 7830457);

    mpz_mul(a, a, b);
    mpz_add_ui(a, a, 1);

    mpz_mod_ui(a, a, 10000000000);

    autofree char *str = mpz_get_str(NULL, 10, a);

    printf("%s\n", str);

    mpz_clears(a, b, NULL);
}
