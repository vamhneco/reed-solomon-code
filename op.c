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

