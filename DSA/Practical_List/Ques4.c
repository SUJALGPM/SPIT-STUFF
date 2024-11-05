// 4. Create a data structure kQueues that represents ‘k’ queues. Implementation of kQueues
// should use only one array, i.e., k queues should use the same array for storing elements.
// Following functions must be supported by kQueues.
// a. enqueue(int x, int qn): adds x to queue number ‘qn’ where qn is from 0 to k-1.
// b. dequeue(int qn): deletes an element from queue number ‘qn’ where qn is from 0
//    to k-1.
// c. displayq( int q ): displays all the elements of the q specified.
// d. displayAll( ):displays the contents of all the queues.


#include <stdio.h>
#include <stdlib.h>

struct kQueues {
    int *arr;       // Array to store elements of all queues
    int *front;     // Front indexes of the queues
    int *rear;      // Rear indexes of the queues
    int *next;      // Next array to manage free space
    int k;          // Number of queues
    int n;          // Total size of the array
    int freeIndex;  // Index of the next free position
};

// Function to create k queues
struct kQueues* createKQueues(int k, int n) {
    struct kQueues* queues = (struct kQueues*)malloc(sizeof(struct kQueues));
    queues->k = k;
    queues->n = n;
    queues->arr = (int*)malloc(n * sizeof(int));
    queues->front = (int*)malloc(k * sizeof(int));
    queues->rear = (int*)malloc(k * sizeof(int));
    queues->next = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < k; i++) {
        queues->front[i] = -1; // Initialize front of each queue
        queues->rear[i] = -1;  // Initialize rear of each queue
    }

    // Initialize next free index and next array
    for (int i = 0; i < n; i++) {
        queues->next[i] = i + 1;
    }
    queues->next[n - 1] = -1; // No free positions left
    queues->freeIndex = 0;    // Start from the first index

    return queues;
}

// Function to check if the queue is full
int isFull(struct kQueues* queues) {
    return queues->freeIndex == -1;
}

// Function to enqueue an element into a specific queue
void enqueue(struct kQueues* queues, int x, int qn) {
    if (isFull(queues)) {
        printf("Queue Overflow! Cannot enqueue %d into queue %d.\n", x, qn);
        return;
    }

    // Get the next available index
    int insertIndex = queues->freeIndex;
    
    // Update freeIndex
    queues->freeIndex = queues->next[insertIndex];

    // Insert the element into the array
    queues->arr[insertIndex] = x;
    
    // Update next for the current rear
    queues->next[insertIndex] = -1; // End of the queue

    // If the queue is empty, set front and rear to the new index
    if (queues->rear[qn] == -1) {
        queues->front[qn] = insertIndex;
    } else {
        queues->next[queues->rear[qn]] = insertIndex; // Link the new node
    }

    queues->rear[qn] = insertIndex; // Update the rear for the queue
}

// Function to check if the queue is empty
int isEmpty(struct kQueues* queues, int qn) {
    return queues->front[qn] == -1;
}

// Function to dequeue an element from a specific queue
int dequeue(struct kQueues* queues, int qn) {
    if (isEmpty(queues, qn)) {
        printf("Queue Underflow! Cannot dequeue from queue %d.\n", qn);
        return -1; // Indicate that the queue is empty
    }

    // Get the front index
    int frontIndex = queues->front[qn];
    
    // Get the value to be dequeued
    int value = queues->arr[frontIndex];
    
    // Move front to the next node
    queues->front[qn] = queues->next[frontIndex];

    // If the front becomes -1, also set rear to -1
    if (queues->front[qn] == -1) {
        queues->rear[qn] = -1;
    }

    // Update the next array to point to the free space
    queues->next[frontIndex] = queues->freeIndex;
    queues->freeIndex = frontIndex; // Make this index available for future enqueues

    return value; // Return the dequeued value
}

// Function to display a specific queue
void displayq(struct kQueues* queues, int qn) {
    if (isEmpty(queues, qn)) {
        printf("Queue %d is empty.\n", qn);
        return;
    }

    printf("Queue %d: ", qn);
    int i = queues->front[qn];
    while (i != -1) {
        printf("%d ", queues->arr[i]);
        i = queues->next[i]; // Move to the next index
    }
    printf("\n");
}

// Function to display all queues
void displayAll(struct kQueues* queues) {
    for (int i = 0; i < queues->k; i++) {
        displayq(queues, i);
    }
}

// Main function to demonstrate kQueues
int main() {
    int k = 3; // Number of queues
    int n = 10; // Total size of the array
    struct kQueues* queues = createKQueues(k, n);

    // Enqueue elements to different queues
    enqueue(queues, 10, 0);
    enqueue(queues, 20, 0);
    enqueue(queues, 30, 1);
    enqueue(queues, 40, 1);
    enqueue(queues, 50, 2);
    enqueue(queues, 60, 2);
    
    // Display all queues
    printf("Displaying all queues:\n");
    displayAll(queues);

    // Dequeue elements from different queues
    printf("Dequeued from queue 0: %d\n", dequeue(queues, 0));
    printf("Dequeued from queue 1: %d\n", dequeue(queues, 1));

    // Display all queues after dequeue
    printf("Displaying all queues after dequeue:\n");
    displayAll(queues);

    // Clean up
    free(queues->arr);
    free(queues->front);
    free(queues->rear);
    free(queues->next);
    free(queues);

    return 0;
}
