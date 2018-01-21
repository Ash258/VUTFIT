// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.unary.c
// Assignment:      125, I
// Date:            23/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.operand.h"
#include "generator.instruction_set.h"
#include "generator.internal.h"

static OperandImmediate Unary_negativeOneFor(DataType type) {
    return type == DT_FLOAT
           ? Immediate_real(-1)
           : Immediate_int(-1);
}

static Location Unary_variable(GeneratorRef generator, OperatorType operator, Location operand, DataType type) {

    VariableInfoRef dest   = VariableInfo_temporary(generator, type);
    Operand         destOp = Operand_variable(dest->variable);
    Operand         operOp = Operand_symbol(Generator_ensureSymbol(generator, operand));

    switch (operator) {
        case OT_NOT: {
            List_push(generator->inst, Instruction_destFirst(I_NOT, destOp, operOp));
            break;
        }
        case OT_SUB: {
            List_push(generator->inst, Instruction_destFirst(I_MOVE, destOp, operOp));
            Operand negativeOne = Operand_immediate(Unary_negativeOneFor(type));
            List_push(generator->inst, Instruction_create(I_MUL, destOp, negativeOne, destOp));
            break;
        }
        default:DIE(ERR_OTHER);
    }

    return (Location) {.type = LT_SYMBOL, .symbol = Symbol_var(dest->variable)};
}

Location Generator_unaryExpression(GeneratorRef generator, UnaryOperatorExpRef node) {
    Location operand = Generator_expression(generator, node->expression);

    // Rules fo stack version over variable version
    // * operator is OT_NOT ot OT_SUB

    Location result = Unary_variable(generator, node->operator, operand, node->type);
    return Generator_convertDataType(generator, result, node->type);
}

/** End of generator.unary.c */
