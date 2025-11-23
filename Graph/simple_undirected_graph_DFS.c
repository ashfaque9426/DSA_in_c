#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    int visited[MAX_N];
    char labels[MAX_N];
    struct Node* adjLists[MAX_N];
};

struct Node* create_node(int v) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node*));

    node->vertex = v;
    node->next = NULL;

    return node;
}

struct Graph* create_graph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->labels[i] = 'A' + i;
        graph->visited[i] = 0;
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// old Add edge A: C->B, B: D->A, C: E->A, D: B->NULL, E: C->NULL
// void add_edge(struct Graph* graph, int src, int dest) {
//     struct Node* new_node = create_node(dest);
//     new_node->next = graph->adjLists[src];
//     graph->adjLists[src] = new_node;

//     new_node = create_node(src);
//     new_node->next = graph->adjLists[dest];
//     graph->adjLists[dest] = new_node;
// }

// new Add edge A: B->C, B: A->D, C: A->E, D: B->NULL, E: C->NULL
void add_edge(struct Graph* graph, int src, int dest) {
    struct Node* new_node = create_node(dest);

    // because it's srouce's node(dest), add new node at the end.
    if (graph->adjLists[src] == NULL) {
        graph->adjLists[src] = new_node;
    } else {
        struct Node* temp = graph->adjLists[src];
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }

    new_node = create_node(src);

    // because it's detination's node(src), add new node at the end.
    if (graph->adjLists[dest] == NULL) {
        graph->adjLists[dest] = new_node;
    } else {
        struct Node* temp = graph->adjLists[dest];
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}


void DFS(struct Graph* graph, int v) {
    struct Node* tempNode = graph->adjLists[v];
    graph->visited[v] = 1;
    printf("%c ", graph->labels[v]);

    while (tempNode != NULL) {
        int connected_vertex = tempNode->vertex;

        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }

        tempNode = tempNode->next;
    }
}

int main(void) {
    struct Graph* graph = create_graph(5);

    add_edge(graph, 0, 1); // A-B
    add_edge(graph, 0, 2); // A-C
    add_edge(graph, 1, 3); // B-D
    add_edge(graph, 2, 4); // C-E

    printf("Printing of DFS search starts from vertex A: \n");
    DFS(graph, 0);
    printf("\n");

    return 0;
}