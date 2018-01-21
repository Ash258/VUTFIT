// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.variable_info.h
// Assignment:      125, I
// Date:            22/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_GENERATOR_VARIABLE_INFO_H
#define IFJ2017_GENERATOR_VARIABLE_INFO_H

#include "../trie/trie.external.h"
#include "../symtable/symtable.external.h"
#include "generator.operand.h"
#include "generator.structures.h"

typedef enum VariableInfoType {
    VIT_GLOBAL,
    VIT_STATIC,
    VIT_LOCAL,
    VIT_AUXILIARY
} VariableInfoType;

typedef struct VariableInfo {
    OperandVariable variable;
    Int             stack;
} * VariableInfoRef, VariableInfo;

VariableInfoRef VariableInfo_create(GeneratorRef generator, VariableNodeRef variable, VariableInfoType scope);

void VariableInfo_destruct(VariableInfoRef variable);

VariableInfoRef VariableInfo_temporary(GeneratorRef generator, DataType type);

VariableInfoRef VariableInfo_use(GeneratorRef generator, VariableNodeRef variable);

VariableInfoRef VariableInfo_useForStack(GeneratorRef generator, VariableNodeRef variable, int stack);

void VariableInfo_register(GeneratorRef generator, VariableNodeRef variable, VariableInfoRef var);

void VariableInfo_clear(GeneratorRef generator);

#endif //IFJ2017_GENERATOR_VARIABLE_INFO_H

/** End of generator.variable_info.h */
