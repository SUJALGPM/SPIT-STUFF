// 14. Given a linked list and a value x, partition it such that all nodes less than x come before
// nodes greater than or equal to x. You should preserve the original relative order of the nodes
// in each of the two partitions.
// For example:
// ● Input: 1 → 5 → 3 → 2 → 4 → 2 and x = 3
// ● Output: 1 → 2 → 2 → 3 → 5 → 4

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to partition the list around value x
struct Node* partition(struct Node* head, int x) {
    struct Node* lessHead = NULL, *lessTail = NULL;
    struct Node* greaterHead = NULL, *greaterTail = NULL;
    
    while (head != NULL) {
        if (head->data < x) {
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
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    int noOfNodes, value;
    struct Node* head = NULL;
    struct Node* newNode = NULL;
    struct Node* temp = NULL;
    
    printf("Enter number of nodes:\n");
    scanf("%d", &noOfNodes);
    
    for (int i = 0; i < noOfNodes; i++) {
        printf("Enter data for your node: ");
        scanf("%d", &value);
        
        newNode = createNode(value); 
        
        if (head == NULL) {
            head = newNode;
        } else {
            temp->next = newNode;
        }
        
        temp = newNode;
    }
    
    int x;
    printf("Enter the value of x to partition the list: ");
    scanf("%d", &x);
    
    printf("Original list:\n");
    printList(head);
    
    // Partition the list around x
    struct Node* partitionedHead = partition(head, x);
    printf("\nPartitioned list around %d:\n", x);
    printList(partitionedHead);

    return 0;
}
