#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10

struct Node {
    int vertex;
    struct Node* outdegNodeFromSrc;
};

struct Graph {
    int numVertices;
    int visited[MAX_N];
    char labels[MAX_N];
    struct Node* adjLists[MAX_N];
};

struct Stack {
    int items[MAX_N];
    int top;
};

void init_st(struct Stack* s) {
    s->top = -1;
}

int is_empty_st(struct Stack* s) {
    return s->top == -1;
}

int is_full_st(struct Stack* s) {
    return s->top == MAX_N - 1;
}

int pop_st(struct Stack* s) {
    if (is_empty_st(s)) {
        printf("Stack is empty. Nothing to return.\n");
        return -1;
    }

    return s->items[(s->top)--];
}

void push_st(struct Stack* s, int v) {
    if (is_full_st(s)) {
        printf("Stack is already full.\n");
        return;
    }

    s->items[++(s->top)] = v;
}

struct Node* create_node(int v) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->vertex = v;
    node->outdegNodeFromSrc = NULL;

    return node;
}

struct Graph* create_graph(int nv) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    graph->numVertices = nv;

    for (int i = 0; i < nv; i++) {
        graph->visited[i] = 0;
        graph->labels[i] = 'A' + i;
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void add_edge(struct Graph* g, int src, int dest) {
    struct Node* node = create_node(dest);
    node->outdegNodeFromSrc = g->adjLists[src];
    g->adjLists[src] = node;
}

void DFS_stacking_for_topo_sort(struct Graph* g, struct Stack* s, int v) {
    g->visited[v] = 1;

    struct Node* tempNode = g->adjLists[v];

    while (tempNode != NULL) {
        int u = tempNode->vertex;
        if (g->visited[u] == 0) {
            DFS_stacking_for_topo_sort(g, s, u);
        }
        tempNode = tempNode->outdegNodeFromSrc;
    }

    push_st(s, v);
}

void topo_sort_display(struct Graph* g, struct Stack* s) {
    for (int i = 0; i < g->numVertices; i++) {
        if (g->visited[i] == 0) {
            DFS_stacking_for_topo_sort(g, s, i);
        }
    }

    while (!is_empty_st(s)) {
        int v = pop_st(s);
        printf("%c:%d ", g->labels[v], v);
    }

    printf("\n");
}

int main(void) {
    struct Graph* g = create_graph(6);

    add_edge(g, 5, 0); // F (5) → A (0)
    add_edge(g, 5, 2); // F (5) → C (2)
    add_edge(g, 2, 3); // C (2) → D (3)
    add_edge(g, 3, 1); // D (3) → B (1)
    add_edge(g, 4, 0); // E (4) → A (0)
    add_edge(g, 4, 1); // E (4) → B (1)

    struct Stack s;
    init_st(&s);

    topo_sort_display(g, &s);
    
    return 0;
}