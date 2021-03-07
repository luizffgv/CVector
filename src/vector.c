#include "../include/vector.h"

#include <math.h> // for ceilf
#include <stdlib.h>
#include <string.h> // for memcpy

struct Vector_
{
    size_t elem_sz;
    size_t elems_n;
    size_t capacity;
    void *data;
};

static const float growth_factor = 1.6180339887498948482;

Vector VecNew(size_t elem_sz)
{
    Vector vec = malloc(sizeof(*vec));
    vec->elem_sz = elem_sz;
    vec->elems_n = 0;
    vec->capacity = 0;
    vec->data = NULL;

    return vec;
}

void VecDelete(Vector vec)
{
    free(vec->data);
    free(vec);
}

size_t VecLength(Vector vec)
{
    return vec->elems_n;
}

size_t VecSize(Vector vec)
{
    return vec->elem_sz;
}

size_t VecCapacity(Vector vec)
{
    return vec->capacity;
}


void *VecData(Vector vec)
{
    return vec->data;
}

void VecDataFree(Vector vec)
{
    free(vec->data);
    vec->elems_n = 0;
    vec->capacity = 0;
}

void *VecDataSteal(Vector vec)
{
    vec->elems_n = 0;
    vec->capacity = 0;

    void *ret = vec->data;
    vec->data = NULL;
    return ret;
}

void *VecAt(Vector vec, size_t index)
{
    return vec->data + index * vec->elem_sz;
}

void *VecPopAt(Vector vec, size_t index)
{
    --vec->elems_n;

    void *elem = malloc(vec->elem_sz);
    memcpy(elem, VecAt(vec, index), vec->elem_sz);

    memmove(VecAt(vec, index),
            VecAt(vec, index + 1), vec->elem_sz * (vec->elems_n - index));

    return elem;
}

void *VecBack(Vector vec)
{
    return VecAt(vec, vec->elems_n - 1);
}

void *VecPopBack(Vector vec)
{
    return VecPopAt(vec, vec->elems_n - 1);
}

void VecPushBack(Vector vec, void *elem)
{
    if (vec->elems_n == vec->capacity)
    {
        vec->capacity = ceilf(vec->capacity ? vec->capacity * growth_factor
                                            : 1);
        vec->data     = realloc(vec->data, vec->capacity * vec->elem_sz);
    }

    memcpy(vec->data + vec->elem_sz * vec->elems_n++, elem, vec->elem_sz);
}

void VecForEach(Vector vec, void (*callback)(void *))
{
    for (size_t i = 0; i < vec->elems_n; ++i)
        callback(VecAt(vec, i));
}

void *VecFindIf(Vector vec, bool (*predicate)(void *))
{
    for (size_t i = 0; i < vec->elems_n; ++i)
        if (predicate(VecAt(vec, i)))
            return VecAt(vec, i);

    return NULL;
}
