#include "utils.h"
#include "bigint.h"

// calculate the length of the Collatz sequence that
// starts at n
u32 collatz(u32 n) {
    u32 col = 0;
    u32 cur = n;
    while (cur > 1) {
        if (cur % 2 == 0) 
            cur /= 2;
        else
            cur = 3*cur + 1;
        ++col;
    }
    return col;
}

int main() {

    printf("----------------------------------\n");
    printf("Problem 14: Largest Collatz Sequence\n");
    printf("https://projecteuler.net/problem=14\n");
    printf("----------------------------------\n");

    /* Note: this problem could be made much faster with the use
       of hash tables, but to avoid having to program them, for now,
       I will do the lazy thing as just calculate every Collatz sequence
       from scratch */
    
    /* We only need to check numbers below 500,000 because any
       collatz(2n) = collatz(n) + 1
    */
    u32 maxn = 1000000;
    u32 maxlen = 1;
    u32 maxnum = 1;
    u32 ilen;

    for (u32 i = maxn/2 + 1; i < maxn; ++i) {
        ilen = collatz(i);
        if (ilen > maxlen) {
            maxlen = ilen;
            maxnum = i;
        }
    }

    printf("Answer        : %u\n", maxnum);
    printf("Correct Answer: %u\n", 837799);
    printf("\n");

    return 0;
}