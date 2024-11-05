#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

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
    int noOfNodes,value;
    struct Node *head = NULL;
    struct Node *newNode = NULL;
    struct Node *temp = NULL;


    printf("Enter how many nodes you want : \n");
    scanf("%d",&noOfNodes);
    
    for(int i=0;i<noOfNodes;i++){
        newNode = (struct Node*)malloc(sizeof(struct Node));

        printf("Enter data for your node :\n");
        scanf("%d",&value);

        newNode->data = value;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
        }else{
            temp->next = newNode;
        }

        temp = newNode;
        
    }

    printLinkedList(head);
    adjacentPairSwap(head);
    printLinkedList(head);

    return 0;
}