#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10

struct Node {
    int v;
    struct Node* next;
};

struct Graph {
    int numVertices;
    int visited[MAX_N];
    char labels[MAX_N];
    struct Node* adjLists[MAX_N];
};

struct Q {
    int items[MAX_N];
    int front, rear;
};

struct Node* create_node(int vertex) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->v = vertex;
    node->next = NULL;

    return node;
}

struct Graph* create_graph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    graph->numVertices = vertices;

    for(int i = 0; i < vertices; i++) {
        graph->labels[i] = 'A' + i;
        graph->visited[i] = 0;
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void init_q(struct Q* q) {
    q->rear = -1;
    q->front = 0;
}

int is_empty_q(struct Q* q) {
    return q->rear < q->front;
}

int full_q(struct Q* q) { 
    return q->rear - q->front + 1 >= MAX_N; 
}

int enqueue(struct Q* q, int v) {
    if (full_q(q)) return 0;
    q->items[++q->rear] = v;
    return 1;
}

int dequeue(struct Q* q) {
    if (is_empty_q(q)) return -1;
    return q->items[q->front++];
}

void add_edge(struct Graph* graph, int src, int dest) {
    struct Node* node = create_node(dest);
    if (graph->adjLists[src] == NULL) {
        graph->adjLists[src] = node;
    } else {
        struct Node* tempNode = graph->adjLists[src];
        while (tempNode->next != NULL) tempNode = tempNode->next;
        tempNode->next = node;
    }

    node = create_node(src);
    if (graph->adjLists[dest] == NULL) {
        graph->adjLists[dest] = node;
    } else {
        struct Node* tempNode = graph->adjLists[dest];
        while (tempNode->next != NULL) tempNode = tempNode->next;
        tempNode->next = node;
    }
}

void BFS(struct Graph* g, int v) {
    struct Q q;
    init_q(&q);
    for (int i = 0; i < g->numVertices; i++) g->visited[i] = 0;

    g->visited[v] = 1;
    int success = enqueue(&q, v);

    if (!success) {
        printf("Unable to enqueue vertex to the queue. Queue is full.\n");
        return;
    }

    while (!is_empty_q(&q)) {
        int u = dequeue(&q);
        if (u == -1) {
            printf("Unable to dequeue the front element from the queue. Queue is empty.\n");
            break;
        }

        printf("%c ", g->labels[u]);

        struct Node* tempNode = g->adjLists[u];
        while (tempNode != NULL) {
            int v = tempNode->v;
            if (g->visited[v] == 0) {
                g->visited[v] = 1;
                enqueue(&q, v);
            }
            tempNode = tempNode->next;
        }
    }
}

int main(void) {
    struct Graph* g = create_graph(5);

    add_edge(g, 0, 1); // A-B
    add_edge(g, 0, 2); // A-C
    add_edge(g, 1, 3); // B-D
    add_edge(g, 2, 4); // c-E

    printf("Printing labels from starting node A:\n");
    BFS(g, 0);
    printf("\n");
    
    return 0;
}