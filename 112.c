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

int get_digit(int64_t x, int digit)
{
    return x / (int)(pow(10, digit)) % 10;
}

int get_len(int64_t x)
{
    return (int)(log(x) / log(10)) + 1;
}

int is_increasing(int64_t x)
{
    int first = -1;
    for (int i = get_len(x) - 1; i >= 0; i--) {
        int digit = get_digit(x, i);
        if (first <= digit) {
            first = digit;
        } else {
            return false;
        }
    }
    return true;
}

int is_decreasing(int64_t x)
{
    int first = 10;
    for (int i = get_len(x) - 1; i >= 0; i--) {
        int digit = get_digit(x, i);
        if (first >= digit) {
            first = digit;
        } else {
            return false;
        }
    }
    return true;
}

int is_bouncy(int64_t x)
{
    return !is_increasing(x) && !is_decreasing(x);
}

double percentage(double num, double den)
{
    return num / den * 100;
}

void find_percent_limit(double percent, size_t limit)
{
    size_t bouncy = 0;
    int do_print = true;
    for (size_t i = 1; i < limit; i++) {
        if (is_bouncy(i)) {
            bouncy++;
        }

        if (percentage(bouncy, i) >= percent && do_print) {
            printf("percentage: %lf, at %ld\n", percentage(bouncy, i), i);
            do_print = false;
        }
    }
}

int main(int argc, char **argv)
{
    assert(is_increasing(134468));
    assert(is_decreasing(644210));
    assert(is_bouncy(155349));

    find_percent_limit(50.00000f, 1000);
    find_percent_limit(99.00000f, LONG_MAX);

    return 0;
}
