#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const unsigned Knuth_C = 2654435761u;

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **buckets;
    size_t m;
    size_t n;
    double max_load;
} HashTable;

static size_t hash_init(int key, size_t m) {
    unsigned int k = (unsigned int)key;
    k *= Knuth_C;

    return (k >> (32 - (int)(32 - __builtin_clz(m - 1)))) % m;
    // simpler:
    // return (k * Knuth_C) % m;
}

static Node *node_create(int key) {
    Node *p = malloc(sizeof *p);
    if (!p) {
        perror("malloc");
        exit(1);
    }

    p->key = key;
    p->next = NULL;
    return p;
}

static HashTable *ht_create(size_t m, double max_load) {
    HashTable *ht = malloc(sizeof *ht);
    if (!ht) {
        perror("malloc");
        exit(1);
    }

    ht->buckets = calloc(m, sizeof *ht->buckets);
    if (!ht->buckets) {
        perror("calloc");
        exit(1);
    }

    ht->m = m;
    ht->n = 0;
    ht->max_load = max_load;
    return ht;
}

void free_list(Node *head) {
    while (head) {
        Node *t_Node = head;
        head = head->next;
        free(t_Node);
    }
}

void destroy_ht(HashTable *ht) {
    for (int i = 0; i < ht->m; ++i) {
        free_list(ht->buckets[i]);
    }

    free(ht->buckets);
    free(ht);
}

void ht_insert_nodeup(HashTable *ht, int key);

void ht_rehash(HashTable *ht, size_t new_m) {
    Node **old = ht->buckets;
    size_t old_buck_size = ht->m;

    Node **new_bucket = calloc(new_m, sizeof(Node*));
    if (!new_bucket) { 
        perror("calloc");
        exit(1);
    }

    ht->buckets = new_bucket;
    ht->m = new_m;
    ht->n = 0;

    for (size_t i = 0; i < old_buck_size; ++i) {
        Node *curr = old[i];
        
        while (curr) {
            ht_insert_nodeup(ht, curr->key);
            curr = curr->next;
        }
        free(old[i]);
    }
    free(old);
}

void ht_insert_nodeup(HashTable *ht, int key) {
    double load = (double)(ht->n + 1) / (double)ht->m;
    if (load > ht->max_load) {
        size_t new_buck_size = ht->m * 2 + 1;
        ht_rehash(ht, new_buck_size);
    }

    size_t idx = hash_init(key, ht->m);
    Node *node = node_create(key);
    node->next = ht->buckets[idx];
    ht->buckets[idx] = node;
    ht->n++;
}

int ht_search(HashTable *ht, int key) {
    size_t idx = hash_init(key, ht->m);

    Node *curr = ht->buckets[idx];

    while (curr) {
        if (curr->key == key) {
            return 1;
        }
        curr = curr->next;
    }

    return 0;
}

int ht_delete(HashTable *ht, int key) {
    size_t idx = hash_init(key, ht->m);
    Node *curr = ht->buckets[idx], *prev = NULL;

    while (curr) {
        if (curr->key == key) {
            if (prev) {
                prev->next = curr->next;
            } else {
                ht->buckets[idx] = curr->next;
            }
        
            free(curr);
            ht->n--;
            return 1;
        }

        prev = curr;
        curr = curr->next;
    }

    return 0;
}

void ht_print(HashTable *ht) {
    printf("HashTable m=%zu n=%zu\n", ht->m, ht->n);
    for (size_t i = 0; i < ht->m; ++i) {
        printf("[%2zu]:", i);
        Node *cur = ht->buckets[i];
        while (cur) {
            printf(" %d ->", cur->key);
            cur = cur->next;
        }
        printf(" NULL\n");
    }
}

int main(void) {
    HashTable *ht = ht_create(7, 0.75);
    int a[] = {10, 20, 17, 37, 27, 47, 5, 15, 25};

    for (int i = 0; i < (int)(sizeof a / sizeof a[0]); ++i) {
        ht_insert_nodeup(ht, a[i]);
    }

    ht_print(ht);

    printf("search 27: %d\n", ht_search(ht, 27));

    ht_delete(ht, 27);

    printf("after delete 27:\n");
    ht_print(ht);

    destroy_ht(ht);
    
    return 0;
}