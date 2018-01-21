// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            list.external.h
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_LIST_EXTERNAL_H
#define IFJ2017_LIST_EXTERNAL_H

#include "../helpers.h"

typedef struct _ListElement {
    struct _ListElement* prev;
    struct _ListElement* next;
    DataRef data;
} * ListElementRef, ListElement;

typedef struct {
    ListElementRef first;
    ListElementRef last;

    void (* destructor)(DataRef);

    UnsignedInt size;
} * ListRef, List;

typedef bool (* ListCallback)(DataRef, ContextRef);

typedef DataRef (* ListMapper)(DataRef, ContextRef);

/**
 * @param destructor - data entry destructor
 * @return instance
 */
ListRef List_create(SimpleDestructor destructor);

/**
 * Initialize given list.
 *
 * @param ref
 */
void List_init(ListRef ref, SimpleDestructor destructor);

/**
 * @param list - instance
 * @return First entry in list
 */
DataRef List_first(ListRef list);

/**
 * @param list - instance
 * @return Last entry in list
 */
DataRef List_last(ListRef list);

/**
 * Add entry to end of list.
 *
 * @param list - instance
 * @param entry - entry to add
 */
void List_push(ListRef list, DataRef entry);

/**
 * Add entry to start of list.
 *
 * @param list - instance
 * @param entry - entry to add
 */
void List_unshift(ListRef list, DataRef entry);

/**
 * Delete entry at the end of list.
 *
 * @param list - instance
 */
DataRef List_pop(ListRef list);

/**
 * Delete entry at the start of list.
 *
 * @param list - instance
 */
DataRef List_shift(ListRef list);

/**
 * Remove first occurance of entry in list.
 *
 * @param list - instance
 * @param entry = entry to remove
 */
void List_remove(ListRef list, DataRef entry);

/**
 * Delete entry by list destructor
 *
 * @param list - instance
 * @param entry = entry to remove
 */
void List_delete(ListRef list, DataRef entry);

/**
 * Remove all occurances of entry in list.
 *
 * @param list - instance
 * @param entry = entry to remove
 */
void List_removeAll(ListRef list, DataRef entry);

/**
 * @param list - instance
 * @return True if list is empty, false otherwise
 */
Bool List_isEmpty(ListRef list);

/**
 * @param list - instance
 * @return - List size
 */
Int List_size(ListRef list);

/**
 * @param list - instance
 * @param comparator - callback for entry comparison
 * @param context - context or callback
 *
 * @return Entry if found, NULL otherwise
 */
DataRef List_search(ListRef list, ListCallback comparator, ContextRef context);

/**
 * @param list - instance
 * @param comparator - callback for entry comparison
 * @param context - context or callback
 *
 * @return True if comparator return true, false otherwise
 */
Bool List_contains(ListRef list, ListCallback comparator, ContextRef context);

/**
 * @param list - instance
 * @param entry - searched entry
 *
 * @return True if list has entry, false otherwise
 */
Bool List_has(ListRef list, DataRef entry);

/**
 * @param list  - instance
 * @param callback - callback for entry. If callback returns false, iteration will stop.
 * @param context - context for callback
 */
void List_forEach(ListRef list, ListCallback callback, ContextRef context);

/**
 * @param list  - instance
 * @param callback - callback for mapper.
 * @param context - context for callback
 */
void List_mapEach(ListRef list, ListMapper callback, ContextRef context);

/**
 * @param list  - instance
 * @param callback - callback for entry. If callback returns false, iteration will stop.
 * @param context - context for callback
 */
void List_forEachReverse(ListRef list, ListCallback callback, ContextRef context);

/**
 * Reverse all elements in list
 *
 * @param list - instance
 */
void List_reverse(ListRef list);

/**
 * Delete all entries in list.
 *
 * @param list - instance
 * @param deleteData - if true and destructor is set, data will be deleted via destructor
 */
void List_dispose(ListRef list, Bool deleteData);

/**
 * Compare two lists,
 *
 * @param firstList ListRef to compare.
 * @param secondList ListRef to compare.
 * @param callback Comparator callback
 *
 * @return true if callback returns true for all cases, false otherwise
 */
Bool List_equals(ListRef firstList, ListRef secondList, ListCallback callback);

/**
 * Delete all entries in list and list
 *
 * @param list - instance
 * @param deleteData - if true and destructor is set, data will be deleted via destructor
 */
void List_destruct(ListRef list, Bool deleteData);

#endif //IFJ2017_LIST_EXTERNAL_H

/** End of list.external.h */
