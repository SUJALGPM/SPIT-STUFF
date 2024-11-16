// 22. Implement a Min Heap tree and sort the elements. The following operations should be supported:
// a. heapify
// b. extractMin (Deleting the min element)
// c. heapsort


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Maximum size of the heap

typedef struct MinHeap {
    int size;
    int arr[MAX_SIZE];
} MinHeap;

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify the tree at index i
void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check if the left child is smaller
    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }

    // Check if the right child is smaller
    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }

    // If the smallest is not the current node, swap and heapify again
    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        heapify(heap, smallest);
    }
}

// Extract the minimum element (root) from the heap
int extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    // Store the minimum value and replace it with the last element
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // Heapify the root
    heapify(heap, 0);

    return root;
}

// Build the Min Heap
void buildMinHeap(MinHeap* heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        heapify(heap, i);
    }
}

// Perform heap sort
void heapSort(int* arr, int n) {
    MinHeap heap;
    heap.size = n;

    // Copy elements to the heap's array
    for (int i = 0; i < n; i++) {
        heap.arr[i] = arr[i];
    }

    // Build the Min Heap
    buildMinHeap(&heap);

    // Extract elements from the heap and store them in sorted order
    for (int i = 0; i < n; i++) {
        arr[i] = extractMin(&heap);
    }
}

// Print the array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Menu-driven function
void menuDriven() {
    MinHeap heap;
    int choice, value, n, i;

    do {
        printf("\nMenu:\n");
        printf("1. Build Min Heap\n");
        printf("2. Extract Min\n");
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
                buildMinHeap(&heap);
                printf("Min Heap built successfully!\n");
                break;

            case 2:
                value = extractMin(&heap);
                if (value != -1) {
                    printf("Extracted Min: %d\n", value);
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
