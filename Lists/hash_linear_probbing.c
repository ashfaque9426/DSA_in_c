#include <stdio.h>
#include <stdlib.h>
const unsigned Knuth_C = 2654435761u;

typedef enum { EMPTY=0, OCCUPIED=1, DELETED=2 } SlotState;

typedef struct {
    int key;
    SlotState state;
} LSlot;

typedef struct {
    LSlot *table;
    size_t m;
    size_t n;
    double max_load;
} LHash;

static size_t hash_init(int key, size_t m) {
    unsigned int k = (unsigned)key;
    return (k * Knuth_C) % m;
}

void p_err_type(const char *peType) {
    perror(peType);
    exit(1);
}

LHash *lh_create(size_t m, double max_load) {
    LHash *ht = malloc(sizeof *ht);
    if (!ht) {
        p_err_type("malloc");
    }

    ht->table = malloc(sizeof *ht->table * m);
    if (!ht->table) {
        p_err_type("malloc");
    }

    for (size_t i = 0; i < m; ++i) {
        ht->table[i].key = 0;
        ht->table[i].state = EMPTY;
    }

    ht->m = m;
    ht->n = 0;
    ht->max_load = max_load;

    return ht;
}

void lh_rehash(LHash *ht, size_t new_m) {
    LSlot *old_table = ht->table;
    size_t old_size = ht->m;

    ht->table = malloc(sizeof *ht->table * new_m);
    if (!ht->table) {
        p_err_type("malloc");
    }

    for (size_t i = 0; i < new_m; ++i) {
        ht->table[i].key = 0;
        ht->table[i].state = EMPTY;
    }

    ht->m = new_m;
    ht->n = 0;

    for (size_t i = 0; i < old_size; ++i) {
        if (old_table[i].state == OCCUPIED) {
            int key = old_table[i].key;
            int idx = hash_init(key, new_m);
            while (ht->table[idx].state == OCCUPIED) idx = (idx + 1) % ht->m;
            ht->table[idx].key = key;
            ht->table[idx].state = OCCUPIED;
            ht->n++;
        }
    }

    free(old_table);
}

int lh_insert(LHash *ht, int key) {
    double load = (double)(ht->n + 1) / (double)ht->m;
    if (load > ht->max_load) {
        size_t new_size = ht->m * 2 + 1;
        lh_rehash(ht, new_size);
    }

    size_t idx = hash_init(key, ht->m);
    ssize_t first_deleted = -1;

    while (1) {
        if (ht->table[idx].state == EMPTY) {
            size_t dest = (first_deleted != -1) ? (size_t)(first_deleted) : idx;
            ht->table[dest].key = key;
            ht->table[dest].state = OCCUPIED;
            ht->n++;
            return 1;
        }
        else if (ht->table[idx].state == DELETED) {
            if (first_deleted == -1) first_deleted = (ssize_t)idx;
        }
        else if (ht->table[idx].state == OCCUPIED && ht->table[idx].key == key) {
            return 0;
        }
        idx = (idx + 1) % ht->m;
    }
}

int lh_search(LHash *ht, int key) {
    size_t idx = hash_init(key, ht->m);
    size_t start = idx;

    while (1) {
        if (ht->table[idx].state == EMPTY) {
            return -1;
        }
        else if (ht->table[idx].state == OCCUPIED && ht->table[idx].key == key) {
            return (int)idx;
        }

        idx = (idx + 1) % ht->m;
        if (idx == start) return -1;
    }
}

int lh_delete(LHash *ht, int key) {
    size_t idx = hash_init(key, ht->m);
    size_t start = idx;

    while (1) {
        if (ht->table[idx].state == EMPTY) {
            return 0;
        }
        else if (ht->table[idx].state == OCCUPIED && ht->table[idx].key == key) {
            ht->table[idx].key = 0;
            ht->table[idx].state = EMPTY;
            ht->n--;
            return 1;
        }

        idx = (idx + 1) % ht->m;
        if (idx == start) {
            return 0;
        }
    }
}

void lh_destroy(LHash *ht) {
    free(ht->table);
    free(ht);
}

void lh_print(LHash *ht) {
    printf("Linear Hash m=%zu, n=%zu\n", ht->m, ht->n);
    
    for (size_t i = 0; i < ht->m; ++i) {
        if (ht->table[i].state == EMPTY) printf("IDX: %d Status: Empty\n", i);
        else if (ht->table[i].state == DELETED) printf("IDX: %d Status: Deleted\n", i);
        else printf("IDX: %d Key: %d\n", i, ht->table[i].key);
    }
}

int main(void) {
    LHash *ht = lh_create(7, 0.6);
    int a[] = {10, 20, 30, 17, 27, 37, 47};

    for (int i = 0; i < (int)(sizeof a / sizeof a[0]); ++i) {
        lh_insert(ht, a[i]);
    }

    printf("Printing the Linear Hash Table after node insertion: \n");
    lh_print(ht);

    printf("\n");

    int s_result = lh_search(ht, 27);
    if (s_result > 0) printf("Key 27 is found in at index: %d\n", s_result);
    else printf("Key 27 is not present in Linear Hash Table.\n");

    int d_result = lh_delete(ht, 27);
    if (d_result) printf("Key 27 has been deleted from Linear Hash Table.\n");
    else printf("Key 27 is not found in the Linear Hash Table.\n");

    printf("\n");

    printf("Printing the Hash Table after deletion: \n");
    lh_print(ht);

    lh_destroy(ht);
    
    return 0;
}