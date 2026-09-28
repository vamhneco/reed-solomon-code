#ifndef DECODER_H
#define DECODER_H

#include "array.h"
#include "op.h"

struct Array *rs_calc_syndromes(struct Array *msg, size_t nsym, struct GF_tables *tables);



#endif
