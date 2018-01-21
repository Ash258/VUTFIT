// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            symtable.h
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_SYMTABLE_H
#define IFJ2017_SYMTABLE_H

#include "../helpers.h"

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

//region Tree Internal

typedef Address TreeKey;

typedef struct {
    DataRef data;
    TreeKey key;
} * TreeEntryRef, TreeEntry;

typedef struct _TreeNode {
    TreeKey key;
    DataRef data;
    struct _TreeNode* left;
    struct _TreeNode* right;
} TreeNode, * TreeNodeRef;

typedef Int (* Comparator)(TreeNodeRef, TreeNodeRef);

typedef void (* TreeEntryDestructor)(TreeEntry);

/**
 * Initialize new tree.
 *
 * @param rootOfTree Root node of tree.
 */
void Tree_init(TreeNodeRef* rootOfTree);

/**
 * Insert new node into tree.
 *
 * @param rootOfTree Where to put new node.
 * @param key Key of new node.
 * @param data Data of new node.
 * @param cmp Compare function.
 * @param des Destructor function.
 */
void Tree_insert(TreeNodeRef* rootOfTree, TreeKey key, DataRef data, Comparator cmp, TreeEntryDestructor des);

/**
 * Search tree for specific node.
 *
 * @param rootOfTree Where to search.
 * @param key What to search.
 * @param cmp Compare function.
 *
 * @return Reference to data of found node.
 *
 * @throws NULL
 */
DataRef Tree_search(TreeNodeRef rootOfTree, TreeKey key, Comparator cmp);

/**
 * Delete node with given key from tree. (Don't delete data)
 *
 * @param rootOfTree Node will be deleted from this tree.
 * @param key Key of node.
 * @param cmp Compare function.
 *
 * @return Data of deleted tree.
 *
 * @throws NULL
 */
TreeEntry Tree_delete(TreeNodeRef* rootOfTree, TreeKey key, Comparator cmp);

/**
 * Traverse through whole tree.
 *
 * @param root Root of tree.
 * @param callback
 * @param context
 */
void Tree_forEach(TreeNodeRef root, void (* callback)(DataRef data, ContextRef cont), ContextRef context);

/**
 * Remove whole tree.
 *
 * @param root Root node of tree to delete.
 * @param des Destructor function.
 */
void Tree_dispose(TreeNodeRef* root, TreeEntryDestructor keyDestructor);

//endregion Tree Internal

//region Binary Tree

typedef struct {
    TreeNodeRef root;

    Int (* comparator)(TreeNodeRef node1, TreeNodeRef node2);

    TreeEntryDestructor destructor;
} * BinaryTreeRef, BinaryTree;

/**
 * Allocate new binary tree.
 *
 * @return Reference to created tree.
 */
BinaryTreeRef BT_create(void);

/**
 * Initialize binary tree.
 *
 * @param tree Tree to be initialized.
 * @param cmp Function for comparing nodes.
 * @param des Function for destroying node data.
 * @param keyDestructor Function for destroying key.
 */
void BT_init(BinaryTreeRef tree, Comparator cmp, TreeEntryDestructor destructor);

/**
 * Insert new node into tree.
 *
 * @param tree Where to put new node.
 * @param key Key of new node.
 * @param data Data of new node.
 */
void BT_insert(BinaryTreeRef tree, TreeKey key, DataRef data);

/**
 * Search tree for specific node.
 *
 * @param tree Where to search.
 * @param key What to search.
 *
 * @return Reference to data of found node.
 *
 * @throws NULL
 */
DataRef BT_search(BinaryTreeRef tree, TreeKey key);

/**
 * Check if binary tree has node with given key.
 *
 * @param tree Where to search.
 * @param key What to search.
 *
 * @return true if data are set.
 */
Bool BT_has(BinaryTreeRef tree, TreeKey key);

/**
 * Travers through whole tree.
 *
 * @param tree Tree to traverse.
 * @param callback Function to be called.
 * @param context Context.
 */
void BT_forEach(BinaryTreeRef tree, void (* callback)(DataRef data, ContextRef cont), ContextRef context);

/**
 * Delete node from tree.
 *
 * @param tree From where node will be deleted.
 * @param key Key of node.
 *
 * @return Data of deleted tree.
 *
 * @throws NULL
 */
TreeEntry BT_delete(BinaryTreeRef tree, TreeKey key);

/**
 *
 * @param tree
 * @param data
 * @param key
 */
void BT_deleteEntry(BinaryTreeRef tree, DataRef data, TreeKey key);

/**
 * Dispose tree.
 *
 * @param tree - Tree to be disposed.
 * @param deleteData - if true and destructor is set, data will be deleted via destructor
 */
void BT_dispose(BinaryTreeRef tree, Bool deleteData);

/**
 * Delete data and self.
 *
 * @param tree Tree to be deleted.
 */
void BT_destruct(BinaryTreeRef tree);

//endregion Binary Tree

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
FunctionNodeRef Table_insertFunction(SymbolTableRef table, String name, DataType returnType, ListRef parameters, Bool defined, Bool declared);

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

#endif //IFJ2017_SYMTABLE_H

/** End of symtable.h */
