// 25. Rotate a Linked List by ‘k’ places. 
// Example 1: input: 1 → 2 → 3 → 4 → 5 , k = 1 output: 5 → 1 → 2 → 3 → 4 
// Example 2: input: 1 → 2 → 3 → 4 → 5 , k = 2 output: 4 → 5 → 1 → 2 → 3

#include <stdio.h>
#include <stdlib.h>

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

// Function to calculate the length of the linked list
int getLength(struct Node* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

// Function to rotate the linked list by k places
struct Node* rotateList(struct Node* head, int k) {
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
    struct Node* current = head;
    int stepsToNewHead = length - k - 1;
    for (int i = 0; i < stepsToNewHead; i++) {
        current = current->next;
    }

    // New head and tail adjustments
    struct Node* newHead = current->next;
    current->next = NULL;

    // Find the old tail and connect it to the old head
    struct Node* tail = newHead;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = head;

    return newHead;
}

// Function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    int noOfNodes, value, k;
    struct Node* head = NULL;
    struct Node* newNode = NULL;
    struct Node* temp = NULL;
    
    // Take input for the linked list
    printf("Enter number of nodes: ");
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

    // Take input for rotation
    printf("Enter the number of places to rotate: ");
    scanf("%d", &k);

    // Print the original list
    printf("\nOriginal list:\n");
    printList(head);

    // Rotate the list
    head = rotateList(head, k);
    printf("\nList after rotating by %d places:\n", k);
    printList(head);

    return 0;
}
