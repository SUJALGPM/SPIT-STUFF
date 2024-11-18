// 9. Implement univariate Polynomial addition using linked lists. A univariate polynomial should be represented in the decreasing order of its coefficient.


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
    struct Node* newNode = createNode(coefficient, exponent);

    // Case 1: Insert at the beginning if the list is empty or exponent is the largest
    if (head == NULL || head->exponent < exponent) {
        newNode->next = head;
        head = newNode;
        return head;
    }

    // Case 2: Traverse and find the correct position
    struct Node* current = head;
    while (current->next != NULL && current->next->exponent > exponent) {
        current = current->next;
    }
    
    // Insert the new node at the correct position
    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    // Traverse both polynomials
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            result = insertNode(result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            result = insertNode(result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            // Same exponents: Add coefficients
            int sumCoeff = poly1->coefficient + poly2->coefficient;
            if (sumCoeff != 0) {
                result = insertNode(result, sumCoeff, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    // Add remaining terms from poly1
    while (poly1 != NULL) {
        result = insertNode(result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    // Add remaining terms from poly2
    while (poly2 != NULL) {
        result = insertNode(result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
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



// Main function
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    // Create first polynomial: 5x^3 + 4x^2 + 2x
    poly1 = insertNode(poly1, 5, 3);
    poly1 = insertNode(poly1, 4, 2);
    poly1 = insertNode(poly1, 2, 1);

    // Create second polynomial: 3x^3 + x^2 + 6
    poly2 = insertNode(poly2, 3, 3);
    poly2 = insertNode(poly2, 1, 2);
    poly2 = insertNode(poly2, 6, 0);

    // Print the polynomials
    printf("First Polynomial: ");
    printPolynomial(poly1);

    printf("Second Polynomial: ");
    printPolynomial(poly2);

    // Add the two polynomials
    struct Node* result = addPolynomials(poly1, poly2);
    printf("Resultant Polynomial: ");
    printPolynomial(result);

    return 0;
}