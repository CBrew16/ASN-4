//
// Created by Cameron Brewster on 2024-11-23.
//

#ifndef MWAY_TREE_H
#define MWAY_TREE_H
#define m 4

typedef struct node {
    int count; // number of keys in the node
    int key[m-1]; // array to hold up to m-1 keys
    struct node *child[m]; // array of pointers to child nodes
} TNODE;



TNODE *create_node();
/*
 *Parameters - none
 *returns a pointer to created node
 */

TNODE *insert_key(TNODE **root, int key);

/*
 *Paramerters - pointer to root node
 *Int key to be inserted
 *returns new tree
*/

void split_node(TNODE **parent, int index);
// A helpter function for insert that splits nodes
//Additionally it moves the middle key up to the parent Node
//paremeters : accepts a pointer to the pointer of the parent node that requires splitting
//Accepts the index of the child in the subtree to be split

int search_key(TNODE *root, int key);
/*
 *parameters - pointer to root node
 *key to search for
 *returns 1 if found else 0
 */

void print_inorder(TNODE *root);
/*
 *Parameters - pointer to root
 *prints the tree in order
 */

void display_tree(TNODE *root);
/*
 * parameters - pointer to the root node
 * displays the tree
 */

int delete_key(TNODE **root, int key);
/*
 *parameters - a pointer to the root pointer
 * A key integer to be deleted
 *
 * returns 1 for success else 0
 */




#endif