#include <stdio.h>      // For input and output functions
#include <ctype.h>      // For character type checking functions

char stack[20];         // Array to use as stack for operators
int top = -1;           // Stack pointer, -1 means stack is empty

// Function to push an element onto the stack
void push(char x) {
    stack[++top] = x;   // Increment top and add x to stack
}

// Function to pop an element from the stack
int pop() {
    if (top == -1)      // If stack is empty
        return -1;      // Return -1 to indicate empty

    return stack[top--]; // Return top element and decrement top
}

// Function to get priority of operators
int priority(char x) {
    if (x == '(') 
        return 0;       // Lowest priority for '('
    if (x == '+' || x == '-')
        return 1;       // '+' and '-' have priority 1
    if (x == '*' || x == '/')
        return 2;       // '*' and '/' have priority 2
    return -1;          // For other characters, return -1
}

int main(void) {
    char exp[20];       // Array to store input expression
    char *e, x;         // Pointer for traversing expression, variable for popped value

    printf("Enter the expression :: "); // Ask user for input
    scanf("%s", exp);   // Read the expression as a string
    e = exp;            // Set pointer to start of expression

    // Loop through each character in the expression
    while (*e != '\0') {
        if (isalnum(*e))            // If character is a number or letter
            printf("%c", *e);       // Print it directly (operand)
        else if (*e == '(')         // If character is '('
            push(*e);               // Push '(' onto stack
        else if (*e == ')') {       // If character is ')'
            while ((x = pop()) != '(') // Pop and print until '(' is found
                printf("%c", x);
        }
        else {                      // If character is an operator
            while (priority(stack[top]) >= priority(*e)) // While stack top has higher or equal priority
                printf("%c", pop()); // Pop and print operators from stack
            push(*e);               // Push current operator onto stack
        }
        e++;                        // Move to next character
    }

    // Pop and print any remaining operators in the stack
    while (top != -1)
        printf("%c", pop());

    return 0;                       // End program
}