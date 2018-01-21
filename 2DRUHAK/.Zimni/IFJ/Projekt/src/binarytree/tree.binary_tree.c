// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tree.binary_tree.c
// Assignment:      125, I
// Date:            13/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "tree.binary_tree.h"

static TreeNode prototype;

//region Internals

/**
 * Set prototype properties.
 *
 * @param key Key of node.
 * @param data Data of node.
 */
TreeNodeRef setPrototype(TreeKey key, DataRef data) {
    prototype.key  = key;
    prototype.data = data;

    return &prototype;
}

/**
 * Helper function for delete the most right node.
 *
 * @param rootOfTree Root node of tree.
 * @param replaced Where will be node moved.
 */
DataRef replaceByTheRightMost(TreeNodeRef* rootOfTree, TreeNodeRef replaced) {
    assertNotNull(*rootOfTree);
    IF_NULL_RETURN_NULL(rootOfTree);

    if ((*rootOfTree)->right) {
        return replaceByTheRightMost(&((*rootOfTree)->right), replaced);
    } else {
        replaced->key  = (*rootOfTree)->key;
        replaced->data = (*rootOfTree)->data;
        TreeNodeRef aux = *rootOfTree;
        *rootOfTree = (*rootOfTree)->left;
        free(aux);
    }

    return NULL;
}

static TreeNodeRef Tree_createNode(TreeKey key, DataRef data) {
    assertNotNull(data);
    assertNotNull(key);

    TreeNodeRef new = (TreeNodeRef) malloc(sizeof(TreeNode));
    IF_NULL_RETURN_NULL(new);

    new->key  = key;
    new->data = data;
    new->left = new->right = NULL;

    return new;
}

//endregion Internals

void Tree_init(TreeNodeRef* rootOfTree) {
    *rootOfTree = NULL;
}

void Tree_insert(TreeNodeRef* rootOfTree, TreeKey key, DataRef data, Comparator cmp, TreeEntryDestructor des) {
    assertNotNull(key);
    assertNotNull(data);

    if (*rootOfTree == NULL) {
        *rootOfTree = Tree_createNode(key, data);
        return;
    }

    int result = cmp(*rootOfTree, setPrototype(key, NULL));

    if (result == 0) {
        des((TreeEntry) {(*rootOfTree)->data, (*rootOfTree)->key});
        (*rootOfTree)->data = data;
        (*rootOfTree)->key  = key;
    } else if (result > 0) {
        Tree_insert(&(*rootOfTree)->left, key, data, cmp, des);
    } else {
        Tree_insert(&(*rootOfTree)->right, key, data, cmp, des);
    }
}

DataRef Tree_search(TreeNodeRef rootOfTree, TreeKey key, Comparator cmp) {
    assertNotNull(key);
    IF_NULL_RETURN_NULL(rootOfTree);

    int result = cmp(rootOfTree, setPrototype(key, NULL));

    if (result == 0) {
        return rootOfTree->data;
    } else if (result > 0) {
        return Tree_search(rootOfTree->left, key, cmp);
    } else {
        return Tree_search(rootOfTree->right, key, cmp);
    }
}

void Tree_forEach(TreeNodeRef root, void (* callback)(Address, Address), Address context) {
    IF_NULL_RETURN_VOID(root);

    Tree_forEach(root->left, callback, context);
    Tree_forEach(root->right, callback, context);
    callback(root->data, context);
}

TreeEntry Tree_delete(TreeNodeRef* rootOfTree, TreeKey key, Comparator cmp) {
    if (*rootOfTree == NULL) return (TreeEntry) {.key = NULL, .data = NULL};

    int result = cmp(*rootOfTree, setPrototype(key, NULL));

    DataRef retData = NULL;
    TreeKey retKey  = NULL;

    if (result > 0) {
        return Tree_delete(&(*rootOfTree)->left, key, cmp);
    } else if (result < 0) {
        return Tree_delete(&(*rootOfTree)->right, key, cmp);
    } else if (result == 0) {
        TreeNodeRef aux = *rootOfTree;
        retData = aux->data;
        retKey  = aux->key;
        if (!aux->right) {
            *rootOfTree = aux->left;
            free(aux);
        } else if (!aux->left) {
            *rootOfTree = aux->right;
            free(aux);
        } else {
            replaceByTheRightMost(&(*rootOfTree)->left, *rootOfTree);
        }
    }

    return (TreeEntry) {.data = retData, .key = retKey};
}

static void Tree_deleteData(TreeNodeRef tree, TreeEntryDestructor des) {
    if (des) des((TreeEntry) {.data = tree->data, .key = tree->key});
}

void Tree_dispose(TreeNodeRef* root, TreeEntryDestructor des) {
    if (*root) {
        Tree_dispose(&(*root)->left, des);
        Tree_dispose(&(*root)->right, des);
        Tree_deleteData(*root, des);

        free(*root);
        Tree_init(root);
    }
}

/** End of tree.binary_tree.c */
