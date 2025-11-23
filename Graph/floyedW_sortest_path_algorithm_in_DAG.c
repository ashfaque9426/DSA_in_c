#include <stdio.h>
#include <stdlib.h>
#define INF 99999
#define V 6

void init_Dist_Next_Matrix(int dist[V][V], int next[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
            next[i][j] = -1;
        }
    }

    dist[5][0] = 10; next[5][0] = 0;
    dist[5][2] = 5;  next[5][2] = 2;
    dist[2][3] = 3;  next[2][3] = 3;
    dist[3][1] = 4;  next[3][1] = 1;
    dist[4][0] = 7;  next[4][0] = 0;
    dist[4][1] = 2;  next[4][1] = 1;
}

void floyd_warshall_algorithm_sortest_path(int dist[V][V], int next[V][V]) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void print_dist_matrix(int dist[V][V]) {
    printf("\nPrinting Shortest Distance Matrix(dist): \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                printf("%4s ", "INF");
            } else {
                printf("%4d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

void print_path(int next[V][V], int u, int v) {
    if (next[u][v] == -1) {
        printf("There is no direct path from %d, %d.\n", u, v);
        return;
    }

    printf("Printing the path from %d to %d: %d", u, v, u);

    while (u != v) {
        u = next[u][v];
        printf(" -> %d", u);
    }

    printf("\n");
}

int main(void) {
    int dist[V][V], next[V][V];

    init_Dist_Next_Matrix(dist, next);
    floyd_warshall_algorithm_sortest_path(dist, next);
    print_dist_matrix(dist);

    printf("\n--- Reconstructed Paths ---\n");
    print_path(next, 5, 1); // 5 → 1
    print_path(next, 5, 3); // 5 → 3
    print_path(next, 4, 0); // 4 → 0
    print_path(next, 4, 1); // 4 → 1
    printf("\n");
    
    return 0;
}