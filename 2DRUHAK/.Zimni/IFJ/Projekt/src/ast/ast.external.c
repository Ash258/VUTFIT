// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            ast.external.c
// Assignment:      125, I
// Date:            13/11/17
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "typing.ast.h"
#include "../trie/trie.external.h"

typedef struct ParamData {
    SymbolTableRef table;
    TrieNodeRef    params;
} ParamData, * ParamDataRef;

OperatorTypeRef OperatorType_of(OperatorType type) {
    return copyInstance(sizeof(OperatorType), &type);
}

OperatorType OperatorType_from(Address value) {
    return *((OperatorTypeRef) value);
}

static Bool isFunctionUndefined(void* dataRef1, void* contextRef) {
    return !((FunctionNodeRef) dataRef1)->defined;
}

static Bool compareParamsCompatibility(void* dataRef1, void* dataRef2) {
    return areCompatible(((ParameterRef) dataRef1)->type, ((ParameterRef) dataRef2)->type);
}

static Bool compareParamAndExpressionCompatibility(void* dataRef1, void* dataRef2) {
    return areCompatible(((ParameterRef) dataRef1)->type, getExpressionType(dataRef2));
}

static Bool isImmediate(ASTNodeRef expression) {
    switch (expression->type) {
        case AST_IMMEDIATE_EXP: return true;
        case AST_BINARY_OPERATOR_EXP: return ((BinaryOperatorExpRef) expression)->isImmediate;
        case AST_UNARY_OPERATOR_EXP: return ((UnaryOperatorExpRef) expression)->isImmediate;
        default: return false;
    }
}

static Bool checkParam(ParameterRef node, ParamDataRef data) {
    IF_TRUE_DIE(Table_hasFunction(data->table, node->name), ERR_SEMANTIC_DEFINITION); // check for function name
    IF_TRUE_DIE(Trie_has(data->params, node->name), ERR_SEMANTIC_DEFINITION); // check for duplicity
    Trie_insert(data->params, node->name, node->name);
    return true;
}

static void checkParams(ListRef params, SymbolTableRef table) {
    ParamDataRef data = &(ParamData) {.table = table, .params = &(TrieNode) {0}};
    Trie_init(data->params);
    List_forEach(params, (ListCallback) checkParam, data);
    Trie_dispose(data->params, NULL);
}

//region GeneralDefinitions

ASTNodeRef AST_createASTNode(ASTNodeType type, Address ref) {
    ASTNodeRef astNode = HeapRegister_allocate(G_UNDEFINED, sizeof(ASTNode));

    astNode->type = type;
    astNode->ref  = ref;

    return astNode;
}

ScopeRef AST_createScope(ListRef statements, SymbolTableRef symbolTable) {
    ScopeRef scope = HeapRegister_allocate(G_UNDEFINED, sizeof(Scope));

    scope->statements    = statements;
    scope->symbolTable   = symbolTable;
    scope->inheritedVars = List_create(simpleDestructor);
    scope->carryVars     = List_create(simpleDestructor);
    scope->staticVars    = List_create(simpleDestructor);

    return scope;
}

VariableDefRef AST_createVariableDef(String name, ASTNodeRef initialization, DataType type, Bool isStatic,
                                     SymbolTableRef table) {
    IF_TRUE_DIE(Table_hasVariable(table, name, false) || Table_hasFunction(table, name),
                ERR_SEMANTIC_DEFINITION) //name is used
    IF_FALSE_DIE(initialization == NULL || areCompatible(getExpressionType(initialization), type),
                 ERR_SEMANTIC_COMPATIBILITY);
    IF_FALSE_DIE(initialization == NULL || areCompatible(getExpressionType(initialization), type),
                 ERR_SEMANTIC_COMPATIBILITY);
    IF_TRUE_DIE(isStatic && initialization && !isImmediate(initialization),
                ERR_SEMANTIC_OTHER);

    VariableDefRef variableDef = HeapRegister_allocate(G_UNDEFINED, sizeof(VariableDef));

    variableDef->variable = Table_insertVariable(table, name, type);;
    variableDef->initialization = initialization;
    variableDef->isStatic       = isStatic;

    return variableDef;
}

FunctionNodeRef AST_registerFunctionDefinition(SymbolTableRef table, String name, DataType type, ListRef parameters) {
    TableNodeRef    node = Table_search(table, name);
    FunctionNodeRef function;
    if (node != NULL) {
        IF_TRUE_DIE(node->type == ST_VARIABLE, ERR_SEMANTIC_DEFINITION);
        function = node->ref;

        IF_TRUE_DIE(function->defined, ERR_SEMANTIC_DEFINITION);
        IF_TRUE_DIE(function->declared && !List_equals(function->parameters, parameters, compareParamsCompatibility),
                    ERR_SEMANTIC_DEFINITION);

        IF_TRUE_DIE(function->type != type, ERR_SEMANTIC_DEFINITION);

        List_destruct(function->parameters, true);
        function->parameters = parameters;
        function->defined    = true;
    } else {
        checkParams(parameters, table);
        function = Table_insertFunction(table, name, type, parameters, true, false);
    }

    return function;
}

FunctionNodeRef AST_registerFunctionDeclaration(SymbolTableRef table, String name, DataType type, ListRef parameters) {
    IF_TRUE_DIE(Table_hasVariable(table, name, false) || Table_hasFunction(table, name),
                ERR_SEMANTIC_DEFINITION) //name is used

    checkParams(parameters, table);

    return Table_insertFunction(table, name, type, parameters, false, true);
}

FunctionDefRef AST_createFunctionDef(ScopeRef scope, FunctionNodeRef function, ListRef parameters) {
    FunctionDefRef functionDef = HeapRegister_allocate(G_UNDEFINED, sizeof(FunctionDef));

    functionDef->scope    = scope;
    functionDef->function = function;

    return functionDef;
}

RootRef AST_createRoot(ScopeRef main, ListRef variables, ListRef functions) {
    IF_TRUE_DIE(List_contains(Table_allFunctions(main->symbolTable), isFunctionUndefined, NULL),
                ERR_SEMANTIC_DEFINITION);

    RootRef root = HeapRegister_allocate(G_UNDEFINED, sizeof(Root));

    root->main      = main;
    root->variables = variables;
    root->functions = functions;

    return root;
}

//endregion GeneralDefinitions

//region StatementsDefinitions

AssignmentStRef
AST_createAssignmentSt(ASTNodeRef expression, String variableName, SymbolTableRef table, OperatorType operatorType) {
    if (operatorType != OT_NONE) {
        expression = AST_createASTNode(AST_BINARY_OPERATOR_EXP, AST_createBinaryOperatorExp(
                operatorType,
                AST_createASTNode(AST_VARIABLE_EXP, AST_createVariableExp(variableName, table)),
                expression
        ));
    }

    VariableNodeRef variableNode = Table_searchVariable(table, variableName, true);
    IF_NULL_DIE(variableNode, ERR_SEMANTIC_DEFINITION);
    IF_FALSE_DIE(areCompatible(getExpressionType(expression), variableNode->type), ERR_SEMANTIC_COMPATIBILITY);

    AssignmentStRef assignmentSt = HeapRegister_allocate(G_UNDEFINED, sizeof(AssignmentSt));

    assignmentSt->expression = expression;
    assignmentSt->variable   = variableNode;

    return assignmentSt;
}

LoopStRef AST_createLoopSt(ASTNodeRef expression, ScopeRef scope) {
    IF_TRUE_DIE(getExpressionType(expression) != DT_BOOL, ERR_SEMANTIC_COMPATIBILITY);

    LoopStRef loopSt = HeapRegister_allocate(G_UNDEFINED, sizeof(LoopSt));

    loopSt->condition = expression;
    loopSt->scope     = scope;

    return loopSt;
}

ReturnStRef AST_createReturnSt(ASTNodeRef expression, FunctionNodeRef function) {
    IF_FALSE_DIE(areCompatible(getExpressionType(expression), function->type), ERR_SEMANTIC_COMPATIBILITY);

    ReturnStRef returnSt = HeapRegister_allocate(G_UNDEFINED, sizeof(ReturnSt));

    returnSt->expression = expression;
    returnSt->function   = function;

    return returnSt;
}

IfStRef AST_createIfSt(ASTNodeRef condition, ScopeRef onTrue, ScopeRef onFalse, ListRef alternatives) {
    IF_TRUE_DIE(getExpressionType(condition) != DT_BOOL, ERR_SEMANTIC_COMPATIBILITY);

    IfStRef ifSt = HeapRegister_allocate(G_UNDEFINED, sizeof(IfSt));

    ifSt->condition    = condition;
    ifSt->onTrue       = onTrue;
    ifSt->onFalse      = onFalse;
    ifSt->alternatives = alternatives;

    return ifSt;
}

PrintStRef AST_createPrintSt(ListRef expressions) {
    PrintStRef outputSt = HeapRegister_allocate(G_UNDEFINED, sizeof(PrintSt));

    outputSt->expressions = expressions;

    return outputSt;
}

InputStRef AST_createInputSt(String variableName, SymbolTableRef table) {
    VariableNodeRef variableNode = Table_searchVariable(table, variableName, true);
    IF_NULL_DIE(variableNode, ERR_SEMANTIC_DEFINITION);

    InputStRef inputSt = HeapRegister_allocate(G_UNDEFINED, sizeof(InputSt));

    inputSt->variable = variableNode;

    return inputSt;
}

//endregion StatementsDefinitions

//region ExpressionsDefinitions

FunctionCallExpRef AST_createFunctionCallExp(String name, ListRef arguments, SymbolTableRef table, Bool isNative) {
    FunctionNodeRef function = Table_searchFunction(table, name);
    IF_NULL_DIE(function, ERR_SEMANTIC_DEFINITION); // undefined function
    IF_TRUE_DIE(!List_equals(function->parameters, arguments, compareParamAndExpressionCompatibility),
                ERR_SEMANTIC_COMPATIBILITY); // checks parameters count and dataTypes

    FunctionCallExpRef functionCallExp = HeapRegister_allocate(G_UNDEFINED, sizeof(FunctionCallExp));

    functionCallExp->arguments      = arguments;
    functionCallExp->calledFunction = function;
    functionCallExp->isNative       = isNative;

    return functionCallExp;
}

BinaryOperatorExpRef AST_createBinaryOperatorExp(OperatorType operator, ASTNodeRef left, ASTNodeRef right) {
    BinaryOperatorExpRef binaryOperatorExp = HeapRegister_allocate(G_UNDEFINED, sizeof(BinaryOperatorExp));

    binaryOperatorExp->operator    = operator;
    binaryOperatorExp->left        = left;
    binaryOperatorExp->right       = right;
    binaryOperatorExp->isImmediate = isImmediate(left) && isImmediate(right);
    binaryOperatorExp->type        = getBinaryExpressionType( //check type compatibility
            getExpressionType(left),
            getExpressionType(right),
            operator
    );

    return binaryOperatorExp;
}

ImmediateExpRef AST_createImmediateExp(Address value, DataType type) {
    ImmediateExpRef immediateExp = HeapRegister_allocate(G_UNDEFINED, sizeof(ImmediateExp));

    immediateExp->value = value;
    immediateExp->type  = type;

    return immediateExp;
}

UnaryOperatorExpRef AST_createUnaryOperatorExp(OperatorType operator, ASTNodeRef expression) {

    UnaryOperatorExpRef ref = HeapRegister_allocate(G_UNDEFINED, sizeof(UnaryOperatorExp));
    ref->expression  = expression;
    ref->operator    = operator;
    ref->type        = getUnaryExpressionType(operator, getExpressionType(expression));
    ref->isImmediate = isImmediate(expression);

    return ref;
}

VariableNodeRef AST_createVariableExp(String name, SymbolTableRef table) {
    VariableNodeRef variableNode = Table_searchVariable(table, name, true);
    IF_NULL_DIE(variableNode, ERR_SEMANTIC_DEFINITION); //undefined variable

    return variableNode;
}

//endregion ExpressionsDefinitions

void AST_destructScope(DataRef data) {
    ScopeRef scope = data;

    List_destruct(scope->inheritedVars, true);
    List_destruct(scope->carryVars, true);
    List_destruct(scope->staticVars, true);
    List_destruct(scope->statements, true);

    free(scope);
}

void AST_destructFunctionDef(DataRef data) {
    AST_destructScope(((FunctionDefRef) data)->scope);
    free(data);
}

void AST_destructIfSt(DataRef data) {
    IfStRef statement = data;

    AST_destructASTNode(statement->condition);
    if (statement->alternatives != NULL) List_destruct(statement->alternatives, true);
    if (statement->onFalse != NULL) AST_destructScope(statement->onFalse);
    if (statement->onTrue != NULL) AST_destructScope(statement->onTrue);

    free(statement);
}

void AST_destructASTNode(DataRef data) {
    ASTNodeRef node = data;

    switch (node->type) {
        case AST_VARIABLE_DEF: {
            VariableDefRef def = (VariableDefRef) node->ref;
            if (def->initialization != NULL) AST_destructASTNode(def->initialization);
            free(node->ref);
            break;
        }
        case AST_VARIABLE_EXP:break; //is in symtable
        case AST_BINARY_OPERATOR_EXP:AST_destructASTNode(((BinaryOperatorExpRef) node->ref)->right);
            AST_destructASTNode(((BinaryOperatorExpRef) node->ref)->left);
            free(node->ref);
            break;
        case AST_IMMEDIATE_EXP:free(((ImmediateExpRef) node->ref)->value);
            free(node->ref);
            break;
        case AST_FUNCTION_CALL_EXP:List_destruct(((FunctionCallExpRef) node->ref)->arguments, true);
            free(node->ref);
            break;
        case AST_ASSIGNMENT_ST:AST_destructASTNode(((AssignmentStRef) node->ref)->expression);
            free(node->ref);
            break;
        case AST_RETURN_ST:AST_destructASTNode(((ReturnStRef) node->ref)->expression);
            free(node->ref);
            break;
        case AST_LOOP_ST:AST_destructASTNode(((LoopStRef) node->ref)->condition);
            AST_destructScope(((LoopStRef) node->ref)->scope);
            free(node->ref);
            break;
        case AST_PRINT_ST:List_destruct(((PrintStRef) node->ref)->expressions, true);
            free(node->ref);
            break;
        case AST_IF_ST:AST_destructIfSt(node->ref);
            break;
        case AST_INPUT_ST:free(node->ref);
            break;
        case AST_UNARY_OPERATOR_EXP:AST_destructASTNode(((UnaryOperatorExpRef) node->ref)->expression);
            free(node->ref);
            break;
        case AST_SCOPE_ST:AST_destructScope(node->ref);
            break;
    }

    free(node);
}

/** End of ast.external.c */
