// 13. Given a sorted linked list, delete all duplicates such that each element appears only once.
// For example:
// ● Given 1→1 → 2, return 1 → 2
// ● Given 1 → 1 → 2 → 3 → 3, return 1 → 2 → 3

#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to create a new node
struct ListNode* createNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// Function to reverse a linked list
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* current = head;
    struct ListNode* next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Function to add two numbers represented by linked lists
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    l1 = reverseList(l1);
    l2 = reverseList(l2);

    struct ListNode* dummyHead = createNode(0);
    struct ListNode* current = dummyHead;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
        carry = sum / 10;
        current->next = createNode(sum % 10);
        current = current->next;

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    struct ListNode* result = reverseList(dummyHead->next);
    free(dummyHead);
    return result;
}

// Function to print a linked list
void printList(struct ListNode* head) {
    while (head) {
        printf("%d", head->val);
        if (head->next) printf(" → ");
        head = head->next;
    }
    printf("\n");
}

// Function to dynamically create a linked list
struct ListNode* createLinkedList() {
    int noOfNodes, value;
    struct ListNode* head = NULL;
    struct ListNode* newNode = NULL;
    struct ListNode* temp = NULL;

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
    struct ListNode* operand_1 = createLinkedList();

    printf("Create operand_2:\n");
    struct ListNode* operand_2 = createLinkedList();

    printf("\nOperand_1: ");
    printList(operand_1);

    printf("Operand_2: ");
    printList(operand_2);

    struct ListNode* result = addTwoNumbers(operand_1, operand_2);

    printf("\nResult: ");
    printList(result);

    // Free memory (cleanup)
    while (result) {
        struct ListNode* temp = result;
        result = result->next;
        free(temp);
    }

    return 0;
}
