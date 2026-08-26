// Source: https://projecteuler.net/problem=91
//
// The points P(x1, y1) and Q(x2, y2) are plotted at integer co-ordinates and are joined to the
// origin, O(0, 0), to form 🔺OPQ.
//
// There are exactly fourteen triangles containing a right angle that can be formed when each
// co-ordinate lies between 0 and 2 inclusive; that is, 0 <= x1, y1, x2, y2 <= 2.
//
// Given that 0 <= x1, y1, x2, y2 <= 50, how many right triangles can be formed?

#include "common.h"

i32 powi(i32 base, i32 exponent)
{
    i32 result = 1;
    while (exponent-- > 0) {
        result *= base;
    }
    return result;
}

i32 distance_sq(i32 x1, i32 y1, i32 x2, i32 y2)
{
    return ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));
}

i32 count_triangles(i32 upper_bound)
{
    i32 count = 0;

    for (i32 x1 = 0; x1 <= upper_bound; x1++) {
    for (i32 y1 = 0; y1 <= upper_bound; y1++) {
    for (i32 x2 = 0; x2 <= upper_bound; x2++) {
    for (i32 y2 = 0; y2 <= upper_bound; y2++) {
        i32 distances[3] = { 0 };

        i32 a_sq = distance_sq(0,  0,  x1, y1);
        i32 b_sq = distance_sq(0,  0,  x2, y2);
        i32 c_sq = distance_sq(x1, y1, x2, y2);

        if (a_sq == 0 || b_sq == 0 || c_sq == 0)
            continue;

        distances[0] = a_sq;
        distances[1] = b_sq;
        distances[2] = c_sq;

        qsort(distances, ARRSIZE(distances), sizeof(distances[0]), comp_i32);

        if (distances[0] + distances[1] == distances[2]) {
            // printf("O (0, 0), P (%d, %d), Q (%d, %d)\n", x1, y1, x2, y2);
            // printf("Right Triangle: (%d + %d == %d)\n", distances[0], distances[1], distances[2]);
            count++;
        }
    }
    }
    }
    }

    // NOTE We count the same triangles twice by not expertly picking iterations for x and y above.
    // But, we can just divide the count we have by 2. EZPZ Lemon Squeezy.

    return count / 2;
}

int main(int argc, char **argv)
{
    assert(count_triangles(2) == 14);
    i32 count50 = count_triangles(50);
    printf("%d\n", count50);
}
