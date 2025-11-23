void add_edge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = create_node(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
