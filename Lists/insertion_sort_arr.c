#include <stdio.h>

void insertion_sort(int list[], int size){
    for (int i = 1; i < size; i++) {
        int key = list[i];
        int j = i - 1;

        while (j >= 0 && list[j] > key) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}

void print_int_arr(int list[], int size) {
    printf("Printing the given integer list:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[8] = { 14, 33, 27, 10, 35, 19, 42, 44 };

    insertion_sort(arr, 8);

    print_int_arr(arr, 8);

    return 0;
}