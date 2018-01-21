// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            trie.external.c
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "trie.external.h"

void Trie_init(TrieNodeRef root) {
    root->key   = '\0';
    root->left  = NULL;
    root->right = NULL;
    root->trie  = NULL;
    root->data  = NULL;
}

static TrieNodeRef Trie_createTrieNode(char key) {
    TrieNodeRef ref = calloc(1, sizeof(TrieNode));
    ref->key = key;

    return ref;
}

static DataRef _Trie_insert(TrieNodeRef* root, String key, DataRef data) {
    assertNotNull(key);

    if (*root == NULL) {
        *root = Trie_createTrieNode(*key);
        if (*(++key) == '\0') {
            (*root)->data = data;
        } else {
            _Trie_insert(&(*root)->trie, key, data);
        }

        return NULL;
    }

    if (*key == (*root)->key) {
        if (*(++key) == '\0') {
            DataRef old = (*root)->data;
            (*root)->data = data;

            return old;
        }

        return _Trie_insert(&((*root)->trie), key, data);
    } else {
        return _Trie_insert(*key < (*root)->key ? &(*root)->left : &(*root)->right, key, data);
    }
}

DataRef Trie_insert(TrieNodeRef root, String key, DataRef data) {
    return _Trie_insert(&root, key, data);
}

static TrieNodeRef Trie_searchNode(TrieNodeRef root, String key) {
    assertNotNull(key);
    IF_NULL_RETURN_NULL(root);

    if (*key == root->key) {
        return *(++key) == '\0' ? root : Trie_searchNode(root->trie, key);
    } else {
        return Trie_searchNode(*key < root->key ? root->left : root->right, key);
    }
}

DataRef Trie_search(TrieNodeRef root, String key) {
    TrieNodeRef node = Trie_searchNode(root, key);

    return node != NULL ? node->data : NULL;
}

static bool _Trie_hasKey(TrieNodeRef root, String key) {
    if (root == NULL) return false;

    if (*key == root->key) {
        return *(++key) == '\0' ? true : _Trie_hasKey(root->trie, key);
    } else {
        return _Trie_hasKey(*key < root->key ? root->left : root->right, key);
    }
}

Bool Trie_hasKey(TrieNodeRef root, String key) {
    return _Trie_hasKey(root, key);
}

Bool Trie_has(TrieNodeRef root, String key) {
    return Trie_search(root, key) != NULL;
}

static void Trie_keyTraverse(TrieNodeRef root, StringBuilderRef builder, ListRef keys) {
    IF_NULL_RETURN_VOID(root);

    Trie_keyTraverse(root->left, builder, keys);

    StringBuilder_append(builder, root->key);
    if (root->data != NULL) {
        List_push(keys, StringBuilder_build(builder, false));
    }

    Trie_keyTraverse(root->trie, builder, keys);

    StringBuilder_removeLast(builder);

    Trie_keyTraverse(root->right, builder, keys);
}

ListRef Trie_getKeys(TrieNodeRef root) {
    StringBuilder builder;
    StringBuilder_init(&builder);
    ListRef keys = List_create(simpleDestructor);
    Trie_keyTraverse(root, &builder, keys);
    StringBuilder_dispose(&builder);

    return keys;
}

static void Trie_replaceByTheRightMost(TrieNodeRef* root, TrieNodeRef replaced) {
    assertNotNull(*root);
    IF_NULL_RETURN_VOID(root);

    if ((*root)->right) {
        Trie_replaceByTheRightMost(&((*root)->right), replaced);
    } else {
        replaced->key  = (*root)->key;
        replaced->data = (*root)->data;
        TrieNodeRef aux = *root;
        *root = (*root)->left;
        free(aux);
    }
}

static void Trie_deleteNode(TrieNodeRef* root) {
    TrieNodeRef aux = *root;

    if (aux->left != NULL && aux->right != NULL) {
        Trie_replaceByTheRightMost(&(*root)->left, aux);
    } else {
        (*root) = aux->right != NULL ? aux->right : aux->left;
        free(aux);
    }
}

static DataRef _Trie_delete(TrieNodeRef* root, String key) {
    IF_NULL_RETURN_NULL(*root);

    if (*key == (*root)->key) {
        if (*(++key) == '\0') {
            DataRef data = (*root)->data;
            (*root)->data = NULL;

            //delete node if is not suffix
            if ((*root)->trie == NULL) Trie_deleteNode(root);
            return data;
        }

        DataRef data = _Trie_delete(&((*root)->trie), key);
        if ((*root)->trie == NULL && (*root)->data == NULL) Trie_deleteNode(root);

        return data;
    } else {
        return _Trie_delete(*key < (*root)->key ? &(*root)->left : &(*root)->right, key);
    }
}

DataRef Trie_delete(TrieNodeRef root, String key) {
    return _Trie_delete(&root, key);
}

void Trie_dispose(TrieNodeRef root, SimpleDestructor destructor) {
    assertNotNull(root);

    Trie_destruct(root->left, destructor);
    Trie_destruct(root->right, destructor);
    Trie_destruct(root->trie, destructor);

    root->left  = NULL;
    root->right = NULL;
    root->trie  = NULL;
}

void Trie_destruct(TrieNodeRef root, SimpleDestructor destructor) {
    if (root != NULL) {
        Trie_destruct(root->left, destructor);
        Trie_destruct(root->right, destructor);
        Trie_destruct(root->trie, destructor);

        if (root->data != NULL && destructor != NULL) destructor(root->data);
        free(root);
    }
}

void Trie_forEach(TrieNodeRef root, SimpleCallback callback, ContextRef context) {
    IF_NULL_RETURN_VOID(root);

    if (root->data != NULL) callback(root->data, context);

    Trie_forEach(root->trie, callback, context);
    Trie_forEach(root->left, callback, context);
    Trie_forEach(root->right, callback, context);
}

TrieNodeRef Trie_create() {
    TrieNodeRef ref = HeapRegister_allocate(G_UNDEFINED, sizeof(TrieNode));
    Trie_init(ref);

    return ref;
}

/** End of trie.external.c */
