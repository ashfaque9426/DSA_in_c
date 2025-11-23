#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void print_tree(char tree[], int size) {
    printf("Index\tNode\tLeft\tRight\n");
    for(int i = 0; i < size; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        printf("%d\t%c\t", i, tree[i]);

        if(left < size)
            printf("%c\t", tree[left]);
        else
            printf("-\t");

        if(right < size)
            printf("%c\n", tree[right]);
        else
            printf("-\n");
    }
}

int main(void) {
    char bi_tree_arr[MAX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
    int size = 7;

    print_tree(bi_tree_arr, size);

    return 0;
}