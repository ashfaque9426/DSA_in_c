#include <stdio.h>

void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i = i + 1;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, high);
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}

void print_arr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[7] = { 10, 80, 30, 90, 40, 50, 70 };
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Printing array before quick sort: \n");
    print_arr(arr, size);

    quick_sort(arr, 0, 6);

    printf("Printing array after quick sort: \n");
    print_arr(arr, size);

    return 0;
}