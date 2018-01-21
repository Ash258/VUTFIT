// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.binary.c
// Assignment:      125, I
// Date:            20/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.internal.h"
#include "generator.instruction_set.h"

static DataType Binary_ensureDataTypes(GeneratorRef generator, OperatorType operator, Location* left, Location* right) {
    DataType leftType  = Generator_locationType(*left);
    DataType rightType = Generator_locationType(*right);

    if (operator == OT_IDIV) {
        *right = Generator_convertDataType(generator, *right, DT_INTEGER);
        *left  = Generator_convertDataType(generator, *left, DT_INTEGER);

        *right = Generator_convertDataType(generator, *right, DT_FLOAT);
        *left  = Generator_convertDataType(generator, *left, DT_FLOAT);
        return DT_FLOAT;
    }

    if (operator == OT_DIV) {
        *right = Generator_convertDataType(generator, *right, DT_FLOAT);
        *left  = Generator_convertDataType(generator, *left, DT_FLOAT);
        return DT_FLOAT;
    }
    if (leftType == rightType) {
        return leftType;
    }
    if (leftType == DT_FLOAT && rightType == DT_INTEGER) {
        *right = Generator_convertDataType(generator, *right, DT_FLOAT);
        return DT_FLOAT;
    }
    if (leftType == DT_INTEGER && rightType == DT_FLOAT) {
        *left = Generator_convertDataType(generator, *left, DT_FLOAT);
        return DT_FLOAT;
    }

    DIE(ERR_OTHER);
}

static InstructionSet Binary_tableVariable(OperatorType operator, DataType type) {
    switch (operator) {
        case OT_ADD: return type == DT_STRING ? I_CONCAT : I_ADD;
        case OT_SUB: return I_SUB;
        case OT_DIV: return I_DIV;
        case OT_MUL: return I_MUL;

        case OT_GT: return I_GT;
        case OT_LT: return I_LT;
        case OT_EQ: return I_EQ;
        case OT_AND: return I_AND;
        case OT_OR: return I_OR;

        case OT_GEQ: return I_LT;
        case OT_LEQ: return I_GT;
        case OT_NEQ: return I_EQ;

        default:DIE(ERR_OTHER);
    }
}

static Location Binary_variable(GeneratorRef generator, OperatorType operator, Location left, Location right) {
    DataType        type    = Binary_ensureDataTypes(generator, operator, &left, &right);
    VariableInfoRef dest    = VariableInfo_temporary(generator, type);
    Operand         destOp  = Operand_variable(dest->variable);
    Operand         leftOp  = Operand_symbol(Generator_ensureSymbol(generator, left));
    Operand         rightOp = Operand_symbol(Generator_ensureSymbol(generator, right));

    switch (operator) {
        case OT_GT:
        case OT_LT:
        case OT_EQ: dest->variable.dataType = DT_BOOL;
        case OT_ADD:
        case OT_SUB:
        case OT_DIV:
        case OT_MUL:
        case OT_AND:
        case OT_OR: {
            InstructionSet is = Binary_tableVariable(operator, type);
            List_push(generator->inst, Instruction_create(is, destOp, leftOp, rightOp));
            break;
        }
        case OT_GEQ:
        case OT_LEQ:
        case OT_NEQ: {
            dest->variable.dataType = DT_BOOL;
            InstructionSet is       = Binary_tableVariable(operator, type);
            List_push(generator->inst, Instruction_create(is, destOp, leftOp, rightOp));
            List_push(generator->inst, Instruction_destFirst(I_NOT, destOp, destOp));
            break;
        }
        case OT_IDIV: {
            List_push(generator->inst, Instruction_create(I_DIV, destOp, leftOp, rightOp));
            break;
        }
        default: DIE(ERR_OTHER);
    }

    return (Location) {.type = LT_SYMBOL, .symbol = Symbol_var(dest->variable)};
}

Location Generator_binaryExpression(GeneratorRef generator, BinaryOperatorExpRef node) {
    Location left  = Generator_expression(generator, node->left);
    Location right = Generator_expression(generator, node->right);

    // Rules of stack version over variable version:
    // * left is on stack
    // * right is on stack and operator is commutative

    Location result = Binary_variable(generator, node->operator, left, right);
    return Generator_convertDataType(generator, result, node->type);
}

/** End of generator.binary.c */
