// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            binary_tree.external.h
// Assignment:      125, I
// Date:            01/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_BINARY_TREE_EXTERNAL_H
#define IFJ2017_BINARY_TREE_EXTERNAL_H

#include <string.h>
#include "tree.binary_tree.h"

typedef struct {
    TreeNodeRef root;

    Int (* comparator)(TreeNodeRef node1, TreeNodeRef node2);

    TreeEntryDestructor destructor;
} * BinaryTreeRef, BinaryTree;

/**
 * Allocate new binary tree.
 *
 * @return Reference to created tree.
 */
BinaryTreeRef BT_create(void);

/**
 * Initialize binary tree.
 *
 * @param tree Tree to be initialized.
 * @param cmp Function for comparing nodes.
 * @param des Function for destroying node data.
 * @param keyDestructor Function for destroying key.
 */
void BT_init(BinaryTreeRef tree, Comparator cmp, TreeEntryDestructor destructor);

/**
 * Insert new node into tree.
 *
 * @param tree Where to put new node.
 * @param key Key of new node.
 * @param data Data of new node.
 */
void BT_insert(BinaryTreeRef tree, TreeKey key, DataRef data);

/**
 * Search tree for specific node.
 *
 * @param tree Where to search.
 * @param key What to search.
 *
 * @return Reference to data of found node.
 *
 * @throws NULL
 */
DataRef BT_search(BinaryTreeRef tree, TreeKey key);

/**
 * Check if binary tree has node with given key.
 *
 * @param tree Where to search.
 * @param key What to search.
 *
 * @return true if data are set.
 */
Bool BT_has(BinaryTreeRef tree, TreeKey key);

/**
 * Travers through whole tree.
 *
 * @param tree Tree to traverse.
 * @param callback Function to be called.
 * @param context Context.
 */
void BT_forEach(BinaryTreeRef tree, void (* callback)(DataRef data, ContextRef cont), ContextRef context);

/**
 * Delete node from tree.
 *
 * @param tree From where node will be deleted.
 * @param key Key of node.
 *
 * @return Data of deleted tree.
 *
 * @throws NULL
 */
TreeEntry BT_delete(BinaryTreeRef tree, TreeKey key);

/**
 *
 * @param tree
 * @param data
 * @param key
 */
void BT_deleteEntry(BinaryTreeRef tree, DataRef data, TreeKey key);

/**
 * Dispose tree.
 *
 * @param tree - Tree to be disposed.
 * @param deleteData - if true and destructor is set, data will be deleted via destructor
 */
void BT_dispose(BinaryTreeRef tree, Bool deleteData);

/**
 * Delete data and self.
 *
 * @param tree Tree to be deleted.
 */
void BT_destruct(BinaryTreeRef tree);

#endif //IFJ2017_BINARY_TREE_EXTERNAL_H

/** End of binary_tree.external.h */
