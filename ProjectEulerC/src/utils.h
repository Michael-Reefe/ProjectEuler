#include <stdlib.h>
#include "lists.h"

#ifndef PROJECTEULERC_UTILS
#define PROJECTEULERC_UTILS

    // A prime factorization structure that contains a list of prime factors
    // and a list of exponents on those prime factors
    typedef struct PrimeFactorization {
        LinkedList *factors;
        LinkedList *exponents;
    } PrimeFactorization;

    // Functions for PrimeFactorizations
    PrimeFactorization create_prime_factorization(LinkedList *prime_factors, LinkedList *exponents);
    PrimeFactorization primefactorize(uint64_t number);

#endif