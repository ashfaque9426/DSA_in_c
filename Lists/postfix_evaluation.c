#include <stdio.h>      // Include standard input/output functions for printing and reading
#include <ctype.h>      // Include functions to check character types (like isdigit)

// Declare a character array to act as a stack for operands and results
char stack[20];
// Declare an integer to keep track of the top of the stack, -1 means stack is empty
int top = -1;

// Function to push a value onto the stack
void push(char x) {
    stack[++top] = x;   // Increase top by 1 and put x at that position in stack
}

// Function to pop a value from the stack
int pop() {
    return stack[top--]; // Return the top element and decrease top by 1
}

int main(void) {
    char exp[20], *e;   // Array to store the input expression, pointer to traverse it
    int n1, n2, n3, num; // Variables for operands and result

    printf("Enter the expression :: \n"); // Ask user to enter a postfix expression
    scanf("%s", exp);   // Read the expression from user

    e = exp;            // Set pointer to start of the expression

    // Loop through each character in the expression
    while (*e != '\0') {
        if (isdigit(*e)) {         // If character is a digit (operand)
            num = *e - 48;         // Convert character to integer (ASCII to number)
            push(num);             // Push the number onto the stack
        }
        else {                     // If character is an operator (+, -, *, /)
            n1 = pop();            // Pop the top value (second operand)
            n2 = pop();            // Pop the next value (first operand)

            switch(*e) {           // Check which operator it is
                case '+':
                {
                    n3 = n1 + n2; // Add the two operands
                    break;
                }    
                case '-':
                {
                    n3 = n1 - n2; // Subtract second from first
                    break;
                }
                case '*':
                {
                    n3 = n1 * n2; // Multiply the operands
                    break;
                }
                case '/':
                {
                    n3 = n1 / n2; // Divide first by second
                    break;
                }
            }

            push(n3);              // Push the result back onto the stack
        }

        e++;                       // Move to next character in expression
    }

    // Print the final result (last value on stack)
    printf("The result of expression %s = %d\n\n", exp, pop());
    return 0;                      // End the program
}