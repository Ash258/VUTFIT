// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            helpers.c
// Assignment:      125, I
// Date:            16/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include <memory.h>
#include "helpers.h"

void simpleDestructor(void* data) {
    IF_NULL_RETURN_VOID(data)
    free(data);
}

void* copyInstance(size_t size, const void* source) {
    void* destination = HeapRegister_allocate(G_UNDEFINED, size);
    memcpy(destination, source, size);

    return destination;
}

void* copyImmediate(size_t size, const void* source) {
    void* destination = HeapRegister_allocate(G_IMMEDIATE, size);
    memcpy(destination, source, size);

    return destination;
}

Int* Int_of(Int value) {
    return copyImmediate(sizeof(Int), &value);
}

Int Int_from(Address value) {
    return *((Int*) value);
}

Real* Real_of(Real value) {
    return copyImmediate(sizeof(Real), &value);
}

Real Real_from(Address value) {
    return *((Real*) value);
}

Bool* Bool_of(Bool value) {
    return copyImmediate(sizeof(Bool), &value);
}

Bool Bool_from(Address value) {
    return *((Bool*) value);
}

String String_from(void* value) {
    return (char*) value;
}

/** End of helpers.c */
