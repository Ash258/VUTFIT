// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.variable_info.c
// Assignment:      125, I
// Date:            22/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.variable_info.h"
#include "../format/format.h"
#include "generator.instruction_set.h"
#include "generator.internal.h"

static ListRef VI_ensureList(TrieNodeRef trie, String name) {
    ListRef list = Trie_search(trie, name);
    if (list == NULL) {
        list = HeapRegister_allocate(G_GLOBAL, sizeof(List));
        List_init(list, NULL);
        Trie_insert(trie, name, list);
    }

    return list;
}

static String VI_ensureRename(VariableInfoType type, String name, int scope) {
    switch (type) {
        case VIT_GLOBAL: return Format_name(2, GENERATOR_GLOBAL_PREFIX, name);
        case VIT_AUXILIARY: return Format_generateAddress();
        case VIT_STATIC: {
            String addr = Format_generateAddress();
            String res  = Format_name(3, GENERATOR_STATIC_PREFIX, name, addr);
            free(addr);
            return res;
        }
        case VIT_LOCAL: {
            String addr = Format_generateAddress();
            String res  = Format_name(2, name, addr);
            free(addr);
            return res;
        }
        default: DIE(ERR_OTHER);
    }
}

static inline VariableScope VI_typeOf(VariableInfoType type) {
    switch (type) {
        case VIT_GLOBAL: return VS_GLOBAL;
        case VIT_STATIC: return VS_GLOBAL;
        case VIT_LOCAL: return VS_LOCAL;
        case VIT_AUXILIARY: return VS_TEMP;
    }
    DIE(ERR_OTHER);
}

static VariableInfoRef VI_find(GeneratorRef gen, String name) {
    assertNotNull(gen);
    assertNotNull(name);

    ListRef list = Trie_search(&gen->variables, name);
    return list ? List_first(list) : NULL;
}

bool VI_hasStack(VariableInfoRef variableInfo, const int* stack) {
    return variableInfo->stack <= *stack;
}

static VariableInfoRef VI_findWithStack(GeneratorRef gen, String name, int stack) {
    assertNotNull(gen);
    assertNotNull(name);

    ListRef list = Trie_search(&gen->variables, name);
    return List_search(list, (ListCallback) VI_hasStack, &stack);
}

static void VI_generate(GeneratorRef gen, VariableInfoRef var) {
    List_push(gen->inst, Instruction_defvar(var->variable));
    OperandImmediate value = Generator_implicitValue(var->variable.dataType);
    List_push(gen->inst, Instruction_move(var->variable, Symbol_immediate(value)));
}

VariableInfoRef VariableInfo_create(GeneratorRef gen, VariableNodeRef variable, VariableInfoType scope) {
    assertNotNull(gen);
    assertNotNull(variable);

    VariableInfoRef last = VI_find(gen, variable->name);
    // Already defined in scope or register/clear was not called!
    IF_TRUE_DIE(last && last->stack == List_size(&gen->scopes), ERR_OTHER);

    VariableInfoRef var = HeapRegister_allocate(G_VARIABLES, sizeof(VariableInfo));
    var->stack    = List_size(&gen->scopes);
    var->variable = (OperandVariable) {
            .name = VI_ensureRename(scope, variable->name, var->stack),
            .dataType = variable->type,
            .scope = VI_typeOf(scope)
    };

    VI_generate(gen, var);
    return var;
}

VariableInfoRef VariableInfo_temporary(GeneratorRef gen, DataType type) {
    assertNotNull(gen);

    // TODO: Register VariableInfo destructor to heap register
    VariableInfoRef var = HeapRegister_allocate(G_VARIABLES, sizeof(VariableInfo));
    var->stack    = List_size(&gen->scopes);
    var->variable = (OperandVariable) {
            .name = Format_generateAddress(),
            .dataType = type,
            .scope = VS_TEMP
    };

    VI_generate(gen, var);
    return var;
}

void VariableInfo_destruct(VariableInfoRef variable) {
    free(variable->variable.name);
    free(variable);
}

VariableInfoRef VariableInfo_use(GeneratorRef gen, VariableNodeRef variable) {
    assertNotNull(gen);
    assertNotNull(variable);

    VariableInfoRef var = VI_find(gen, variable->name);
    IF_NULL_DIE(var, ERR_OTHER);

    IF_TRUE_DIE(var->stack > List_size(&gen->scopes), ERR_OTHER);
    return var;
}

VariableInfoRef VariableInfo_useForStack(GeneratorRef gen, VariableNodeRef variable, int stack) {
    assertNotNull(gen);
    assertNotNull(variable);

    VariableInfoRef var = VI_findWithStack(gen, variable->name, stack);
    IF_NULL_DIE(var, ERR_OTHER);

    IF_TRUE_DIE(var->stack > List_size(&gen->scopes), ERR_OTHER);
    return var;
}

void VariableInfo_register(GeneratorRef gen, VariableNodeRef variable, VariableInfoRef var) {
    assertNotNull(gen);
    assertNotNull(variable);
    assertNotNull(var);

    ListRef list = VI_ensureList(&gen->variables, variable->name);
    List_unshift(list, var);
}

static Bool VI_pop(VariableNodeRef variable, GeneratorRef gen) {
    ListRef list = Trie_search(&gen->variables, variable->name);
    IF_NULL_DIE(list, ERR_OTHER);
    List_shift(list);
    return true;
}

void VariableInfo_clear(GeneratorRef gen) {
    assertNotNull(gen);

    ScopeRef scope = List_first(&gen->scopes);
    ListRef  list  = Table_allVariables(scope->symbolTable);
    List_forEach(list, (ListCallback) VI_pop, gen);
    List_destruct(list, false);
}

/** End of generator.variable_info.c */
