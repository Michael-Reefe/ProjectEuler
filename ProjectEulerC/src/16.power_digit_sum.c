#include "utils.h"
#include "bigint.h"

int main(void) {

    printf("----------------------------------\n");
    printf("Problem 16: Power Digit Sum\n");
    printf("https://projecteuler.net/problem=16\n");
    printf("----------------------------------\n");

    // Initialize some "bigint" types to hold arbitrarily large integers
    BigInt *power2 = bigint_init(32);
    BigInt *two    = bigint_from_int(2);

    // generate a bigint of 2^1000
    bigint_set_int(power2, 1);
    for (u64 i = 0; i < 1000; ++i) {
        bigint_imul(power2, two);
    }
    // string representation of 2^1000
    char *power2str = bigint_to_string(power2);

    bigint_free(power2);
    bigint_free(two);

    // now loop through the string and sum up the digits
    u64 digitsum = 0;
    u64 i = 0;
    while (power2str[i] != '\0') {
        digitsum += power2str[i]-'0';
        ++i;
    }
    free(power2str);

    printf("Answer        : %lu\n", digitsum);
    printf("Correct Answer: %lu\n", 1366UL);
    printf("\n");

    return 0;
}
