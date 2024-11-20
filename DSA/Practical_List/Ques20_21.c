// 20. Write a program to implement a Hash Table using linear probing as the collision resolution strategy. The table should support the following operations:
// a. Insert
// b. Search

// 21. Write a program to implement a Hash Table using quadratic probing as the collision resolution strategy. The table should support the following operations:
// a. Insert
// b. Search

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define PRIME 7 

struct HashTable {
    int *table;        // Hash table array
    bool *occupied;    // Boolean array to track occupied slots
};

// Initialize hash table
struct HashTable* createHashTable() {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->table = (int*)malloc(sizeof(int) * TABLE_SIZE);
    ht->occupied = (bool*)malloc(sizeof(bool) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = -1;
        ht->occupied[i] = false;
    }
    return ht;
}

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Linear probing for collision resolution
void insertLinear(struct HashTable *hashTable, int key) {
    int index = hashFunction(key);
    int originalIndex = index; // 2
    int i = 0;

    while (hashTable->occupied[index]) {
        i++;
        index = (originalIndex + i) % TABLE_SIZE; 
        if (index == originalIndex) {
            printf("Hash table is full. Cannot insert key: %d\n", key);
            return;
        }
    }

    hashTable->table[index] = key;
    hashTable->occupied[index] = true;
    printf("Inserted key %d at index %d using linear probing.\n", key, index);
}

// Quadratic probing for collision resolution
void insertQuadratic(struct HashTable *hashTable, int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int i = 0;

    while (hashTable->occupied[index]) {
        index = (originalIndex + i * i) % TABLE_SIZE; 
        i++;
        if (i >= TABLE_SIZE) {
            printf("Hash table is full. Cannot insert key: %d\n", key);
            return;
        }
    }

    hashTable->table[index] = key;
    hashTable->occupied[index] = true;
    printf("Inserted key %d at index %d using quadratic probing.\n", key, index);
}

// Display hash table
void displayTable(struct HashTable *hashTable) {
    printf("Index\tValue\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t%d\n", i, hashTable->table[i]);
    }
}

// Main function
int main() {
    struct HashTable* ht = createHashTable();

    int choice, key;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert using Linear Probing\n");
        printf("2. Insert using Quadratic Probing\n");
        printf("3. Display Hash Table\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key to insert (Linear Probing): ");
            scanf("%d", &key);
            insertLinear(ht, key);
            break;
        case 2:
            printf("Enter key to insert (Quadratic Probing): ");
            scanf("%d", &key);
            insertQuadratic(ht, key);
            break;
        case 3:
            displayTable(ht);
            break;
        case 4:
            free(ht->table);
            free(ht->occupied);
            free(ht);
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
