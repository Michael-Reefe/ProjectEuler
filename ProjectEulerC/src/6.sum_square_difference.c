#include "utils.h"

int main() {

    printf("----------------------------------\n");
    printf("Problem 6: Sum Square Difference  \n");
    printf("https://projecteuler.net/problem=6\n");
    printf("----------------------------------\n");

    /* This one is pretty straightforward, just compute the
       sum of squares and the square of the sum */
    i32 sum_of_squares = 0, square_of_sum = 0;
    for (i16 i = 1; i <= 100; ++i) {
        sum_of_squares += i*i;
        square_of_sum += i;
    }
    square_of_sum *= square_of_sum;

    i32 sum_diff = square_of_sum - sum_of_squares;

    printf("Answer: %d\n", sum_diff);
    
    return 0;
}