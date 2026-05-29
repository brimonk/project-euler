// There are exactly ten ways of selecting three from five, 12345:
//
//   123, 124, 125, 134, 135, 145, 234, 235, 245, 345
//
// In combinatorics, we use the notation, (5 3) = 10.
//
// In general, (n r) = n! / r! (n - r)!, where r <= n, n! = n * (n - 1) * .. * 3 * 2 * 1, and 0! =
// 1.
//
// It is not until n = 23, that a value exceeds one-million: (23 10) = 1144066.
//
// How many, not necessarily distinct, values of (n r) for 1 <= n <= 100, are greater than
// one-million?

#include "common.h"

u64 *expand_factorial(u64 v)
{
    u64 *values = NULL;
    while (v > 0) {
        arrput(values, v);
        v--;
    }
    return values;
}

u64 combinatorics(u64 n, u64 r)
{
    // NOTE To avoid overflow, we expand the factorial and all of the individual values, cancel
    // them, then we perform the arithmetic.

    autofreearr u64 *numer = expand_factorial(n);
    autofreearr u64 *denom = expand_factorial(r);

    // now, we add the (n - r)! bit into the denom list we just constructed

    autofreearr u64 *others = expand_factorial(n - r);
    while (arrlen(others) > 0) {
        u64 popped = arrpop(others);
        arrput(denom, popped);
    }

    // do a little sorting...

    qsort(numer, arrlen(numer), sizeof(numer[0]), comp_u64);
    qsort(denom, arrlen(denom), sizeof(denom[0]), comp_u64);

    // so we can follow up with a little cancelling

    for (i32 i = 0; i < arrlen(denom); i++) {
        for (i32 j = 0; j < arrlen(numer); j++) {
            if (denom[i] == numer[j]) {
                arrdel(denom, i);
                arrdel(numer, j);
                i--;
                j--;
            }
        }
    }

    // then do the math

    mpz_t ansn, ansd;

    mpz_inits(ansn, ansd, NULL);

    mpz_set_ui(ansn, 1);
    mpz_set_ui(ansd, 1);

    for (i32 i = 0; i < arrlen(numer); i++) {
        mpz_mul_ui(ansn, ansn, numer[i]);
    }

    for (i32 i = 0; i < arrlen(denom); i++) {
        mpz_mul_ui(ansd, ansd, denom[i]);
    }

    mpz_cdiv_q(ansn, ansn, ansd);

    bool answer = mpz_cmp_ui(ansn, 1000000) > 0;

    mpz_clears(ansn, ansd, NULL);

    return answer;
}

int main(int argc, char **argv)
{
    u64 answer = 0;
    for (u64 n = 1; n <= 100; n++) {
        for (u64 r = 0; r <= n; r++) {
            bool is_greater_than_1m = combinatorics(n, r);
            if (is_greater_than_1m) {
                answer++;
            }
        }
    }
    printf("%lu\n", answer);
}
