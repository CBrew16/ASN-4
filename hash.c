//
// Created by Cameron Brewster on 2024-11-26.
//

#include "hash.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


int hash(char *key, int size) {
    int sum = 0;
    while(*key) { // Looping through the string
        sum += *key++; // Adding the ASCII values to get the total sum of all the ASCII values of the string for each character
    }
    return sum % size; // Getting the hash function
}



HASHTABLE *new_hashtable(int size) {
    HASHTABLE *ht = (HASHTABLE*)malloc(sizeof(HASHTABLE)); // Allocating memory for the hashtable
    if (!ht) { // checking if the hashtable exists
        return NULL; // Memory allocation failed
    }

    // Allocate memory for the array of HASHNODE pointers
    ht->hna = (HASHNODE**)malloc(sizeof(HASHNODE*) * size);
    if (!ht->hna) {
        free(ht); // Free the HASHTABLE structure if allocation fails
        return NULL;
    }

    // Initialize the array to NULL
    for (int i = 0; i < size; i++) { // looping  through the size of the hashtable
        ht->hna[i] = NULL; // initializing the hash array buckets to null
    }

    ht->size = size; // Initialize the hashtable
    ht->count = 0; // The number of unique entries
    return ht;
}


int hashtable_insert(HASHTABLE *ht, char *key, int value) {
    int index = hash(key, ht->size); // Get the index using the hash function

    HASHNODE *current = ht->hna[index]; // Check if the index is occupied
    HASHNODE *prev = NULL;

    // Traverse the linked list at this index
    while (current) {
        if (strcmp(current->key, key) == 0) {
            // If key exists, update the value and return 0 (indicating no insert was made)
            current->value = value;
            return 0;
        }
        prev = current;
        current = current->next;
    }

    // Key doesn't exist, so we create a new node
    HASHNODE *newNode = (HASHNODE*)malloc(sizeof(HASHNODE));
    if (!newNode) {
        return -1; // Memory allocation failed
    }

    // Allocate memory for the key and copy it
    newNode->key = strdup(key);
    if (!newNode->key) {
        free(newNode);
        return -1; // Memory allocation failed for key
    }

    // Set the value and next pointer for the new node
    newNode->value = value;
    newNode->next = NULL;

    // If no previous node exists, we are inserting at the head of the linked list at the index
    if (!prev) {
        ht->hna[index] = newNode; // Insert at the beginning
    } else {
        prev->next = newNode; // Append to the end of the list if there already is a node at that index
    }

    ht->count++; // Increment the count of elements in the hash table
    return 1; // Return 1 to indicate successful insertion
}





HASHNODE *hashtable_search(HASHTABLE *ht, char *key) {
    int index = hash(key,ht->size) ; // Calling the hash function to get index
    HASHNODE *current = ht->hna[index];

    while(current) {
        if(strcmp(current->key,key)==0) { // If key is found (first index)
            return current;
        }
        current = current -> next; // Moving to the next index if there's multiple
    }
    return NULL; // Key not found
}

int hashtable_delete(HASHTABLE *ht, char *key) {
    int index = hash(key,ht->size); // Calling the hashnode function to find the index

    HASHNODE *current = ht -> hna[index]; // Creating a pointer starting at first index
    HASHNODE *prev = NULL;

    while(current) { // Traverse the linked list bucket
        if(strcmp(current -> key, key) == 0) { // If the key is found
            if(prev) { //If the node isnt first in the list
                prev -> next = current -> next; // Moving the prev pointer so list isnt broken
            } else { // If its the first in the list
                ht -> hna[index] = current -> next; // Moving the second index in the list to the front
            }
            free(current -> key); // Freeing the desired key
            ht->count --;
            return 1;
        }
        prev = current; // Moving the list pointers
        current = current -> next;
    }
    return 0; // Key not found
}

void hashtable_clean(HASHTABLE **ht) {
    if(!ht ||!*ht) {
        return; // Edge case if hash table DNE
    }

    for(int i = 0; i < (*ht) -> size; i++) {
        HASHNODE *current = (*ht) -> hna[i]; // Start at the lowest array bucket
        while(current) { // Traverse the linked list
            HASHNODE *temp = current; // Creating a temp so the list isnt broken
            current = current -> next; // Advancing pointers
            free(temp->key);
            free(temp); // Freeing the desired key and its pointer
        }
    }
    free((*ht) -> hna); // Freeing the hashtable and hash node array
    free(*ht);
    *ht = NULL;
}


