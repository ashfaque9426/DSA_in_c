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

void lh_destroy(LHash *ht) {
    free(ht->table);
    free(ht);
}

void lh_print(LHash *ht) {
    printf("Linear Hash m=%zu, n=%zu\n", ht->m, ht->n);
    
    for (size_t i = 0; i < ht->m; ++i) {
        if (ht->table[i].state = EMPTY) printf("Empty\n");
        else if (ht->table[i].state = DELETED) printf("Deleted\n");
        else printf("%d\n", ht->table[i].key);
    }
}

int main(void) {
    
    return 0;
}