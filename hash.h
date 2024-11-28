//
// Created by Cameron Brewster on 2024-11-26.
//

#ifndef HASH_H
#define HASH_H



typedef struct {
    char key[20]; //Defining the hashdata structure; intermediate step for storing data into a table
    int value;
}HASHDATA;

typedef struct HASHNODE { // Defining the Hashnode structure. This is the chain that handles collisions at an index
    char *key; //
    int value;
    struct HASHNODE *next;
}HASHNODE;

typedef struct HASHTABLE { // Defining the hashtable structure
    HASHNODE **hna;
    int size;
    int count;
}HASHTABLE;


int hash( char *key, int size);
/* The hash function
 *paramaters - pointer to input string
 * int size of the current hashtable
 * returns the index for the key to be stored based on the hashfunction
 */


HASHTABLE *new_hashtable(int size);
/* parameters - int the size of the current hashtable
 * Returns a new hashtable structure
 * creates and initializes a hashtable
 */

int hashtable_insert(HASHTABLE *ht, char *key, int value);
/* Parameters - ht pointer to hash table
 * key - pointer to the string to be inserted
 * int value the data to store
 returns 1 if successful else 0
 */



HASHNODE *hashtable_search(HASHTABLE *ht, char *key);
/* parameters ht pointer to hashtable
 * string pointer to search for
 * returns the hashnode found
 */


int hashtable_delete(HASHTABLE *ht, char *key);
/* parameters - ht pointer into the hashtable
 * a string pointer to be deleted
 * returns 1 if successful deletion else 0
 */


void hashtable_clean(HASHTABLE **ht);
/* parameters - pointer to hash table
 * clears the hashtable
 */



#endif //HASH_H




