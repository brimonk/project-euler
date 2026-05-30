// It is possible to write ten as the sum of primes in exactly five different ways:
//
//   7 + 3
//   5 + 5
//   5 + 3 + 2
//   3 + 3 + 2 + 2
//   2 + 2 + 2 + 2 + 2
//
// What is the first value which can be written as the sum of primes in over five thousand different
// ways.

#include "common.h"

#define LIMIT 100000

u8 *primes = NULL;

void compute_primes(void)
{
    assert(sizeof(size_t) == 8);

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

u64 count_sum_of_primes_recurse(u64 target, u64 curr, u64 *p, i32 idx)
{
    u64 count = 0;

    for (i32 i = idx; curr < target && i < arrlen(p); i++) {
        if (target == curr + p[i]) {
            count++;
        }
        u64 count_in_subtree = count_sum_of_primes_recurse(target, curr + p[i], p, i);
        count += count_in_subtree;
    }

    return count;
}

u64 count_sum_of_primes(u64 n)
{
    // NOTE I don't really know how to compute this exactly, but we'll start by getting all of the
    // primes less than n. Then, starting at the highest, repeatedly approach 2 (lowest prime),
    // summing up the primes as we descent.

    autofreearr u64 *local_primes = NULL;

    for (u64 i = 2; i < n; i++) {
        if (primes[i]) {
            arrput(local_primes, (u64)i);
        }
    }

    // ?
    qsort(local_primes, arrlen(local_primes), sizeof(local_primes[0]), comp_u64_rev);

    u64 count = count_sum_of_primes_recurse(n, 0, local_primes, 0);

    return count;
}

int main(int argc, char **argv)
{
    compute_primes();

    u64 answer = ULONG_MAX;

    // printf("primes to compute 10: %lu\n", count_sum_of_primes(10));

    for (u64 i = 1; i < LIMIT; i++) {
        if (count_sum_of_primes(i) > 5000) {
            answer = i;
            break;
        }
    }

    if (answer == ULONG_MAX) {
        printf("answer not found!\n");
    } else {
        printf("answer: %lu\n", answer);
    }
}
