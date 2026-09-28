#include "encoder.h"
#include "op.h"
#include "array.h"

#include <string.h>
#include <assert.h>

struct Array* rs_generator_poly(size_t nsym, struct GF_tables *tables) {

    struct Array *res = newArray(1);
    res->array[0] = 1;

    struct Array *tmp = newArray(2);
    tmp->array[0] = 1;

    for(size_t i = 0; i < nsym; i ++) {
        tmp->array[1] = gf_pow(2, i, tables);
        res = gf_poly_mul(res, tmp, tables);
    }

    return res;
}

struct Array *rs_encode_msg(struct Array *msg_in, size_t nsym, struct GF_tables *tables) {
    if(msg_in->length + nsym > 255) {
        exit(EXIT_FAILURE);
    }

    struct Array *gen = rs_generator_poly(nsym, tables);

    assert(gen->length - 1 == nsym); 
    struct Array *msg_out = newZArray(msg_in->length + nsym);

    memcpy(msg_out->array, msg_in->array, msg_in->length * sizeof(uint8_t));

    for(size_t i = 0; i < msg_in->length; i ++) {
        uint8_t coef = msg_out->array[i];
        if(coef != 0) {
            for(size_t j = 1; j < gen->length; j ++) {
                msg_out->array[i + j] ^= gf_mul(gen->array[j], coef, tables);
            }
        }
    }
    memcpy(msg_out->array, msg_in->array, msg_in->length * sizeof(uint8_t));

    return msg_out;
}
