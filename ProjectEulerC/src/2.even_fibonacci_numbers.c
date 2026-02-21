#include <stdio.h>

int main() {

    printf("----------------------------------\n");
    printf("Problem 2: Even Fibonacci Numbers \n");
    printf("https://projecteuler.net/problem=2\n");
    printf("----------------------------------\n");

    // The two starting fibonacci numbers (start at 1 and 1 instead of 1 and 2 so
    // that we explicitly check whether 2 is part of the final sum; hint: it is)
    int fib1 = 1;
    int fib2 = 1;
    // Loop through and compute the following fibonacci numbers
    int fib3 = 0;
    int fib_sum = 0;
    while (1) {
        // get the next fibonacci number
        fib3 = fib1 + fib2;
        // check if we've exceeded the 4 million limit
        if (fib3 > 4000000) break;
        // if it's even, add it to the sum
        if (fib3 % 2 == 0) fib_sum += fib3;
        // update variables for the next loop iteration
        fib1 = fib2;
        fib2 = fib3;
    }

    // Output the result
    printf("Answer: %d\n", fib_sum);
    printf("\n");

    return 0;
}