#include "skiplist.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SL_MAX_LEVEL 16
#define SL_P 0.5

static int random_level(void) {
    int lvl = 1;
    while ((rand() / (double)RAND_MAX) < SL_P && lvl < SL_MAX_LEVEL)
        lvl++;
    return lvl;
}

static SLNode* node_create(int level, int value) {
    SLNode* n = (SLNode*)malloc(sizeof(SLNode));
    if (!n) return NULL;
    n->value = value;
    n->level = level;
    n->forward = (SLNode**)calloc((size_t)level, sizeof(SLNode*));
    if (!n->forward) { free(n); return NULL; }
    return n;
}

void skiplist_init(SkipList *sl) {
    if (!sl) return;
    sl->max_level = SL_MAX_LEVEL;
    sl->level = 1;
    sl->size = 0;
    sl->header = node_create(sl->max_level, INT_MIN);
}

void skiplist_free(SkipList *sl) {
    if (!sl || !sl->header) return;
    SLNode* cur = sl->header->forward[0];
    while (cur) {
        SLNode* next = cur->forward[0];
        free(cur->forward);
        free(cur);
        cur = next;
    }
    free(sl->header->forward);
    free(sl->header);
    sl->header = NULL;
    sl->level = 1;
    sl->size = 0;
}

size_t skiplist_size(const SkipList *sl) {
    return sl ? sl->size : 0;
}

bool skiplist_findElement(const SkipList *sl, int value) {
    if (!sl || !sl->header) return false;
    const SLNode* x = sl->header;
    for (int i = sl->level - 1; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->value < value)
            x = x->forward[i];
    }
    x = x->forward[0];
    return x && x->value == value;
}

bool skiplist_insertElement(SkipList *sl, int value) {
    if (!sl || !sl->header) return false;
    SLNode* update[SL_MAX_LEVEL] = {0};
    SLNode* x = sl->header;
    for (int i = sl->level - 1; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->value < value)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[0];
    // allow duplicates: always insert new node
    int lvl = random_level();
    if (lvl > sl->level) {
        for (int i = sl->level; i < lvl; ++i) {
            update[i] = sl->header;
        }
        sl->level = lvl;
    }
    SLNode* n = node_create(lvl, value);
    if (!n) return false;
    for (int i = 0; i < lvl; ++i) {
        n->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = n;
    }
    sl->size++;
    return true;
}

bool skiplist_removeElement(SkipList *sl, int value) {
    if (!sl || !sl->header) return false;
    SLNode* update[SL_MAX_LEVEL] = {0};
    SLNode* x = sl->header;
    for (int i = sl->level - 1; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->value < value)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[0];
    if (!x || x->value != value) return false;
    for (int i = 0; i < sl->level; ++i) {
        if (update[i]->forward[i] != x) break;
        update[i]->forward[i] = x->forward[i];
    }
    free(x->forward);
    free(x);
    while (sl->level > 1 && sl->header->forward[sl->level - 1] == NULL)
        sl->level--;
    sl->size--;
    return true;
}

size_t skiplist_findAllElements(const SkipList *sl, int value, int *out_buf, size_t out_cap) {
    if (!sl || !sl->header) return 0;
    const SLNode* x = sl->header;
    for (int i = sl->level - 1; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->value < value)
            x = x->forward[i];
    }
    x = x->forward[0];
    size_t count = 0;
    while (x && x->value == value) {
        if (out_buf && count < out_cap) out_buf[count] = x->value;
        count++;
        x = x->forward[0];
    }
    return count;
}

size_t skiplist_removeAllElements(SkipList *sl, int value) {
    if (!sl || !sl->header) return 0;
    size_t removed = 0;
    while (skiplist_removeElement(sl, value)) {
        removed++;
    }
    return removed;
}
