#include <stdio.h>

int main(void) {
    int list[7] = {44, 43, 20, 10, 55, 15, 25};
    int size = sizeof(list) / sizeof(int);

    for (int i = 0; i < size - 1; i++) {
        int pos_min = i;

        for (int j = i + 1; j < size; j++) {
            if (list[j] < list[pos_min]) {
                pos_min = j;
            }
        }

        if (pos_min != i) {
            int temp = list[i];
            list[i] = list[pos_min];
            list[pos_min] = temp;
        }
    }

    printf("Sorted elements of list are printed: \n");
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }

    return 0;
}