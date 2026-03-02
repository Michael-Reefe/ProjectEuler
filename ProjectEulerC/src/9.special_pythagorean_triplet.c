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
    
int main() {

    printf("----------------------------------\n");
    printf("Problem 9: Special Pythagorean Triplet\n");
    printf("https://projecteuler.net/problem=9\n");
    printf("----------------------------------\n");

    /* we just need to generate some pythagorean triplets
       and check if their sum equals 1000.
       set an upper limit on the search range for n and m
       of 1000. */
    i8 found = 0;
    SArray_i32 *triplet = init_SArray_i32(3);
    for (i32 i = 1; i <= 1000; ++i) {
        if (found) break;
        for (i32 j = i+1; j <= 1000; ++j) {
            pythagorean_triplet(i, j, triplet);
            if (i_sum(triplet->arr, triplet->length) == 1000) {
                found = 1;
                break;
            }
        }
    }
    
    // Now that we have the triplet, we must find the product of the array
    i64 abc = i_prod(triplet->arr, triplet->length);

    // Dont forget to free memory
    free_SArray_i32(triplet);

    printf("Answer: %ld\n", abc);
    
    return 0;
}