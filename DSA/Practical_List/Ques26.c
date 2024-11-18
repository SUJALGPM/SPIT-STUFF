// 26. Swap nodes of a linked list in pairs
// Example 1:
// input: 1 → 2 → 3 → 4
// output: 2 → 1 → 4 → 3
// Example 2:
// input: 1 → 2 → 3
// output: 2 → 1 → 3


#include <stdio.h>
#include <stdlib.h>

struct Node{
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

void printLinkedList(struct Node *head){
    printf("Traversed Linked list...\n");
    while(head != NULL){
        printf("%d\n",head->data);
        head = head->next;
    }
};

void swap(int *a,int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
};

void adjacentPairSwap(struct Node* head){
    struct Node *temp = head;
    while (temp!=NULL && temp->next !=NULL)
    {
        swap(&temp->data,&temp->next->data);
        temp = temp->next->next;
    }
    
}

int main(){
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

    printLinkedList(head);
    adjacentPairSwap(head);
    printLinkedList(head);

    return 0;
}