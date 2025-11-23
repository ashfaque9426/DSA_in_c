#include <stdio.h>

int main() {
    // Declare and initialize the array, variables for search item, index, and flag
    int num_arr[] = { 1, 2, 3, 4, 5 }, item, j = 0, position_found = 0;
    // Calculate the length of the array
    int arr_len = sizeof(num_arr) / sizeof(int);

    // Prompt the user to enter the number to search for
    printf("Please enter a number to check if it is stored within the array: \n");
    // Read the search item from user input
    scanf("%d", &item);

    // Loop through the array to search for the item
    while (j < arr_len) {
        // Check if the current element matches the search item
        if (num_arr[j] == item) {
            // Set flag if item is found
            position_found = 1;
            // Exit the loop since item is found
            break;
        }
        // Move to the next element
        j++;
    }

    // Print the result based on whether the item was found
    if (position_found) printf("Your given item %d is found at the position %d. \n", item, j + 1);
    else printf("Your given item %d is not found. \n", item);

    // End of program
    return 0;
}