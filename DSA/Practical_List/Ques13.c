// 13. Given a sorted linked list, delete all duplicates such that each element appears only once.
// For example:
// ● Given 1→1 → 2, return 1 → 2
// ● Given 1 → 1 → 2 → 3 → 3, return 1 → 2 → 3
#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list
struct Node {
    int val;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// Function to reverse a linked list
struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Function to add two numbers represented by linked lists
struct Node* addTwoNumbers(struct Node* l1, struct Node* l2) {
    l1 = reverseList(l1);
    l2 = reverseList(l2);

    struct Node* dummyHead = createNode(0);
    struct Node* current = dummyHead;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
        carry = sum / 10;
        current->next = createNode(sum % 10);
        current = current->next;

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    struct Node* result = reverseList(dummyHead->next);
    free(dummyHead);
    return result;
}

// Function to print a linked list
void printList(struct Node* head) {
    while (head) {
        printf("%d", head->val);
        if (head->next) printf(" → ");
        head = head->next;
    }
    printf("\n");
}

// Function to dynamically create a linked list
struct Node* createLinkedList() {
    int noOfNodes, value;
    struct Node* head = NULL;
    struct Node* newNode = NULL;
    struct Node* temp = NULL;

    printf("Enter the number of nodes: ");
    scanf("%d", &noOfNodes);

    for (int i = 0; i < noOfNodes; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &value);

        newNode = createNode(value);
        if (head == NULL) {
            head = newNode;
        } else {
            temp->next = newNode;
        }
        temp = newNode;
    }

    return head;
}

// Main function
int main() {
    printf("Create operand_1:\n");
    struct Node* operand_1 = createLinkedList();

    printf("Create operand_2:\n");
    struct Node* operand_2 = createLinkedList();

    printf("\nOperand_1: ");
    printList(operand_1);

    printf("Operand_2: ");
    printList(operand_2);

    struct Node* result = addTwoNumbers(operand_1, operand_2);

    printf("\nResult: ");
    printList(result);

    // Free memory (cleanup)
    while (result) {
        struct Node* temp = result;
        result = result->next;
        free(temp);
    }

    return 0;
}
