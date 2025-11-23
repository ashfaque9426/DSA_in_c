#include <stdio.h>

void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void heapify(int arr[], int start_index, int heap_size) {
    int i = start_index, j = 2 * i + 1, k = 2 * i + 2;

    if (j >= heap_size) return;

    int largest = i;

    if (j < heap_size && arr[j] > arr[largest]) {
        largest = j;
    }
        
    if (k < heap_size && arr[k] > arr[largest]) {
        largest = k;
    }

    if (largest != i) {
        swap(arr, i, largest);
        heapify(arr, largest, heap_size);
    }   
}

void heap_sort(int arr[], int size) {
    for (int i = size/2 - 1; i >= 0; i--) {
        heapify(arr, i, size);
    }

    for (int i = size - 1; i > 0; i--) {
        swap(arr, 0, i);
        heapify(arr, 0, i);
    }
}

void display_arr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int array[] = { 5, 2, 3, 4, 1, 7, 9 };
    int size = sizeof(array) / sizeof(array[0]);

    printf("Beore heap sort: \n");
    display_arr(array, size);

    heap_sort(array, size);

    printf("After heap sort: \n");
    display_arr(array, size);

    return 0;
}