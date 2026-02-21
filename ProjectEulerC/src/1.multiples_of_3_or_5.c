#include <stdio.h>

int main() {

    printf("----------------------------------\n");
    printf("Problem 1: Multiples of 3 or 5    \n");
    printf("https://projecteuler.net/problem=1\n");
    printf("----------------------------------\n");

    // A counter to hold the sum 
    int s = 0;

    // Loop through and check if divisible by 3 or 5 before adding to the sum
    for (int i = 0; i < 1000; i++) {
        if (!(i % 3 == 0) && !(i % 5 == 0)) continue;
        s += i;
    }

    printf("Answer: %d\n", s);
    printf("\n");

    return 0;
}