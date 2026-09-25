#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include <stdlib.h>


struct Array { uint8_t *array;
    size_t length;
    size_t cap;
};

struct Array* newArray(size_t size);

struct Array* newZArray(size_t size);

/// @brief Extend the array to cap atleast of size
void extendArray(struct Array *a, size_t size);

void freeArray(struct Array *a);

void pushArray(uint8_t x); 


#endif
