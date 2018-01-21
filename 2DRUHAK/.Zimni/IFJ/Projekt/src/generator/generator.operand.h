// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.operand.h
// Assignment:      125, I
// Date:            17.11.2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_GENERATOR_OPERAND_H
#define IFJ2017_GENERATOR_OPERAND_H

#include "../c_alias.h"
#include "../symtable/symtable.external.h"
#include "../ast/ast.external.h"

#define EMPTY_OPERAND (Operand){.type = O_NULL}

typedef enum {
    O_NULL,
    O_IMMEDIATE,
    O_VARIABLE,
    O_LABEL,
    O_DATATYPE
} OperandType;

typedef enum VariableScope {
    VS_GLOBAL,
    VS_LOCAL,
    VS_TEMP,
} VariableScope;

typedef struct OperandVariable {
    DataType      dataType;
    String        name;
    VariableScope scope;
} OperandVariable;

typedef struct OperandImmediate {
    DataType dataType;
    Address  value;
} OperandImmediate;

typedef struct OperandSymbol {
    OperandType type;
    union {
        OperandImmediate immediate;
        OperandVariable  variable;
    };
} OperandSymbol;

typedef struct Operand {
    OperandType type;
    union {
        OperandImmediate immediate;
        OperandVariable  variable;
        String           label;
        DataType         dataType;
    };
} Operand;

//region Generic operands

Operand Operand_immediate(OperandImmediate value);

Operand Operand_variable(OperandVariable value);

Operand Operand_symbol(OperandSymbol value);

Operand Operand_label(String value);

Operand Operand_dataType(DataType value);

//endregion

//region Symbol, Variable, Immediate

OperandSymbol Symbol_var(OperandVariable variable);

OperandVariable Variable_of(DataType type, String name, VariableScope scope);

OperandSymbol Symbol_immediate(OperandImmediate immediate);

OperandImmediate Immediate_of(DataType type, Address value);

OperandImmediate Immediate_string(String value);

OperandImmediate Immediate_int(Int value);

OperandImmediate Immediate_real(Real value);

OperandImmediate Immediate_bool(Bool value);

//endregion

DataType Symbol_dataTypeOf(OperandSymbol symbol);

#endif //IFJ2017_GENERATOR_OPERAND_H

/** End of generator.operand.h */
