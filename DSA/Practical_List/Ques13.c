// 13. Given a sorted linked list, delete all duplicates such that each element appears only once.
// For example:
// ● Given 1→1 → 2, return 1 → 2
// ● Given 1 → 1 → 2 → 3 → 3, return 1 → 2 → 3


#include <stdio.h>
#include <stdlib.h>

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

// Function to delete duplicates in a sorted linked list
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* current = head;
    
    while (current != NULL && current->next != NULL) {
        if (current->val == current->next->val) {
            // Duplicate found, remove the next node
            struct ListNode* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            // Move to the next node if no duplicate
            current = current->next;
        }
    }
    
    return head;
}

// Function to print the linked list
void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

// Free the linked list memory
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Create a sorted linked list 1 -> 1 -> 2 -> 3 -> 3
    struct ListNode* head = createNode(1);
    head->next = createNode(1);
    head->next->next = createNode(2);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(3);
    
    printf("Original list:\n");
    printList(head);
    
    // Delete duplicates
    head = deleteDuplicates(head);
    printf("\nList after removing duplicates:\n");
    printList(head);

    // Free the list memory
    freeList(head);

    return 0;
}
