// 12. Implement the following operations on doubly linked lists:
// a. Insert (end)
// b. concatenate two lists
// c. display
#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *prev;
    int data;
    struct Node *next;
};

void TraversedDoublyLinkedList(struct Node *head) {
    struct Node *ptr = head;
    printf("Traversed of doubly linked list..\n");
    while (ptr != NULL) {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }
}

struct Node *InsertionAtLast(struct Node *head) {
    int value;
    struct Node *temp = head;
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    printf("Enter data for new node:\n");
    scanf("%d", &value);

    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;

    return head;
}

struct Node *ConcatenateDoublyLinkedList(struct Node *head1, struct Node *head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct Node *temp = head1;

    // Traverse to the end of the first list
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Connect the end of the first list to the beginning of the second list
    temp->next = head2;
    head2->prev = temp;

    printf("Lists concatenated.\n");
    return head1;
}

int main() {
    int noOfNode, value, choice, listChoice;
    struct Node *head1 = NULL;
    struct Node *head2 = NULL;

    do {
        printf("\nMenu:\n");
        printf("1. Display the first list\n");
        printf("2. Display the second list\n");
        printf("3. Insert at the end of the first list\n");
        printf("4. Insert at the end of the second list\n");
        printf("5. Concatenate both lists\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("First List:\n");
                TraversedDoublyLinkedList(head1);
                break;
            case 2:
                printf("Second List:\n");
                TraversedDoublyLinkedList(head2);
                break;
            case 3:
                printf("Inserting at the end of the first list.\n");
                head1 = InsertionAtLast(head1);
                TraversedDoublyLinkedList(head1);
                break;
            case 4:
                printf("Inserting at the end of the second list.\n");
                head2 = InsertionAtLast(head2);
                TraversedDoublyLinkedList(head2);
                break;
            case 5:
                printf("Concatenating the two lists.\n");
                head1 = ConcatenateDoublyLinkedList(head1, head2);
                TraversedDoublyLinkedList(head1);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

