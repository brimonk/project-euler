// The prime 41, can be written as the sum of six consecutive primes:
//
//   41 = 2 + 3 + 5 + 7 + 11 + 13
//
// This is the longest sum of consecutive primes that adds to a prime below one-hundred.
//
// The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms,
// and it equal to 953.
//
// Which prime, below one-million, can be written as the sum of the most consecutive primes?

#define PRIMES_LIMIT 1000000
#include "common.h"

i32 GetConsecutiveSumLength(i32 prime)
{
    i64 max_length = 0;

    for (i64 i = 2; i < prime; i++) {
        if (!is_prime(i))
            continue;

        i64 length = 0;
        i64 curr_sum = 0;

        for (i64 j = i; j < prime && curr_sum < prime;) {
            curr_sum += j;
            j = (i64)get_next_prime(j);
            length++;
        }

        if (curr_sum == prime) {
            if (max_length < length) {
                max_length = length;
                return max_length;
            }
        }
    }

    return max_length;
}

int main(int argc, char **argv)
{
    i32 max_length_prime = 0;
    i32 max_sum_length = 0;

    assert(GetConsecutiveSumLength(41) == 6);
    assert(GetConsecutiveSumLength(953) == 21);

    for (i32 i = 0; i < PRIMES_LIMIT; i++) {
        if (PRIMES[i]) {
            i32 length = GetConsecutiveSumLength(i);
            if (max_sum_length < length) {
                max_length_prime = i;
                max_sum_length = length;
            }
        }
    }

    printf("%d\n", max_length_prime);
}
