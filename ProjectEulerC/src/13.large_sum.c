#include "utils.h"
#include "bigint.h"

int main() {

    printf("----------------------------------\n");
    printf("Problem 13: Large Sum\n");
    printf("https://projecteuler.net/problem=13\n");
    printf("----------------------------------\n");

    u64 init = 1234567890987654321;
    BigInt *bi = bigint_from_int(init);
    printf("init: %lu\n", init);
    printf("low : %u\n", bi->data->arr[0]);
    printf("high: %u\n", bi->data->arr[1]);

    // u64 bignum = bigint_to_int(bi);
    // printf("big:  %lu (this WILL lose data)\n", bignum);
    char *out1 = bigint_to_string(bi);
    printf("out1 : %s\n", out1);
    free(out1);

    char *init2 = "999888777666555444333222111000111222333444555666777888999\0";
    BigInt *b2 = bigint_from_string(init2);
    printf("init2    : %s\n", init2);
    printf("bigint[0]: %u\n", b2->data->arr[0]);
    printf("bigint[1]: %u\n", b2->data->arr[1]);
    printf("bigint[2]: %u\n", b2->data->arr[2]);

    char *out2 = bigint_to_string(b2);
    printf("out2 : %s\n", out2);
    free(out2);

    // printf("\n");

    return 0;
}