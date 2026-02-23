#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lists.h"
#include "utils.h"

/*

This utils module contains various functions that will be
useful for many problems in Project Euler.

*/

// a constructor for PrimeFactorization structs
PrimeFactorization create_prime_factorization() {
    PrimeFactorization pf;
    LinkedList_ui64 *factors   = create_linked_list_ui64();
    LinkedList_ui64 *exponents = create_linked_list_ui64();
    pf.factors = factors;
    pf.exponents = exponents;
    return pf;
}

void free_prime_factorization(PrimeFactorization pf) {
    free_list(pf.factors);
    free_list(pf.exponents);
}

// This function calculates the prime factorization of a number,
// returning it as a PrimeFactorization object, which is just two 
// linked lists containing the prime factors and exponents
PrimeFactorization primefactorize(uint64_t number) {

    // Set up the outputs
    PrimeFactorization pf = create_prime_factorization();

    // Start with 2
    append(pf.factors,   2);
    append(pf.exponents, 0);

    // Edge case
    if (number < 2) {
        return pf;
    }

    // Set a running division product
    uint64_t nreduced = number;

    // Remove factors of 2 first
    while (nreduced % 2 == 0) {
        nreduced /= 2;
        incr_at_index(pf.exponents, 1, get_length(pf.exponents)-1);  // increment the value in exponents by 1
    }

    // We will find the prime factors by trial division, in other words
    // just checking every number to see if it evenly divides the target.
    uint64_t candidate = 3;
    uint64_t primelimit = (uint64_t)sqrt((double)number);
    while (1) {
        // once nreduced reaches 1, we have found all factors and can stop
        if (nreduced == 1) break;
        // if candidate ever exceeds primelimit, then we know that
        // the remaining "nreduced" must be a prime, so we can stop
        if (candidate > primelimit + 1) {
            append(pf.factors,  nreduced);
            append(pf.exponents,       1);
            break;
        }
        // see if candidate evenly divides number 
        if (nreduced % candidate == 0) {
            append(pf.factors,  candidate);
            append(pf.exponents,        0);
            while (nreduced % candidate == 0) {
                // update the running division result
                nreduced /= candidate;
                incr_at_index(pf.exponents, 1, get_length(pf.exponents)-1);
            }
            // update the upper limit we need to check
            primelimit = (uint64_t)sqrt((double)nreduced);
        }
        // increment candidate by 2 since all factors of 2 have already been removed
        candidate += 2;
    }

    return pf;
}
