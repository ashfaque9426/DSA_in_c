#include <stdio.h>

int bi_search(int arr[], int target, int n) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }

    return -1;
}

int main(void) {
    int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int size = sizeof(arr) / sizeof(int);

    int idx = bi_search(arr, 50, size);

    if (idx == -1) {
        printf("Item not found. \n");
    } else {
        printf("Item is found at index: %d\n", idx);
    }

    return 0;
}