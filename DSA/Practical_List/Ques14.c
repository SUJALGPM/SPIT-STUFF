// 14. Given a linked list and a value x, partition it such that all nodes less than x come before
// nodes greater than or equal to x. You should preserve the original relative order of the nodes
// in each of the two partitions.
// For example:
// ● Input: 1 → 5 → 3 → 2 → 4 → 2 and x = 3
// ● Output: 1 → 2 → 2 → 3 → 5 → 4


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

// Function to partition the list around value x
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode* lessHead = NULL, *lessTail = NULL;
    struct ListNode* greaterHead = NULL, *greaterTail = NULL;
    
    while (head != NULL) {
        if (head->val < x) {
            // Insert into the 'less than x' list
            if (lessHead == NULL) {
                lessHead = lessTail = head;
            } else {
                lessTail->next = head;
                lessTail = head;
            }
        } else {
            // Insert into the 'greater than or equal to x' list
            if (greaterHead == NULL) {
                greaterHead = greaterTail = head;
            } else {
                greaterTail->next = head;
                greaterTail = head;
            }
        }
        head = head->next;
    }
    
    // Connect the two lists
    if (lessTail != NULL) {
        lessTail->next = greaterHead;
    }
    if (greaterTail != NULL) {
        greaterTail->next = NULL;
    }
    
    // Return the head of the 'less' list if it exists, otherwise 'greater' list
    return (lessHead != NULL) ? lessHead : greaterHead;
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
    // Create the linked list 1 -> 5 -> 3 -> 2 -> 4 -> 2
    struct ListNode* head = createNode(1);
    head->next = createNode(5);
    head->next->next = createNode(3);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(4);
    head->next->next->next->next->next = createNode(2);
    
    int x = 3;
    printf("Original list:\n");
    printList(head);
    
    // Partition the list around x
    struct ListNode* partitionedHead = partition(head, x);
    printf("\nPartitioned list around %d:\n", x);
    printList(partitionedHead);

    // Free the partitioned list
    freeList(partitionedHead);

    return 0;
}
