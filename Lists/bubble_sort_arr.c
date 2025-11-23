#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int list[], int indx_1, int indx_2) {
    if (list[indx_1] > list[indx_2]) {
        int temp = list[indx_1];
        list[indx_1] = list[indx_2];
        list[indx_2] = temp;
    }
}

int* sorted_arr(int list[], int size) {
    int* sorted_arr = malloc(size * sizeof(int));
    if (!sorted_arr) {
        perror("Memory allocation failed");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        sorted_arr[i] = list[i];
    }

    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (sorted_arr[j] > sorted_arr[j + 1]) {
                swap(sorted_arr, j, j+1);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    return sorted_arr;
}

int main(void) {
    int list[5] = { 14, 35, 27, 33, 10 };

    printf("Initial List: \n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", list[i]);
    }

    printf("\n\n");

    int* sortedArray = sorted_arr(list, 5);

    printf("Sorted List: \n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", sortedArray[i]);
    }

    return 0;
}