// 13. Given a sorted linked list, delete all duplicates such that each element appears only once.
// For example:
// ● Given 1→1 → 2, return 1 → 2
// ● Given 1 → 1 → 2 → 3 → 3, return 1 → 2 → 3

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

// Function to delete duplicates in a sorted linked list
struct Node* deleteDuplicates(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }
    
    struct Node* p = head;
    struct Node* q = head->next;
    
    while (q != NULL) {
        if (p->data != q->data) {
            p = q;
            q = q->next;
        } else {
            p->next = q->next;
            free(q);
            q = p->next;
        }
    }
    return head;
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
    
    printf("Enter no of nodes:\n");
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
    
    printf("Original list:\n");
    printList(head);
    
    // Delete duplicates
    head = deleteDuplicates(head);
    printf("\nList after removing duplicates:\n");
    printList(head);

    return 0;
}
