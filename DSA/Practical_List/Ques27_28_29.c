// 27. Construct a binary tree using recursion and traverse it in all possible traversal.
// 28. Construct a binary tree and count the number of leaves in the tree
// 29. Construct a binary tree using recursion and get the height of given node.


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data){
    struct Node *treeNode = (struct Node*)malloc(sizeof(struct Node));
    treeNode->data = data;
    treeNode->left = NULL;
    treeNode->right = NULL;

    return treeNode;
}

struct Node *insertLevelOrder(int *arr, struct Node *root, int i, int n){
    if(i < n){
        struct Node *temp = createNode(arr[i]);
        root = temp;

        // Insert left child
        root->left = insertLevelOrder(arr, root->left, 2*i+1, n);

        // Insert right child
        root->right = insertLevelOrder(arr, root->right, 2*i+2, n);
    }

    return root;
}

// Preorder traversal (Root, Left, Right)
void preOrderTraversed(struct Node* root){
    if(root != NULL){
        printf("%d ", root->data);
        preOrderTraversed(root->left);
        preOrderTraversed(root->right);
    }
}

// Postorder traversal (Left, Right, Root)
void postOrderTraversal(struct Node *root){
    if(root != NULL){
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Inorder traversal (Left, Root, Right)
void inOrderTraversed(struct Node* root){
    if(root != NULL){
        inOrderTraversed(root->left);
        printf("%d ", root->data);
        inOrderTraversed(root->right);
    }
}

// Function to count leaves in the binary tree
int countLeaves(struct Node *root){
    if(root == NULL){
        return 0;
    }
    if(root->left == NULL && root->right == NULL){
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}

// Function to calculate the height of the binary tree
int height(struct Node *root){
    if(root == NULL){
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
    
int main(){
    int i, n;

    printf("How many nodes do you want in the tree?\n");
    scanf("%d", &n);

    if(n <= 0){
        printf("The number of nodes must be positive.\n");
        return 1;
    }

    // Dynamic array to store input for tree nodes
    int *arr = (int *)malloc(n * sizeof(int));

    // Get input for the tree nodes and store in array
    for(i = 0; i < n; i++){
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    struct Node *root = NULL;
    root = insertLevelOrder(arr, root, 0, n);

    // Traversals
    printf("Preorder Traversal: ");
    preOrderTraversed(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postOrderTraversal(root);
    printf("\n");

    printf("Inorder Traversal: ");
    inOrderTraversed(root);
    printf("\n");

    // Counting leaves
    int leafCount = countLeaves(root);
    printf("Number of leaves in the tree: %d\n", leafCount);

    // Calculating height
    int treeHeight = height(root);
    printf("Height of the tree: %d\n", treeHeight);

    // Free dynamically allocated memory
    free(arr);

    return 0;
}
