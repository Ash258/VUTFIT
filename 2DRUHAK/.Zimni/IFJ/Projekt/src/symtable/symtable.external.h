// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            symtable.external.h
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_SYMTABLE_EXTERNAL_H
#define IFJ2017_SYMTABLE_EXTERNAL_H

#include <stdbool.h>
#include "../binarytree/binary_tree.external.h"

//region Members

typedef enum {
    ST_VARIABLE,
    ST_FUNCTION,
} STNodeType;

typedef enum {
    DT_INTEGER,
    DT_FLOAT,
    DT_STRING,
    DT_BOOL,
} * DataTypeRef, DataType;

typedef struct {
    String   name;
    DataType type;
    ListRef  parameters;
    Bool     defined;
    Bool     declared;
} * FunctionNodeRef, FunctionNode;

typedef struct {
    String   name;
    DataType type;
} * ParameterRef, * VariableNodeRef, VariableNode, Parameter;

//endregion Members

typedef struct {
    STNodeType type;
    Address    ref;
} * TableNodeRef, TableNode;

typedef struct _SymbolTable {
    struct _SymbolTable* parent;
    BinaryTree values;
} * SymbolTableRef, SymbolTable;

/**
 * @param type - value of instance
 *
 * @return instance
 */
DataTypeRef DataType_of(DataType type);

/**
 * @param value - instance
 *
 * @return value
 */
DataType DataType_from(Address value);

/**
 * Create table.
 *
 * @param parent Parent table.
 *
 * @return Reference to created table.
 *
 * @throws NULL
 */
SymbolTableRef Table_create(SymbolTableRef parent);

/**
 * Initialize table.
 *
 * @param table Table to be initialized.
 * @param parent Parent table.
 */
void Table_init(SymbolTableRef table, SymbolTableRef parent);

/**
 * Create parameter.
 *
 * @param name Parameter name.
 * @param type Parameter type.
 *
 * @return Reference to created parameter.
 *
 * @throws NULL
 */
ParameterRef Table_createParameter(String name, DataType type);

/**
 * Insert function node into table.
 *
 * @param table Where to insert.
 * @param name Name of node to be inserted.
 * @param returnType Return type of function.
 * @param parameters List of parameters.
 * @param defined Was function defined?
 * @param declared Was function declared?
 */
FunctionNodeRef
Table_insertFunction(SymbolTableRef table, String name, DataType returnType, ListRef parameters, Bool defined,
                     Bool declared);

/**
 * Insert variable node into table.
 *
 * @param table Where to insert.
 * @param name Name of variable node.
 * @param type Type of variable.
 */
VariableNodeRef Table_insertVariable(SymbolTableRef table, String name, DataType type);

/**
 * Check if there is function node with given name in table.
 *
 * @param table Where to search.
 * @param name What to search.
 *
 * @return true if there is function with given name.
 *         false otherwise
 */
Bool Table_hasFunction(SymbolTableRef table, String name);

/**
 * Check if there is variable node with given name in table.
 *
 * @param table Where to search.
 * @param name What to search.
 * @param ripple Look in current table or in chain?
 *
 * @return true if there is variable with given name.
 *         false otherwise
 */
Bool Table_hasVariable(SymbolTableRef table, String name, Bool ripple);

/**
 * @param table - instance
 * @param name - name to search
 *
 * @return True if table has registered name (either function or variable], false otherwise
 */
Bool Table_has(SymbolTableRef table, String name);

/**
 * @param table - instance
 * @param name - name to search
 *
 * @return Node with ref to function or variable
 */
TableNodeRef Table_search(SymbolTableRef table, String name);

/**
 * Search if there is function node with given name in table.
 *
 * @param table Where to search.
 * @param name What to search.
 *
 * @return Reference to found function node.
 *
 * @throws NULL
 */
FunctionNodeRef Table_searchFunction(SymbolTableRef table, String name);

/**
 * Search if there is variable node with given name in table.
 *
 * @param table Where to search.
 * @param name What to search.
 * @param ripple Look in current table or in table chain?
 *
 * @return Reference to found variable node.
 *
 * @throws NULL
 */
VariableNodeRef Table_searchVariable(SymbolTableRef table, String name, Bool ripple);

/**
 * List all functions.
 *
 * @param table In this table list all functions.
 *
 * @return Reference to list of all functions.
 */
ListRef Table_allFunctions(SymbolTableRef table);

/**
 * List all variables.
 *
 * @param table In this table list all variables.
 *
 * @return Reference to list of all variables.
 */
ListRef Table_allVariables(SymbolTableRef table);

/**
 * Destroy parameter.
 *
 * @param parameter Parameter to be destroyed.
 */
void Table_destructParameter(DataRef parameter);

/**
 * Dispose given table.
 *
 * @param toDispose Table to be disposed.
 */
void Table_dispose(DataRef toDispose);

#endif //IFJ2017_SYMTABLE_EXTERNAL_H

/** End of symtable.external.h */
