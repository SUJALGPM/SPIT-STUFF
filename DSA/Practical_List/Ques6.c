// 6. Evaluation of Prefix expression using Stack.

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
    return (st.top == -1);
}

int isFull() {
    return (st.top == st.size - 1);
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
        return -1;  // Indicates error: Stack is empty
    }
    return st.arr[st.top--];
}

int peak() {
    if (isEmpty()) {
        return -1;  // Indicates error: Stack is empty
    }
    return st.arr[st.top];
}

// Function to evaluate prefix expression
int evaluatePrefix(char *s) {
    int i;
    for (i = strlen(s) - 1; i >= 0; i--) {  // Start from the right
        // If current character is an operand (digit)
        if (isdigit(s[i])) {
            int m = s[i] - '0';  // Convert char to int
            push(m);
        } else {
            // Operator encountered
            int n1 = pop();  // Pop the top two elements for the operation
            int n2 = pop();
            int ans;

            switch (s[i]) {
                case '+': ans = n1 + n2; break;
                case '-': ans = n1 - n2; break;
                case '*': ans = n1 * n2; break;
                case '/': ans = n1 / n2; break;
                case '^': ans = pow(n1, n2); break;
                default:
                    printf("Unsupported operator: %c\n", s[i]);
                    return -1;
            }

            push(ans);  // Push the result of the operation back onto the stack
        }
    }
    return peak();  // Return the final result from the stack
}

int main() {
    char s[100];

    printf("Enter prefix expression: \n");
    scanf("%s", s);

    int len = strlen(s);
    init(len);

    int result = evaluatePrefix(s);
    if (result != -1) {
        printf("Evaluation of prefix expression is: %d\n", result);
    } else {
        printf("Error in evaluation.\n");
    }

    return 0;
}