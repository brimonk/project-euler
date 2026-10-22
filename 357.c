#define PRIMES_LIMIT 1000000000
#include "common.h"

int main(int argc, char **argv)
{
    compute_primes();

    u64 sum = 1;
    for (int i = 2; i <= PRIMES_LIMIT; i += 4) {
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
}
