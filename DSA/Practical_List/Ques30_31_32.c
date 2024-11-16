// 15. Write a program to construct a binary search tree and traverse it with all methods that uses recursion.

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node *insertBST(struct Node *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }

    if (key < root->key)
    {
        root->left = insertBST(root->left, key);
    }
    else
    {
        root->right = insertBST(root->right, key);
    }

    return root;
}

struct Node *searchNode(struct Node *root, int key)
{
    if (root == NULL || root->key == key)
    {
        return root;
    }

    if (key < root->key)
    {
        searchNode(root->left, key);
    }
    else
    {
        searchNode(root->right, key);
    }
}

// Function to find the in-order predecessor (largest node in the left subtree)
struct Node *predecessor(struct Node *root)
{
    struct Node *curr = root->left;
    while (!curr && !curr->right)
    {
        curr = curr->right;
    }

    return curr;
}

// Function to find the in-order successor (smallest node in the right subtree)
struct Node *successor(struct Node *root)
{
    struct Node *curr = root->right;
    while (!curr && !curr->left)
    {
        curr = curr->left;
    }

    return curr;
}

// Function to get the minimum key (leftmost node)
struct Node *minKey(struct Node *root)
{
    struct Node *current = root;
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// Function to get the maximum key (rightmost node)
struct Node *maxKey(struct Node *root)
{
    struct Node *current = root;
    while (current && current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

struct Node *DeleteNode(struct Node *root, int key)
{

    // base condition...
    if (root == NULL)
    {
        return root;
    }

    // search in subtree..
    if (key < root->key)
    {
        root->left = DeleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = DeleteNode(root->right, key);
    }
    else
    {
        // case when root has no child or only right child...
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        // case when root has no child or only left child.
        if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *succ = successor(root);
        root->key = succ->key;
        root->right = DeleteNode(root->right, succ->key);
    }

    return root;
}

void Preorder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->key);
    Preorder(root->left);
    Preorder(root->right);
}

void Postorder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    Postorder(root->left);
    Postorder(root->right);
    printf("%d ", root->key);
}

void InOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    InOrder(root->left);
    printf("%d ", root->key);
    InOrder(root->right);
}

int main()
{
    int choice;
    struct Node *root = NULL;

    do
    {
        printf("\nBST Operation Menu:\n");
        printf("1. Insert Element\n");
        printf("2. Preorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Inorder Traversal\n");
        printf("5. Searching in BST\n");
        printf("6. Delete Element\n");
        printf("7. Find Minimum Key\n");
        printf("8. Find Maximum Key\n");
        printf("9. Find Predecessor\n");
        printf("10. Find Successor\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int key;
            printf("Enter data for node :\n");
            scanf("%d", &key);
            root = insertBST(root, key);
            printf("Node inserted: %d", key);
            break;
        }
        case 2:
            printf("Preorder Traversal:\n");
            Preorder(root);
            break;
        case 3:
            printf("Postorder Traversal:\n");
            Postorder(root);
            break;
        case 4:
            printf("Inorder Traversal:\n");
            InOrder(root);
            break;
        case 5:
        {
            int element;
            printf("Enter element to search:\n");
            scanf("%d", &element);
            struct Node *result = searchNode(root, element);
            if (result != NULL)
            {
                printf("Element found in BST: %d", element);
            }
            else
            {
                printf("Element not found in BST: %d", element);
            }
            break;
        }
        case 6:
        {
            int element;
            printf("Enter element to delete:\n");
            scanf("%d", &element);
            root = DeleteNode(root, element);
            break;
        }
        case 7:
        {
            struct Node *minNode = minKey(root);
            if (minNode != NULL)
            {
                printf("Minimum Key: %d", minNode->key);
            }
            else
            {
                printf("Tree is empty.\n");
            }
            break;
        }
        case 8:
        {
            struct Node *maxNode = maxKey(root);
            if (maxNode != NULL)
            {
                printf("Maximum Key: %d", maxNode->key);
            }
            else
            {
                printf("Tree is empty.\n");
            }
            break;
        }
        case 9:
        {
            struct Node *pred = predecessor(root);
            if (pred != NULL)
            {
                printf("Predecessor of Root is: %d", pred->key);
            }
            else
            {
                printf("No predecessor for Root");
            }
            break;
        }
        case 10:
        {
            struct Node *succ = successor(root);
            if (succ != NULL)
            {
                printf("Successor of Root is: %d", succ->key);
            }
            else
            {
                printf("No successor for Root");
            }
            break;
        }
        case 11:
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (choice != 11);

    return 0;
}