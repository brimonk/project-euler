// For non-negative integers m, n, the Ackermann function A(m, n) is defined as follows:
//
//             {  n + 1                if m = 0
//   A(m, n) = | A(m - 1, 1)           if m > 0 and n = 0
//             { A(m - 1, A(m, n - 1)) if m > 0 and n > 0
//
// For example A(1, 0) = 2, A(2, 2) = 7 and A(3, 4) = 125
//
// Find 6 ∑ n = 0 ( A(n, n) ) and give your answer mod 14^8.

#include "common.h"

typedef struct AckerKey {
    u64 m;
    u64 n;
} AckerKey;

typedef struct AckerLookup {
    AckerKey key;
    u64 value;
} AckerLookup;

static AckerLookup *lookup = NULL;

void clear_lookup(void)
{
    hmfree(lookup);
    lookup = NULL;
}

AckerKey make_key(u64 m, u64 n)
{
    AckerKey key = {
        .m = m,
        .n = n,
    };
    return key;
}

// acker0: naive implementation
u64 acker0(u64 m, u64 n)
{
    AckerKey key = {
        .m = m,
        .n = n,
    };

    ptrdiff_t acker_lookup = hmgeti(lookup, key);
    if (acker_lookup >= 0) {
        return lookup[acker_lookup].value;
    }

    u64 value = 0;

    if (m == 0) {
        value = n + 1;
    } else if (m > 0 && n == 0) {
        value = acker0(m - 1, 1);
    } else {
        value = acker0(m - 1, acker0(m, n - 1));
    }

    AckerLookup new_lookup_value = {
        .key = key,
        .value = value
    };

    hmputs(lookup, new_lookup_value);

    printf("A(%lu, %lu) = %lu\n", m, n, value);

    return value;
}

// acker1: keep the stack on the heap, so we don't explode from recursion
u64 acker1(u64 m, u64 n)
{
    // NOTE We keep a stack of 'AckerKey' items, and when the stack is finally out, we have our
    // value. Given that this won't explode with recursion calls, we're probably going to need to
    // handle the mod 14^8 thing in here somewhere.
    //
    // Because the number of computations is still immense, we're still going to use the lookup
    // table.

    autofreearr AckerKey *keys = NULL;

    arrput(keys, make_key(m, n));
    u64 value = 0;

    while (arrlen(keys) > 0) {
        AckerKey current_key = arrpop(keys);

        ptrdiff_t current_key_lookup = hmgeti(lookup, current_key);
        if (current_key_lookup >= 0) {
            value = lookup[current_key_lookup].value;
        } else {
            if (current_key.m == 0) { // base case
                value = current_key.n + 1;
            } else if (current_key.m > 0 && current_key.n == 0) { // recursive
                AckerKey pushed_key = {
                    .m = current_key.m - 1,
                    .n = 1
                };

                ptrdiff_t inner_lookup = hmgeti(lookup, pushed_key);
                if (inner_lookup >= 0) {
                    value = lookup[inner_lookup].value;
                } else {
                    // push the key we have "now" back onto the stack
                    arrput(keys, current_key);

                    // then put the "new key" onto the stack, so we can resolve it
                    arrput(keys, pushed_key);

                    // and continue the loop
                    continue;
                }
            } else {
                // recursive, but with a double lookup

                // Now, we determine what key to push on top of the stack. Given the "real" recursive
                // statement is this:
                //
                //    value = acker0(m - 1, acker0(m, n - 1));

                AckerKey inner_key = {
                    .m = current_key.m,
                    .n = current_key.n - 1
                };

                ptrdiff_t inner_key_lookup = hmgeti(lookup, inner_key);
                if (inner_key_lookup >= 0) {
                    // If we have an inner key, we then attempt to resolve the outer key with a value.

                    AckerKey outer_key = {
                        .m = current_key.m - 1,
                        .n = lookup[inner_key_lookup].value
                    };

                    ptrdiff_t outer_key_lookup = hmgeti(lookup, outer_key);
                    if (outer_key_lookup >= 0) {
                        value = lookup[outer_key_lookup].value;
                    } else {
                        // If we don't have an outer key, we simply put the outer key on the stack with
                        // the value we derived from resolving the inner key.

                        arrput(keys, current_key);
                        arrput(keys, outer_key);

                        continue;
                    }
                } else {
                    // If we don't have an inner key, we put the current key and the inner key onto the
                    // stack. When we need to re-resolve this current key, we'll simply rerun the loop,
                    // and NOT come to this branch again.

                    arrput(keys, current_key);
                    arrput(keys, inner_key);

                    continue;
                }
            }

            // store in the lookup table if we haven't seen this key before
            if (current_key_lookup < 0) {
                AckerLookup new_lookup_value = {
                    .key = current_key,
                    .value = value
                };

                // printf("A(%lu, %lu) = %lu\n", new_lookup_value.key.m, new_lookup_value.key.n, value);

                hmputs(lookup, new_lookup_value);
            }
        }
    }

    return value;
}

int main(int argc, char **argv)
{
    // assert(acker0(1, 0) == acker1(1, 0));
    // assert(acker0(2, 2) == acker1(2, 2));
    // assert(acker0(3, 4) == acker1(3, 4));

    // acker0(2, 2);
    // clear_lookup();
    // acker1(2, 2);

    // printf("A(%d, %d) = %lu\n", 3, 3, acker1(3, 3));
    // printf("A(%d, %d) = %lu\n", 3, 4, acker1(3, 4));
    // printf("A(%d, %d) = %lu\n", 4, 4, acker1(4, 4));

    u64 sum = 0;

    for (i32 i = 0; i <= 6; i++) {
        u64 a = acker1(i, i);
        printf("A(%d, %d) = %lu\n", i, i, a);
        sum += a;
    }

    printf("Answer: %lu\n", sum);

    return 0;
}
