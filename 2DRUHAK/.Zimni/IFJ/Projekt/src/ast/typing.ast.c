// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            typing.ast.c
// Assignment:      125, I
// Date:            19/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "typing.ast.h"

DataType getExpressionType(ASTNodeRef node) {
    IF_NULL_DIE(node, ERR_OTHER);

    switch (node->type) {
        case AST_FUNCTION_CALL_EXP: return ((FunctionCallExpRef) node->ref)->calledFunction->type;
        case AST_VARIABLE_EXP: return ((VariableNodeRef) node->ref)->type;
        case AST_IMMEDIATE_EXP: return ((ImmediateExpRef) node->ref)->type;
        case AST_BINARY_OPERATOR_EXP: return ((BinaryOperatorExpRef) node->ref)->type;
        case AST_UNARY_OPERATOR_EXP: return ((UnaryOperatorExpRef) node->ref)->type;
        default: DIE(ERR_OTHER);
    }
}

DataType getBinaryExpressionType(DataType leftOperand, DataType rightOperand, OperatorType operator) {
    switch (operator) {
        case OT_ADD:IF_TRUE_RETURN_DFLT(leftOperand == DT_STRING && rightOperand == DT_STRING, DT_STRING);
        case OT_SUB:
        case OT_MUL:IF_TRUE_RETURN_DFLT(leftOperand == DT_INTEGER && rightOperand == DT_INTEGER, DT_INTEGER);
            IF_TRUE_RETURN_DFLT(leftOperand == DT_FLOAT && rightOperand == DT_FLOAT, DT_FLOAT);
            IF_TRUE_RETURN_DFLT((leftOperand == DT_FLOAT || leftOperand == DT_INTEGER) &&
                                (rightOperand == DT_FLOAT || rightOperand == DT_INTEGER), DT_FLOAT);
            DIE(ERR_SEMANTIC_COMPATIBILITY);
        case OT_DIV:IF_TRUE_RETURN_DFLT((leftOperand == DT_FLOAT || leftOperand == DT_INTEGER) &&
                                        (rightOperand == DT_FLOAT || rightOperand == DT_INTEGER), DT_FLOAT);
            DIE(ERR_SEMANTIC_COMPATIBILITY);
        case OT_IDIV:IF_TRUE_RETURN_DFLT((leftOperand == DT_FLOAT || leftOperand == DT_INTEGER) &&
                                         (rightOperand == DT_FLOAT || rightOperand == DT_INTEGER), DT_INTEGER);
            DIE(ERR_SEMANTIC_COMPATIBILITY);
        case OT_LT:
        case OT_LEQ:
        case OT_GT:
        case OT_GEQ:
        case OT_EQ:
        case OT_NEQ:IF_TRUE_RETURN_DFLT(leftOperand == rightOperand, DT_BOOL); //accept same operands of any type
            IF_TRUE_RETURN_DFLT(leftOperand == DT_FLOAT && rightOperand == DT_INTEGER, DT_BOOL);
            IF_TRUE_RETURN_DFLT(leftOperand == DT_INTEGER && rightOperand == DT_FLOAT, DT_BOOL);
            DIE(ERR_SEMANTIC_COMPATIBILITY);
        case OT_AND:
        case OT_OR:
        case OT_NOT:IF_TRUE_RETURN_DFLT(leftOperand == DT_BOOL && rightOperand == DT_BOOL, DT_BOOL);
            DIE(ERR_SEMANTIC_COMPATIBILITY);
        default:DIE(ERR_SEMANTIC_COMPATIBILITY);
    }
}

DataType getUnaryExpressionType(OperatorType operator, DataType expression) {
    switch (operator) {
        case OT_SUB:IF_TRUE_RETURN_DFLT(expression == DT_INTEGER || expression == DT_FLOAT, expression);
            DIE(ERR_SEMANTIC_COMPATIBILITY);
        case OT_NOT:IF_TRUE_RETURN_DFLT(expression == DT_BOOL, DT_BOOL);
            DIE(ERR_SEMANTIC_COMPATIBILITY);
        default: DIE(ERR_SEMANTIC_COMPATIBILITY);
    }
}

Bool areConvertible(DataType first, DataType second) {
    IF_TRUE_RETURN_DFLT(first == DT_FLOAT && second == DT_INTEGER, true);
    IF_TRUE_RETURN_DFLT(first == DT_INTEGER && second == DT_FLOAT, true);

    return false;
}

Bool areCompatible(DataType first, DataType second) {
    return first == second || areConvertible(first, second);
}

/** End of typing.ast.c */
