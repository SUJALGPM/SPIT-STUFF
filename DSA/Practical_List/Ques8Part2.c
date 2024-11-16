#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to create a new node
struct ListNode* createNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = value;
    newNode->next = NULL; 
    return newNode;
}

// Function to check if the linked list is a palindrome
int isPalindrome(struct ListNode* head) {
    if (!head || !head->next) return 1;

    // Step 1: Create a reversed copy of the linked list
    struct ListNode* reversedHead = NULL;
    struct ListNode* temp = head;
    while (temp != NULL) {
        struct ListNode* newNode = createNode(temp->val);
        newNode->next = reversedHead;
        reversedHead = newNode;
        temp = temp->next;
    }

    // Step 2: Compare the original and reversed lists node by node
    struct ListNode* original = head;
    struct ListNode* reversed = reversedHead;
    while (original != NULL && reversed != NULL) {
        if (original->val != reversed->val) {
            // Free the reversed list before returning
            while (reversedHead != NULL) {
                struct ListNode* del = reversedHead;
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
        struct ListNode* del = reversedHead;
        reversedHead = reversedHead->next;
        free(del);
    }

    return 1;
}

int main() {
    // Create linked list 1->2->2->1
    struct ListNode* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(2);
    head->next->next->next = createNode(1);

    // Check if it's a palindrome
    if (isPalindrome(head)) {
        printf("The linked list is a palindrome.\n");
    } else {
        printf("The linked list is not a palindrome.\n");
    }

    // Free the list memory
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
