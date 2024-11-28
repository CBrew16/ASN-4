//
// Created by Cameron Brewster on 2024-11-23.
//

#ifndef MYRECORD_AVL_H
#define MYRECORD_AVL_H
#include "avl.h"


typedef struct {
    AVLNODE *root;
    int count;
    float mean;
    float stddev;
} AVLDS;





void inOrder(AVLNODE *rootp_source, AVLNODE**arr, int *index);
/* Filling the array with the source tree nodes
 *
 * @param rootp - pointer to the source tree root
 * arr - pointer to an array of NODES
 * index - pointer to the index of the array
 * Helper function for merge_avl
 *
 *
 */

//Merging a tree with another tree
AVLNODE* merge_avl(AVLNODE *rootp_dest, AVLNODE *rootp_source);
//Parameters:
// rootp_dest: Pointer to the root of the destination tree.
// rootp_source: Pointer to the root of the source tree.
// Returns: Updates the destination tree with all nodes from the source tree.

AVLNODE* merge_avlds(AVLNODE* rootp_dest, AVLNODE* rootp_source);
//
// Parameters:
//  source: Pointer to the source AVLDS.
//  dest: Pointer to the destination AVLDS.
// Returns Merged tree


void calculate_stats(AVLDS* dsroot);

/* Parameters:
 * Pointer to root node of tree
 * updates standard deviation, and everything else in AVLDS struct
*/
void inOrder_values(AVLNODE *dsroot, float *values, int *index);

/*Parameters:
 *
 *Pointer to the source root
 *Function pushes all the values of the tree into an array
 *Helper function for calculate_stats
*/

void avlds_clean(AVLDS *dsroot);
/* parameters  - pointer to DS root
 * Clears the tree
 */

int remove_record(AVLDS *dsroot, char *name);
// Removes a record from the AVLDS structure by name.
//  Updates the AVL tree and recalculates the statistics.
//  Parameters:
//  dsroot: Pointer to the AVLDS.
//  name: Name of the record to be removed.
//  Returns: 1 if the record is removed; 0 otherwise.

int add_record(AVLDS *dsroot,RECORD data);
// Adds a record to the AVLDS structure.
// Updates the AVL tree and recalculates the statistics.
// Parameters:
//  dsroot: Pointer to the AVLDS.
// data: Record to be added.
// Returns: 1 if the record is added; 0 otherwise



#endif //MYRECORD_AVL_H
