#include "utils.h"


/* generate a pythagorean triplet from a pair of
    integers (n, m) where m > n, using a variant of
    Euclid's algorithm */
void pythagorean_triplet(i32 n, i32 m, SArray_i32* triplet) {
    triplet->arr[0] = 2*m*n;
    triplet->arr[1] = m*m - n*n;
    triplet->arr[2] = m*m + n*n;
    if ((n % 2 != 0) && (m % 2 != 0)) {
        for (i8 i = 0; i < 3; ++i) triplet->arr[i] = triplet->arr[i] / 2;
    }
}
    
int main(void) {

    printf("----------------------------------\n");
    printf("Problem 9: Special Pythagorean Triplet\n");
    printf("https://projecteuler.net/problem=9\n");
    printf("----------------------------------\n");

    /* we just need to generate some pythagorean triplets
       and check if their sum equals 1000.
       set an upper limit on the search range for n and m
       of 1000. */
    i8 found = 0;
    i64 s;
    SArray_i32 *triplet = init_SArray_i32(3);
    for (i32 i = 1; i <= 1000; ++i) {
        if (found) break;
        for (i32 j = i+1; j <= 1000; ++j) {
            pythagorean_triplet(i, j, triplet);
            // sum of the triplet
            s = triplet->arr[0] + triplet->arr[1] + triplet->arr[2];
            if (s == 1000) {
                found = 1;
                break;
            }
        }
    }
    
    // Now that we have the triplet, we must find the product of the array
    i64 abc = triplet->arr[0] * triplet->arr[1] * triplet->arr[2];

    // Dont forget to free memory
    free_SArray_i32(triplet);

    printf("Answer        : %ld\n", abc);
    printf("Correct Answer: %ld\n", 31875000L);
    printf("\n");
    
    return 0;
}
