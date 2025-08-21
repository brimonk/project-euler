#include "common.h"

struct gcd_memo_key {
    int a, b, c;
};

struct gcd_memo {
    struct gcd_memo_key key;
    int value;
};

struct gcd_memo *gcd_memo_table = NULL;

void sort3(int *a, int *b, int *c)
{
    int a0 = MAX(*a, MAX(*b, *c));
    int b0 = MIN(*a, MAX(*b, *c));
    int c0 = MIN(*a, MIN(*b, *c));
    *a = a0;
    *b = b0;
    *c = c0;
}

int gcd(int a, int b)
{
    return a % b == 0 ? b : gcd(b, a % b);
}

int gcd3(int a, int b, int c)
{
    sort3(&a, &b, &c);
    struct gcd_memo_key key = { a, b, c };
    struct gcd_memo *lookup = hmgetp_null(gcd_memo_table, key);

    if (lookup != NULL) {
        printf("CACHE HIT  [%d, %d, %d] -> %d\n", a, b, c, lookup->value);
        return lookup->value;
    } else {
        int answer = gcd(a, gcd(b, c));
        printf("CACHE MISS [%d, %d, %d] -> %d\n", a, b, c, answer);
        hmput(gcd_memo_table, key, answer);
        return answer;
    }
}

#define PERIMETER_LIMIT 10000000

int main(int argc, char **argv)
{
    i64 count = 0;

    for (i32 i = 1; i < PERIMETER_LIMIT; i++)
    for (i32 j = i; j < PERIMETER_LIMIT; j++) {
        printf("ITER: %d, %d\n", i, j);
    for (i32 k = j; k < PERIMETER_LIMIT; k++) {
        i32 perimeter = i + j + k;
        if (perimeter > PERIMETER_LIMIT) {
            continue;
        }

        if (gcd3(i, j, k) == 1) {
            count++;
        }
    }
    }

    printf("answer: %ld\n", count);

    hmfree(gcd_memo_table);

    return 0;
}
