// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tree.binary_tree.h
// Assignment:      125, I
// Date:            13/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TREE_BINARY_TREE_H
#define IFJ2017_TREE_BINARY_TREE_H

#include "../helpers.h"

typedef Address TreeKey;

typedef struct {
    DataRef data;
    TreeKey key;
} * TreeEntryRef, TreeEntry;

typedef struct _TreeNode {
    TreeKey key;
    DataRef data;
    struct _TreeNode* left;
    struct _TreeNode* right;
} TreeNode, * TreeNodeRef;

typedef Int (* Comparator)(TreeNodeRef, TreeNodeRef);

typedef void (* TreeEntryDestructor)(TreeEntry);

/**
 * Initialize new tree.
 *
 * @param rootOfTree Root node of tree.
 */
void Tree_init(TreeNodeRef* rootOfTree);

/**
 * Insert new node into tree.
 *
 * @param rootOfTree Where to put new node.
 * @param key Key of new node.
 * @param data Data of new node.
 * @param cmp Compare function.
 * @param des Destructor function.
 */
void Tree_insert(TreeNodeRef* rootOfTree, TreeKey key, DataRef data, Comparator cmp, TreeEntryDestructor des);

/**
 * Search tree for specific node.
 *
 * @param rootOfTree Where to search.
 * @param key What to search.
 * @param cmp Compare function.
 *
 * @return Reference to data of found node.
 *
 * @throws NULL
 */
DataRef Tree_search(TreeNodeRef rootOfTree, TreeKey key, Comparator cmp);

/**
 * Delete node with given key from tree. (Don't delete data)
 *
 * @param rootOfTree Node will be deleted from this tree.
 * @param key Key of node.
 * @param cmp Compare function.
 *
 * @return Data of deleted tree.
 *
 * @throws NULL
 */
TreeEntry Tree_delete(TreeNodeRef* rootOfTree, TreeKey key, Comparator cmp);

/**
 * Traverse through whole tree.
 *
 * @param root Root of tree.
 * @param callback
 * @param context
 */
void Tree_forEach(TreeNodeRef root, void (* callback)(DataRef data, ContextRef cont), ContextRef context);

/**
 * Remove whole tree.
 *
 * @param root Root node of tree to delete.
 * @param des Destructor function.
 */
void Tree_dispose(TreeNodeRef* root, TreeEntryDestructor keyDestructor);

#endif //IFJ2017_TREE_BINARY_TREE_H

/** End of tree.binary_tree.h */
