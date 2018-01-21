// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            list.external.c
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "list.external.h"

void List_deleteElement(ListRef list, ListElementRef element);

ListRef List_create(SimpleDestructor destructor) {
    ListRef ref = HeapRegister_allocate(G_UNDEFINED, sizeof(List));
    List_init(ref, destructor);

    return ref;
}

void List_init(ListRef ref, SimpleDestructor destructor) {
    assertNotNull(ref);

    ref->destructor = destructor;
    ref->size       = 0;
    ref->first      = ref->last = NULL;
}

DataRef List_first(ListRef list) {
    assertNotNull(list);

    return List_isEmpty(list) ? NULL : list->first->data;
}

DataRef List_last(ListRef list) {
    assertNotNull(list);

    return List_isEmpty(list) ? NULL : list->last->data;
}

ListElementRef List_createElement(DataRef entry) {
    ListElementRef ref = calloc(1, sizeof(ListElement));
    IF_NULL_RETURN_NULL(ref);
    ref->data = entry;

    return ref;
}

void List_push(ListRef list, DataRef entry) {
    assertNotNull(list);

    ListElementRef element = List_createElement(entry);
    if (List_isEmpty(list)) {
        list->first = list->last = element;
    } else {
        element->prev    = list->last;
        list->last->next = element;
        list->last       = element;
    }

    list->size++;
}

void List_unshift(ListRef list, DataRef entry) {
    assertNotNull(list);

    ListElementRef element = List_createElement(entry);
    if (List_isEmpty(list)) {
        list->first = list->last = element;
    } else {
        element->next     = list->first;
        list->first->prev = element;
        list->first       = element;
    }

    list->size++;
}

DataRef List_pop(ListRef list) {
    assertNotNull(list);

    DataRef data = NULL;
    if (!List_isEmpty(list)) {
        data = list->last->data;
        List_deleteElement(list, list->last);
    }

    return data;
}

DataRef List_shift(ListRef list) {
    assertNotNull(list);

    DataRef data = NULL;
    if (!List_isEmpty(list)) {
        data = list->first->data;
        List_deleteElement(list, list->first);
    }

    return data;
}

void List_remove(ListRef list, DataRef entry) {
    assertNotNull(list);

    ListElementRef element = list->first;
    while (element != NULL) {
        ListElementRef aux = element;
        element = element->next;

        if (aux->data == entry) {
            List_deleteElement(list, aux);
            return;
        }
    }
}

void List_delete(ListRef list, DataRef entry) {
    assertNotNull(list);

    if (list->destructor != NULL) {
        list->destructor(entry);
    }
}

void List_removeAll(ListRef list, DataRef entry) {
    assertNotNull(list);

    ListElementRef element = list->first;
    while (element != NULL) {
        ListElementRef aux = element;
        element = element->next;

        if (aux->data == entry) {
            List_deleteElement(list, aux);
        }
    }
}

Bool List_isEmpty(ListRef list) {
    assertNotNull(list);

    return list->size == 0;
}

Int List_size(ListRef list) {
    assertNotNull(list);

    return list->size;
}

DataRef List_search(ListRef list, ListCallback comparator, ContextRef context) {
    assertNotNull(list);
    assertNotNull(comparator);

    ListElementRef entry = list->first;
    while (entry != NULL) {
        if (comparator(entry->data, context)) return entry->data;

        entry = entry->next;
    }

    return NULL;
}

Bool List_contains(ListRef list, ListCallback comparator, ContextRef context) {
    assertNotNull(list);
    assertNotNull(comparator);

    return List_search(list, comparator, context) != NULL;
}

Bool List_has(ListRef list, DataRef entry) {
    assertNotNull(list);
    assertNotNull(entry);

    ListElementRef element = list->first;
    while (element != NULL) {
        if (element->data == entry) return true;

        element = element->next;
    }

    return false;
}

void List_dispose(ListRef list, Bool deleteData) {
    assertNotNull(list);

    while (!List_isEmpty(list)) {
        DataRef data = list->first->data;
        List_removeAll(list, data);
        if (deleteData && list->destructor) list->destructor(data);
    }
}

void List_forEach(ListRef list, ListCallback callback, ContextRef context) {
    ListElementRef element = list->first;
    while (element != NULL) {
        if (!callback(element->data, context)) return;

        element = element->next;
    }
}

void List_swap(ListElementRef* first, ListElementRef* second) {
    ListElementRef tmp = *first;
    *first  = *second;
    *second = tmp;
}

void List_reverse(ListRef list) {
    ListElementRef element = list->first;
    while (element != NULL) {
        List_swap(&element->prev, &element->next);
        element = element->prev;
    }

    List_swap(&list->last, &list->first);
}

void List_forEachReverse(ListRef list, ListCallback callback, ContextRef context) {
    ListElementRef element = list->last;
    while (element != NULL) {
        if (!callback(element->data, context)) return;

        element = element->prev;
    }
}

void List_deleteElement(ListRef list, ListElementRef element) {
    assertNotNull(list);
    assertNotNull(element);

    if (element->prev != NULL) {
        element->prev->next = element->next;
    }

    if (element->next != NULL) {
        element->next->prev = element->prev;
    }

    if (element == list->first) {
        list->first = element->next;
    }

    if (element == list->last) {
        list->last = element->prev;
    }

    free(element);
    list->size--;
}

Bool List_equals(ListRef firstList, ListRef secondList, ListCallback callback) {
    assertNotNull(firstList);
    assertNotNull(secondList);

    if (firstList->size != secondList->size) return false;

    ListElementRef firstElement  = firstList->first;
    ListElementRef secondElement = secondList->first;

    while (firstElement != NULL && secondElement != NULL) {
        if (!callback(firstElement->data, secondElement->data)) return false;

        firstElement  = firstElement->next;
        secondElement = secondElement->next;
    }

    return true;
}

void List_destruct(ListRef list, Bool deleteData) {
    assertNotNull(list);

    List_dispose(list, deleteData);
    free(list);
}

void List_mapEach(ListRef list, ListMapper callback, ContextRef context) {
    ListElementRef element = list->first;
    while (element != NULL) {
        element->data = callback(element->data, context);
        element = element->next;
    }
}

/** End of list.external.c */
