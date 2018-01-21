// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.optimizations.c
// Assignment:      125, I
// Date:            20/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.operand.h"
#include "generator.instruction_set.h"
#include "generator.internal.h"

static InstructionSet Conversion_instructionTable(Location loc, DataType to) {
    bool     stack = loc.type == LT_STACK;
    DataType from  = Generator_locationType(loc);

    IF_TRUE_RETURN_VALUE(stack && from == DT_FLOAT && to == DT_INTEGER, I_FLOAT2R2EINTS)
    IF_TRUE_RETURN_VALUE(stack && from == DT_INTEGER && to == DT_FLOAT, I_INT2FLOATS)
    IF_TRUE_RETURN_VALUE(!stack && from == DT_FLOAT && to == DT_INTEGER, I_FLOAT2R2EINT)
    IF_TRUE_RETURN_VALUE(!stack && from == DT_INTEGER && to == DT_FLOAT, I_INT2FLOAT)
    DIE(ERR_OTHER);
}

static Location interpretConversion(GeneratorRef generator, Location location, DataType to) {
    InstructionSet is = Conversion_instructionTable(location, to);
    switch (location.type) {
        case LT_STACK: {
            List_push(generator->inst, Instruction_empty(is));
            return (Location) {.type = LT_STACK, .dataType = to};
        }
        case LT_SYMBOL: {
            VariableInfoRef var   = VariableInfo_temporary(generator, to);
            Operand         varOp = Operand_variable(var->variable);
            Operand         symOp = Operand_symbol(location.symbol);
            List_push(generator->inst, Instruction_destFirst(is, varOp, symOp));
            return (Location) {.type = LT_SYMBOL, .symbol = Symbol_var(var->variable)};
        }
        default:DIE(ERR_OTHER);
    }
}

Location Generator_convertDataType(GeneratorRef generator, Location location, DataType to) {
    IF_TRUE_RETURN_VALUE(location.type == LT_STACK && location.dataType == to, location)
    IF_TRUE_RETURN_VALUE(location.type == LT_SYMBOL && Symbol_dataTypeOf(location.symbol) == to, location)

    return interpretConversion(generator, location, to);
}

/** End of generator.optimizations.c */
