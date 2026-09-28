#include <stdio.h>
#include "encoder.h"
#include "op.h"
#include "array.h"
#include <string.h>

int main() {

    struct GF_tables *tables = init_tables();

    struct Array *msg = newArray(16);
    uint8_t a[] = {0x40, 0xd2, 0x75, 0x47, 0x76, 0x17, 0x32, 0x06,
                   0x27, 0x26, 0x96, 0xc6, 0xc6, 0x96, 0x70, 0xec};

    memcpy(msg->array, a, msg->length * sizeof(uint8_t));

    for(size_t i = 0; i < msg->length; i ++) {
        printf("0x%02x ", msg->array[i]);
    }
    printf("\n");

    struct Array *msg_out = rs_encode_msg(msg, 10, tables);
    for(size_t i = 0; i < msg_out->length; i ++) {
        printf("0x%02x ", msg_out->array[i]);
    }

    

    return 0;
}

