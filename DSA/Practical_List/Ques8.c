// 8. Given a singly linked list, determine if it's a palindrome. Return 1 or 0 denoting if it's a
// palindrome or not, respectively. For example
// a. List 1 → 2 → 1 is a palindrome.
// b. List 1 → 2 → 3 is not a palindrome.


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the linked list is a palindrome
int isPalindrome(struct Node* head) {
    if (!head || !head->next) return 1;

    // Step 1: Create a reversed copy of the linked list
    struct Node* reversedHead = NULL;
    struct Node* temp = head;
    while (temp != NULL) {
        struct Node* newNode = createNode(temp->data);
        newNode->next = reversedHead;
        reversedHead = newNode;
        temp = temp->next;
    }

    // Step 2: Compare the original and reversed lists node by node
    struct Node* original = head;
    struct Node* reversed = reversedHead;
    while (original != NULL && reversed != NULL) {
        if (original->data != reversed->data) {
            // Free the reversed list before returning
            while (reversedHead != NULL) {
                struct Node* del = reversedHead;
                reversedHead = reversedHead->next;
                free(del);
            }
            return 0;
        }
        original = original->next;
        reversed = reversed->next;
    }

    // Free the reversed list
    while (reversedHead != NULL) {
        struct Node* del = reversedHead;
        reversedHead = reversedHead->next;
        free(del);
    }

    return 1;
}

int main() {
    int noOfNodes, value;
    struct Node* head = NULL;
    struct Node* newNode = NULL;
    struct Node* temp = NULL;

    printf("Enter how many nodes you want: ");
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

    // Check if it's a palindrome
    if (isPalindrome(head)) {
        printf("The linked list is a palindrome.\n");
    } else {
        printf("The linked list is not a palindrome.\n");
    }

    return 0;
}
