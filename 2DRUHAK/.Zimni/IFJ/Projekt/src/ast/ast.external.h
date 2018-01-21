// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            ast.external.h
// Assignment:      125, I
// Date:            05/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_AST_EXTERNAL_H
#define IFJ2017_AST_EXTERNAL_H

#include "../helpers.h"
#include "../symtable/symtable.external.h"

//region General

typedef enum {
    // General

    AST_VARIABLE_DEF,

    // Expressions

    AST_VARIABLE_EXP,
    AST_BINARY_OPERATOR_EXP,
    AST_UNARY_OPERATOR_EXP,
    AST_IMMEDIATE_EXP,
    AST_FUNCTION_CALL_EXP,

    // Statements

    AST_ASSIGNMENT_ST,
    AST_RETURN_ST,
    AST_LOOP_ST,
    AST_PRINT_ST,
    AST_IF_ST,
    AST_INPUT_ST,
    AST_SCOPE_ST
} ASTNodeType;

typedef enum {
    OT_NONE,   //operator as NULL value
    OT_ADD,    // +    addition
    OT_SUB,    // -    subtraction
    OT_DIV,    // /    result of division is number with floating point
    OT_IDIV,   // \    result of division is integer
    OT_MUL,    // *    multiple

    OT_GT,     // >    greater than
    OT_GEQ,    // >=   greater equal
    OT_LT,     // <    lower than
    OT_LEQ,    // <=   lower equal
    OT_EQ,     // =    equal
    OT_NEQ,    // <>   not equal

    OT_NOT,
    OT_AND,
    OT_OR
} * OperatorTypeRef, OperatorType;

typedef struct {
    ASTNodeType type;
    Address     ref;
} * ASTNodeRef, ASTNode;

typedef struct {
    ListRef        statements;
    ListRef        inheritedVars;
    ListRef        carryVars;
    ListRef        staticVars;
    SymbolTableRef symbolTable;
} * ScopeRef, Scope;

typedef struct {
    VariableNodeRef variable;
    Bool            isStatic;
    ASTNodeRef      initialization;
} * VariableDefRef, VariableDef;

typedef struct {
    FunctionNodeRef function;
    ScopeRef        scope;
} * FunctionDefRef, FunctionDef;

typedef struct {
    ScopeRef main;
    ListRef  variables;
    ListRef  functions;
} * RootRef, Root;

//endregion General

//region Expressions

typedef struct {
    FunctionNodeRef calledFunction;
    ListRef         arguments;
    Bool            isNative;
} * FunctionCallExpRef, FunctionCallExp;

typedef struct {
    Address  value;
    DataType type;
} * ImmediateExpRef, ImmediateExp;

typedef struct {
    OperatorType operator;
    ASTNodeRef   left;
    ASTNodeRef   right;
    DataType     type;
    Bool         isImmediate;
} * BinaryOperatorExpRef, BinaryOperatorExp;

typedef struct {
    ASTNodeRef   expression;
    OperatorType operator;
    DataType     type;
    Bool         isImmediate;
} * UnaryOperatorExpRef, UnaryOperatorExp;

//endregion Expressions

//region Statements

typedef struct {
    ASTNodeRef      expression;
    VariableNodeRef variable;
} * AssignmentStRef, AssignmentSt;

typedef struct {
    ASTNodeRef condition;
    ScopeRef   scope;
} * LoopStRef, LoopSt;

typedef struct {
    ASTNodeRef      expression;
    FunctionNodeRef function;
} * ReturnStRef, ReturnSt;

typedef struct _IfSt {
    ASTNodeRef condition;
    ScopeRef   onTrue;
    ScopeRef   onFalse;
    ListRef    alternatives;
} * IfStRef, IfSt;

typedef struct {
    VariableNodeRef variable;
} * InputStRef, InputSt;

typedef struct {
    ListRef expressions;
} * PrintStRef, PrintSt;

//endregion Statements

//region GeneralDeclarations

/**
 * @param type - instance value
 *
 * @return instance
 */
OperatorTypeRef OperatorType_of(OperatorType type);

/**
 * @param value - instance
 *
 * @return value
 */
OperatorType OperatorType_from(Address value);

/**
 * @param type NodeType
 * @param ref Address reference.
 *
 * @return Reference to created structure.
 */
ASTNodeRef AST_createASTNode(ASTNodeType type, Address ref);

/**
 * @param data - node to destruct
 */
void AST_destructASTNode(DataRef data);

/**
 * @param statements Statements list.
 * @param symbolTable SymbolTable.
 *
 * @return Reference to created structure.
 */
ScopeRef AST_createScope(ListRef statements, SymbolTableRef symbolTable);

/**
 * @param name Variable name.
 * @param initialization Node reference.
 * @param data DataType
 * @param symbolTable SymbolTable.
 *
 * @return Reference to created structure.
 */
VariableDefRef AST_createVariableDef(String name, ASTNodeRef initialization, DataType data, Bool isStatic, SymbolTableRef table);

/**
 * @param table - current symbol table
 * @param name - function name
 * @param type - function type
 * @param parameters - function parameters
 *
 * @return instance
 */
FunctionNodeRef AST_registerFunctionDefinition(SymbolTableRef table, String name, DataType type, ListRef parameters);

/**
 * @param table - current symbol table
 * @param name - function name
 * @param type - function type
 * @param parameters - function parameters
 *
 * @return instance
 */
FunctionNodeRef AST_registerFunctionDeclaration(SymbolTableRef table, String name, DataType type, ListRef parameters);

/**
 *
 * @param scope - Scope reference.
 * @param function - symtable node reference
 *
 * @return Reference to created structure.
 */
FunctionDefRef AST_createFunctionDef(ScopeRef scope, FunctionNodeRef function, ListRef parameters);

/**
 * @param data - scope to destruct
 */
void AST_destructScope(DataRef data);

/**
 * @param data - function to destruct
 */
void AST_destructFunctionDef(DataRef data);

/**
 *
 * @param main Scope reference.
 * @param variables Variables list.
 * @param functions Functions list.
 *
 * @return Reference to created structure.
 */
RootRef AST_createRoot(ScopeRef main, ListRef variables, ListRef functions);

//endregion GeneralDeclarations

//region ExpressionsDeclarations

/**
 * @param name Function name.
 * @param arguments Arguments list.
 * @param table Symbol table.
 *
 * @return Reference to created structure.
 */
FunctionCallExpRef AST_createFunctionCallExp(String name, ListRef arguments, SymbolTableRef table, Bool isNative);

/**
 * @param value Address.
 * @param type Symbol table.
 *
 * @return Reference to created structure.
 */
ImmediateExpRef AST_createImmediateExp(Address value, DataType type);

/**
 * @param operator
 * @param expression
 *
 * @return instance
 */
UnaryOperatorExpRef AST_createUnaryOperatorExp(OperatorType operator, ASTNodeRef expression);

/**
 * @param operator OperatorType
 * @param left Node reference.
 * @param right Node reference.
 * @param table Symbol table.
 *
 * @return Reference to created structure.
 */
BinaryOperatorExpRef AST_createBinaryOperatorExp(OperatorType operator, ASTNodeRef left, ASTNodeRef right);

/**
 * @param name Variable name.
 * @param table Symbol table.
 *
 * @return Reference to created structure.
 */
VariableNodeRef AST_createVariableExp(String name, SymbolTableRef table);

//endregion ExpressionsDeclarations

//region StatementsDeclarations

/**
 * @param expression Node reference.
 * @param variableName Variable name.
 * @param table Symbol table.
 *
 * @return Reference to created structure.
 */
AssignmentStRef AST_createAssignmentSt(ASTNodeRef expression, String variableName, SymbolTableRef table, OperatorType operatorType);

/**
 * @param condition Node reference.
 * @param scope Scope reference.
 *
 * @return Reference to created structure.
 */
LoopStRef AST_createLoopSt(ASTNodeRef condition, ScopeRef scope);

/**
 * @param expression Node
 * @param functionName Function name.
 * @param table Symbol table.
 *
 * @return Reference to created structure.
 */
ReturnStRef AST_createReturnSt(ASTNodeRef expression, FunctionNodeRef function);

/**
 * @param condition Node reference.
 * @param onTrue Scope reference.
 * @param onFalse Scope reference.
 * @param alternatives Alternatives list.
 *
 * @return Reference to created structure.
 */
IfStRef AST_createIfSt(ASTNodeRef condition, ScopeRef onTrue, ScopeRef onFalse, ListRef alternatives);

/**
 * @param data - data to destruct
 */
void AST_destructIfSt(DataRef data);

/**
 * @param variable Input name.
 * @param table Symbol table.
 *
 * @return Reference to created structure.
 */
InputStRef AST_createInputSt(String variableName, SymbolTableRef table);

/**
 * @param expression Expression list.
 *
 * @return Reference to created structure.
 */
PrintStRef AST_createPrintSt(ListRef expressions);

//endregion StatementsDeclarations

#endif //IFJ2017_AST_EXTERNAL_H

/** End of ast.external.h */
