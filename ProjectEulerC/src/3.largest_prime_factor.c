#include <stdlib.h>
#include <stdio.h>
#include "lists.h"
#include "utils.h"

int main() {

    printf("----------------------------------\n");
    printf("Problem 3: Largest Prime Factor   \n");
    printf("https://projecteuler.net/problem=3\n");
    printf("----------------------------------\n");

    PrimeFactorization pf = primefactorize(600851475143);
    uint64_t lpf = max_in_list(pf.factors);
    free_prime_factorization(pf);

    // Output the result
    printf("Answer: %llu\n", lpf);
    printf("\n");

    return 0;
}