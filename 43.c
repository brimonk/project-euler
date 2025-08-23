#include "common.h"

#define START  1000000000
#define END    9999999999

i64 is_pandigital(i64 input)
{
    i64 copy = input;
    u8 digits[10] = { 0 };
    for (; input; input /= 10) {
        int v = input % 10;
        digits[v]++;
        if (digits[v] > 1) {
            return 0;
        }
    }

    for (int i = 0; i < ARRSIZE(digits); i++) {
        if (digits[i] == 0) {
            return 0;
        }
    }

    return copy;
}

int is_divisible(char *s, int start, int divisor)
{
    int v = 0;

    v += (s[start + 0] - '0') * 100;
    v += (s[start + 1] - '0') * 10;
    v += (s[start + 2] - '0') * 1;

    return v % divisor == 0;
}

i64 is_valid(i64 input)
{
    if (!is_pandigital(input)) {
        return 0;
    }

    // this is slow - will optimize after I get something that works

    char str[11] = { 0 };
    snprintf(str, sizeof str, "%ld", input);

    if (is_divisible(str,  1,  2) &&
        is_divisible(str,  2,  3) &&
        is_divisible(str,  3,  5) &&
        is_divisible(str,  4,  7) &&
        is_divisible(str,  5, 11) &&
        is_divisible(str,  6, 13) &&
        is_divisible(str,  7, 17)) {
        return input;
    } else {
        return 0;
    }
}

int main(int argc, char **argv)
{
#if 0
    int a = is_pandigital(1234567890);
    int b = is_pandigital(1234567899);
    printf("%d\n", a);
    printf("%d\n", b);
#endif

    i64 sum = 0;

    printf("is_valid %ld\n", is_valid(1406357289));

    for (i64 i = START; i <= END; i++) {
        if (((i % 1000) % 17 == 0) && is_valid(i)) {
            printf("is_valid %ld\n", i);
            sum += i;
        }
    }

    printf("%ld\n", sum);
}
