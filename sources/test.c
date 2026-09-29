#include <stdio.h>
#include <stdint.h>
#include "decoder.h"
#include "encoder.h"
#include "op.h"
#include "array.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

void print_msg(struct Array *a) {
    for(size_t i = 0; i < a->length; i ++) {
        printf("0x%02x ", a->array[i]);
    }
    printf("\n");
}

int getRandom(int l, int r) {
    return rand() % (r - l + 1) + l;
}

int test(struct Array *msg, int nsym, struct GF_tables *tables) {
    struct Array *corrupted_msg = newArray(msg->length);
    
    struct Array *err_pos = newArray(255);
    err_pos->length = 0;

    for(size_t i = 0; i < msg->length; i ++) {
        uint8_t err = (getRandom(1, 1000) <= 5) * getRandom(1, 255);
        corrupted_msg->array[i] = msg->array[i] ^ err; 
        
        if(err != 0) err_pos->array[err_pos->length++] = i;
    }

    if(err_pos->length == 0) return 1;   
    if(err_pos->length > nsym) return -1;

    struct Array *synd = rs_calc_syndromes(corrupted_msg, nsym, tables);
    struct Array *corrected_msg = rs_correct_errata(corrupted_msg, synd, err_pos, tables);

    for(size_t i = 0; i < msg->length; i ++) {
        if(msg->array[i] != corrected_msg->array[i]) return 0;
    }
    return 1;
}

int main() {

    srand(time(NULL));

    struct GF_tables *tables = init_tables();
    
    size_t N = 214, nsym = 30;
    struct Array *msg = newArray(N);
    for(size_t i = 0; i < msg->length; i ++) msg->array[i] = getRandom(0, 255);

    struct Array *encoded_msg = rs_encode_msg(msg, nsym, tables); 
    
    // test(encoded_msg, nsym, tables);
    
    int nTest = 100000;
    for(int i = 1; i <= nTest; i ++) {
        int x = test(encoded_msg, nsym, tables);
        if(x == 0) {
            printf("WAT DE HEOOOOOOOOOOO!\n");
            exit(EXIT_FAILURE);
        }
        else printf("\rpass %d test!", i);
    }

    
    return 0;
}

