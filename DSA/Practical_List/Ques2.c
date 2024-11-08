// 2. Conversion of Infix expression to prefix expression using stack.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure and functions
char stack[MAX];
int top = -1;

// Function to check if stack is empty
int isEmpty() {
    return top == -1;
}

// Function to push an element onto the stack
void push(char item) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = item;
}

// Function to pop an element from the stack
char pop() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

// Function to get the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to check if an operator is right-associative
int isRightAssociative(char op) {
    return op == '^';  // Only the power operator is right-associative
}

// Function to reverse a string
void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    char ch;

    while ((ch = infix[i++]) != '\0') {
        if (isalnum(ch)) {  // Operand
            postfix[j++] = ch;
        }
        else if (ch == ')') {  // right parenthesis
            push(ch);
        }
        else if (ch == '(') {  // left parenthesis
            while (!isEmpty() && stack[top] != ')') {
                postfix[j++] = pop();
            }
            pop();  // Pop the ')'
        }
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

    while (!isEmpty()) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';  // Null-terminate the postfix expression
}

// Function to convert infix to prefix expression
void infixToPrefix(char* infix, char* prefix) {
    // Step 1: Reverse the infix expression
    reverseString(infix);

    // Step 3: Get postfix expression of modified infix
    char postfix[MAX];
    infixToPostfix(infix, postfix);

    // Step 4: Reverse postfix to get prefix
    reverseString(postfix);

    // Copy postfix to prefix
    strcpy(prefix, postfix);
}

// Main function
int main() {
    char infix[MAX], prefix[MAX];

    printf("Enter the infix expression: ");
    fgets(infix, MAX, stdin);

    // Remove newline character from the input if exists
    infix[strcspn(infix, "\n")] = '\0';

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}
