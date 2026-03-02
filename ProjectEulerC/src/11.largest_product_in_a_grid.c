#include <string.h>
#include "utils.h"

int main() {

    printf("----------------------------------\n");
    printf("Problem 11: Largest Product in a Grid\n");
    printf("https://projecteuler.net/problem=11\n");
    printf("----------------------------------\n");

    FILE *fptr;

    // Read in a text file containing our grid data 
    fptr = fopen("../data/11.grid.dat", "r");
    // Make sure the file was read successfully
    if (fptr == NULL) {
        printf("ERROR: Cannot read file 11.grid.dat");
        exit(1);
    }

    // Parse file contents into a 2D 20 x 20 array
    char line[100];
    char *end;
    u8 len1 = 20, len2 = 20;
    SArray2D_u8 *s2d = init_SArray2D_u8(len1, len2);
    for (u8 i = 0; i < len1; ++i) {
        char *line_ptr = fgets(line, 100, fptr);  // read the line
        if (line_ptr == NULL) break;
        char *scan_ptr = strtok(line, " ");       // split by spaces
        u8 j = 0;
        while (scan_ptr != NULL) {
            assert(j < len2);
            s2d->arr[i][j] = (u8)strtoul(scan_ptr, &end, 10);      // parse token into integer
            scan_ptr = strtok(NULL, " ");                          // get the next token
            ++j;
        }
    }
    // close the file
    fclose(fptr);

    // now we need to check rows, columns, and diagonals
    u8  window_size = 4;
    u32 maxprod = 0;
    u32 testprod, p1, p2;

    // loop through every position
    for (u8 i = 0; i < len1; ++i) {
        for (u8 j = 0; j < len2; ++j) {
            // check the row, if in range:
            if (j <= len2-window_size) {
                testprod = 1;
                // product of the row from j to j+window_size-1
                for (u8 k = 0; k < window_size; ++k) testprod *= (u32)s2d->arr[i][j+k];
                maxprod = max(maxprod, testprod);
            }
            // check the column, if in range:
            if (i <= len1-window_size) {
                testprod = 1;
                // product of the column from i to i+window_size-1
                for (u8 k = 0; k < window_size; ++k) testprod *= (u32)s2d->arr[i+k][j];
                maxprod = max(maxprod, testprod);
            }
            // check the diagonals, if in range:
            if ((i <= len1-window_size) && (j <= len2-window_size)) {
                p1 = 1;
                p2 = 1;
                for (u8 k = 0; k < window_size; ++k) {
                    p1 *= (u32)s2d->arr[i+k][j+k];                   // "forward" diagonal
                    p2 *= (u32)s2d->arr[i+window_size-1-k][j+k];     // "backward" diagonal
                }
                testprod = max(p1, p2);
                maxprod = max(maxprod, testprod);
            }
        }
    }

    // free memory
    free_SArray2D_u8(s2d);

    printf("Answer: %u\n", maxprod);

    return 0;
}