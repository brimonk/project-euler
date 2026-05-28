// The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to
// simply it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling
// the 9s.
//
// We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
//
// There are exactly four non-trivial examples of this type of fraction, less than one in value, and
// containing two digits in the numerator and denominator.
//
// If the product of these four fractions is given in its lowest common terms, find the value of the
// denominator.

#include "common.h"

i32 gcd(i32 a, i32 b)
{
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

i32 same_digits(i32 *a, i32 *b)
{
    // this routine is stupid, but I didn't want to think that hard

#if 0
    // NOTE From the problem example, we DON'T want to cancel BOTH the first digits, or BOTH the
    // second digits. These are "trivial examples".

    if (*a % 10 == *b % 10) {
        *a /= 10;
        *b /= 10;
        return *a; 
    }

    if (*a / 10 == *b / 10) { 
        *a %= 10;
        *b %= 10;
        return *a; 
    }
#endif

    if (*a / 10 == *b % 10) {
        *a %= 10;
        *b /= 10;
        return *a; 
    }

    if (*a % 10 == *b / 10) { 
        *a /= 10;
        *b %= 10;
        return *a; 
    }

    return -1;
}

int main(int argc, char **argv)
{
    autofreearr i32 *numers = NULL;
    autofreearr i32 *denoms = NULL;

    for (i32 i = 10; i < 100; i++) {
        for (i32 j = i + 1; j < 100; j++) {
            i32 a = i;
            i32 b = j;

            if (same_digits(&a, &b) == -1) {
                continue;
            }

            i32 g0 = gcd(i, j);
            i32 g1 = gcd(a, b);

            // Reduce the fractions, now that we have the GCD.

            i32 ii = i / g0;
            i32 jj = j / g0;

            i32 aa = a / g1;
            i32 bb = b / g1;

            if (ii == aa && jj == bb) {
                printf("%d/%d == %d/%d\n", i, j, a, b);
                arrput(numers, i);
                arrput(denoms, j);
            }
        }
    }

    assert(arrlen(denoms) == 4);
    assert(arrlen(numers) == 4);

    i32 ansn = 1;
    i32 ansd = 1;

    for (i32 i = 0; i < arrlen(numers); i++) {
        ansn *= numers[i];
    }
    for (i32 i = 0; i < arrlen(denoms); i++) {
        ansd *= denoms[i];
    }

    i32 g2 = gcd(ansn, ansd);

    ansn /= g2;
    ansd /= g2;

    printf("%d/%d\n", ansn, ansd);
    printf("%d\n", ansd);
}
