#include <stdio.h>
#define MAX_N 10

char labels[MAX_N];
int visited[MAX_N];
int Adj_M[MAX_N][MAX_N];
int n;

void DFS(int v) {
    visited[v] = 1;
    printf("%c ", labels[v]);

    for (int u = 0; u < n; u++) {
        if (Adj_M[v][u] == 1 && !visited[u]) {
            DFS(u);
        }
    }
}

int main(void) {
    n = 5;

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        labels[i] = 'A' + i;

        for (int j = 0; j < n; j++)
            Adj_M[i][j] = 0;
    }

    Adj_M[0][1] = Adj_M[1][0] = 1;
    Adj_M[0][2] = Adj_M[2][0] = 1;
    Adj_M[1][3] = Adj_M[3][1] = 1;
    Adj_M[2][4] = Adj_M[4][2] = 1;

    printf("Printing Nodes of undirected simple graph by DFS algorithm: \n");
    DFS(0);
    printf("\n");
    
    return 0;
}