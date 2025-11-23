// Include standard input/output functions
#include <stdio.h>
// Include functions for memory allocation
#include <stdlib.h>
// Include string handling functions
#include <string.h>
// Include boolean type support
#include <stdbool.h>

// Define the structure for a node in the linked list
struct node {
    int data;                // Store the data value
    int key;                 // Store the key value
    struct node *Next;       // Pointer to the next node
};

// Declare a global pointer to the head of the list
struct node *head = NULL;
// Declare a global pointer for current node (not used everywhere)
struct node *current = NULL;

// Function to insert a new node at the beginning of the list
void insertFirst(int key, int data) {
    struct node *link = (struct node*) malloc(sizeof(struct node)); // Allocate memory for new node

    link->data = data;       // Set the data for the new node
    link->key = key;         // Set the key for the new node

    link->Next = head;       // Point new node to current head
    head = link;             // Update head to new node
}

// Function to print all nodes in the linked list
void printList() {
    struct node *ptr = head; // Start from the head node
    
    printf("\n[ ");          // Print opening bracket

    while (ptr != NULL) {    // Loop through all nodes
        printf("(Key: %d, Data: %d)", ptr->key, ptr->data); // Print key and data
        if (ptr->Next != NULL) printf(", "); // Print comma if not last node
        ptr = ptr->Next;     // Move to next node
    }

    printf(" ]");            // Print closing bracket
}

// Function to check if the list is empty
bool isEmpty() {
    return head == NULL;     // Return true if head is NULL
}

// Function to delete the first node and return it
struct node* deleteFirst() {
    struct node *tempData = head; // Store the head node

    if(isEmpty()) {          // If list is empty, return NULL
        return NULL;
    }

    head = head->Next;       // Move head to next node
    return tempData;         // Return deleted node
}

// Function to get the length of the linked list
int linkLen() {
    int length = 0;          // Initialize length

    struct node *current;    // Pointer for traversal

    for(current = head; current != NULL; current = current->Next) {
        length++;            // Increment length for each node
    }

    return length;           // Return total length
}

// Function to find a node by key
struct node* find(int key) {
    if (isEmpty()) return NULL; // If list is empty, return NULL

    struct node *current = head; // Start from head

    while (current->key != key) { // Loop until key is found
        if (current->Next == NULL) return NULL; // If end reached, return NULL
        current = current->Next; // Move to next node
    }

    return current;              // Return found node
}

// Function to delete a node by key and return it
struct node* delete(int key) {
    if (isEmpty()) return NULL; // If list is empty, return NULL
    struct node *current = head; // Start from head
    struct node *previous = NULL; // Pointer to previous node

    while (current->key != key) { // Loop until key is found
        if (current->Next == NULL) return NULL; // If end reached, return NULL
        previous = current;       // Move previous to current
        current = current->Next;  // Move current to next node
    }

    if (current == head)          // If node to delete is head
        head = head->Next;        // Move head to next node
    else
        previous->Next = current->Next; // Link previous to next node

    return current;               // Return deleted node
}

// Function to sort the linked list using bubble sort
void bubble_sort() {
    int i, j, tempData, tempKey, size = linkLen(); // Get size of list
    struct node *current;
    struct node *next;

    for (i = 0; i < size - 1; i++) { // Outer loop for passes
        current = head;              // Start from head
        next = current->Next;        // Next node

        for (j = 0; j < size - i - 1; j++) { // Inner loop for comparisons
            if(current->data > next->data) { // If current data is greater
                tempData = current->data;    // Swap data
                current->data = next->data;
                next->data = tempData;

                tempKey = current->key;      // Swap key
                current->key = next->key;
                next->key = tempKey;
            }
            current = current->Next;         // Move to next node
            next = next->Next;               // Move next pointer
        }
    }
}

// Function to reverse the linked list
void reverse(struct node** head_ref) {
    struct node *prev = NULL;        // Previous node pointer
    struct node *curr = *head_ref;   // Current node pointer
    struct node *next;               // Next node pointer

    while (curr != NULL) {           // Loop through all nodes
        next = curr->Next;           // Store next node
        curr->Next = prev;           // Reverse the link
        prev = curr;                 // Move prev to current
        curr = next;                 // Move current to next
    }

    *head_ref = prev;                // Update head to new first node
}

// Main function to test the linked list operations
int main(void) {
    insertFirst(6,60);               // Insert node with key 6 and data 60
    insertFirst(5,50);               // Insert node with key 5 and data 50
    insertFirst(4,40);               // Insert node with key 4 and data 40
    insertFirst(3,300);              // Insert node with key 3 and data 300
    insertFirst(2,20);               // Insert node with key 2 and data 20
    insertFirst(1,10);               // Insert node with key 1 and data 10

    // deleteFirst();                // Uncomment to delete first node
    delete(5);                       // Delete node with key 5

    bubble_sort();                   // Sort the linked list
    reverse(&head);                  // Reverse the linked list

    printf("Printing Linked List: \n"); // Print message
    printList();                     // Print all nodes

    int link_len = linkLen();        // Get length of the list

    printf("\nAnd the legth of the linked list is: %d\n", link_len); // Print length

    struct node *found_Link = find(3); // Find node with key 3

    if(found_Link != NULL)             // If node found
        printf("The data found by the key 3 is: %d", found_Link->data); // Print its data

    return 0;                          // End program
}