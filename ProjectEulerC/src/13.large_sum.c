#include "utils.h"
#include "bigint.h"

int main() {

    printf("----------------------------------\n");
    printf("Problem 13: Large Sum\n");
    printf("https://projecteuler.net/problem=13\n");
    printf("----------------------------------\n");

    u64 init0 = 123456;
    BigInt *bi0 = bigint_from_int(init0);
    printf("init: %lu\n", init0);
    printf("low : %u\n", bi0->data->arr[0]);
    printf("high: %u\n", bi0->data->arr[1]);
    char *out0 = bigint_to_string(bi0);
    printf("out  : %s\n", out0);
    bigint_free(bi0);
    free(out0);

    u64 init = 1234567890987654321;
    BigInt *bi = bigint_from_int(init);
    printf("init: %lu\n", init);
    printf("low : %u\n", bi->data->arr[0]);
    printf("high: %u\n", bi->data->arr[1]);
    u64 bignum = bigint_to_int(bi);
    printf("big:  %lu (this WILL lose data)\n", bignum);
    bigint_free(bi);

    char *init2 = "999888777666555444333222111000123123123456456456789789789000\0";
    BigInt *b2 = bigint_from_string(init2);
    printf("init2    : %s\n", init2);
    printf("bigint[0]: %u\n", b2->data->arr[0]);
    printf("bigint[1]: %u\n", b2->data->arr[1]);
    char *out2 = bigint_to_string(b2);
    printf("out2 : %s\n", out2);
    bigint_free(b2);
    free(out2);

    char *init3 = "1000000000000000000000000000000000000000000000000000000000000\0";
    char *init4 = "12345\0";
    BigInt *b3 = bigint_from_string(init3);
    printf("b3[0]: %u\n", b3->data->arr[0]);
    BigInt *b4 = bigint_from_string(init4);
    printf("b4[0]: %u\n", b4->data->arr[0]);
    BigInt *b5 = bigint_init(b3->data->length*4*2);
    printf("b5[0]: %u\n", b5->data->arr[0]);

    bigint_add(b3, b4, b5);
    char *out3 = bigint_to_string(b5);
    printf("out3: %s\n", out3);
    free(out3);

    bigint_set_string(b4, "10\0");
    bigint_iadd(b5, b4);
    char *out4 = bigint_to_string(b5);
    printf("out4: %s\n", out4);
    free(out4);

    bigint_set_string(b4, "12356\0");
    bigint_sub(b5, b4, b3);
    char *out5 = bigint_to_string(b3);
    printf("out5: %s\n", out5);
    free(out5);

    bigint_set_string(b4, "111\0");
    bigint_isub(b3, b4);
    char *out6 = bigint_to_string(b3);
    printf("out6: %s\n", out6);
    free(out6);

    bigint_set_string(b4, "112\0");
    bigint_iadd(b3, b4);
    bigint_set_string(b4, "69420\0");
    bigint_mul(b3, b4, b5);
    char *out7 = bigint_to_string(b5);
    printf("out7: %s\n", out7);
    free(out7);

    bigint_set_string(b4, "100000\0");
    bigint_imul(b5, b4);
    char *out8 = bigint_to_string(b5);
    printf("out8: %s\n", out8);
    free(out8);

    bigint_div(b5, b4, b3);
    char *out9 = bigint_to_string(b3);
    printf("out9: %s\n", out9);
    free(out9);

    bigint_idiv(b3, b4);
    char *out10 = bigint_to_string(b3);
    printf("ot10: %s\n", out10);
    free(out10);

    BigInt *b6 = bigint_init(b3->data->length*4*2);
    bigint_set_string(b4, "7777777777777777777777777777777777777777\0");
    bigint_divmod(b3, b4, b5, b6);
    char *out11 = bigint_to_string(b5);
    char *out12 = bigint_to_string(b6);
    printf("ot11: %s\n", out11);
    printf("ot12: %s\n", out12);
    free(out11);
    free(out12);

    bigint_imul(b5, b4);
    bigint_iadd(b5, b6);
    char *out13 = bigint_to_string(b5);
    printf("ot13: %s\n", out13);
    free(out13);

    bigint_mod(b5, b4, b6);
    char *out14 = bigint_to_string(b6);
    printf("ot14: %s\n", out14);
    free(out14);

    bigint_imod(b5, b4);
    char *out15 = bigint_to_string(b5);
    printf("ot15: %s\n", out15);
    free(out15);

    bigint_free(b3);
    bigint_free(b4);
    bigint_free(b5);
    bigint_free(b6);

    printf("\n");

    return 0;
}