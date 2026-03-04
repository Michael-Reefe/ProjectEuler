#include "utils.h"

// compute the GCD of two numbers "a" and "b" using the Euclidean algorithm
i32 gcd(i32 a, i32 b) {
    // repeatedly take the mod of the larger number until one of them is 0
    // note: arguments are not mutated here because they are not pointers, they are copies
    while ((a > 0) && (b > 0) && (a != b)) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    // the GCD is the resultant a or b which is not 0
    return max(a, b);
}

// compute the LCM via its relationship to the GCD
i32 lcm(i32 a, i32 b) {
    /* do the division first to prevent overflows for (really) large numbers.
       note that we don't have to worry about using integer division here because
       the GCD, by definition, will evenly divide both a and b */ 
    return abs(a) / gcd(a, b) * abs(b);
}

int main() {

    printf("----------------------------------\n");
    printf("Problem 5: Smallest Multiple      \n");
    printf("https://projecteuler.net/problem=5\n");
    printf("----------------------------------\n");

    /* The LCM of many numbers is the same as the LCM of
       nested pairs of numbers, i.e.:
       LCM(a,b,c,...) = LCM(a,LCM(b,LCM(c,...))) */
    i32 lcmout = 1;
    for (i32 i = 1; i <= 20; i++) lcmout = lcm(lcmout, i);

    printf("Answer        : %d\n", lcmout);
    printf("Correct Answer: %d\n", 232792560);
    printf("\n");
    
    return 0;
}