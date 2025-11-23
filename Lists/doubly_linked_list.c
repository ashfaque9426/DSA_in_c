// Include standard input/output library for printing and scanning
#include <stdio.h>
// Include standard library for memory allocation functions like malloc
#include <stdlib.h>
// Include boolean type support (true/false)
#include <stdbool.h>

// Define a structure for a node in the doubly linked list
typedef struct LIST {
    int data;              // The value stored in the node
    int key;               // A unique identifier for the node
    struct LIST *Next;     // Pointer to the next node in the list
    struct LIST *Prev;     // Pointer to the previous node in the list
} DLL;

// Declare a pointer to the head (first node) of the list, initially empty
DLL *head = NULL;
// Declare a pointer for current node (not used in this code)
DLL *current = NULL;

// Function to check if the list is empty
bool is_empty() {
    return head == NULL;   // Returns true if head is NULL (list is empty)
}

// Function to insert a new node at the beginning of the list
int insert_first(int dataElem, int dataKey) {
    // Allocate memory for the new node
    DLL *link = (DLL*) malloc(sizeof(DLL));
    link->data = dataElem; // Set the data value
    link->key = dataKey;   // Set the key value
    link->Prev = NULL;     // New node will be the first, so no previous node

    if (is_empty()) {
        // If the list is empty, set both Next and Prev to NULL
        link->Prev = NULL;
        link->Next = NULL;
    } else {
        // If list is not empty, link new node before current head
        link->Next = head;
        head->Prev = link;
    }

    // Update head to point to the new node
    head = link;
    return 0; // Return 0 to indicate success
}

// Function to find a node by its key value
DLL* find_node(int key) {
    if (is_empty()) return NULL; // If list is empty, return NULL
    DLL* curr = head;            // Start from the head

    // Traverse the list until the key is found or end is reached
    while (curr != NULL && curr->key != key) {
        curr = curr->Next;
    }

    if (curr == NULL) {
        // If node not found, print error and return NULL
        printf("Error: Node not found. Invalid node key.\n");
        return NULL;
    }

    return curr; // Return pointer to found node
}

// Function to delete a node by its key value
DLL* delete_node(int key) {
    if (is_empty()) {
        // If list is empty, print error and return NULL
        printf("You can't delete anything from an empty linked list.\n");
        return NULL;
    }

    DLL *curr = head; // Start from the head
    DLL *prev = NULL; // To store previous node
    DLL *next = NULL; // To store next node

    // Traverse the list to find the node with the given key
    while (curr->key != key) {
        curr = curr->Next;
    }

    if (curr == NULL) {
        // If node not found, print error and return NULL
        printf("Error: No node element found matching the given key.Invalid Key.\n");
        return NULL;
    }

    // If node to delete is the head and there are more nodes
    if (curr == head && curr->Next != NULL) {
        curr->Next->Prev = NULL; // Remove link to current node
        head = curr->Next;       // Update head to next node
        return curr;             // Return deleted node
    } else if (curr == head && curr->Next == NULL) {
        // If node to delete is the only node
        head = NULL;             // List becomes empty
        return curr;             // Return deleted node
    }

    // For nodes in the middle or end
    prev = curr->Prev;
    next = curr->Next;

    if (next != NULL) {
        next->Prev = prev;       // Link next node to previous node
    }

    prev->Next = next;           // Link previous node to next node

    return curr;                 // Return deleted node
}

// Function to insert a node before a node with a given key
void insert_prev(DLL *node, int key) {
    if (is_empty()) {
        // Can't insert before if list is empty
        printf("Error: Can't insert any node element prior to an element of an empty list.\n");
        return;
    }

    DLL *curr = head;        // Start from head
    DLL *prev_to_curr = NULL;// To store previous node

    // Traverse to find the node with the given key
    while (curr->key != key) {
        curr = curr->Next;
    }

    if (curr == head) {
        // Can't insert before the head node
        printf("Error: An node element can't be inserted as the previous element of the head element in linked list.\n");
        return;
    }

    prev_to_curr = curr->Prev; // Get previous node
    prev_to_curr->Next = node; // Link previous node to new node
    curr->Prev = node;         // Link current node to new node
    node->Prev = prev_to_curr; // Set new node's previous pointer
    node->Next = curr;         // Set new node's next pointer
}

// Function to insert a node after a node with a given key
void insert_next(DLL *node, int key) {
    if (is_empty()) {
        // Can't insert after if list is empty
        printf("Error: Can't insert any node element prior to an element of an empty list.\n");
        return;
    }

    DLL *curr = head;        // Start from head
    DLL *next_to_curr = NULL;// To store next node

    // Traverse to find the node with the given key
    while (curr->key != key) {
        curr = curr->Next;
    }

    if (curr == NULL) {
        // If node not found, print error
        printf("Error: No node element found matching the given key.Invalid Key.\n");
        return;
    }

    next_to_curr = curr->Next; // Get next node
    curr->Next = node;         // Link current node to new node
    node->Prev = curr;         // Set new node's previous pointer
    node->Next = next_to_curr; // Set new node's next pointer
}

// Function to display the previous node of a node with a given key
void display_prev(int key) {
    if (is_empty()) {
        // If list is empty, print error
        printf("Error: Previous node element not found. List is empty.\n");
        return;
    }

    DLL* prev = NULL; // To store previous node
    DLL* curr = head; // Start from head

    // Traverse to find the node with the given key
    while (curr->key != key) {
        curr = curr->Next;
    }

    if (curr == head) {
        // Head node has no previous node
        printf("Error: There is no previous element for the head element in linked list.\n");
        return;
    }

    if (curr == NULL) {
        // If node not found, print error
        printf("Error: No node element found matching the given key.Invalid Key.\n");
        return;
    }

    prev = curr->Prev; // Get previous node
    printf("The previous node elements of the given node key %d is: (Key: %d, Data: %d)\n", curr->key, prev->key, prev->data);
}

// Function to display the next node of a node with a given key
void display_next(int key) {
    if (is_empty()) {
        // If list is empty, print error
        printf("Error: Previous node element not found. List is empty.\n");
        return;
    }

    DLL* next = NULL; // To store next node
    DLL* curr = head; // Start from head

    // Traverse to find the node with the given key
    while (curr->key != key) {
        curr = curr->Next;
    }

    if (curr == NULL) {
        // If node not found, print error
        printf("Error: No node element found matching the given key.Invalid Key.\n");
        return;
    }

    if (curr->Next == NULL) {
        // Last node has no next node
        printf("Error: There is no next node element for the last element in linked list.\n");
        return;
    }

    next = curr->Next; // Get next node
    printf("The next node elements of the given node key %d is: (Key: %d, Data: %d)\n", curr->key, next->key, next->data);
}

// Function to display all nodes in the list
void display_list() {
    if (is_empty()) {
        // If list is empty, print message
        printf("The list is empty.\n");
        return;
    }

    DLL *ptr = head; // Start from head
    
    printf("\n[ ");

    // Traverse and print each node's key and data
    while (ptr != NULL) {
        printf("(Key: %d, Data: %d)", ptr->key, ptr->data);
        if (ptr->Next != NULL) printf(", ");
        ptr = ptr->Next;
    }

    printf(" ]\n");
}

// Function to reverse the order of nodes in the list
void reverse_list(DLL **head_ref) {
    DLL *curr = *head_ref; // Start from head
    DLL *temp = NULL;      // Temporary pointer

    // Traverse the list and swap Next and Prev for each node
    while (curr != NULL) {
        temp = curr->Prev;
        curr->Prev = curr->Next;
        curr->Next = temp;
        curr = curr->Prev;
    }

    // After reversal, update head to the new first node
    if (temp != NULL) {
        *head_ref = temp->Prev;
    }
}

// Main function to demonstrate the list operations
int main(void) {
    // Insert nodes at the beginning of the list
    insert_first(7, 70);
    insert_first(6, 60);
    insert_first(5, 50);
    insert_first(4, 40);
    insert_first(3, 30);
    insert_first(2, 20);
    insert_first(1, 10);

    // Create new nodes to insert before and after specific nodes
    DLL new_prev_node = {9, 65, NULL, NULL};
    DLL new_next_node = {11, 55, NULL, NULL};

    // Insert new_prev_node before node with key 70
    insert_prev(&new_prev_node, 70);
    // Insert new_next_node after node with key 50
    insert_next(&new_next_node, 50);

    // Delete node with key 20 and store pointer to deleted node
    DLL *deleted_node = delete_node(20);

    // If a node was deleted, print its details
    if (deleted_node) printf("The Deleted node elements by the key %d are: (key: %d, data: %d)\n", deleted_node->key, deleted_node->key, deleted_node->data);

    // Reverse the list
    reverse_list(&head);

    // Display the entire list
    display_list();
    // Display the previous node of node with key 30
    display_prev(30);
    // Display the next node of node with key 10
    display_next(10);

    // Find node with key 70 and print its details if found
    DLL *node = find_node(70);
    if (node) printf("The node is found by the key %d, the elements are: (Key: %d, Data: %d)\n", node->key, node->key, node->data);

    return 0; // End of program
}