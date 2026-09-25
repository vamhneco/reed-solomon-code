#ifndef OP_H
#define OP_H

#include <stdint.h>
#include "array.h"

#define _PRIME_MOD 0x11d

struct GF_tables {
    uint8_t *exp;
    uint8_t *log;
};

struct GF_tables* init_tables();

uint8_t gf_mul(uint8_t x, uint8_t y, struct GF_tables *tables);

uint8_t gf_div(uint8_t x, uint8_t y, struct GF_tables *tables);

uint8_t gf_pow(uint8_t x, uint16_t pow, struct GF_tables *tables);

uint8_t gf_inv(uint8_t x, struct GF_tables *tables);


#endif
