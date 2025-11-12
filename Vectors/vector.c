#include "vector.h"
#include <stdlib.h>
#include <string.h>

static void vector_grow(Vector *v, size_t min_capacity) {
    if (v->capacity >= min_capacity) return;
    size_t new_cap = v->capacity ? v->capacity : 4;
    while (new_cap < min_capacity) new_cap *= 2;
    int *new_data = (int*)realloc(v->data, new_cap * sizeof(int));
    if (!new_data) {
        // Allocation failed; keep old state
        return;
    }
    v->data = new_data;
    v->capacity = new_cap;
}

void vector_init(Vector *v, size_t initial_capacity) {
    if (!v) return;
    v->size = 0;
    v->capacity = 0;
    v->data = NULL;
    if (initial_capacity) {
        v->data = (int*)malloc(initial_capacity * sizeof(int));
        if (v->data) {
            v->capacity = initial_capacity;
        }
    }
}

void vector_free(Vector *v) {
    if (!v) return;
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

size_t vector_size(const Vector *v) {
    return v ? v->size : 0;
}

bool vector_is_empty(const Vector *v) {
    return !v || v->size == 0;
}

bool vector_elemRank(const Vector *v, size_t rank, int *out_value) {
    if (!v || rank >= v->size) return false;
    if (out_value) *out_value = v->data[rank];
    return true;
}

bool vector_replaceRank(Vector *v, size_t rank, int new_value, int *old_value) {
    if (!v || rank >= v->size) return false;
    if (old_value) *old_value = v->data[rank];
    v->data[rank] = new_value;
    return true;
}

bool vector_insertRank(Vector *v, size_t rank, int value) {
    if (!v) return false;
    if (rank > v->size) return false; // can insert at size (append)
    if (v->size + 1 > v->capacity) {
        vector_grow(v, v->size + 1);
        if (v->size + 1 > v->capacity) return false; // grow failed
    }
    if (rank < v->size) {
        memmove(&v->data[rank+1], &v->data[rank], (v->size - rank) * sizeof(int));
    }
    v->data[rank] = value;
    v->size += 1;
    return true;
}

bool vector_removeRank(Vector *v, size_t rank, int *removed_value) {
    if (!v || rank >= v->size) return false;
    if (removed_value) *removed_value = v->data[rank];
    if (rank + 1 < v->size) {
        memmove(&v->data[rank], &v->data[rank+1], (v->size - rank - 1) * sizeof(int));
    }
    v->size -= 1;
    return true;
}
