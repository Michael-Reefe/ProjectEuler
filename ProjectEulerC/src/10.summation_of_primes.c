#include "utils.h"

int main(void) {

    printf("----------------------------------\n");
    printf("Problem 10: Summation of Primes\n");
    printf("https://projecteuler.net/problem=10\n");
    printf("----------------------------------\n");

    /* This problem is really easy because we already
       have a Sieve of Eratosthenes function that we
       made for problem 7.  We can just call that to
       get all the primes below 2 million and then sum
       them up */
    
    u64 n = 2000000;
    SArray_u64 *primes = sieve_of_eratosthenes(n);
    i64 psum = 0;
    for (i64 i = 0; i < primes->length; ++i) psum += primes->arr[i];

    // Dont forget to free!
    free_SArray_u64(primes);

    printf("Answer        : %ld\n", psum);
    printf("Correct Answer: %ld\n", 142913828922);
    printf("\n");
    
    return 0;
}
