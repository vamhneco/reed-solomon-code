#include "encoder.h"
#include "op.h"
#include "array.h"

#include <stdio.h>

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
