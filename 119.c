// The number 512 is interesting because it is equal to the sum of its digits raised to some power:
// 5 + 1 + 2 = 8, and 8 ^ 3 = 512. Another example of a number with this property is 614656 = 28 ^
// 4.
//
// We shall define a_n to be the nth term of this sequence and insist that a number must contain at
// least two digits to have a sum.
//
// You are given that a_2 = 512 and a_10 = 614656.
//
// Find a_30.

#include "common.h"

i64 powi(i64 base, i64 exponent)
{
    i64 result = 1;
    while (exponent-- > 0) {
        result *= base;
    }
    return result;
}

i64 digit_sum(i64 n)
{
    i64 sum = 0;

    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

int main(int argc, char **argv)
{
    assert(digit_sum(512) == 8);

    autofreearr i64 *values = NULL;

    for (i32 i = 1; i < 1000; i++) {
        for (i32 j = 1; j < 100; j++) {
            i64 d = powi(i, j);

            if (d < 10) { // skip numbers with less than 2 digits (can't have a sum)
                continue;
            }

            if (digit_sum(d) == i) {
                arrput(values, d);
            }
        }
    }

    qsort(values, arrlen(values), sizeof(*values), comp_i64);

#if 0
    for (i32 i = 0; i < arrlen(values); i++) {
        printf("%d - %ld\n", i + 1, values[i]);
    }
#endif

    printf("A(30) = %ld\n", values[29]);
}
