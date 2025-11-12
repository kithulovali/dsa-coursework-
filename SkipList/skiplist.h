#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SLNode {
    int value;
    struct SLNode **forward;
    int level; // number of levels for this node
} SLNode;

typedef struct SkipList {
    SLNode *header;
    int max_level; // e.g., 16
    int level;     // current highest non-empty level (0-based)
    size_t size;   // count of elements (including duplicates)
} SkipList;

void skiplist_init(SkipList *sl);
void skiplist_free(SkipList *sl);
size_t skiplist_size(const SkipList *sl);

bool skiplist_findElement(const SkipList *sl, int value);
bool skiplist_insertElement(SkipList *sl, int value);
bool skiplist_removeElement(SkipList *sl, int value);
size_t skiplist_findAllElements(const SkipList *sl, int value, int *out_buf, size_t out_cap);
size_t skiplist_removeAllElements(SkipList *sl, int value);

// Aliases matching requested names (typos preserved)
#define findelement(sl, value)             skiplist_findElement((sl), (value))
#define insetelement(sl, value)            skiplist_insertElement((sl), (value))
#define revomeelement(sl, value)           skiplist_removeElement((sl), (value))
#define findallelement(sl, value, buf, c)  skiplist_findAllElements((sl), (value), (buf), (c))
#define removeallelements(sl, value)       skiplist_removeAllElements((sl), (value))

#ifdef __cplusplus
}
#endif

#endif // SKIPLIST_H
