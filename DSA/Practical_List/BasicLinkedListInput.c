#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Node* head){
    struct Node* temp = head;
    
    if(temp == NULL){
        return;
    }
    
    while(temp!=NULL){
        printf("%d\n",temp->data);
        temp = temp->next;
    }
}


int main(){
    int noOfNodes, value;
    struct Node* head = NULL;
    struct Node* newNode = NULL;
    struct Node* temp = NULL;
    
    printf("Enter no of nodes :\n");
    scanf("%d",&noOfNodes);
    
    for(int i=0;i<noOfNodes;i++){
        printf("Enter data for your node :");
        scanf("%d",&value);
        
        newNode = createNode(value); 
        
        if(head == NULL){
            head = newNode;
        }else{
            temp->next = newNode;
        }
        
        temp = newNode;
    }
    
    
    printList(head);
   

    return 0;
}