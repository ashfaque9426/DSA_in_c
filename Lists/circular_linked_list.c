#include <stdio.h>           // Include standard input/output functions
#include <stdlib.h>          // Include functions for memory allocation

// Define the structure for a node in the circular linked list
struct Node {
    int data;                // Store the data value
    struct Node *Next;       // Pointer to the next node
};

// Declare a global pointer to the last node in the list
struct Node *last = NULL;

// Function to insert the first node into an empty circular linked list
struct Node *insert_to_empty_list(struct Node *last, int data) {
    if (last != NULL) return last;   // If list is not empty, do nothing

    last = (struct Node*) malloc(sizeof(struct Node)); // Allocate memory for new node

    last->data = data;               // Set the data for the new node

    last->Next = last;               // Point next to itself (circular)

    return last;                     // Return the pointer to the last node
}

// Function to add a node at the beginning of the circular linked list
struct Node *add_begin(struct Node *last, int data) {
    if (last == NULL) return insert_to_empty_list(last, data); // If list is empty, insert first node

    struct Node* temp = (struct Node*) malloc(sizeof(struct Node)); // Allocate memory for new node

    temp->data = data;               // Set the data for the new node
    temp->Next = last->Next;         // Point new node to first node
    last->Next = temp;               // Update last node to point to new node

    return last;                     // Return the pointer to the last node
}

// Function to add a node at the end of the circular linked list
struct Node *add_end(struct Node *last, int data) {
    if (last == NULL) return insert_to_empty_list(last, data); // If list is empty, insert first node

    struct Node* temp = (struct Node*) malloc(sizeof(struct Node)); // Allocate memory for new node

    temp->data = data;               // Set the data for the new node
    temp->Next = last->Next;         // Point new node to first node
    last->Next = temp;               // Update last node to point to new node

    last = temp;                     // Update last to new node

    return last;                     // Return the pointer to the last node
}

// Function to add a node after a specific node in the circular linked list
struct Node *add_after(struct Node *last, int data, int item) {
     if (last == NULL) return NULL;  // If list is empty, do nothing

    struct Node *temp, *p;           // Declare pointers for traversal

    p = last->Next;                  // Start from the first node

    do {
        if(p->data == item) {        // If current node matches the item
            temp = (struct Node*) malloc(sizeof(struct Node)); // Allocate memory for new node
            temp->data = data;       // Set the data for the new node
            temp->Next = p->Next;    // Point new node to next node
            p->Next = temp;          // Update current node to point to new node

            if (p == last) last = temp; // If item is last node, update last
            return last;             // Return the pointer to the last node
        }
        p = p->Next;                 // Move to next node
    } while (p != last->Next);       // Continue until back to first node

    printf("Your given item does not match with any item within the list.\n"); // Item not found
    return last;                     // Return the pointer to the last node
}

// Function to print all nodes in the circular linked list
void print_nodes(struct Node *last) {
    struct Node *p;                  // Declare pointer for traversal
    p = last->Next;                  // Start from the first node
    printf("\n[ ");                  // Print opening bracket
    do {
        printf("%d", p->data); // Print data of current node
        if (p != last) printf(", "); // Print comma if not last node
        p = p->Next;                 // Move to next node
    } while (p != last->Next);       // Continue until back to first node

    printf(" ]\n");                  // Print closing bracket
}

// Main function to test the circular linked list operations
int main(void) {
    last = insert_to_empty_list(last, 20); // Insert first node with data 20

    last = add_begin(last, 10);            // Add node with data 10 at beginning
    last = add_after(last, 30, 20);        // Add node with data 30 after node with data 20

    print_nodes(last);                     // Print all nodes in the list

    return 0;                             // End program
}