#include <stdio.h>

int main() {
    // Declare and initialize the array, and variables for index and new element
    int num_arr[] = { 1, 2, 3, 4, 5 }, given_index, given_elem;

    // Prompt the user to enter the index to modify
    printf("Please give an array index to store array element between 0-4:\n");
    // Read the index from user input
    scanf("%d", &given_index);

    // Check if the given index is within the valid range
    if (given_index > 4) {
        // Print error message if index is out of bounds
        printf("Your given index is exceeding our array boundary.\n");
        return 1;
    }

    // Prompt the user to enter the new element to store
    printf("Please give an integer element to store at your given index within the array:\n");
    // Read the new element from user input
    scanf("%d", &given_elem);

    // Store the new element at the specified index
    num_arr[given_index] = given_elem;

    // Print the array after modification
    printf("Array elements after insertion operation: \n");

    // Loop through the array and print each element
    for (int i = 0; i < 5; i++) {
        printf("Index: [%d], Item: %d \n", i, num_arr[i]);
    }
    // End of program
    return 0;
}