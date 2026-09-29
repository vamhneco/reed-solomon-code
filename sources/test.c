#include <stdio.h>
#include <stdint.h>
#include "decoder.h"
#include "encoder.h"
#include "op.h"
#include "array.h"
#include <string.h>

void print_msg(struct Array *a) {
    for(size_t i = 0; i < a->length; i ++) {
        printf("0x%02x ", a->array[i]);
    }
    printf("\n");
}

int main() {

    struct GF_tables *tables = init_tables();

    struct Array *msg = newArray(16);
    uint8_t a[] = {0x40, 0xd2, 0x75, 0x47, 0x76, 0x17, 0x32, 0x06,
                   0x27, 0x26, 0x96, 0xc6, 0xc6, 0x96, 0x70, 0xec};

    memcpy(msg->array, a, msg->length * sizeof(uint8_t));

    struct Array *ecod_msg = rs_encode_msg(msg, 10, tables);

     int n_e;
     scanf("%d", &n_e);

     struct Array *e_pos = newArray(n_e);
     for(size_t i = 0; i < e_pos->length; i ++) {
         int x; scanf("%d", &x);
         e_pos->array[i] = (uint8_t)x;
     }
    
    struct Array *cor_msg = rs_encode_msg(msg, 10, tables);
    for(size_t i = 0; i < e_pos->length; i ++) {
        cor_msg->array[e_pos->array[i]] ++;
    }

    struct Array *synd = rs_calc_syndromes(cor_msg, 10, tables);
    struct Array *corrected = rs_correct_errata(cor_msg, synd, e_pos, tables);

    print_msg(ecod_msg);
    print_msg(cor_msg);
    print_msg(synd);
    print_msg(corrected);


    return 0;
}

