// 24. Add 2 non-negative numbers that have been given as a linked list Given two non-empty linked lists representing two non-negative integers. 
//     The most significant digit comes first and each of their nodes contains a single digit. 
//     Add the two numbers and return the sum as a linked list. You may assume the two numbers do not contain any leading zero, except the number 0 itself. 
//     Example 1: operand_1: 7 → 2 → 3 → 3
//     result: 
//     Example 2: operand_2: 5 → 7 → 4 
//     result: 7 → 8 → 0 → 7


#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list
struct ListNode {
    int val;
    struct ListNode *next;
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

// Example usage
int main() {
    // Create operand_1: 7 → 2 → 3 → 3
    struct ListNode* operand_1 = createNode(7);
    operand_1->next = createNode(2);
    operand_1->next->next = createNode(3);
    operand_1->next->next->next = createNode(3);

    // Create operand_2: 5 → 7 → 4
    struct ListNode* operand_2 = createNode(5);
    operand_2->next = createNode(7);
    operand_2->next->next = createNode(4);

    // Add the two numbers
    struct ListNode* result = addTwoNumbers(operand_1, operand_2);

    // Print the result
    printf("Result: ");
    printList(result);

    // Free memory (cleanup)
    while (result) {
        struct ListNode* temp = result;
        result = result->next;
        free(temp);
    }

    return 0;
}
