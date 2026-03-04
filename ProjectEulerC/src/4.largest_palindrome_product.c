#include "utils.h"

// A function that checks if a number is a palindrome
i8 is_palindrome(i32 number) {

    // calculate the length of string we need
    i16 length = (i16)((ceil(log10((f64)number)))+1)*sizeof(char);

    // edge case where the length needs an extra digit if log10 is
    // exactly equal to an integer
    if (log10((f64)number) == (i32)(ceil(log10((f64)number)))) {
        length += 1;
    }

    // parse the number into a string
    char s[length];
    sprintf(s, "%d", number);

    // check if it is equal to itself reversed
    i8 ispal = 1;
    for (i16 i = 0; i < length/2; ++i) {
        // bounds checking (probably overkill)
        assert((i >= 0) && (i < length));
        assert((length-2-i >= 0) && (length-2-i < length));
        ispal &= (s[i] == s[length-2-i]);
    }

    return ispal;
}


int main() {

    printf("----------------------------------\n");
    printf("Problem 4: Largest Palindrome Product\n");
    printf("https://projecteuler.net/problem=4\n");
    printf("----------------------------------\n");

    const i16 minn = 100;
    const i16 maxn = 999;
    i32 gpp = 0, prod;

    /* Loop through every possible product of two 3 digit numbers.
       Start from the large end since that's more likely to contain 
       a large palindrome */
    for (i16 n1 = maxn; n1 >= minn; n1--) {
        /* For the inner loop, use a min value of n1 so we don't have to
           repeat pairs of values */
        for (i16 n2 = maxn; n2 >= n1; n2--) {
            prod = n1*n2;
            /* we only need to check if the number is a palindrome if it's larger
               than the previous palindrome product */            
            if ((prod > gpp) && is_palindrome(prod)) gpp = prod;
        }
    }

    printf("Answer        : %d\n", gpp);
    printf("Correct Answer: %d\n", 906609);
    printf("\n");


    return 0;
}
