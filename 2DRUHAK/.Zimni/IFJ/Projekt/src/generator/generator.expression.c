// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.expression.c
// Assignment:      125, I
// Date:            28/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.internal.h"

Location Generator_variable(GeneratorRef generator, VariableNodeRef variable) {
    OperandSymbol symbol = Symbol_var(VariableInfo_use(generator, variable)->variable);
    return (Location) {.type = LT_SYMBOL, .symbol = symbol};
}

Location Generator_immediate(ImmediateExpRef node) {
    OperandSymbol symbol = Symbol_immediate(Immediate_of(node->type, node->value));
    return (Location) {.type = LT_SYMBOL, .symbol = symbol};
}

Location Generator_expression(GeneratorRef generator, ASTNodeRef node) {
    switch (node->type) {
        case AST_VARIABLE_EXP: return Generator_variable(generator, node->ref);
        case AST_IMMEDIATE_EXP: return Generator_immediate(node->ref);
        case AST_FUNCTION_CALL_EXP: return Generator_functionCall(generator, node->ref);
        case AST_BINARY_OPERATOR_EXP: return Generator_binaryExpression(generator, node->ref);
        case AST_UNARY_OPERATOR_EXP: return Generator_unaryExpression(generator, node->ref);
        default:DIE(ERR_OTHER);
    }
}

/** End of generator.expression.c */
