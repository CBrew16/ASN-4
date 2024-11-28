//
// Created by Cameron Brewster on 2024-11-23.
//

#include "mway_tree.h"

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

TNODE *create_node() {
    TNODE *newNode = (TNODE*)malloc(sizeof(TNODE)); // Allocating memory
    if(newNode == NULL) { // Edge case if memory allocation fails
        return NULL;
    }

    newNode -> count = 0; // Initializing values of node

    for(int i = 0; i <m-1  ; i++) { // initializing the keys
        newNode -> key[i] = 0;
    }
    for(int i = 0; i<m; i++) { // Initializing the child pointers
        newNode -> child[i] = NULL;
    }

    return newNode; // Return the newNode created
}

void split_node(TNODE **parent, int index) {
    TNODE *fullNode= (*parent) -> child[index]; // Accessing the child  to be split
    TNODE *newNode = create_node(); // Creating a new node for the split process

    int middle = (m-1)/2;

    newNode -> count = fullNode ->count -middle -1; // Update number of keys in newNode
    for(int i = 0; i<newNode -> count; i++) { // Looping through the number of keys in newNode
        newNode -> key[i] = fullNode->key[middle +1 + i]; // setting the keys in newNode to the right half of the keys
    }

    if(fullNode -> child[0] != NULL) { // If the child pointer isn't null(Not a leaf)
        for(int i =0; i<= newNode ->count; i++) {//Looping through the count of keys in newNode
            newNode->child[i] = fullNode ->child[middle +i +1]; // Setting newNode's child pointers
        }
    }
    fullNode-> count = middle; //Changing the count of the split node


    for(int i = (*parent) -> count; i>index;i--) { //levelling up the middle key to the parent node
        (*parent)->key[i] = (*parent)->key[i-1]; // Determining the proper position for the key to be added
        (*parent)->child[i +1] = (*parent) -> child[i]; // Shifting the child subtrees
    }
        (*parent) ->key[index] = fullNode->key[middle]; // Setting the values in the new parent with middle key levelled up
        (*parent) -> child[index+1] = newNode; // Setting the parent's pointer to the newNode that was created from the split; This is +1 as its bigger that the orginal node split
        (*parent) -> count++; // Incrementing the key count in parent

}


TNODE *insert_key(TNODE **root, int key) {

    if(*root ==NULL) { //Edge case if the tree DNE
        *root = create_node();
        (*root) -> key[0] = key;
        (*root) -> count = 1; // Initializing values
        return *root;
    }

    if((*root) -> count == m-1) { // If the root node is full it requires splitting
        TNODE* newRoot = create_node(); // Creating a new root;
        newRoot -> child[0] = *root; //Adding newRoot to the children of root
        *root = newRoot;

        split_node(root,0); // Calling the split node function
    }

    TNODE *current = *root;

    while(current->child[0] != NULL) { // Traversing the child nodes
        int i;
        for(i = 0; i<current -> count; i++) {
            //Looping through the key count
            if(key < current -> key[i]) {// Breaking the loop when the correct subtree is found
                break;
            }
        }

        if(current -> child[i] -> count == m-1) { // If the child if full
            split_node(&current,i); // calling the split node function
            if(key> current ->key[i]) {
                i++; // Finding the proper subtree after the split
            }
        }
        current = current -> child[i];
    }

        int i;
        for(i = current -> count-1; i>= 0 && key< current -> key[i]; i--) { // Looping though the keys in the node that the level up occurs
            current -> key[i+1] = current -> key[i]; // Finding the insertion place for the key
        }
    current -> key[i+1] = key; // Inserting the key into the root
    current -> count ++; // Incrementing the root's count
    return *root;
}

int search_key(TNODE *root, int key) {
    if(root == NULL) {
        return 0; // Edge case if tree DNE
    }

    TNODE *node = root;
    int i = 0 ;

    while (i<node->count && key > node -> key[i]){ // Traversing the keys in the current node to find the currect subtree
        i++;
    }
    if(i<node -> count && key == node->key[i]) { // Check if the key is in current node
        return 1;
    }
    return search_key(node->child[i],key); // Recursively search to find the right child
}


void print_inorder(TNODE *root) {
    if(root == NULL) {
        return; //Edge case if tree DNE
    }

    TNODE* node=  root;



    for(int i = 0; i<root->count; i++) {
        print_inorder(root->child[i]); // Recursive call sending in each left subtree
        printf("%d ", root -> key[i]); // printing the key

    }
    print_inorder(root->child[root->count]); // Recursively calling the right subtree

}

void display_tree(TNODE *root) {
    // Track the level
    static int level = 0;
    if(root == NULL) {
        if(level == 0) { //Edge case level is 0 and tree DNE
            printf("Tree does not exist \n");
        }
      return;
    }


    for(int i =0; i<level; i++) {
        printf("  ");
    }
    printf("Node keys: ");
    for(int i =0; i<root -> count; i++) { // Looping through the node
        printf("%d ", root->key[i]); // Printing the keys
    }
    printf("\n");

    for(int i = 0; i<= root-> count; i++) { // Printing the children
        if(root->child[i] != NULL) {
            for(int j = 0; j < level; j++) {
                printf("  ");
            }
            printf("Child %d ->\n", i);

            level++; // incrementing level
            display_tree(root->child[i]); // Recursively calling the function sending in the next child
            level--; // Decrementing level
        }
    }
}

int delete_key(TNODE **root, int key) {
    if (*root == NULL) {
        return 0; // Tree does not exist
    }

    TNODE *current = *root;
    int i;


    for (i = 0; i < current->count && key > current->key[i]; i++) {} // Search for key

    // Key found in the current node
    if (i < current->count && key == current->key[i]) {
        if (current->child[0] == NULL) {
            // Case: Key in a leaf node
            for (int j = i; j < current->count - 1; j++) {
                current->key[j] = current->key[j + 1]; // Shifting the keys in node before deletion
            }
            current->count--; // Decrement key count

            // Handle underflow in the root if the node becomes empty
            if (current->count == 0 && current == *root) {
                *root = NULL;
                free(current);
            }
            return 1;
        } else {
            // Key in an internal node
            TNODE *successor = current->child[i + 1];
            while (successor->child[0] != NULL) { //Finding the leftmost successor to replace the current key with
                successor = successor->child[0];
            }
            current->key[i] = successor->key[0]; // Replacing the key
            return delete_key(&(current->child[i + 1]), successor->key[0]); // Recursively calling delete to delete successor's leaf node
        }
    }


    if (current->child[0] != NULL) { // Recursive search to child if key isnt found in current node
        int result = delete_key(&(current->child[i]), key);

        // Fix underfull nodes
        if (current->child[i] != NULL && current->child[i]->count < (m - 1) / 2) {
            TNODE *left_sibling = (i > 0) ? current->child[i - 1] : NULL;
            TNODE *right_sibling = (i < current->count) ? current->child[i + 1] : NULL;

            if (left_sibling && left_sibling->count >= (m - 1) / 2) { // if the sibiling has sufficient keys
                // Borrow from left sibling
                for (int j = current->child[i]->count; j > 0; j--) { // Looping through its keys
                    current->child[i]->key[j] = current->child[i]->key[j - 1]; // Shifting the keys
                }
                current->child[i]->key[0] = current->key[i - 1];
                if (current->child[i]->child[0] != NULL) {
                    for (int j = current->child[i]->count + 1; j > 0; j--) {
                        current->child[i]->child[j] = current->child[i]->child[j - 1]; // Shifting children if necessary
                    }
                    current->child[i]->child[0] = left_sibling->child[left_sibling->count]; // performing the switch
                }
                current->key[i - 1] = left_sibling->key[left_sibling->count - 1]; //adjusting the key count
                left_sibling->count--;
                current->child[i]->count++;
            } else if (right_sibling && right_sibling->count >= (m - 1) / 2) {// borrow from right sibling if it has enough keys
                current->child[i]->key[current->child[i]->count] = current->key[i];// shifting the keys
                if (current->child[i]->child[0] != NULL) {
                    current->child[i]->child[current->child[i]->count + 1] = right_sibling->child[0];
                }
                current->key[i] = right_sibling->key[0]; //performing the switch
                for (int j = 0; j < right_sibling->count - 1; j++) {
                    right_sibling->key[j] = right_sibling->key[j + 1];
                }
                if (right_sibling->child[0] != NULL) {
                    for (int j = 0; j < right_sibling->count; j++) {
                        right_sibling->child[j] = right_sibling->child[j + 1]; // Shifting the children if necessary
                    }
                }
                right_sibling->count--;
                current->child[i]->count++;
            } else {
                // Merge nodes
                if (left_sibling) { // Merge into left sibling
                    left_sibling->key[left_sibling->count] = current->key[i - 1]; // moving the first key
                    for (int j = 0; j < current->child[i]->count; j++) { // Looping and moving all the keys from the current node child[i] to the left
                        left_sibling->key[left_sibling->count + 1 + j] = current->child[i]->key[j];
                    }
                    for (int j = 0; j <= current->child[i]->count; j++) {
                        left_sibling->child[left_sibling->count + 1 + j] = current->child[i]->child[j]; // Moving all the children from current node child[i] left
                    }
                    left_sibling->count += current->child[i]->count + 1; // Updating the count in left node (adding the current node's count)
                    free(current->child[i]); //freeing current child

                    // Shift parent's keys and children
                    for (int j = i - 1; j < current->count - 1; j++) {
                        current->key[j] = current->key[j + 1];
                        current->child[j + 1] = current->child[j + 2];
                    }
                    current->count--;

                    if (current->count == 0 && current == *root) {
                        *root = left_sibling;
                        free(current);
                    }
                } else if (right_sibling) {  //Instead Merge with right sibling if its not full - bring the right sibiling into current node

                    current->child[i]->key[current->child[i]->count] = current->key[i]; //Moving key I to the right child
                    for (int j = 0; j < right_sibling->count; j++) {
                        current->child[i]->key[current->child[i]->count + 1 + j] = right_sibling->key[j]; // Moving all keys from right to the current child
                    }
                    for (int j = 0; j <= right_sibling->count; j++) {
                        current->child[i]->child[current->child[i]->count + 1 + j] = right_sibling->child[j];
                    }
                    current->child[i]->count += right_sibling->count + 1; // Updating the count
                    free(right_sibling);

                    for (int j = i; j < current->count - 1; j++) { // Shifting the keys in the current node and children
                        current->key[j] = current->key[j + 1];
                        current->child[j + 1] = current->child[j + 2];
                    }
                    current->count--;

                    if (current->count == 0 && current == *root) { // if the node is empty and its the root
                        *root = current->child[i]; // Set the root to the new child
                        free(current);
                    }
                }
            }
        }

        return result;
    }

    return 0; // Key not found
}
