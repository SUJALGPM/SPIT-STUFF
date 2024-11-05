// 7. Write a program to implement Queue using a circular array. The following operations need to be
// supported:
// a. enqueue
// b. dequeue
// c. isEmpty
// d. isFull
// e. front
// f. rear

#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int front;
    int back;
    int size;
    int *store;
};

// Function to initialize the queue
struct Queue* createQueue(int size) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->size = size;
    queue->front = -1;
    queue->back = -1;
    queue->store = (int*)malloc(queue->size * sizeof(int));
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Function to check if the queue is full
int isFull(struct Queue* queue) {
    return (queue->back + 1) % queue->size == queue->front;
}

// Function to get the front element
int front(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->store[queue->front];
}

// Function to get the rear element
int rear(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->store[queue->back];
}

// Function to add an element to the queue
void enqueue(struct Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full (overflow)..!!\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->back = (queue->back + 1) % queue->size;
    queue->store[queue->back] = value;
    printf("Enqueued %d to the queue.\n", value);
}

// Function to remove an element from the queue
void dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty (underflow)..!!\n");
        return;
    }
    int deleteItem = queue->store[queue->front];
    printf("Dequeued item from queue: %d\n", deleteItem);
    if (queue->front == queue->back) {
        // Queue has only one element, so we reset it to empty
        queue->front = -1;
        queue->back = -1;
    } else {
        queue->front = (queue->front + 1) % queue->size;
    }
}

// Function to display all elements of the queue
void traverseQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty..!!\n");
        return;
    }
    printf("Queue elements:\n");
    int i = queue->front;
    while (1) {
        printf("%d ", queue->store[i]);
        if (i == queue->back) break;
        i = (i + 1) % queue->size;
    }
    printf("\n");
}

int main() {
    int size, choice, value;
    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    struct Queue* queue = createQueue(size);

    do {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Check if Queue is Empty\n");
        printf("4. Check if Queue is Full\n");
        printf("5. Get Front Element\n");
        printf("6. Get Rear Element\n");
        printf("7. Display Queue\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            case 2:
                dequeue(queue);
                break;
            case 3:
                if (isEmpty(queue)) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Queue is not empty.\n");
                }
                break;
            case 4:
                if (isFull(queue)) {
                    printf("Queue is full.\n");
                } else {
                    printf("Queue is not full.\n");
                }
                break;
            case 5:
                value = front(queue);
                if (value != -1) {
                    printf("Front element is: %d\n", value);
                }
                break;
            case 6:
                value = rear(queue);
                if (value != -1) {
                    printf("Rear element is: %d\n", value);
                }
                break;
            case 7:
                traverseQueue(queue);
                break;
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    // Free allocated memory for the queue
    free(queue->store);
    free(queue);

    return 0;
}
