#include "decoder.h"
#include "array.h"
#include "op.h"
#include <string.h>
#include <assert.h>


struct Array *rs_calc_syndromes(struct Array *msg, size_t nsym, struct GF_tables *tables) {
    struct Array *synd = newArray(nsym + 1);
    
    synd->array[nsym] = 0; 
    for(size_t i = 0; i < nsym; i ++) {
        synd->array[i] = gf_poly_eval(msg, gf_pow(2, nsym - i - 1, tables), tables);
    }    
    return synd;
}

int rs_check(struct Array *synd,  struct GF_tables *tables) {
    for(size_t i = 0; i < synd->length; i ++) {
        if(synd->array[i] != 0) return 0; 
    } 
    return 1;
}

struct Array *rs_calc_errata_locator(struct Array *epos, struct GF_tables *tables) {
    struct Array *eloc = newArray(1); 
    eloc->array[0] = 1;
    
    struct Array *pol = newArray(2);
    pol->array[1] = 1;

    for(size_t i = 0; i < epos->length; i ++) {
        struct Array *old_eloc = eloc;
        pol->array[0] = gf_pow(2, epos->array[i], tables);
        eloc = gf_poly_mul(eloc, pol, tables);

        freeArray(old_eloc);
    } 

    freeArray(pol);
    return eloc;
}

struct Array *rs_calc_error_evaluator(struct Array *synd, struct Array *eloc, size_t nsym, struct GF_tables *tables) {
    struct Array *omega = gf_poly_mul(synd, eloc, tables);
    

    assert(omega->length >= (nsym + 1));
    size_t pos = omega->length - (nsym + 1);
    memmove(omega->array, omega->array + pos, (nsym + 1) * sizeof(uint8_t));

    omega->length = nsym + 1;

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

    struct Array *E = newZArray(msg->length);

    size_t len = X->length;
    for(size_t i = 0; i < len; i ++) {
        uint8_t xi_inv = gf_inv(X->array[i], tables);
        uint8_t err_loc_prime = 1;
    
        for(size_t j = 0; j < len; j ++) if(j != i) {
            // err_loc_prime = product (1 - xi_inv * X[i])
            err_loc_prime = gf_mul(err_loc_prime, 1 ^ gf_mul(xi_inv, X->array[j], tables), tables); 
        }

        // y = omega(xi_inv) / err_loc_prime

        uint8_t y = gf_poly_eval(err_eval, xi_inv, tables);
        y = gf_mul(y, X->array[i], tables); // need to cancel the padding of synd
        
        if(err_loc_prime == 0) exit(EXIT_FAILURE);

        y = gf_div(y, err_loc_prime, tables);

        E->array[e_pos->array[i]] = y; 
    }    

    struct Array *res = gf_poly_add(msg, E, tables);
    freeArray(E);
    freeArray(err_loc);
    freeArray(err_eval);
    freeArray(coef_pos);

    return res;
}
