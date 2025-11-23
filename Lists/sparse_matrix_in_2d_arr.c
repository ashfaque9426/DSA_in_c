#include <stdio.h>

int main() {
    // Declare and initialize the 4x5 sparse matrix
    int sparseMatrix[4][5] =
    {
        {0 , 0 , 3 , 0 , 4 },
        {0 , 0 , 5 , 7 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 2 , 6 , 0 , 0 }
    };

    // Variable to count the number of non-zero elements
    int size = 0;

    // Loop through the matrix to count non-zero elements
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            // If the element is non-zero, increment the count
            if (sparseMatrix[i][j] != 0) size++;
        }
    }

    // Declare the compact matrix to store row, column, and value of non-zero elements
    int compactMatrix[3][size];

    // Variable to keep track of the position in the compact matrix
    int k = 0;

    // Loop through the sparse matrix to fill the compact matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            // If the element is non-zero, store its row, column, and value
            if (sparseMatrix[i][j] != 0) {
                compactMatrix[0][k] = i;
                compactMatrix[1][k] = j;
                compactMatrix[2][k] = sparseMatrix[i][j];
                k++;
            }
        }
    }

    // Array of strings for labeling the rows of the compact matrix
    char* dimension[3] = {"Rows", "Cols", "Values"};

    // Print the compact matrix with labels
    printf("The compact matrix after storing non zero values and their co-ordinates are: \n");
    for (int i = 0; i < 3; i++) {
        printf("%s: ", dimension[i]);
        for (int j = 0; j < size; j++) {
            printf("%d ", compactMatrix[i][j]);
        }
        printf("\n");
    }

    // End of program
    return 0;
}