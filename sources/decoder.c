#include "decoder.h"
#include "array.h"
#include "op.h"
#include <string.h>


struct Array *rs_calc_syndromes(struct Array *msg, size_t nsym, struct GF_tables *tables) {
    struct Array *synd = newArray(nsym + 1);
    
    synd->array[nsym] = 0; 
    for(size_t i = 0; i < nsym; i ++) {
        synd->array[i] = gf_poly_eval(msg, gf_pow(2, nsym - i - 1, tables), tables);
    }    
    return synd;
}

int rs_check(struct Array *msg, size_t nsym, struct GF_tables *tables) {
    struct Array *res = rs_calc_syndromes(msg, nsym, tables);
    for(size_t i = 0; i < res->length; i ++) {
        if(res->array[i] != 0) return 0; 
    } 
    return 1;
}

struct Array *rs_calc_errata_locator(struct Array *epos, struct GF_tables *tables) {
    struct Array *eloc = newArray(1); 
    eloc->array[0] = 1;
    
    struct Array *pol = newArray(2);
    pol->array[1] = 1;

    for(size_t i = 0; i < epos->length; i ++) {
        pol->array[0] = gf_pow(2, epos->array[i], tables);
        eloc = gf_poly_mul(eloc, pol, tables);
    } 

    return eloc;
}

struct Array *rs_calc_error_evaluator(struct Array *synd, struct Array *eloc, size_t nsym, struct GF_tables *tables) {
    struct Array *omega = gf_poly_mul(synd, eloc, tables);
    
    size_t pos = omega->length - (nsym + 1);
    memmove(omega->array, omega->array + pos, (nsym + 1) * sizeof(uint8_t));

    omega->length = nsym;

    return omega;
}

struct Array *rs_correct_errata(struct Array *msg, struct Array *synd, struct Array *e_pos, struct GF_tables *tables) {
    
    struct Array *coef_pos = newArray(e_pos->length);
    for(size_t i = 0; i < coef_pos->length; i ++) coef_pos->array[i] = msg->length - e_pos->array[i] - 1;
    
    struct Array *err_loc = rs_calc_errata_locator(coef_pos, tables);
    struct Array *err_eval = rs_calc_error_evaluator(synd, err_loc, err_loc->length - 1, tables);

    struct Array *X = newArray(coef_pos->length);
    for(size_t i = 0; i < coef_pos->length; i ++) {
        X->array[i] = gf_pow(2, coef_pos->array[i], tables);
    }

    // TODO 


}
