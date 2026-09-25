#include "array.h"

struct Array* newArray(size_t size) {
    struct Array *a = (struct Array*)malloc(sizeof(struct Array));
    a->array = (uint8_t*)malloc(size * sizeof(uint8_t));
    if(a->array == NULL) {
        freeArray(a);
        exit(EXIT_FAILURE);
    }
    a->length = size;
    a->cap = size;

    return a;
} 

struct Array* newZArray(size_t size) {
    struct Array *a = (struct Array*)malloc(sizeof(struct Array));
    a->array = (uint8_t*)calloc(size, sizeof(uint8_t));
    if(a->array == NULL) {
        freeArray(a);
        exit(EXIT_FAILURE);
    }
    a->length = size;
    a->cap = size;

    return a;
}

void extendArray(struct Array *a, size_t size) {
    if(a->cap >= size) return;
    a->cap = a->cap << 1;

    void *p = realloc(a->array, a->cap);
    if(p == NULL) exit(EXIT_FAILURE);

    a->array = p;
}

void freeArray(struct Array *a) {
    if(a->array != NULL) {
        free(a->array);
        a->array = NULL;
    }
    a->length = 0;
    a->cap = 0;
}
