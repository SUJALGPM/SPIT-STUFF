// 16. Write a program to represent the given graph using adjacency matrix and implement Breadth-First Search Traversal for a given Graph.
// 17. Write a program to represent the given graph using adjacency linked list and implement Breadth-First Search Traversal for a given Graph.
// 18. Write a program to represent the given graph using adjacency matrix and implement Depth First Search Traversal for a given graph
// 19. Write a program to represent the given graph using adjacency linked list and implement Depth First Search Traversal for a given graph.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int level[MAX]; // BFS levels

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
};

struct Graph {
    int vertices;
    struct List* array;
};

struct Queue {
    int size;
    int front;
    int rear;
    int *arr;
};

// Function to enqueue an element to the queue
void enqueue(struct Queue *q, int i) {
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = i;
}

// Function to dequeue an element from the queue
int dequeue(struct Queue *q) {
    if (q->front == -1) {
        return -1;
    }
    int x = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->size;
    }
    return x;
}

// BFS function for adjacency matrix representation
void bfsMatrix(int adj[MAX][MAX], int V, int s) {
    struct Queue q;
    q.size = MAX;
    q.front = -1;
    q.rear = -1;
    q.arr = (int *)malloc(q.size * sizeof(int));

    bool visited[MAX] = {false};
    int bfsTraversal[MAX];
    int index = 0;

    for (int i = 0; i < MAX; i++) {
        level[i] = -1;
    }
    level[s] = 0;
    visited[s] = true;
    enqueue(&q, s);
    while (q.front != -1) {
        int curr = dequeue(&q);
        bfsTraversal[index++] = curr;

        for (int j = 0; j < V; j++) {
            if (adj[curr][j] == 1 && !visited[j]) {
                visited[j] = true;
                level[j] = level[curr] + 1;
                enqueue(&q, j);
            }
        }
    }

    printf("BFS Traversal (Matrix): ");
    for (int i = 0; i < index; i++) {
        printf("%d ", bfsTraversal[i]);
    }
    printf("\n");
    free(q.arr);
}

// DFS function for adjacency list representation
void DFS(struct Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    struct Node* currentNode = graph->array[vertex].head;
    while (currentNode) {
        int adjacentVertex = currentNode->data;
        if (!visited[adjacentVertex]) {
            DFS(graph, adjacentVertex, visited);
        }
        currentNode = currentNode->next;
    }
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices (adjacency list)
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->array = (struct List*)malloc(vertices * sizeof(struct List));

    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to the graph (adjacency list)
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the adjacency list of the graph
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->vertices; v++) {
        struct Node* temp = graph->array[v].head;
        printf("Adjacency list of vertex %d: ", v);
        while (temp) {
            printf("-> %d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

// DFS function for adjacency matrix representation
void dfsMatrix(int adj[MAX][MAX], int V, int visited[], int v) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < V; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            dfsMatrix(adj, V, visited, i);
        }
    }
}

// Main function to implement all the operations
int main() {
    int V, edges, startVertex, choice;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    struct Graph* graph = createGraph(V);
    int adj[MAX][MAX] = {0};

    for (int i = 0; i < edges; i++) {
        int u, v;
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    printf("\nAdjacency List Representation:\n");
    printGraph(graph);

    do {
        printf("\nMenu:\n");
        printf("1. Perform DFS (Adjacency Matrix)\n");
        printf("2. Perform BFS (Adjacency Matrix)\n");
        printf("3. Perform DFS (Adjacency List)\n");
        printf("4. Perform BFS (Adjacency List)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // DFS (Adjacency Matrix)
                printf("\nDFS starting from which vertex? ");
                scanf("%d", &startVertex);
                int visitedDFS[MAX] = {0};
                printf("DFS Traversal (Matrix): ");
                dfsMatrix(adj, V, visitedDFS, startVertex);
                printf("\n");
                break;

            case 2: // BFS (Adjacency Matrix)
                printf("\nBFS starting from which vertex? ");
                scanf("%d", &startVertex);
                bfsMatrix(adj, V, startVertex);
                break;

            case 3: // DFS (Adjacency List)
                printf("\nDFS starting from which vertex? ");
                scanf("%d", &startVertex);
                bool visitedDFSList[MAX] = {false};
                printf("DFS Traversal (List): ");
                DFS(graph, startVertex, visitedDFSList);
                printf("\n");
                break;

            case 4: // BFS (Adjacency List)
                printf("\nBFS starting from which vertex? ");
                scanf("%d", &startVertex);
                bfsMatrix(adj, V, startVertex); // Same BFS function can be reused
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 5);

    // Free memory
    for (int i = 0; i < V; i++) {
        struct Node* current = graph->array[i].head;
        while (current) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
