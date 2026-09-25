#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include <stdlib.h>


struct Array { uint8_t *array;
    size_t length;
    size_t cap;
};

void initArray(struct Array *a, size_t size);

void initZArray(struct Array *a, size_t size);

/// @brief Extend the array to cap atleast of size
void extendArray(struct Array *a, size_t size);

void freeArray(struct Array *a);

#endif
