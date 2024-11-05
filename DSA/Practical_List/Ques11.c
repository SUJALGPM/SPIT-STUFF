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

struct Node *InsertionAtBegin(struct Node *head) {
    int value;
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    printf("Enter value for new node:\n");
    scanf("%d", &value);
    newNode->data = value;

    newNode->prev = NULL;
    newNode->next = head;
    if (head != NULL) {
        head->prev = newNode;
    }

    return newNode;
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

struct Node *InsertionAtMiddle(struct Node *head) {
    int value, index, i = 0;
    struct Node *temp = head;
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    printf("Enter data for new node:\n");
    scanf("%d", &value);
    printf("Enter the position to insert (starting from 1):\n");
    scanf("%d", &index);

    newNode->data = value;

    if (index == 1) {
        return InsertionAtBegin(head);
    }

    while (i < index - 2 && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds. Inserting at the end.\n");
        return InsertionAtLast(head);
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;

    return head;
}

// Function to sort the doubly linked list
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
        printf("2. Insert at the beginning\n");
        printf("3. Insert at the end\n");
        printf("4. Insert at a specific position\n");
        printf("5. Sort the list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                TraversedDoublyLinkedList(head);
                break;
            case 2:
                head = InsertionAtBegin(head);
                TraversedDoublyLinkedList(head);
                break;
            case 3:
                head = InsertionAtLast(head);
                TraversedDoublyLinkedList(head);
                break;
            case 4:
                head = InsertionAtMiddle(head);
                TraversedDoublyLinkedList(head);
                break;
            case 5:
                head = SortDoublyLinkedList(head);
                TraversedDoublyLinkedList(head);
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
