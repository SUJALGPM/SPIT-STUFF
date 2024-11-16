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
 
typedef struct { 
    int *table; 
    bool *occupied;  
} HashTable; 
 
int hash(int key) { 
    return key % TABLE_SIZE; 
} 
 
HashTable* createHashTable() { 
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable)); 
    ht->table = (int*)malloc(sizeof(int) * TABLE_SIZE); 
    ht->occupied = (bool*)malloc(sizeof(bool) * TABLE_SIZE); 
    for (int i = 0; i < TABLE_SIZE; i++) { 
        ht->table[i] = -1; 
        ht->occupied[i] = false; 
    } 
    return ht; 
} 
 
 
// Linear Probing 
bool linearProbingInsert(HashTable* ht, int key) { 
    int idx = hash(key); 
    int original_idx = idx; 
    int step = -1;   
     
    // Show initial hash calculation 
    printf("%d %% %d = %d\n", key, TABLE_SIZE, key % TABLE_SIZE); 
     
    while (true) { 
        // After collision, calculate next position using linear probing 
        step++; 
        idx = (original_idx + step) % TABLE_SIZE; 
        printf("Step %d: (h(%d) + %d) mod %d = %d\n",  
               step, key, step, TABLE_SIZE, idx); 
                
        // Check if current position is empty 
        if (!ht->occupied[idx]) { 
            ht->table[idx] = key; 
            ht->occupied[idx] = true; 
            printf("Inserted %d at index %d\n", key, idx); 
            return true; 
        } 
         
        // Position is occupied - show collision 
        printf("Collision occurred: position %d is occupied by %d\n",  
               idx, ht->table[idx]); 
         
        // Check if table is full 
        if (step >= TABLE_SIZE - 1) { 
            printf("Table is full! Cannot insert %d\n", key); 
            return false; 
        } 
    } 
} 
// Quadratic Probing with detailed index calculation steps 
bool quadraticProbingInsert(HashTable* ht, int key) { 
    int idx = hash(key); 
    int original_idx = idx;  
    int i = 0; 
 
    while (ht->occupied[idx]) { 
        printf("Collision occurred for %d at index %d\n", key, idx); 
        printf("Step %d: Original index = %d\n", i, original_idx); 
 
        int probe_value = (original_idx + i * i) % TABLE_SIZE; 
        printf("Step %d: (%d + %d^2) mod %d = %d (new index)\n", i, original_idx, i, 
        TABLE_SIZE, probe_value); 
 
        idx = probe_value; 
        i++; 
 
        if (i >= TABLE_SIZE) { 
            return false;  
        } 
    } 
 
    ht->table[idx] = key; 
    ht->occupied[idx] = true; 
    printf("Inserted %d at index %d\n", key, idx);  
    return true; 
} 
 
// Double Hashing 
int secondHash(int key) { 
    return PRIME - (key % PRIME);  
} 
 
bool doubleHashingInsert(HashTable* ht, int key) { 
    int idx = hash(key); 
    int original_idx = idx;  
    int step = secondHash(key); 
    int i = 0; 
 
    // Display initial hashing values 
    printf("Inserting %d:\n", key); 
    printf("h1(%d) = %d\n", key, idx); 
 
    while (ht->occupied[idx]) { 
        printf("Collision occurred for %d at index %d\n", key, idx); 
         
        printf("h2(%d) = %d - (%d mod %d) = %d\n", key, PRIME, key, PRIME, step); 
         
        // Calculate the new index 
        idx = (original_idx + (i * step)) % TABLE_SIZE;  
         
        // Show new index calculation 
        printf("Step %d: (h(%d) + %d * %d) mod %d = %d\n", i + 1, original_idx, i, step, 
        TABLE_SIZE, idx); 
 
        // Increment the probe count 
        i++; 
 
        // Check if we have looped back to the original index 
         
    } 
 
    // If the slot is empty, insert the key 
    ht->table[idx] = key; 
    ht->occupied[idx] = true; 
    printf("Inserted %d at index %d\n", key, idx); // Print the final index 
    return true; 
} 
 
 
// Display the hash table with a title 
void displayHashTable(HashTable* ht, const char* title) { 
    printf("%s:\n", title); 
    for (int i = 0; i < TABLE_SIZE; i++) { 
        if (ht->occupied[i]) { 
            printf("Index %d: %d\n", i, ht->table[i]); 
        } else { 
            printf("Index %d: Empty\n", i); 
        } 
    } 
    printf("\n"); 
} 
 
// Free the hash table 
void freeHashTable(HashTable* ht) { 
    free(ht->table); 
    free(ht->occupied); 
    free(ht); 
} 
 
int main() { 
    HashTable* ht = createHashTable(); 
    int choice, numKeys, key; 
 
    while (1) { 
        printf("Menu:\n"); 
        printf("1. Insert elements into the hash table\n"); 
        printf("2. Print the hash table\n"); 
        printf("3. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
 
        switch (choice) { 
            case 1: 
                printf("Enter the number of keys to insert (max %d): ", TABLE_SIZE); 
                scanf("%d", &numKeys); 
                if (numKeys > TABLE_SIZE) { 
                    printf("Number of keys exceeds table size.\n"); 
                    break; 
                } 
                 
                printf("Choose probing method:\n"); 
                printf("1. Linear Probing\n"); 
                printf("2. Quadratic Probing\n"); 
                printf("3. Double Hashing\n"); 
                printf("Enter your choice: "); 
                int probingChoice; 
                scanf("%d", &probingChoice); 
 
                if (probingChoice < 1 || probingChoice > 3) { 
                    printf("Invalid probing method.\n"); 
                    break; 
                } 
                 
                // Prompt user for keys 
                for (int i = 0; i < numKeys; i++) { 
                    printf("Enter key %d: ", i + 1); 
                    scanf("%d", &key); 
                    switch (probingChoice) { 
                        case 1: 
                            linearProbingInsert(ht, key); 
                            break; 
                        case 2: 
                            quadraticProbingInsert(ht, key); 
                            break; 
                        case 3: 
                            doubleHashingInsert(ht, key); 
                            break; 
                    } 
                } 
                break; 
 
            case 2: 
                displayHashTable(ht, "Hash Table"); 
                break; 
 
            case 3: 
                printf("Exist from loop..\n"); 
                return(0); 
                break; 
 
            default: 
                printf("Invalid choice. Please try again.\n"); 
        } 
    } 
 
    return 0; 
}