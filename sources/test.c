#include <stdio.h>
#include "encoder.h"
#include "op.h"
#include "array.h"

int main() {

    struct GF_tables *tables = init_tables();

    struct Array *gen = rs_generator_poly(4, tables);

    printf("%zu\n", gen->length); 
    for(size_t i = 0; i < gen->length; i ++) {
        printf("%x ", gen->array[i]);
    }
    printf("\n");

    return 0;
}

