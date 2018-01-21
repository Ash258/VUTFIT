// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            trie.external.h
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TRIE_EXTERNAL_H
#define IFJ2017_TRIE_EXTERNAL_H

#include "../helpers.h"
#include "../list/list.external.h"
#include "../stringbuilder/string_builder.external.h"

typedef struct _TrieNode {
    char    key;
    DataRef data;
    struct _TrieNode* trie;
    struct _TrieNode* parent;
    struct _TrieNode* left;
    struct _TrieNode* right;
} TrieNode, * TrieNodeRef;

/**
 * @return instance
 */
TrieNodeRef Trie_create();

/**
 * @param root - instance
 */
void Trie_init(TrieNodeRef root);

/**
 * @param root - instance
 * @param key - data key
 * @param data - data to store
 *
 * @return Old data if given key has been already used, NULL otherwise
 */
DataRef Trie_insert(TrieNodeRef root, String key, DataRef data);

/**
 * @param root - instance
 * @param key - data key
 *
 * @return - data if key was found, NULL otherwise
 */
DataRef Trie_search(TrieNodeRef root, String key);

/**
 * @param root - instance
 * @param key - data key
 *
 * @return True if key is in trie, false otherwise
 */
Bool Trie_hasKey(TrieNodeRef root, String key);

/**
 * @param root - instance
 * @param key - data key
 *
 * @return True if data with given key are set in trie, false otherwise
 */
Bool Trie_has(TrieNodeRef root, String key);

/**
 * @param root - instance
 * @param callback - callback which will be called upon each entry
 * @param context - context for callback
 */
void Trie_forEach(TrieNodeRef root, SimpleCallback callback, ContextRef context);

/**
 * @param root - instance
 * @param key - data key
 *
 * @return data if key was found, NULL otherwise
 */
DataRef Trie_delete(TrieNodeRef root, String key);

/**
 * @param root - instance
 * @param destructor - if is set, destructor will be called on each data entry
 */
void Trie_dispose(TrieNodeRef root, SimpleDestructor destructor);

/**
 * @param root - instance
 * @param destructor - if is set, destructor will be called on each data entry
 */
void Trie_destruct(TrieNodeRef root, SimpleDestructor destructor);

/**
 * @param root - instance
 *
 * @return - all keys in instance with lexicographical order
 */
ListRef Trie_getKeys(TrieNodeRef root);

#endif //IFJ2017_TRIE_EXTERNAL_H

/** End of trie.external.h */
