// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            binary_tree.external.c
// Assignment:      125, I
// Date:            08/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "binary_tree.external.h"

BinaryTreeRef BT_create() {
    return (BinaryTreeRef) calloc(1, sizeof(BinaryTree));
}

void BT_init(BinaryTreeRef tree, Comparator cmp, TreeEntryDestructor des) {
    assertNotNull(tree);

    Tree_init(&tree->root);
    tree->comparator = cmp;
    tree->destructor = des;
}

void BT_insert(BinaryTreeRef tree, TreeKey key, DataRef data) {
    assertNotNull(tree);

    Tree_insert(&tree->root, key, data, tree->comparator, tree->destructor);
}

DataRef BT_search(BinaryTreeRef tree, TreeKey key) {
    assertNotNull(tree);

    return Tree_search(tree->root, key, tree->comparator);
}

void BT_forEach(BinaryTreeRef tree, void (* callback)(DataRef, ContextRef), ContextRef context) {
    assertNotNull(tree);

    Tree_forEach(tree->root, callback, context);
}

Bool BT_has(BinaryTreeRef tree, TreeKey key) {
    assertNotNull(tree);

    return BT_search(tree, key) != NULL;
}

void BT_deleteEntry(BinaryTreeRef tree, DataRef data, TreeKey key) {
    assertNotNull(tree);

    tree->destructor((TreeEntry) {.key = key, .data = data});
}

TreeEntry BT_delete(BinaryTreeRef tree, TreeKey key) {
    assertNotNull(tree);

    return Tree_delete(&tree->root, key, tree->comparator);
}

void BT_dispose(BinaryTreeRef tree, Bool deleteData) {
    assertNotNull(tree);

    Tree_dispose(&tree->root, deleteData ? tree->destructor : NULL);
}

void BT_destruct(BinaryTreeRef tree) {
    assertNotNull(tree);

    BT_dispose(tree, true);
    free(tree);
}

/** End of binary_tree.external.c */
