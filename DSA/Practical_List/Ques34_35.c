// 34.Construct an AVL tree and excecute left rotatio on it.
// 35.Construct an AVL tree and excecute right rotatio on it.


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Calculate height of the node
int height(struct Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Calculate max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
struct Node *createNode(int key) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Get balance factor of node n
int balanceFactor(struct Node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// Perform right rotation
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Perform left rotation
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Insertion in AVL tree
struct Node *insertion(struct Node *root, int key) {
    // Perform standard BST insertion
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insertion(root->left, key);
    else if (key > root->key)
        root->right = insertion(root->right, key);
    else
        return root; // Duplicate keys not allowed

    // Update height of current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get balance factor of this node
    int balance = balanceFactor(root);  

    // Left Left Case (RR rotation)
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right Case (LL rotation)
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Case (LR rotation)
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case (RL rotation)
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order traversal of the tree
void InOrder(struct Node *root) {
    if (root != NULL) {
        InOrder(root->left);
        printf("%d ", root->key);
        InOrder(root->right);
    }
}

int main() {
 
    int choice;
    struct Node *root = NULL;

    do {
        printf("\nAVL Tree Operation Menu:\n");
        printf("1. Insert Element\n");
        printf("2. In-order Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int key;
                printf("Enter data for node: ");
                scanf("%d", &key);
                root = insertion(root, key);
                printf("Node inserted: %d\n", key);
            }
            break;
            
            case 2:
                printf("In-order Traversal: ");
                InOrder(root);
                printf("\n");
                break;
                
            case 3:
                printf("Exiting.\n");
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
