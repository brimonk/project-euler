// It was proposed by Christian Goldback that every odd composite number can be written as the sum
// of a prime and twice a square.
//
//    9 =  7 + 2 * 1 ^ 2
//   15 =  7 + 2 * 2 ^ 2
//   21 =  3 + 2 * 3 ^ 2
//   25 =  7 + 2 * 3 ^ 2
//   27 = 19 + 2 * 2 ^ 2
//   33 = 31 + 2 * 1 ^ 2

#define PRIMES_LIMIT 1000000
#include "common.h"

i32 *get_lesser_primes(i32 n)
{
    i32 *list = NULL;
    for (i32 i = 1; i < n; i++) {
        if (PRIMES[i]) {
            arrput(list, i);
        }
    }
    return list;
}

bool follows_conjecture(i32 n)
{
    autofreearr i32 *list = get_lesser_primes(n);

    for (i32 i = 0; i < arrlen(list); i++) {
        i32 p = list[i];

        i32 j = 1;
        i32 v = 1;

        do {
            v = p + 2 * (j * j);
            if (v == n) {
                return true;
            }
            j++;
        } while (v < n);
    }

    return false;
}

int main(int argc, char **argv)
{
    i32 answer = 0;

    compute_primes();

    const i32 limit = PRIMES_LIMIT;

    for (i32 i = 3; i < limit; i++) {
        if (i % 2 == 1 && !PRIMES[i]) {
            if (!follows_conjecture(i)) {
                answer = i;
                break;
            }
        }
    }

    printf("%d\n", answer);
}
