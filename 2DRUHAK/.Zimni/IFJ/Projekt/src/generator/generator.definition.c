// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.definition.c
// Assignment:      125, I
// Date:            28/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "../symtable/symtable.external.h"
#include "generator.internal.h"
#include "generator.instruction_set.h"

void Generator_variableDef(GeneratorRef generator, VariableDefRef node) {
    assertNotNull(generator);
    assertNotNull(node);

    VariableInfoType type = node->isStatic ? VIT_STATIC : VIT_LOCAL;
    if (node->isStatic) Generator_instructionList(generator, IL_INIT);

    VariableInfoRef var = VariableInfo_create(generator, node->variable, type);

    if (node->initialization) {
        Location value = Generator_expression(generator, node->initialization);
        value = Generator_convertDataType(generator, value, var->variable.dataType);
        Generator_ensureSymbolFor(generator, var, value, true);
    }

    if (node->isStatic) Generator_instructionList(generator, IL_CODE);

    VariableInfo_register(generator, node->variable, var);
}

static Bool Function_handleParams(ParameterRef parameter, GeneratorRef generator) {
    VariableInfoRef var = VariableInfo_create(generator, parameter, VIT_LOCAL);
    List_push(generator->inst, Instruction_pops(var->variable));
    VariableInfo_register(generator, parameter, var);
    return true;
}

void Generator_functionDef(GeneratorRef generator, FunctionDefRef function) {
    assertNotNull(generator);
    assertNotNull(function);

    List_unshift(&generator->scopes, function->scope);
    List_push(generator->inst, Instruction_label(function->function->name));

    List_push(generator->inst, Instruction_createframe());
    List_push(generator->inst, Instruction_pushframe());
    List_push(generator->inst, Instruction_createframe());

    List_forEach(function->function->parameters, (ListCallback) Function_handleParams, generator); // Args in LF
    if (List_isEmpty(function->scope->statements)) {
        VariableInfo_clear(generator);
    }
    List_shift(&generator->scopes);

    Generator_nestedScope(generator, function->scope);

    OperandImmediate implicit = Generator_implicitValue(function->function->type);

    List_push(generator->inst, Instruction_pushs(Symbol_immediate(implicit)));
    List_push(generator->inst, Instruction_popframe());
    List_push(generator->inst, Instruction_return());
}

void Generator_return(GeneratorRef generator, ReturnStRef node) {
    Location location = Generator_expression(generator, node->expression);
    location = Generator_convertDataType(generator, location, node->function->type);
    Generator_ensureOnStack(generator, location);

    Generator_NestedScope_return(generator);

    List_push(generator->inst, Instruction_return());
}

/** End of generator.definition.c */
