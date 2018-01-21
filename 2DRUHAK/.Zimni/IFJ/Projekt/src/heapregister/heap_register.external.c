// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            heap_register.external.c
// Assignment:      125, I
// Date:            2/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "heap_register.external.h"

static List heap[G_HEAP_SIZE] = {0};

void HeapRegister_setDestructor(Group group, HeapRegisterDestructor destructor) {
    List_init(heap + group, destructor);
}

Address HeapRegister_allocate(Group group, Size size) {
    Address address = calloc(1, size);
    IF_NULL_DIE(address, ERR_OTHER)

    if (group != G_UNDEFINED) {
        List_push(heap + group, address);
    }
    return address;
}

void HeapRegister_free(Group group, Address address) {
    assertNotNull(address);
    if (group == G_UNDEFINED) return;

    List_removeAll(heap + group, address);
    List_delete(heap + group, address);
}

void HeapRegister_sweepGroup(Group group) {
    List_dispose(heap + group, true);
}

void HeapRegister_sweep(void) {
    for (UnsignedInt i = 0; i < G_HEAP_SIZE; ++i) {
        HeapRegister_sweepGroup((Group) i);
    }
}

/** End of heap_register.external.c */
