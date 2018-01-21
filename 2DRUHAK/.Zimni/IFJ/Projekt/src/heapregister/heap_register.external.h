// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            heap_register.external.h
// Assignment:      125, I
// Date:            2/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_HEAP_REGISTER_EXTERNAL_H
#define IFJ2017_HEAP_REGISTER_EXTERNAL_H

#include "../config.h"
#include "../c_alias.h"
#include "../list/list.external.h"

typedef enum Group {
    G_UNDEFINED,
    G_GLOBAL,

    G_TOKENS,

    G_INSTRUCTIONS,

    G_VARIABLES,

    G_IMMEDIATE,

    G_HEAP_SIZE
} Group;

typedef void (* HeapRegisterDestructor)(Address);

/**
 * Set destructor for group.
 *
 * @param group
 * @param destructor
 */
void HeapRegister_setDestructor(Group group, HeapRegisterDestructor destructor);

/**
 * Allocate new memory block with given size into given group.
 *
 * @param Size size - size of the memory block.
 *
 * @return Address
 */
Address HeapRegister_allocate(Group group, Size size);

/**
 * Free memory block in group.
 *
 * @param Address address - to free
 */
void HeapRegister_free(Group group, Address address);

/**
 * Free memory blocks for given group.
 */
void HeapRegister_sweepGroup(Group group);

/**
 * Free all active memory blocks.
 */
void HeapRegister_sweep(void);

#endif //IFJ2017_HEAP_REGISTER_EXTERNAL_H

/** End of heap_register.external.h */
