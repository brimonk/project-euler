#include "common.h"

u8 *sieve(size_t count)
{
    count = count + count / 2;
    u8 *primes = calloc(count, sizeof(*primes));
    memset(primes, 0xff, count * sizeof(*primes));

    for (size_t i = 2; i < count; i++) {
        for (size_t j = i + i; primes[i] && j < count; j += i) {
            primes[j] = 0;
        }
    }

    return primes;
}

u8 *PRIMES = NULL;

#define LIMIT 100000000
// #define LIMIT 100

int main(int argc, char **argv)
{
    PRIMES = sieve(LIMIT);
    u64 sum = 1;
    for (int i = 2; i <= LIMIT; i += 4) {
        if (PRIMES[i + 1] && PRIMES[2 + i / 2]) {
            int valid = true;
            for (int divisor = 3; divisor * divisor <= i; divisor++) {
                if (i % divisor != 0) {
                    continue;
                }

                if (!PRIMES[divisor + i / divisor]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                sum += i;
            }
        }
    }
    printf("ANSWER: %lu\n", sum);
    free(PRIMES);
}
