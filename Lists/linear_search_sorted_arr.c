#include <stdio.h>

int linear_search(int arr[], int target, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;
    }

    return -1;
}

int main(void) {
    int arr[] = { 100, 200, 300, 400, 500, 600, 700 };
    int size = sizeof(arr) / sizeof(int);

    int idx = linear_search(arr, 300, size);

    if (idx == -1) {
        printf("Item not found.\n");
    } else {
        printf("Item found at index: %d\n", idx);
    }

    return 0;
}