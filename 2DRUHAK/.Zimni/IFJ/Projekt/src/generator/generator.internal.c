// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.internal.c
// Assignment:      125, I
// Date:            17/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.operand.h"
#include "generator.instruction_set.h"
#include "generator.internal.h"
#include "../ast/ast.external.h"

DataType Generator_locationType(Location location) {
    switch (location.type) {
        case LT_STACK: return location.dataType;
        case LT_SYMBOL: return Symbol_dataTypeOf(location.symbol);
        default: DIE(ERR_OTHER);
    }
}

OperandImmediate Generator_implicitValue(DataType type) {
    switch (type) {
        case DT_STRING: return Immediate_string("");
        case DT_INTEGER: return Immediate_int(0);
        case DT_FLOAT: return Immediate_real(0.0);
        case DT_BOOL: return Immediate_bool(false);
        default: DIE(ERR_OTHER);
    }
}

OperandSymbol Generator_ensureSymbol(GeneratorRef generator, Location location) {
    switch (location.type) {
        case LT_SYMBOL: return location.symbol;
        case LT_STACK: {
            VariableInfoRef var = VariableInfo_temporary(generator, location.dataType);
            List_push(generator->inst, Instruction_pops(var->variable));
            return Symbol_var(var->variable);
        }
        default:DIE(ERR_OTHER);
    }
}

Location Generator_ensureSymbolFor(GeneratorRef generator, VariableInfoRef var, Location value, bool useInstruction) {
    switch (value.type) {
        case LT_STACK: List_push(generator->inst, Instruction_pops(var->variable));
            break;
        case LT_SYMBOL: List_push(generator->inst, Instruction_move(var->variable, value.symbol));
            break;
        default: DIE(ERR_OTHER);
    }
    return (Location) {.type = LT_SYMBOL, .symbol = Symbol_var(var->variable)};
}

Location Generator_ensureOnStack(GeneratorRef generator, Location value) {
    switch (value.type) {
        case LT_STACK: return value;
        case LT_SYMBOL: {
            List_push(generator->inst, Instruction_pushs(value.symbol));
            return (Location) {.type = LT_STACK, .dataType = Symbol_dataTypeOf(value.symbol)};
        }
        default: DIE(ERR_OTHER);
    }
}

void Generator_instructionList(GeneratorRef generator, ILType type) {
    generator->inst = generator->instructionLists + type;
}

/** End of generator.internal.c */
