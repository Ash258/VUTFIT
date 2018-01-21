// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            symtable.mock.c
// Assignment:      125, I
// Date:            29.11.2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "../../../../src/c_alias.h"
#include "../../../../src/symtable/symtable.external.h"
#include "../../../../src/ast/ast.external.h"

static int comparationNodesMock(TreeNodeRef node1, TreeNodeRef node2) {
    return strcmp(node1->key, node2->key);
}

SymbolTableRef SymTableMock() {
    return Table_create(NULL);
}

SymbolTableRef SymTableMock_withVar(String name, DataType type) {
    SymbolTableRef table = SymTableMock();
    Table_insertVariable(table, name, type);
    return table;
}

ScopeRef ScopeMock() {
    ScopeRef scope = HeapRegister_allocate(G_GLOBAL, sizeof(Scope));
    scope->symbolTable = SymTableMock();

    scope->statements    = NULL;
    scope->inheritedVars = NULL;
    scope->carryVars     = NULL;
    scope->staticVars    = NULL;

    return scope;
}

ScopeRef ScopeMock_withVar(String name, DataType type) {
    ScopeRef scope = ScopeMock();
    Table_insertVariable(scope->symbolTable, name, type);
    return scope;
}
