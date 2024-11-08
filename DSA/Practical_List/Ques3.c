// 3. Write a program to maintain multiple queues in a single array.

#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int front;
    int back;
    int size;
    int *store;
};

struct MultipleQueues {
    int numQueues;      // Total number of queues
    int queueSize;      // Size of each queue
    struct Queue *queues;      // Array of Queue structures
};

// Function to initialize multiple queues
struct MultipleQueues* createMultipleQueues(int numQueues, int queueSize) {
    struct MultipleQueues *multiQueue = (struct MultipleQueues*)malloc(sizeof(struct MultipleQueues));
    multiQueue->numQueues = numQueues;
    multiQueue->queueSize = queueSize;
    multiQueue->queues = (struct Queue*)malloc(numQueues * sizeof(struct Queue));

    // Initialize each queue
    for (int i = 0; i < numQueues; i++) {
        multiQueue->queues[i].front = -1;
        multiQueue->queues[i].back = -1;
        multiQueue->queues[i].size = queueSize;
        multiQueue->queues[i].store = (int*)malloc(queueSize * sizeof(int));
    }

    return multiQueue;
}

// Function to check if a specific queue is empty
int isEmpty(struct Queue *queue) {
    return queue->front == -1;
}

// Function to check if a specific queue is full
int isFull(struct Queue *queue) {
    return (queue->back + 1) % queue->size == queue->front;
}

// Function to enqueue an element to a specific queue
void enqueue(struct MultipleQueues *multiQueue, int queueIndex, int value) {
    if (queueIndex < 0 || queueIndex >= multiQueue->numQueues) {
        printf("Invalid queue index.\n");
        return;
    }

    struct Queue *queue = &multiQueue->queues[queueIndex];

    if (isFull(queue)) {
        printf("Queue %d is full (overflow)..!!\n", queueIndex);
        return;
    }
    
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    
    queue->back = (queue->back + 1) % queue->size;
    queue->store[queue->back] = value;
    printf("Enqueued %d to queue %d.\n", value, queueIndex);
}

// Function to dequeue an element from a specific queue
void dequeue(struct MultipleQueues *multiQueue, int queueIndex) {
    if (queueIndex < 0 || queueIndex >= multiQueue->numQueues) {
        printf("Invalid queue index.\n");
        return;
    }

    struct Queue *queue = &multiQueue->queues[queueIndex];

    if (isEmpty(queue)) {
        printf("Queue %d is empty (underflow)..!!\n", queueIndex);
        return;
    }
    
    int deleteItem = queue->store[queue->front];
    printf("Dequeued item from queue %d: %d\n", queueIndex, deleteItem);

    if (queue->front == queue->back) {
        // Queue has only one element, so we reset it to empty
        queue->front = -1;
        queue->back = -1;
    } else {
        queue->front = (queue->front + 1) % queue->size;
    }
}

// Function to display all elements of a specific queue
void traverseQueue(struct MultipleQueues *multiQueue, int queueIndex) {
    if (queueIndex < 0 || queueIndex >= multiQueue->numQueues) {
        printf("Invalid queue index.\n");
        return;
    }

    struct Queue *queue = &multiQueue->queues[queueIndex];

    if (isEmpty(queue)) {
        printf("Queue %d is empty..!!\n", queueIndex);
        return;
    }

    printf("Queue %d elements:\n", queueIndex);
    int i = queue->front;
    while (1) {
        printf("%d ", queue->store[i]);
        if (i == queue->back) break;
        i = (i + 1) % queue->size;
    }
    printf("\n");
}

int main() {
    int numQueues, queueSize, choice, queueIndex, value;

    printf("Enter the number of queues: ");
    scanf("%d", &numQueues);
    printf("Enter the size of each queue: ");
    scanf("%d", &queueSize);

    struct MultipleQueues *multiQueue = createMultipleQueues(numQueues, queueSize);

    do {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter queue index (0 to %d): ", numQueues - 1);
                scanf("%d", &queueIndex);
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(multiQueue, queueIndex, value);
                break;
            case 2:
                printf("Enter queue index (0 to %d): ", numQueues - 1);
                scanf("%d", &queueIndex);
                dequeue(multiQueue, queueIndex);
                break;
            case 3:
                printf("Enter queue index (0 to %d): ", numQueues - 1);
                scanf("%d", &queueIndex);
                traverseQueue(multiQueue, queueIndex);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Free allocated memory for queues
    for (int i = 0; i < numQueues; i++) {
        free(multiQueue->queues[i].store);
    }
    free(multiQueue->queues);
    free(multiQueue);

    return 0;
}
