// 23. Implement the Max Heap tree and sort the elements. The following operations should be supported:
// a. heapify
// b. extractMax (Deleting the max element)
// c. heapsort


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Maximum size of the heap

typedef struct MaxHeap {
    int size;
    int arr[MAX_SIZE];
} MaxHeap;

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify the tree at index i
void heapify(MaxHeap* heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check if the left child is larger
    if (left < heap->size && heap->arr[left] > heap->arr[largest]) {
        largest = left;
    }

    // Check if the right child is larger
    if (right < heap->size && heap->arr[right] > heap->arr[largest]) {
        largest = right;
    }

    // If the largest is not the current node, swap and heapify again
    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        heapify(heap, largest);
    }
}

// Extract the maximum element (root) from the heap
int extractMax(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    // Store the maximum value and replace it with the last element
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // Heapify the root
    heapify(heap, 0);

    return root;
}

// Build the Max Heap
void buildMaxHeap(MaxHeap* heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        heapify(heap, i);
    }
}

// Perform heap sort
void heapSort(int* arr, int n) {
    MaxHeap heap;
    heap.size = n;

    // Copy elements to the heap's array
    for (int i = 0; i < n; i++) {
        heap.arr[i] = arr[i];
    }

    // Build the Max Heap
    buildMaxHeap(&heap);

    // Extract elements from the heap and store them in sorted order
    for (int i = n - 1; i >= 0; i--) {
        // Move current root (max) to the end
        arr[i] = extractMax(&heap);
    }
}

// Print the array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Menu driven function
void menuDriven() {
    MaxHeap heap;
    int choice, value, n, i;

    do {
        printf("\nMenu:\n");
        printf("1. Build Max Heap\n");
        printf("2. Extract Max\n");
        printf("3. Heap Sort\n");
        printf("4. Display Heap\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of elements: ");
                scanf("%d", &n);
                heap.size = n;

                printf("Enter the elements:\n");
                for (i = 0; i < n; i++) {
                    scanf("%d", &heap.arr[i]);
                }
                buildMaxHeap(&heap);
                printf("Max Heap built successfully!\n");
                break;

            case 2:
                value = extractMax(&heap);
                if (value != -1) {
                    printf("Extracted Max: %d\n", value);
                }
                break;

            case 3:
                printf("Enter number of elements for sorting: ");
                scanf("%d", &n);

                printf("Enter the elements to be sorted:\n");
                for (i = 0; i < n; i++) {
                    scanf("%d", &heap.arr[i]);
                }

                heapSort(heap.arr, n);
                printf("Sorted array: ");
                printArray(heap.arr, n);
                break;

            case 4:
                printf("Heap Elements: ");
                printArray(heap.arr, heap.size);
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

int main() {
    menuDriven();
    return 0;
}
