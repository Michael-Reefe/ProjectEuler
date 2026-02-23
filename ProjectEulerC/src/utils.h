#include <stdlib.h>
#include "lists.h"

#ifndef PROJECTEULERC_UTILS
#define PROJECTEULERC_UTILS

    // A prime factorization structure that contains a list of prime factors
    // and a list of exponents on those prime factors
    typedef struct PrimeFactorization {
        LinkedList_ui64 *factors;
        LinkedList_ui64 *exponents;
    } PrimeFactorization;

    // Functions for PrimeFactorizations

    PrimeFactorization create_prime_factorization();
    void free_prime_factorization(PrimeFactorization pf);

    PrimeFactorization primefactorize(uint64_t number);

#endif