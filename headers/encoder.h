#ifndef ENCODER_H
#define ENCODER_H


#include <stdint.h>
#include "op.h"
#include "array.h"

struct Array* rs_generator_poly(size_t nsym, struct GF_tables *tables);
struct Array* rs_encode_msg(struct Array *msg_in, size_t nsym, struct GF_tables *tables);

#endif

