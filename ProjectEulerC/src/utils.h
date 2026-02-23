#include <stdlib.h>

#ifndef PROJECTEULERC_UTILS
#define PROJECTEULERC_UTILS

    // A prime factorization iterator structure.
    // Like in the Julia version, this is conceptually an iterator
    // that, at any given time, holds a state vector containing 
    // information about the prime factorization calculation
    typedef struct _PrimeFactorIterator {
        uint64_t nreduced;
        uint64_t primelimit;
        uint64_t candidate;
        uint8_t  stop;
    } PrimeFactorIterator;

    // This PrimeFactor structure, meanwhile, holds the result of one
    // step in the iteration process (the factor itself, and the exponent)
    typedef struct _PrimeFactor {
        uint64_t factor;
        uint64_t exponent;
    } PrimeFactor;

    // Functions for PrimeFactorizations
    PrimeFactorIterator *initialize_prime_factor_iterator(uint64_t number);
    void destroy_prime_factor_iterator(PrimeFactorIterator *it);
    PrimeFactor prime_iterate(PrimeFactorIterator *it);

#endif