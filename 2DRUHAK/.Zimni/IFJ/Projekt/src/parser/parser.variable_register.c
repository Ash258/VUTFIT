// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            parser.variable_register.c
// Assignment:      125, I
// Date:            17/11/17
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "parser.variable_register.h"
#include "../trie/trie.external.h"

static TrieNodeRef usedVars = NULL, inheritedVars = NULL;
static ListRef     usedVarsStack;

typedef struct {
    ListRef     local;
    ScopeRef    scope;
    TrieNodeRef inheritedVars;
} * FilterInheritedContextRef, FilterInheritedContext;

typedef struct {
    TrieNodeRef usedVars;
    ListRef     carry;
} * FilterCarryContextRef, FilterCarryContext;

typedef struct {
    Bool            isDefined;
    Bool            isShadowed;
    Bool            isStatic;
    VariableNodeRef variable;
} * UsedParameterRef, UsedParameter;

static UsedParameterRef createEntry(VariableNodeRef node, bool isDefined, bool isStatic) {
    UsedParameterRef parameter = HeapRegister_allocate(G_UNDEFINED, sizeof(UsedParameter));

    parameter->variable  = node;
    parameter->isDefined = isDefined;
    parameter->isStatic  = isStatic;

    return parameter;
}

static void iterateUsedVars(DataRef data, ContextRef context) {
    UsedParameterRef          entry = data;
    FilterInheritedContextRef ref   = context;

    if (!entry->isDefined) {
        entry->isShadowed = Table_hasVariable(ref->scope->symbolTable, entry->variable->name, false);
        UsedParameterRef old = Trie_insert(ref->inheritedVars, entry->variable->name, entry);
        if (old != NULL) free(old);

        List_push(ref->scope->inheritedVars, entry->variable);
    } else {
        if (entry->isStatic) List_push(ref->scope->staticVars, entry->variable);
        List_push(ref->local, entry);
        Trie_delete(inheritedVars, entry->variable->name);
    }
}

static void iterateCarryVars(DataRef data, ContextRef context) {
    UsedParameterRef      entry = data;
    FilterCarryContextRef ref   = context;

    if (!Trie_has(ref->usedVars, entry->variable->name)) {
        List_push(ref->carry, entry->variable);
    }
}

void pickScopeVars(ScopeRef scope) {
    assertNotNull(scope);

    FilterCarryContext carryFilter = {.carry = scope->carryVars, .usedVars = usedVars};
    Trie_forEach(inheritedVars, iterateCarryVars, &carryFilter);

    FilterInheritedContext inheritedFilter = {.scope = scope, .local = List_create(simpleDestructor), .inheritedVars = inheritedVars};
    Trie_forEach(usedVars, iterateUsedVars, &inheritedFilter);
    List_destruct(inheritedFilter.local, true);

    Trie_dispose(usedVars, NULL);
    usedVars = List_pop(usedVarsStack);

    if (usedVars == NULL) { //all scopes are solved
        Trie_destruct(inheritedVars, simpleDestructor);
        inheritedVars = NULL;
    }
}

void registerVarAssign(VariableNodeRef variableNode) {
    assertNotNull(variableNode);

    if (!Trie_has(usedVars, variableNode->name)) {
        Trie_insert(usedVars, variableNode->name, createEntry(variableNode, false, false));
    }
}

void registerVarExp(VariableNodeRef variableNode) {
    assertNotNull(variableNode);

    if (!Trie_has(usedVars, variableNode->name)) {
        Trie_insert(usedVars, variableNode->name, createEntry(variableNode, false, false));
    }
}

void registerVarDef(VariableNodeRef variableNode, Bool isStatic) {
    assertNotNull(variableNode);

    if (!Trie_has(usedVars, variableNode->name)) {
        Trie_insert(usedVars, variableNode->name, createEntry(variableNode, true, isStatic));
    }
}

void registerInputSt(VariableNodeRef variableNode) {
    assertNotNull(variableNode);

    if (!Trie_has(usedVars, variableNode->name)) {
        Trie_insert(usedVars, variableNode->name, createEntry(variableNode, false, false));
    }
}

void registerScope() {
    if (inheritedVars == NULL) inheritedVars = Trie_create();
    if (usedVarsStack == NULL) usedVarsStack = List_create(simpleDestructor); //will delete trie when pop is called

    List_push(usedVarsStack, usedVars);
    usedVars = Trie_create();
}

/** End of parser.variable_register.c */
