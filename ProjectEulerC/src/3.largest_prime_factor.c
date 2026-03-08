#include "utils.h"

int main(void) {

    printf("----------------------------------\n");
    printf("Problem 3: Largest Prime Factor   \n");
    printf("https://projecteuler.net/problem=3\n");
    printf("----------------------------------\n");

    // Set up the iterator
    PrimeFactorIterator *it = initialize_prime_factor_iterator(600851475143);

    PrimeFactor pf;    // container
    u64 lpf = 0;  // largest prime factor
    u64 cpf = 0;  // current prime factor

    // Iterate through the prime factors and keep track of the maximum 
    while (it->stop != 1) {
        pf = prime_iterate(it);
        cpf = pf.factor;
        if (cpf > lpf) lpf = cpf;
    }

    // Don't forget to deallocate!
    destroy_prime_factor_iterator(it);

    // Output the result
    printf("Answer        : %lu\n", lpf);
    printf("Correct Answer: %lu\n", 6857UL);
    printf("\n");

    return 0;
}
