// Problem 124
//
// The radical of n, rad(n), is the product of the distinct prime factors of n. For example,
// 504 = 2^3 * 3^2 * 7, so rad(504) = 2 * 3 * 7 = 42.
//
// If we calculate rad(n) for 1 <= n <= 10, then sort them on rad(n), and sorting on n if the
// radical values are equal, we get:
//
// Let E(k) be the k-th element in the sorted n column; for example, E(4) = 8 and E(6) = 9.
//
//       Unsorted         Sorted
//   n    rad(n)     n   rad(n)   k
//   1       1       1      1     1
//   2       2       2      2     2
//   3       3       4      2     3
//   4       2       8      2     4
//   5       5       3      3     5
//   6       6       9      3     6
//   7       7       5      5     7
//   8       2       6      6     8
//   9       3       7      7     9
//  10      10      10     10    10
//
// If rad(n) is sorted for 1 <= n <= 100000, find E(10000).

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

    return factors;
}

u64 compute_product_of_distinct(i32 *factors)
{
    qsort(factors, arrlen(factors), sizeof(*factors), comp_i32);

    u64 n = 1;
    i32 last = -1;

    for (i32 i = 0; i < arrlen(factors); i++) {
        if (last != factors[i]) {
            n *= factors[i];
            last = factors[i];
        }
    }

    return n;
}

u64 compute_rad(u64 n)
{
    autofreearr i32 *factors = prime_factors(n);
    return compute_product_of_distinct(factors);
}

typedef struct Sorted {
    i64 n;
    i64 rad_n;
} Sorted;

int comp_sorted(const void *a, const void *b)
{
    const Sorted *sa = a;
    const Sorted *sb = b;

    if (sa->rad_n < sb->rad_n) return -1;
    if (sa->rad_n > sb->rad_n) return 1;
    if (sa->n < sb->n) return -1;
    if (sa->n > sb->n) return 1;
    return 0;
}

int main(int argc, char **argv)
{
    // const int problem_limit = 10;
    const int problem_limit = 100000;

    compute_primes();

    autofreearr Sorted *sorted = NULL;

    Sorted placeholder = {
        .n = INT_MIN,
        .rad_n = INT_MIN,
    };

    arrput(sorted, placeholder);

    for (i32 i = 1; i <= problem_limit; i++) {
        u64 r = compute_rad(i);
        Sorted sorted_current = {
            .n = i,
            .rad_n = r,
        };
        arrput(sorted, sorted_current);
    }

    qsort(sorted, arrlen(sorted), sizeof(*sorted), comp_sorted);

    for (i32 i = 1; i < arrlen(sorted); i++) {
        printf("%ld\t%ld\t%ld\n", sorted[i].n, sorted[i].rad_n, (i64)i);
    }

    printf("E(%d) = %ld\n", 4, sorted[4].n);
    printf("E(%d) = %ld\n", 6, sorted[6].n);

    if (problem_limit >= 100000) {
    printf("E(%d) = %ld\n", 10000, sorted[10000].n);
    }
}
