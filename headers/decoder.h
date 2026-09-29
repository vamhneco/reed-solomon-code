#ifndef DECODER_H
#define DECODER_H

#include "array.h"
#include "op.h"

struct Array *rs_calc_syndromes(struct Array *msg, size_t nsym, struct GF_tables *tables);

struct Array *rs_calc_errata_locator(struct Array *epos, struct GF_tables *tables);

struct Array *rs_calc_error_evaluator(struct Array *synd, struct Array *eloc, size_t nsym, struct GF_tables *tables) ;

struct Array *rs_correct_errata(struct Array *msg, struct Array *synd, struct Array *e_pos, struct GF_tables *tables) ;

#endif
