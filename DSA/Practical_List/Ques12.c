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
    while(ptr != NULL) {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }
}

struct Node *InsertionAtLast(struct Node *head) {
    int value;
    struct Node *temp = head;
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    printf("Enter data for new node:\n");
    scanf("%d", &value);

    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode;
    }

    while(temp->next != NULL) {
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
    int noOfNode, value, choice;
    struct Node *head1 = NULL;
    struct Node *head2 = NULL;
    struct Node *temp = NULL;
    struct Node *newNode = NULL;

    // Create first doubly linked list
    printf("Enter the number of nodes in the first doubly linked list:\n");
    scanf("%d", &noOfNode);
    for(int i = 0; i < noOfNode; i++) {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter data for node:\n");
        scanf("%d", &value);
        newNode->data = value;
        newNode->prev = NULL;
        newNode->next = NULL;

        if(head1 == NULL) {
            head1 = newNode;
        } else {
            newNode->prev = temp;
            temp->next = newNode;
        }

        temp = newNode;
    }

    // Create second doubly linked list
    printf("Enter the number of nodes in the second doubly linked list:\n");
    scanf("%d", &noOfNode);
    temp = NULL;
    for(int i = 0; i < noOfNode; i++) {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter data for node:\n");
        scanf("%d", &value);
        newNode->data = value;
        newNode->prev = NULL;
        newNode->next = NULL;

        if(head2 == NULL) {
            head2 = newNode;
        } else {
            newNode->prev = temp;
            temp->next = newNode;
        }

        temp = newNode;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Display the first list\n");
        printf("2. Display the second list\n");
        printf("3. Concatenate both lists\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                TraversedDoublyLinkedList(head1);
                break;
            case 2:
                TraversedDoublyLinkedList(head2);
                break;
            case 3:
                head1 = ConcatenateDoublyLinkedList(head1, head2);
                TraversedDoublyLinkedList(head1);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

