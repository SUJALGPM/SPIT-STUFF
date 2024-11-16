// 11. Implement the following operations on doubly linked lists:
// a. Insert (after position)
// b. sort the list
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

struct Node *InsertionAfterPosition(struct Node *head) {
    int position, value, i = 0;
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = head;

    printf("Enter the position after which to insert (starting from 1):\n");
    scanf("%d", &position);
    printf("Enter the value for the new node:\n");
    scanf("%d", &value);

    newNode->data = value;

    // Traverse to the specified position
    while (i < position - 1 && temp != NULL) {
        temp = temp->next;
        i++;
    }

    // If position is out of bounds
    if (temp == NULL) {
        printf("Position out of bounds. Cannot insert.\n");
        free(newNode);
        return head;
    }

    // Insert the new node
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;

    printf("Node inserted successfully after position %d.\n", position);
    return head;
}

struct Node *SortDoublyLinkedList(struct Node *head) {
    if (head == NULL) return NULL;

    int swapped;
    struct Node *ptr;
    struct Node *last = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != last) {
            if (ptr->data > ptr->next->data) {
                // Swap the data of the nodes
                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);

    printf("List sorted.\n");
    return head;
}

int main() {
    int noOfNode, value, choice;
    struct Node *head = NULL;
    struct Node *temp = NULL;
    struct Node *newNode = NULL;

    printf("Enter the number of nodes in the doubly linked list:\n");
    scanf("%d", &noOfNode);

    for(int i = 0; i < noOfNode; i++) {
        newNode = (struct Node*)malloc(sizeof(struct Node));

        printf("Enter data for node:\n");
        scanf("%d", &value);
        newNode->data = value;
        newNode->prev = NULL;
        newNode->next = NULL;

        if(head == NULL) {
            head = newNode;
        } else {
            newNode->prev = temp;
            temp->next = newNode;
        }

        temp = newNode;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Display the list\n");
        printf("2. Insert at a specific position\n");
        printf("3. Sort the list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                TraversedDoublyLinkedList(head);
                break;
            case 2:
                head = InsertionAfterPosition(head);
                TraversedDoublyLinkedList(head);
                break;
            case 3:
                head = SortDoublyLinkedList(head);
                TraversedDoublyLinkedList(head);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
