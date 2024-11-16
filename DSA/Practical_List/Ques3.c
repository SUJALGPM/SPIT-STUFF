#include <stdio.h>
#include <stdlib.h>

struct MultipleQueues {
    int *array;      // Array to store elements of all queues
    int *front;      // Front indices for each queue
    int *back;       // Back indices for each queue
    int numQueues;   // Number of queues
    int queueSize;   // Maximum size of each queue
};

// Function to initialize multiple queues...
struct MultipleQueues* createMultipleQueues(int numQueues, int queueSize) {
    struct MultipleQueues *multiQueue = (struct MultipleQueues*)malloc(sizeof(struct MultipleQueues));
    multiQueue->numQueues = numQueues;
    multiQueue->queueSize = queueSize;
    multiQueue->array = (int*)malloc(numQueues * queueSize * sizeof(int));
    multiQueue->front = (int*)malloc(numQueues * sizeof(int));
    multiQueue->back = (int*)malloc(numQueues * sizeof(int));

    // Initialize front and back for each queue...
    for (int i = 0; i < numQueues; i++) {
        multiQueue->front[i] = -1;
        multiQueue->back[i] = -1;
    }

    return multiQueue;
}

// Function to check if a specific queue is empty
int isEmpty(struct MultipleQueues *multiQueue, int queueIndex) {
    return multiQueue->front[queueIndex] == -1;
}

// Function to check if a specific queue is full
int isFull(struct MultipleQueues *multiQueue, int queueIndex) {
    return multiQueue->back[queueIndex] == multiQueue->queueSize - 1;
}

// Function to enqueue an element to a specific queue
void enqueue(struct MultipleQueues *multiQueue, int queueIndex, int value) {
    if (queueIndex < 0 || queueIndex >= multiQueue->numQueues) {
        printf("Invalid queue index.\n");
        return;
    }

    if (isFull(multiQueue, queueIndex)) {
        printf("Queue %d is full (overflow)..!!\n", queueIndex);
        return;
    }

    int offset = queueIndex * multiQueue->queueSize;

    if (isEmpty(multiQueue, queueIndex)) {
        multiQueue->front[queueIndex] = 0;
    }

    multiQueue->back[queueIndex]++;
    multiQueue->array[offset + multiQueue->back[queueIndex]] = value;
    printf("Enqueued %d to queue %d.\n", value, queueIndex);
}

// Function to dequeue an element from a specific queue
void dequeue(struct MultipleQueues *multiQueue, int queueIndex) {
    if (queueIndex < 0 || queueIndex >= multiQueue->numQueues) {
        printf("Invalid queue index.\n");
        return;
    }

    if (isEmpty(multiQueue, queueIndex)) {
        printf("Queue %d is empty (underflow)..!!\n", queueIndex);  
        return;
    }

    int offset = queueIndex * multiQueue->queueSize;
    int deleteItem = multiQueue->array[offset + multiQueue->front[queueIndex]];
    printf("Dequeued item from queue %d: %d\n", queueIndex, deleteItem);

    if (multiQueue->front[queueIndex] == multiQueue->back[queueIndex]) {
        // Queue has only one element, so reset it to empty
        multiQueue->front[queueIndex] = -1;
        multiQueue->back[queueIndex] = -1;
    } else {
        multiQueue->front[queueIndex]++;
    }
}

// Function to display all elements of a specific queue
void traverseQueue(struct MultipleQueues *multiQueue, int queueIndex) {
    if (queueIndex < 0 || queueIndex >= multiQueue->numQueues) {
        printf("Invalid queue index.\n");
        return;
    }

    if (isEmpty(multiQueue, queueIndex)) {
        printf("Queue %d is empty..!!\n", queueIndex);
        return;
    }

    int offset = queueIndex * multiQueue->queueSize;
    printf("Queue %d elements:\n", queueIndex);
    for (int i = multiQueue->front[queueIndex]; i <= multiQueue->back[queueIndex]; i++) {
        printf("%d ", multiQueue->array[offset + i]);
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

    // Free allocated memory
    free(multiQueue->array);
    free(multiQueue->front);
    free(multiQueue->back);
    free(multiQueue);

    return 0;
}
