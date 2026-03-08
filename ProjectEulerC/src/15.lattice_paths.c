#include "utils.h"

int main(void) {

    printf("----------------------------------\n");
    printf("Problem 15: Lattice Paths\n");
    printf("https://projecteuler.net/problem=15\n");
    printf("----------------------------------\n");

    // the lattice paths can be counted by just using
    // the binomial coefficient, AKA the "choose" function,
    // where "n choose k" = n! / k!(n-k)!
    i16 gridx = 20, gridy = 20;

    // In this case, n is the total length of any path from
    // the top-left to the bottom-right of the grid:
    u64 n = gridx + gridy;
    // And since we only have 2 options to move at any grid
    // point, once we have chosen all of the right movements,
    // all of the down movements are fully constrained (and
    // vice versa).  Therefore, since k represents the number
    // of choices, we have:
    u64 k = gridx;

    // So, the problem boils down to calculating 40 choose 20.
    // There is a binomial coefficient function in the "utils"
    // module.
    u64 npaths = binomial(n, k);

    printf("Answer        : %lu\n", npaths);
    printf("Correct Answer: %lu\n", 137846528820);
    printf("\n");

    return 0;
}
