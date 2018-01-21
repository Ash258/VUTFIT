// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.scope.c
// Assignment:      125, I
// Date:            19/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "../ast/ast.external.h"
#include "generator.internal.h"
#include "generator.instruction_set.h"

typedef struct {
    GeneratorRef generator;
    int          scope;
} ScopeData, * ScopeDataRef;

static Bool copyToFrame(VariableNodeRef variable, ScopeDataRef data) {
    VariableInfoRef local = VariableInfo_use(data->generator, variable);
    IF_TRUE_RETURN_VALUE(local->variable.scope == VS_GLOBAL, true);

    OperandVariable temp = local->variable;
    temp.scope = VS_TEMP;
    List_push(data->generator->inst, Instruction_defvar(temp));
    List_push(data->generator->inst, Instruction_move(temp, Symbol_var(local->variable)));
    return true;
}

static Bool copyFromFrame(VariableNodeRef variable, ScopeDataRef data) {
    VariableInfoRef local = VariableInfo_useForStack(data->generator, variable, data->scope);
    IF_TRUE_RETURN_VALUE(local->variable.scope == VS_GLOBAL, true);

    OperandVariable temp = local->variable;
    temp.scope = VS_TEMP;
    List_push(data->generator->inst, Instruction_move(local->variable, Symbol_var(temp)));
    return true;
}

static Bool handleStatement(ASTNodeRef node, GeneratorRef generator) {
    Generator_statement(generator, node);
    return true;
}

static void NestedScope_push(GeneratorRef generator, ScopeRef scope) {
    IF_TRUE_RETURN_VOID(List_isEmpty(scope->statements));

    List_unshift(&generator->scopes, scope);

    IF_TRUE_RETURN_VOID(List_size(&generator->scopes) == 1);

    ScopeDataRef data = &(ScopeData) {.generator = generator, .scope = List_size(&generator->scopes)};
    List_forEach(scope->carryVars, (ListCallback) copyToFrame, data);
    List_forEach(scope->inheritedVars, (ListCallback) copyToFrame, data);
    List_push(generator->inst, Instruction_pushframe());
    List_push(generator->inst, Instruction_createframe());
}

static Bool NestedScope_pop(ScopeRef scope, ScopeDataRef data) {
    List_push(data->generator->inst, Instruction_popframe());

    if (List_size(&data->generator->scopes) != 1) {
        List_forEach(scope->carryVars, (ListCallback) copyFromFrame, data);
        List_forEach(scope->inheritedVars, (ListCallback) copyFromFrame, data);
    }

    List_push(data->generator->inst, Instruction_createframe());

    data->scope--;
    return true;
}

void Generator_NestedScope_return(GeneratorRef generator) {
    ScopeDataRef data = &(ScopeData) {.generator = generator, .scope = List_size(&generator->scopes)};
    List_forEach(&generator->scopes, (ListCallback) NestedScope_pop, data);
}

void Generator_nestedScope(GeneratorRef generator, ScopeRef scope) {
    IF_TRUE_RETURN_VOID(List_isEmpty(scope->statements))

    NestedScope_push(generator, scope);
    List_forEach(scope->statements, (ListCallback) handleStatement, generator);
    VariableInfo_clear(generator);

    if (List_size(&generator->scopes) != 1) {
        ScopeDataRef data = &(ScopeData) {.generator = generator, .scope = List_size(&generator->scopes)};
        NestedScope_pop(scope, data);
    }

    List_shift(&generator->scopes);
}

/** End of generator.scope.c */
