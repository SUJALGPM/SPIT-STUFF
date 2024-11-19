// 15. Write a program to construct a binary search tree and traverse it with all methods that uses recursion.


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

struct Node *insertBST(struct Node* root,int key){
    if(root == NULL){
        return createNode(key);
    }

    if(key < root->key){
        root->left = insertBST(root->left,key);
    }else{
        root->right = insertBST(root->right,key);
    }

    return root;
}

struct Node *searchNode(struct Node *root,int key){
    if(root == NULL || root->key == key){
        return root;
    }

    if(key < root->key){
        searchNode(root->left,key);
    }else{
        searchNode(root->right,key);
    }
}

// Function to find the in-order predecessor (largest node in the left subtree)
struct Node *predecessor(struct Node *root){
    struct Node *curr = root->left;
    while(!curr && !curr->right){
        curr = curr->right;
    }

    return curr;
}

// Function to find the in-order successor (smallest node in the right subtree)
struct Node *successor(struct Node *root){
    struct Node *curr = root->right;
    while(!curr && !curr->left){
        curr = curr->left;
    }

    return curr;
}

struct Node *DeleteNode(struct Node* root, int key){

    //base condition...
    if(root == NULL){
        return root;
    }

    //search in subtree..
    if(key < root->key){ //20 < 30
        root->left = DeleteNode(root->left,key); // 30,20
    }else if(key > root->key){
        root->right = DeleteNode(root->right,key);
    }else{
        //case when root has no child or only right child...
        if(root->left == NULL){
            struct Node *temp  = root->right;
            free(root);
            return temp;
        }

        //case when root has no child or only left child.
        if(root->right == NULL){
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *succ = successor(root);
        root->key = succ->key;
        root->right = DeleteNode(root->right,succ->key);
    }

    return root;
}

void Preorder(struct Node *root){
    if(root == NULL){
        return;
    }

    printf("%d ",root->key);
    Preorder(root->left);
    Preorder(root->right);
}

void Postorder(struct Node *root){
    if(root == NULL){
        return;
    }

    Postorder(root->left);
    Postorder(root->right);
    printf("%d ",root->key);
}

void InOrder(struct Node *root){
    if(root == NULL){
        return;
    }

    InOrder(root->left);
    printf("%d ",root->key);
    InOrder(root->right);
}

int main(){
    int choice;
    struct Node *root = NULL;


    do{
        printf("\nBST Operation Menu:\n");
        printf("1. Insert Element\n");
        printf("2. Preorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Inorder Traversal\n");
        printf("5. Searching in BST\n");
        printf("6. Delete Element\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int key;
            printf("Enter data for node :\n");
            scanf("%d",&key);
            root = insertBST(root,key);
            printf("Node inserted : %d",key);
        }
            break;
        case 2:
            printf("Preorder traversal..\n");
            Preorder(root);
            break;
        case 3:
            printf("Postorder traversal..\n");
            Postorder(root);
            break;
        case 4:
            printf("Inorder Traversal..\n");
            InOrder(root);
            break;
        case 5:
        {
            int element;
            printf("Enter element you want check present or not in BST..\n");
            scanf("%d",&element);
            struct Node *result = searchNode(root,element);
            if(result != NULL){
                printf("Element found in BST  : %d",element);
            }else{
                printf("Element not found in BST : %d",element);
            }
        }
            break;
        case 6:
        {
            int element;
            printf("Enter element you want to delete :\n");
            scanf("%d",&element);
            DeleteNode(root,element);
        }
            break;
        case 7:
            break;
        default:
            break;
        }
    }while (choice != 7);
    
    return 0;
}
