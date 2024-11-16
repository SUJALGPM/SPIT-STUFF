// 25. Rotate a Linked List by ‘k’ places. 
// Example 1: input: 1 → 2 → 3 → 4 → 5 , k = 1 output: 5 → 1 → 2 → 3 → 4 
// Example 2: input: 1 → 2 → 3 → 4 → 5 , k = 2 output: 4 → 5 → 1 → 2 → 3


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

// Function to calculate the length of the linked list
int getLength(struct ListNode* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

// Function to rotate the linked list by k places
struct ListNode* rotateList(struct ListNode* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head; // No rotation needed
    }

    // Calculate the length of the list
    int length = getLength(head);
    k = k % length; // Handle cases where k > length
    if (k == 0) {
        return head; // No rotation needed
    }

    // Find the new tail (length - k - 1) and new head (length - k)
    struct ListNode* current = head;
    int stepsToNewHead = length - k - 1;
    for (int i = 0; i < stepsToNewHead; i++) {
        current = current->next;
    }

    // New head and tail adjustments
    struct ListNode* newHead = current->next;
    current->next = NULL;

    // Find the old tail and connect it to the old head
    struct ListNode* tail = newHead;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = head;

    return newHead;
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
    // Create a linked list 1 -> 2 -> 3 -> 4 -> 5
    struct ListNode* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    int k = 2; // Rotate by k places

    printf("Original list:\n");
    printList(head);

    // Rotate the list
    head = rotateList(head, k);
    printf("\nList after rotating by %d places:\n", k);
    printList(head);

    // Free the list memory
    freeList(head);

    return 0;
}
