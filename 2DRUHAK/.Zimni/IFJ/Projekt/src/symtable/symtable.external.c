// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            symtable.external.c
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "symtable.external.h"

//region Internals

/**
 * Compare two nodes by their key.
 *
 * @param node1 First node.
 * @param node2 Second node.
 *
 * @return Result of string compare.
 */
static int compareNodes(TreeNodeRef node1, TreeNodeRef node2) {
    return strcmp(node1->key, node2->key);
}

/**
 * Create function node.
 *
 * @param name Name of function.
 * @param returnType Return type of function.
 * @param parameters Parameters of function.
 *
 * @return Reference to created function node.
 *
 * @throws NULL
 */
static FunctionNodeRef createFunctionNode(String name, DataType returnType, ListRef parameters, Bool defined, Bool
declared) {
    FunctionNodeRef func = (FunctionNodeRef) malloc(sizeof(FunctionNode));
    IF_NULL_RETURN_NULL(func);

    func->type       = returnType;
    func->name       = name;
    func->parameters = parameters;
    func->defined    = defined;
    func->declared   = declared;

    return func;
}

/**
 * Destroy function node.
 *
 * @param toDelete Node to be destroyed.
 */
static void destructFunctionNode(DataRef toDelete);

/**
 * Create variable node.
 *
 * @param name Name of variable.
 * @param type Type of variable.
 *
 * @return Reference to created variable node.
 *
 * @throws NULL
 */
static VariableNodeRef createVariableNode(String name, DataType type) {
    VariableNodeRef var = (VariableNodeRef) malloc(sizeof(VariableNode));
    IF_NULL_RETURN_NULL(var);

    var->name = name;
    var->type = type;

    return var;
}

static TableNodeRef createTableNode(Address data, STNodeType type) {
    TableNodeRef node = HeapRegister_allocate(G_UNDEFINED, sizeof(TableNode));

    node->type = type;
    node->ref  = data;

    return node;
}

/**
 * Pick function and push it to list.
 *
 * @param data Data to be
 * @param context
 */
void Table_pickFunction(DataRef data, ContextRef context) {
    TableNodeRef node = (TableNodeRef) data;
    if (node->type == ST_FUNCTION) List_push(context, node->ref);
}

/**
 * Pick variable and push it to list.
 *
 * @param data Data to be
 * @param context
 */
void Table_pickVariable(DataRef data, ContextRef context) {
    TableNodeRef node = (TableNodeRef) data;
    if (node->type == ST_VARIABLE) List_push(context, node->ref);
}

//endregion Internals

SymbolTableRef Table_create(SymbolTableRef parent) {
    // TODO: Heap register
    SymbolTableRef table = (SymbolTableRef) malloc(sizeof(SymbolTable));
    IF_NULL_RETURN_NULL(table);

    Table_init(table, parent);

    return table;
}

ParameterRef Table_createParameter(String name, DataType type) {
    ParameterRef parameter = (ParameterRef) malloc(sizeof(Parameter));
    IF_NULL_RETURN_NULL(parameter);

    parameter->name = name;
    parameter->type = type;

    return parameter;
}

//region Destructors

/**
 * Destroy variable node.
 *
 * @param toDelete Node to be destroyed.
 */
void destructVariableNode(DataRef toDelete) {
    free(toDelete);
}

/**
 * Wrapper function for destroying.
 *
 * @param toDelete Reference to data for deleting.
 */
void destructFunctionNode(DataRef toDelete) {
    ((FunctionNodeRef) toDelete)->parameters->destructor(((FunctionNodeRef) toDelete)->parameters);
    free(toDelete);
}

void destructNode(TreeEntry entry) {
    // TODO: Destruct Key
    TableNodeRef node = (TableNodeRef) entry.data;
    (node->type == ST_VARIABLE ? destructVariableNode : destructFunctionNode)(node->ref);
    free(node);
}

void Table_destructParameter(DataRef parameter) {
    free(parameter);
}

//endregion Destructors

void Table_init(SymbolTableRef table, SymbolTableRef parent) {
    table->parent = parent;
    BT_init(&table->values, compareNodes, destructNode);
}

FunctionNodeRef Table_insertFunction(SymbolTableRef table, String name, DataType returnType, ListRef parameters, Bool defined, Bool declared) {
    FunctionNodeRef fun = createFunctionNode(name, returnType, parameters, defined, declared);
    BT_insert(&table->values, name, createTableNode(fun, ST_FUNCTION));

    return fun;
}

VariableNodeRef Table_insertVariable(SymbolTableRef table, String name, DataType type) {
    VariableNodeRef var = createVariableNode(name, type);
    BT_insert(&table->values, name, createTableNode(var, ST_VARIABLE));

    return var;
}

Bool Table_hasFunction(SymbolTableRef table, String name) {
    return Table_searchFunction(table, name) != NULL;
}

Bool Table_hasVariable(SymbolTableRef table, String name, Bool ripple) {
    return Table_searchVariable(table, name, ripple) != NULL;
}

Bool Table_has(SymbolTableRef table, String name) {
    return BT_has(&table->values, name);
}

TableNodeRef Table_search(SymbolTableRef table, String name) {
    return BT_search(&table->values, name);
}

static SymbolTableRef Table_getTableRoot(SymbolTableRef table) {
    while (table->parent != NULL) {
        table = table->parent;
    }

    return table;
}

FunctionNodeRef Table_searchFunction(SymbolTableRef table, String name) {
    assertNotNull(table);

    TableNodeRef aux = BT_search(&Table_getTableRoot(table)->values, name);

    return aux == NULL || aux->type == ST_VARIABLE ? NULL : aux->ref;
}

VariableNodeRef Table_searchVariable(SymbolTableRef table, String name, Bool ripple) {
    assertNotNull(table);

    TableNodeRef node = NULL;

    do {
        node = (TableNodeRef) BT_search(&table->values, name);
        if (node && node->type == ST_VARIABLE) return node->ref;

        table = table->parent;
    } while (ripple && table);

    return NULL;
}

ListRef Table_allFunctions(SymbolTableRef table) {
    ListRef list = List_create(NULL);
    BT_forEach(&Table_getTableRoot(table)->values, &Table_pickFunction, list);

    return list;
}

ListRef Table_allVariables(SymbolTableRef table) {
    ListRef list = List_create(NULL);
    BT_forEach(&table->values, &Table_pickVariable, list);

    return list;
}

void Table_dispose(DataRef table) {
    BT_dispose(&((SymbolTableRef) table)->values, true);
    Table_init(table, NULL);
}

void Table_destruct(DataRef table) {
    assertNotNull(table);

    Table_dispose(table);
    free(table);
}

DataTypeRef DataType_of(DataType type) {
    return copyInstance(sizeof(DataType), &type);
}

DataType DataType_from(Address value) {
    return *((DataTypeRef) value);
}

/** End of symtable.external.c */
