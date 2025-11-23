#include <stdio.h>

int main() {
    // Declare an integer array with space for 7 elements, initialize first 5
    int num_arr[7] = { 1, 2, 3, 4, 5 };
    // Element to insert
    int element = 9, 
        // Index at which to insert the new element
        elem_index = 2, 
        // Current length of the array (number of valid elements)
        arr_len = 5, 
        // Preserve the original array length for shifting
        preserved_arr_len = arr_len;
    // Increase the array length to account for the new element
    arr_len++;

    // Shift elements to the right to make space for the new element
    while (preserved_arr_len >= elem_index) {
        // Move each element one position to the right
        num_arr[preserved_arr_len + 1] = num_arr[preserved_arr_len];
        // Move to the previous element
        preserved_arr_len--;
    }

    // Insert the new element at the specified index
    num_arr[elem_index] = element;

    // Print the array after insertion
    printf("Array elements after insertion operation: \n");

    // Loop through the array and print each element
    for (int i = 0; i < arr_len; i++) {
        printf("Index: [%d], Item: %d \n", i, num_arr[i]);
    }

    // End of program
    return 0;
}