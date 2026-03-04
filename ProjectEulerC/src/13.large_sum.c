#include "utils.h"
#include "bigint.h"

int main() {

    printf("----------------------------------\n");
    printf("Problem 13: Large Sum             \n");
    printf("https://projecteuler.net/problem=13\n");
    printf("----------------------------------\n");

    FILE *fptr;

    // Read in a text file containing our number data 
    fptr = fopen("../data/13.numbers.dat", "r");
    // Make sure the file was read successfully
    if (fptr == NULL) {
        printf("ERROR: Cannot read file 11.grid.dat");
        exit(1);
    }

    // File parsing parameters
    u8 numsize = 50;
    u8 nlines = 100;
    char line[2*numsize];

    // We will store the result in a BigInt type
    BigInt *bigsum = bigint_init(ceil((numsize/log10(2))/8) + 4);

    // Loop through each line in the file, read it in as a BigInt,
    // and add it to the sum
    for (u8 i = 0; i < nlines; ++i) {
        char *line_ptr = fgets(line, 2*numsize, fptr);     // read the line
        if (line_ptr == NULL) break;
        BigInt* bignum = bigint_from_string(line);      // bignum;
        bigint_iadd(bigsum, bignum);                    // bigsum += bignum;
        bigint_free(bignum);                            
    }
    // close the file
    fclose(fptr);

    // get a string representation of our sum
    char *bigsum_str = bigint_to_string(bigsum);

    // print only the first 10 characters
    printf("Answer        : %*.*s\n", 10, 10, bigsum_str);
    printf("Correct Answer: %lu\n", 5537376230);
    printf("\n");

    // release memory
    free(bigsum_str);
    bigint_free(bigsum);

    return 0;
}