// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.structure.h
// Assignment:      125, I
// Date:            28/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_GENERATOR_STRUCTURE_H
#define IFJ2017_GENERATOR_STRUCTURE_H

#include "../list/list.external.h"
#include "../trie/trie.external.h"
#include "generator.operand.h"

typedef enum {
    IL_CODE, IL_INIT, IL_MAX_VALUE
} ILType;

typedef enum {
    LT_STACK, LT_SYMBOL
} LocationType;

typedef struct Location {
    LocationType type;
    union {
        DataType      dataType;
        OperandSymbol symbol;
    };
} Location;

typedef struct Generator {
    ListRef inst;
    List    instructionLists[IL_MAX_VALUE];

    TrieNode variables;
    List     scopes;
} * GeneratorRef, Generator;

#endif //IFJ2017_GENERATOR_STRUCTURE_H

/** End of generator.structure.c */
