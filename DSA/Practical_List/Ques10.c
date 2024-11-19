// 10. Implement univariate Polynomial Multiplication using linked lists. A univariate polynomial should be represented in the decreasing order of its coefficient.


#include <stdio.h>
#include <stdlib.h>

// Define the Node structure
struct Node {
    int coefficient;        // Coefficient of the term
    int exponent;           // Exponent of the term
    struct Node* next;      // Pointer to the next term
};

// Function to create a new node
struct Node* createNode(int coefficient, int exponent) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node into the polynomial in decreasing order of exponents
struct Node* insertNode(struct Node* head, int coefficient, int exponent) {
    if (coefficient == 0) {
        return head; // Skip zero coefficient terms
    }

    struct Node* newNode = createNode(coefficient, exponent);

    // Case 1: Insert at the beginning or if list is empty
    if (head == NULL || head->exponent < exponent) {
        newNode->next = head;
        head = newNode;
        return head;
    }

    struct Node* current = head;

    // Case 2: Traverse to find the correct position or matching exponent
    while (current->next != NULL && current->next->exponent > exponent) {
        current = current->next;
    }

    // Case 3: Combine terms with the same exponent
    if (current->next != NULL && current->next->exponent == exponent) {
        current->next->coefficient += coefficient;
        if (current->next->coefficient == 0) { // Remove zero coefficient terms
            struct Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        }
        return head;
    }

    // Case 4: Insert at the correct position
    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Function to multiply two polynomials...
struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    struct Node* p1 = poly1;
    while (p1 != NULL) {
        struct Node* p2 = poly2;
        while (p2 != NULL) {
            int newCoefficient = p1->coefficient * p2->coefficient;
            int newExponent = p1->exponent + p2->exponent;
            result = insertNode(result, newCoefficient, newExponent);
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    return result;
}


// Function to print a polynomial
void printPolynomial(struct Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coefficient, poly->exponent);
        poly = poly->next;
        if (poly != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to dynamically input a polynomial
struct Node* inputPolynomial() {
    struct Node* poly = NULL;
    int coefficient, exponent;

    printf("Enter terms of the polynomial (enter -1 -1 to stop):\n");
    while (1) {
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &coefficient, &exponent);

        if (coefficient == -1 && exponent == -1) break;

        poly = insertNode(poly, coefficient, exponent);
    }

    return poly;
}

// Main function
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;

    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Input first polynomial\n");
        printf("2. Input second polynomial\n");
        printf("3. Print first polynomial\n");
        printf("4. Print second polynomial\n");
        printf("5. Add polynomials\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Input the first polynomial:\n");
                poly1 = inputPolynomial();
                break;
            case 2:
                printf("Input the second polynomial:\n");
                poly2 = inputPolynomial();
                break;
            case 3:
                printf("First Polynomial: ");
                printPolynomial(poly1);
                break;
            case 4:
                printf("Second Polynomial: ");
                printPolynomial(poly2);
                break;
            case 5:
                result = multiplyPolynomials(poly1, poly2);
                printf("Resultant Polynomial: ");
                printPolynomial(result);
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

}
