#include <stdio.h>

int main() {
    // Declare and initialize the array, set initial length
    int num_arr[] = { 1, 2, 3, 4, 5 }, given_index, arr_len = 5;

    // Prompt the user to enter the index to delete
    printf("Please give an array index to delete the array element between 0-4:\n");
    // Read the index from user input
    scanf("%d", &given_index);

    // Check if the given index is within the valid range
    if (given_index > 4) {
        // Print error message if index is out of bounds
        printf("Your given index is exceeding our array boundary.\n");
        return 1;
    }

    // Shift elements left to overwrite the element at the given index
    for(int i = given_index; i < arr_len - 1; i++) {
        num_arr[i] = num_arr[i + 1];
    }

    // Decrease the array length after deletion
    arr_len--;

    // Print the array after deletion
    printf("Array elements after deletion operation: \n");

    // Loop through the array and print each element
    for (int i = 0; i < arr_len; i++) {
        printf("Index: [%d], Item: %d \n", i, num_arr[i]);
    }

    // End of program
    return 0;
}