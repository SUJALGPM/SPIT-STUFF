// 8. Given a singly linked list, determine if it's a palindrome. Return 1 or 0 denoting if it's a
// palindrome or not, respectively. For example
// a. List 1 → 2 → 1 is a palindrome.
// b. List 1 → 2 → 3 is not a palindrome

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
    newNode->next = NULL;  // explicitly setting next to NULL
    return newNode;
}

// Function to reverse the linked list
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    struct ListNode* next = NULL;
    
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Function to check if the linked list is a palindrome
int isPalindrome(struct ListNode* head) {
    if (!head || !head->next) return 1;

    // Step 1: Find the middle of the linked list
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse the second half
    struct ListNode* secondHalf = reverseList(slow);

    // Step 3: Compare the two halves
    struct ListNode* firstHalf = head;
    struct ListNode* secondHalfCopy = secondHalf;  // To restore the list later if needed
    while (secondHalf != NULL) {
        if (firstHalf->val != secondHalf->val) {
            reverseList(secondHalfCopy);  // Restore list before returning
            return 0;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    // (Optional) Step 4: Restore the second half back
    reverseList(secondHalfCopy);

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
