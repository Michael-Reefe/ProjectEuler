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
PrimeFactorization create_prime_factorization(LinkedList *prime_factors, LinkedList *exponents) {
    PrimeFactorization pf;
    pf.factors = prime_factors;
    pf.exponents = exponents;
    return pf;
}

// This function calculates the prime factorization of a number,
// returning it as a PrimeFactorization object, which is just two 
// linked lists containing the prime factors and exponents
PrimeFactorization primefactorize(uint64_t number) {

    // Set up the linked lists for the outputs
    LinkedList *prime_factors = create_linked_list(ui64, sizeof(number));
    LinkedList *exponents     = create_linked_list(ui64, sizeof(number));

    uint64_t zero = 0;
    uint64_t one  = 1;

    uint64_t pf0 = 2;
    uint64_t ex0 = 0;
    append(prime_factors, &pf0);
    append(exponents,     &ex0);

    // Edge case
    if (number < 2) {
        PrimeFactorization pf = create_prime_factorization(prime_factors, exponents);
        return pf;
    }

    // Set a running division product
    uint64_t nreduced = number;

    // Remove factors of 2 first
    while (nreduced % 2 == 0) {
        nreduced /= 2;
        incr_value_at(exponents, one, exponents->length-1);  // increment the value in exponents by 1
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
            append(prime_factors, &nreduced);
            append(exponents,     &one);
            break;
        }
        // see if candidate evenly divides number 
        if (nreduced % candidate == 0) {
            append(prime_factors, &candidate);
            append(exponents,     &zero);
            while (nreduced % candidate == 0) {
                // update the running division result
                nreduced /= candidate;
                incr_value_at(exponents, one, exponents->length-1);
            }
            // update the upper limit we need to check
            primelimit = (uint64_t)sqrt((double)nreduced);
        }
        // increment candidate by 2 since all factors of 2 have already been removed
        candidate += 2;
    }

    // construct our output object
    PrimeFactorization pf = create_prime_factorization(prime_factors, exponents);
    return pf;
}
