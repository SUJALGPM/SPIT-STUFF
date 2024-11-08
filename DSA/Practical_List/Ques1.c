// 1. Conversion of Infix expression to postfix expression using stack.

#include <stdio.h>
#include <ctype.h>  // for isalnum function
#include <stdlib.h> // for standard library functions

#define MAX 100 // Maximum size of stack

// Stack structure and functions
char stack[MAX];
int top = -1;

// Function to check if stack is empty
int isEmpty()
{
    return top == -1;
}

// Function to push an element onto the stack
void push(char item)
{
    if (top >= MAX - 1)
    {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = item;
}

// Function to pop an element from the stack
char pop()
{
    if (isEmpty())
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

// Function to get the precedence of operators
int precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '^')
    {
        return 3;
    }
    return 0;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char *infix, char *postfix)
{
    int i = 0, j = 0;
    char ch;

    while ((ch = infix[i++]) != '\0')
    {
        // If character is an operand, add it to postfix expression
        if (isalnum(ch))
        {
            postfix[j++] = ch;
        }
        // If character is '(', push it onto stack
        else if (ch == '(')
        {
            push(ch);
        }
        // If character is ')', pop until '(' is found
        else if (ch == ')')
        {
            while (!isEmpty() && stack[top] != '(')
            {
                postfix[j++] = pop();
            }
            pop(); // Pop the '('
        }
        // If character is an operator
        else
        {
            while (!isEmpty() &&
                   ((ch == '^' && precedence(stack[top]) > precedence(ch)) ||
                    (ch != '^' && precedence(stack[top]) >= precedence(ch))))
            {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }

    // Pop all the remaining operators from the stack
    while (!isEmpty())
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0'; // Null-terminate the postfix expression
}

// Main function...
int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter the infix expression: ");
    fgets(infix, MAX, stdin); // Read input from user

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
