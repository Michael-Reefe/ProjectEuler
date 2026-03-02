#include "utils.h"

int main() {

    printf("----------------------------------\n");
    printf("Problem 12: Highly Divisible Triangular Number\n");
    printf("https://projecteuler.net/problem=12\n");
    printf("----------------------------------\n");

    u64 tnum;

    // loop through and have a running total that gives the 
    // triangular numbers
    u32 i = 0;
    u64 ndiv = 1, ndiv_tmp = 1;
    while (ndiv < 500) {
        // triangular numbers can be generated with this formula:
        tnum = i*(i+1)/2;
        /* check how many factors this triangular number has by
           checking the divisors of i and i+1 instead of checking
           for tnum itself (which can get large) */
        if (i % 2 == 0) {
            ndiv_tmp = ndivisors(i+1);
            ndiv = ndivisors(i/2)*ndiv_tmp;
        } else {
            ndiv = ndiv_tmp*ndivisors((i+1)/2);
        }
        ++i;
    }

    printf("Answer: %lu\n", tnum);

    return 0;
}