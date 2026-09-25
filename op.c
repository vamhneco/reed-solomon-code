#include "headers/op.h"

struct GF_tables* init_tables() {

    struct GF_tables *tables = (struct GF_tables*) malloc(sizeof(struct GF_tables)); 

    tables->exp = (uint8_t*) malloc(512 * sizeof(uint8_t));
    tables->log = (uint8_t*) malloc(256 * sizeof(uint8_t));

    uint8_t x = 1;
    for(size_t i = 0; i < 255; i ++) {
        tables->exp[i] = x;
        tables->exp[i + 255] = x;

        tables->log[x] = i;

        x = (x & 0x80) ? (x << 1) ^ _PRIME_MOD : (x << 1); 
    }

    return tables;
}

uint8_t gf_mul(uint8_t x, uint8_t y, struct GF_tables *tables) {
    return tables->exp[tables->log[x] + tables->log[y]];
}

uint8_t gf_div(uint8_t x, uint8_t y, struct GF_tables *tables) {
    return tables->exp[tables->log[x] + 255 - tables->log[y]];
}

uint8_t gf_pow(uint8_t x, uint16_t pow, struct GF_tables *tables) {
    return tables->exp[(pow * tables->log[x]) % 255];
}


uint8_t gf_inv(uint8_t x, struct GF_tables *tables) {
    return tables->exp[255 - tables->log[x]];
}


struct Array* gf_poly_add(struct Array *a, struct Array *b, struct GF_tables *tables) {
    struct Array *res = (struct Array*) malloc(sizeof(struct Array));

    size_t len = a->length > b->length ? a->length : b->length;
    initZArray(res, len);

    for(size_t i = 0; i < a->length; i ++) {
        res->array[i + len - a->length] = a->array[i];
    }

    for(size_t i = 0; i < b->length; i ++) {
        res->array[i + len - b->length] ^= b->array[i];
    }
    
    return res;
}

struct Array* gf_poly_mul(struct Array *a, struct Array *b, struct GF_tables *tables) {
    struct Array *res = (struct Array*) malloc(sizeof(struct Array));

    size_t len = a->length + b->length;
    initZArray(res, len);

    for(size_t i = 0; i < a->length; i ++) {
        for(size_t j = 0; j < b->length; j ++) {
            res->array[i + j] ^= gf_mul(a->array[i], b->array[j], tables);
        }
    }

    return res;
}

uint8_t gf_poly_eval(struct Array *a, uint8_t x, struct GF_tables *tables) {
    uint8_t y = a->array[0];

    for(size_t i = 0; i < a->length; i ++) {
        y = gf_mul(y, x, tables) ^ a->array[i];
    }
    
    return y;
}

