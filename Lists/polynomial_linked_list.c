#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the polynomial linked list
struct node {
    int coeff;              // Coefficient of the term
    int pow;                // Power of the term
    struct node *Next;      // Pointer to the next node
};

// Function to display the polynomial
void show(struct node *n) {
    // Loop through each node in the linked list
    while (n != NULL) {
        // Print the coefficient and power
        printf("%dx^%d", n->coeff, n->pow);
        // Move to the next node
        n = n->Next;
        // Print '+' if there are more terms
        if (n != NULL) printf(" + ");
    }
}

// Function to create a new node and add it to the end of the list
void create_node(int x, int y, struct node** temp) {
    struct node *r, *z;

    // Start from the head of the list
    z = *temp;

    // If the list is empty, create the first node
    if (z == NULL) {
        r = (struct node*) malloc(sizeof(struct node)); // Allocate memory for new node
        r->coeff = x;                                   // Set coefficient
        r->pow = y;                                     // Set power
        *temp = r;                                      // Update head pointer
        r->Next = NULL;                                 // Set next pointer to NULL
    } else {
        // Traverse to the end of the list
        while (z->Next != NULL) z = z->Next;
        r = (struct node*) malloc(sizeof(struct node)); // Allocate memory for new node
        r->coeff = x;                                   // Set coefficient
        r->pow = y;                                     // Set power
        z->Next = r;                                    // Link new node at the end
        r->Next = NULL;                                 // Set next pointer to NULL
    }
}

// Function to add two polynomials represented as linked lists
void polyadd(struct node *poly1, struct node *poly2, struct node **poly) {
    // Loop while both polynomials have terms
    while (poly1 != NULL && poly2 != NULL) {
        // If power of poly1 term is greater, add it to result
        if (poly1->pow > poly2->pow) {
            create_node(poly1->coeff, poly1->pow, poly);
            poly1 = poly1->Next; // Move to next term in poly1
        }
        // If power of poly2 term is greater, add it to result
        else if (poly1->pow < poly2->pow) {
            create_node(poly2->coeff, poly2->pow, poly);
            poly2 = poly2->Next; // Move to next term in poly2
        }
        // If powers are equal, add coefficients and add to result
        else {
            create_node(poly1->coeff + poly2->coeff, poly1->pow, poly);
            poly1 = poly1->Next; // Move to next term in poly1
            poly2 = poly2->Next; // Move to next term in poly2
        }
    }

    // Add remaining terms from poly1, if any
    while (poly1 != NULL) {
        create_node(poly1->coeff, poly1->pow, poly);
        poly1 = poly1->Next;
    }

    // Add remaining terms from poly2, if any
    while (poly2 != NULL) {
        create_node(poly2->coeff, poly2->pow, poly);
        poly2 = poly2->Next;
    }
}


int main() {
    // Declare pointers for the two input polynomials and the result
    struct node *poly1 = NULL, *poly2 = NULL, *poly = NULL;
    
    // Create first polynomial: 5x^2 + 4x^1 + 2x^0
    create_node(5,2,&poly1);
    create_node(4,1,&poly1);
    create_node(2,0,&poly1);

    // Create second polynomial: 5x^1 + 5x^0
    create_node(5,1,&poly2);
    create_node(5,0,&poly2);

    // Display the first polynomial
    printf("1st Number: ");
    show(poly1);

    // Display the second polynomial
    printf("\n2nd Number: ");
    show(poly2);

    // Add the two polynomials and store the result in 'poly'
    polyadd(poly1, poly2, &poly);
    // Display the result polynomial
    printf("\nAdded polynomial: ");
    show(poly);

    // End of program
    return 0;
}