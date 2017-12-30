//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Jakub "Ash258" Čábera <xcaber00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Jakub "Ash258" Čábera
 * 
 * @brief Implementace metod třídy prioritní fronty.
 */

#include <stdlib.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLŇTE IMPLEMENTACI **
//
// Zde doplňte implementaci veřejného rozhraní prioritní fronty (Priority Queue)
// 1. Veřejné rozhraní fronty specifikované v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Případně vaše metody definované v tdd_code.h (sekce "protected:")
//
// Cílem je dosáhnout plně funkční implementace prioritní fronty implementované
// pomocí tzv. "double-linked list", která bude splňovat dodané testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue() { this->head = NULL; }

PriorityQueue::~PriorityQueue() {
    Element_t *actualHead = GetHead();
    Element_t *prev = NULL;

    // Go to tail
    while (actualHead != NULL && actualHead->pNext != NULL) {
        actualHead = actualHead->pNext;
    }

    prev = actualHead != NULL ? actualHead->pPrev : NULL;

    // Delete tail
    while (prev != NULL) {
        prev = actualHead->pPrev;
        delete actualHead;

        actualHead = prev;
    }
}

PriorityQueue::Element_t *PriorityQueue::GetHead() {
    return this->Empty() ? NULL : this->head;
}

bool PriorityQueue::Empty() { return this->head == NULL; }

PriorityQueue::Element_t *PriorityQueue::CreateElement(int value) {
    Element_t *element = new Element_t;
    element->value = value;
    element->pNext = NULL;
    element->pPrev = NULL;

    return element;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value) {
    if (!this->Empty()) {
        Element_t *tmp = this->GetHead();

        while (tmp) {
            if (tmp->value == value) return tmp;
            tmp = tmp->pNext;
        }
    }

    return NULL;
}

void PriorityQueue::Insert(int value) {
    Element_t *newElement = CreateElement(value);

    if (this->Empty()) {
        this->head = newElement;
        return;
    }

    Element_t *current = GetHead();

    while (current) {
        if (current->value < value) {
            // Tail.
            if (current->pNext == NULL) {
                current->pNext = newElement;
                newElement->pPrev = current;
                return;
            }

            current = current->pNext;
            continue;
        }

        // Less or equal to next.
        newElement->pPrev = current->pPrev;
        newElement->pNext = current;

        if (current->pPrev != NULL) {
            current->pPrev->pNext = newElement;
        } else {
            this->head = newElement;
        }

        current->pPrev = newElement;
        return;
    }
}

bool PriorityQueue::Remove(int value) {
    Element_t *current = GetHead();

    while (current) {
        if (current->value == value) {
            if (current->pPrev == NULL) {
                this->head = current->pNext;
            } else {
                current->pPrev->pNext = current->pNext;
            }

            if (current->pNext) current->pNext->pPrev = current->pPrev;

            delete (current);
            return true;
        }

        current = current->pNext;
    }

    return false;
}

/*** Konec souboru tdd_code.cpp ***/