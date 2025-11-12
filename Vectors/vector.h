#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v, size_t initial_capacity);
void vector_free(Vector *v);
size_t vector_size(const Vector *v);
bool vector_is_empty(const Vector *v);

// Returns true on success, false on invalid rank
bool vector_elemRank(const Vector *v, size_t rank, int *out_value);
// Returns true on success, false on invalid rank
bool vector_replaceRank(Vector *v, size_t rank, int new_value, int *old_value);
// Returns true on success, false on invalid rank (0..size)
bool vector_insertRank(Vector *v, size_t rank, int value);
// Returns true on success, false on invalid rank
bool vector_removeRank(Vector *v, size_t rank, int *removed_value);

#ifdef __cplusplus
}
#endif

#endif // VECTOR_H
