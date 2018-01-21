// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            parser.variable_register.h
// Assignment:      125, I
// Date:            17/11/17
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_PARSER_VARIABLE_REGISTER_H
#define IFJ2017_PARSER_VARIABLE_REGISTER_H

#include "../ast/ast.external.h"

/**
 * @param variableNode - used variable
 */
void registerVarAssign(VariableNodeRef variableNode);

/**
 * @param variableNode - used variable
 */
void registerVarExp(VariableNodeRef variableNode);

/**
 * @param variableNode - used variable
 * @param isStatic - true if defined variable is static
 */
void registerVarDef(VariableNodeRef variableNode, Bool isStatic);

/**
 * @param variableNode - used variable
 */
void registerInputSt(VariableNodeRef variableNode);

void registerScope();

/**
 * @param scope - instance
 */
void pickScopeVars(ScopeRef scope);

#endif //IFJ2017_PARSER_VARIABLE_REGISTER_H

/** End of parser.variable_register.h */
