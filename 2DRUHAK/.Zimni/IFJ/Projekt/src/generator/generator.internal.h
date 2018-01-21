// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.internal.h
// Assignment:      125, I
// Date:            19/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_GENERATOR_INTERNAL_H
#define IFJ2017_GENERATOR_INTERNAL_H

#include "../list/list.external.h"
#include "../trie/trie.external.h"
#include "../ast/ast.external.h"
#include "generator.operand.h"
#include "generator.variable_info.h"
#include "generator.structures.h"

//region Definitions

void Generator_functionDef(GeneratorRef generator, FunctionDefRef node);

void Generator_variableDef(GeneratorRef generator, VariableDefRef node);

//endregion

//region Statements

void Generator_statement(GeneratorRef generator, ASTNodeRef node);

void Generator_assignment(GeneratorRef generator, AssignmentStRef node);

void Generator_return(GeneratorRef generator, ReturnStRef node);

void Generator_input(GeneratorRef generator, InputStRef node);

void Generator_print(GeneratorRef generator, PrintStRef node);

void Generator_if(GeneratorRef generator, IfStRef node);

void Generator_loop(GeneratorRef generator, LoopStRef node);

//endregion

//region Expressions

Location Generator_expression(GeneratorRef generator, ASTNodeRef node);

Location Generator_functionCall(GeneratorRef generator, FunctionCallExpRef node);

Location Generator_binaryExpression(GeneratorRef generator, BinaryOperatorExpRef node);

Location Generator_unaryExpression(GeneratorRef generator, UnaryOperatorExpRef node);

Location Generator_immediate(ImmediateExpRef node);

Location Generator_variable(GeneratorRef generator, VariableNodeRef node);

//endregion

//region Scope

void Generator_NestedScope_return(GeneratorRef generator);

void Generator_nestedScope(GeneratorRef generator, ScopeRef scope);

//endregion

void Generator_instructionList(GeneratorRef generator, ILType type);

Location Generator_convertDataType(GeneratorRef generator, Location location, DataType to);

OperandSymbol Generator_ensureSymbol(GeneratorRef generator, Location location);

Location Generator_ensureSymbolFor(GeneratorRef generator, VariableInfoRef var, Location value, bool useInstruction);

Location Generator_ensureOnStack(GeneratorRef generator, Location location);

DataType Generator_locationType(Location loc);

OperandImmediate Generator_implicitValue(DataType type);

#endif //IFJ2017_GENERATOR_INTERNAL_H

/** End of generator.internal.h */
