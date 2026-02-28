#include <stdio.h>
#include <math.h>
#include "utils.h"

/*

This utils module contains various functions that will be
useful for many problems in Project Euler.

*/

PrimeFactorIterator *initialize_prime_factor_iterator(u64 number) {
    PrimeFactorIterator *it = (PrimeFactorIterator*)malloc(sizeof(PrimeFactorIterator));
    it->nreduced   = number;
    it->candidate  = 3;
    it->primelimit = (u64)sqrt((f64)number);
    it->stop       = 0;
    return it;
}

void destroy_prime_factor_iterator(PrimeFactorIterator *it) {
    free(it);
}

// This function calculates the prime factorization of a number,
// returning it as a PrimeFactorization object, which is just two 
// linked lists containing the prime factors and exponents
PrimeFactor prime_iterate(PrimeFactorIterator *it) {

    // Default value
    PrimeFactor pf;
    pf.factor = 2;
    pf.exponent = 0;

    // Error handling
    if (it->stop == 1) {
        printf("ERROR: PrimeFactorIterator iterated too many times!");
        exit(1);
    }

    // Edge case
    if (it->nreduced < 2) {

        // Tell the iterator that we should stop
        it->stop = 1;
        return pf;
    }

    // Remove factors of 2 first
    if (it->nreduced % 2 == 0) {
        while (it->nreduced % 2 == 0) {
            it->nreduced /= 2;
            pf.exponent += 1;
        }
        it->primelimit = (u64)sqrt((f64)it->nreduced);
        it->candidate = 3;
        return pf;
    }

    // We will find the prime factors by trial division, in other words
    // just checking every number to see if it evenly divides the target.
    while (it->nreduced > 1) {
        // if candidate ever exceeds primelimit, then we know that
        // the remaining "nreduced" must be a prime, so we can stop
        if (it->candidate > it->primelimit + 1) {
            pf.factor = it->nreduced;
            pf.exponent = 1;
            it->nreduced = 1;
            it->stop = 1;
            return pf;
        }
        // see if candidate evenly divides number 
        if (it->nreduced % it->candidate == 0) {
            pf.factor = it->candidate;
            pf.exponent = 0;
            while (it->nreduced % it->candidate == 0) {
                // update the running division result
                it->nreduced /= it->candidate;
                pf.exponent += 1;
            }
            it->primelimit = (u64)sqrt((f64)it->nreduced);
            it->candidate += 2;
            return pf;
        }
        // increment candidate by 2 since all factors of 2 have already been removed
        it->candidate += 2;
    }

    // If we ever reach the end of the while loop, we know we have found all factors and can stop
    it->stop = 1;

    return pf;
}
