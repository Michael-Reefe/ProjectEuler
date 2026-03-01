#include "utils.h"

int main() {

    printf("----------------------------------\n");
    printf("Problem 7: 10001st Primie         \n");
    printf("https://projecteuler.net/problem=7\n");
    printf("----------------------------------\n");

    /*
      We need to find the 10,001st prime number.

      To do so, we can make use of the Sieve of Eratosthenes,
      which is a pretty efficient way to mark all of the prime
      numbers below some value n.
      (note: this function is contained in utils)

      Unfortunately, we don't know what n should be here, since
      we don't know how large the 10,001st prime is (that's the
      whole point of the problem). 

      So instead what we can do is iteratively call the Sieve
      of Eratosthenes on chunks of numbers and count up how many
      primes we find until we reach the 10,001st.
    */

    u64 search_target = 10001;
    // "n" holds the first number in the chunk of numbers to be searched
    u64 n = 1;
    // note: integer floor division
    u64 chunksize = search_target / 10;

    // We first do the initial iteration with the regular 
    // Sieve of Eratosthenes:
    SArray_u64 *primes = sieve_of_eratosthenes(chunksize);

    // From here, we do an infinite loop until primes has a
    // length of 10,001
    while (primes->length < search_target) {
        n += chunksize;
        segmented_sieve_step(n, chunksize, primes);
    }

    // Finally, grab the appropriate element of our array
    u64 prime = primes->arr[search_target-1];

    // Don't forget to free our memory
    free_SArray_u64(primes);

    printf("Answer: %lu\n", prime);

    return 0;
}