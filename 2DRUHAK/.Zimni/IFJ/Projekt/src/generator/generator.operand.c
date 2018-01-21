// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.operand.c
// Assignment:      125, I
// Date:            17/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.operand.h"

//region Generic operands

Operand Operand_symbol(OperandSymbol value) {
    return value.type == O_IMMEDIATE
           ? Operand_immediate(value.immediate)
           : Operand_variable(value.variable);
}

Operand Operand_immediate(OperandImmediate value) {
    return (Operand) {.type = O_IMMEDIATE, .immediate = value};
}

Operand Operand_variable(OperandVariable value) {
    return (Operand) {.type = O_VARIABLE, .variable = value};
}

Operand Operand_label(String value) {
    return (Operand) {.type = O_LABEL, .label = value};
}

Operand Operand_dataType(DataType value) {
    return (Operand) {.type = O_DATATYPE, .dataType = value};
}

//endregion

//region Symbol, Variable, Immedate

OperandSymbol Symbol_var(OperandVariable variable) {
    return (OperandSymbol) {.type = O_VARIABLE, .variable = variable};
}

OperandSymbol Symbol_immediate(OperandImmediate immediate) {
    return (OperandSymbol) {.type = O_IMMEDIATE, .immediate = immediate};
}

OperandVariable Variable_of(DataType type, String name, VariableScope scope) {
    return (OperandVariable) {.dataType = type, .name = name, .scope = scope};
}

OperandImmediate Immediate_of(DataType type, Address value) {
    return (OperandImmediate) {.dataType = type, .value = value};
}

OperandImmediate Immediate_string(String value) {
    return Immediate_of(DT_STRING, value);
}

OperandImmediate Immediate_int(Int value) {
    return Immediate_of(DT_INTEGER, Int_of(value));
}

OperandImmediate Immediate_real(Real value) {
    return Immediate_of(DT_FLOAT, Real_of(value));
}

OperandImmediate Immediate_bool(Bool value) {
    return Immediate_of(DT_BOOL, Bool_of(value));
}

DataType Symbol_dataTypeOf(OperandSymbol symbol) {
    return symbol.type == O_VARIABLE ? symbol.variable.dataType : symbol.immediate.dataType;
}

//endregion

/** End of generator.operand.c */
