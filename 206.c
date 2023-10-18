// Brian Chrzanowski
//
// Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0, where each "_"
// is a single digit.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#define START   1020304050607080900
#define END     1929394959697989990

int match(int64_t n)
{
    uint64_t square = n * n;

    int digits[] = { 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int index = 0;

    do {
        int digit = square % 10;
        if (digit != digits[index++]) {
            return false;
        }
        square /= 100;
    } while (square > 0);

    return true;
}

int main(int argc, char **argv)
{
    uint64_t min = 1010101010;
    uint64_t max = 1389026620;

    for (uint64_t x = max; x >= min; x -= 10) {
        int match_v = match(x);
        if (match_v) {
            printf("%ld\n", x);
            break;
        }
    }

    return 0;
}
