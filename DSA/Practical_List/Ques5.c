// 5. Evaluation of Postfix expression using Stack.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Stack {
    int size;
    int top;
    int *arr;
} st;

void init(int size) {
    st.size = size;
    st.top = -1;
    st.arr = (int *)malloc(st.size * sizeof(int));
}

int isEmpty() {
    return st.top == -1;
}

int isFull() {
    return st.top == st.size - 1;
}

void push(int item) {
    if (isFull()) {
        printf("Stack is full.\n");
        return;
    }
    st.arr[++st.top] = item;
}

int pop() {
    if (isEmpty()) {
        printf("Stack is empty, cannot pop.\n");
        return 0; // Could also return an error code
    }
    return st.arr[st.top--];
}

int peak() {
    if (isEmpty()) {
        printf("Stack is empty.\n");
        return 0; // Could also return an error code
    }
    return st.arr[st.top];
}

int evaluate(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        // Check if character is a digit
        if (s[i] >= '0' && s[i] <= '9') {
            int m = s[i] - '0';
            push(m);
        } else {
            // We need at least two numbers in the stack for an operation
            if (isEmpty()) {
                printf("Error: Not enough operands in stack.\n");
                return -1;
            }
            int n1 = pop();
            if (isEmpty()) {
                printf("Error: Not enough operands in stack.\n");
                return -1;
            }
            int n2 = pop();

            int ans;
            switch (s[i]) {
                case '+':
                    ans = n2 + n1;
                    break;
                case '-':
                    ans = n2 - n1;
                    break;
                case '*':
                    ans = n2 * n1;
                    break;
                case '/':
                    if (n1 == 0) {
                        printf("Error: Division by zero.\n");
                        return -1;
                    }
                    ans = n2 / n1;
                    break;
                case '^':
                    ans = (int)pow(n2, n1); // Casting to int, as pow returns double
                    break;
                default:
                    printf("Unsupported operator: %c\n", s[i]);
                    return -1;
            }
            push(ans);
        }
    }

    // At the end of the evaluation, the result should be at the top of the stack
    return peak();
}

int main() {
    char s[100];

    printf("Enter postfix expression: ");
    scanf("%s", s);

    int len = strlen(s);
    init(len);

    int result = evaluate(s);
    if (result != -1) {
        printf("Evaluation of postfix expression is: %d\n", result);
    }

    // Free the allocated memory for the stack
    free(st.arr);
    return 0;
}
