// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            parser.external.c
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "parser.external.h"
#include "../pipeline/pipeline.external.h"
#include "parser.variable_register.h"

static List            symbolTables, expressionChains; //TODO - register all these lists to heap register
static FunctionNodeRef parsedFunction;
static bool            expressionChainsInitialized = false;
static bool            nativeFunctionsInitialized  = false;

//region Declarations

Bool insertParameterIntoTable(DataRef data, ContextRef context);

VariableDefRef parseVariable(TokenizerRef tokenizer, Bool isShared, Bool isStatic);

void parseFunctionDeclaration(TokenizerRef tokenizer);

ListRef parseParameters(TokenizerRef tokenizer);

FunctionDefRef parseFunctionDefinition(TokenizerRef tokenizer);

ScopeRef parseScope(TokenizerRef tokenizer, ListRef parameters);

ASTNodeRef parseStatement(TokenizerRef tokenizer);

ScopeRef parseBlock(TokenizerRef tokenizer, Bool enforceEol);

InputStRef parseInputStatement(TokenizerRef tokenizer);

PrintStRef parsePrintStatement(TokenizerRef tokenizer);

ReturnStRef parseReturnStatement(TokenizerRef tokenizer);

IfStRef parseIfStatement(TokenizerRef tokenizer);

IfStRef parseIfAlternativeStatement(TokenizerRef tokenizer);

LoopStRef parseLoopStatement(TokenizerRef tokenizer);

ASTNodeRef parseExpression(TokenizerRef tokenizer);

ASTNodeRef parseImmediateExpression(TokenizerRef tokenizer, TokenType tokenType, DataType dataType);

ASTNodeRef parseParenthesisExpression(TokenizerRef tokenizer);

ASTNodeRef parseIdentifierExpression(TokenizerRef tokenizer);

void* parseBinaryExpression(void* passable, ContextRef data, ClosurePipeRef next);

void* parseAtomicExpression(void* passable, ContextRef data);

void initializeExpressionChains();

ListRef parseArguments(TokenizerRef tokenizer);

Address parseAssignmentStatement(TokenizerRef tokenizer);

void* parseUnaryOperator(void* passable, ContextRef data, ClosurePipeRef next);

ASTNodeRef parseNativeFunctionCallExpression(TokenizerRef tokenizer);

void initializeNativeFunctions();

//endregion Declarations

RootRef Parser_parse(TokenizerRef tokenizer) {
    List_init(&symbolTables, &Table_dispose);
    List_push(&symbolTables, Table_create(NULL));
    initializeExpressionChains();
    initializeNativeFunctions();

    ListRef  functions = List_create(AST_destructFunctionDef);
    ListRef  variables = List_create(NULL);
    ScopeRef mainScope = NULL;

    while (!Tokenizer_eof(tokenizer)) {
        switch (Tokenizer_current(tokenizer)->type) {
            case T_K_DIM:List_push(variables, parseVariable(tokenizer, true, false));
                break;
            case T_K_DECLARE:parseFunctionDeclaration(tokenizer);
                break;
            case T_K_FUNCTION:List_push(functions, parseFunctionDefinition(tokenizer));
                break;
            case T_K_SCOPE:mainScope = parseBlock(tokenizer, false);
                while (Tokenizer_hasCurrent(tokenizer, T_EOL)) {
                    Tokenizer_next(tokenizer);
                }
                IF_FALSE_DIE(Tokenizer_eof(tokenizer), ERR_SYNTAX);
                break;
            case T_EOL: Tokenizer_next(tokenizer);
                break;
            default: DIE(ERR_SYNTAX);
        }
    }

    IF_NULL_DIE(mainScope, ERR_SYNTAX);
    List_pop(&symbolTables);

    return AST_createRoot(mainScope, variables, functions);
}

void initializeNativeFunctions() {
    if (!nativeFunctionsInitialized) {
        nativeFunctionsInitialized = true;
        SymbolTableRef table       = List_last(&symbolTables);

        ListRef params = List_create(Table_destructParameter);
        List_push(params, Table_createParameter("s", DT_STRING));
        Table_insertFunction(table, "LENGTH", DT_INTEGER, params, true, true);

        params = List_create(Table_destructParameter);
        List_push(params, Table_createParameter("s", DT_STRING));
        List_push(params, Table_createParameter("i", DT_INTEGER));
        List_push(params, Table_createParameter("n", DT_INTEGER));
        Table_insertFunction(table, "SUBSTR", DT_STRING, params, true, true);

        params = List_create(Table_destructParameter);
        List_push(params, Table_createParameter("s", DT_STRING));
        List_push(params, Table_createParameter("i", DT_INTEGER));
        Table_insertFunction(table, "ASC", DT_INTEGER, params, true, true);

        params = List_create(Table_destructParameter);
        List_push(params, Table_createParameter("i", DT_INTEGER));
        Table_insertFunction(table, "CHR", DT_STRING, params, true, true);
    }
}

void initializeExpressionChains() {
    if (!expressionChainsInitialized) {
        expressionChainsInitialized = true;
        List_init(&expressionChains, &simpleDestructor);

        List_push(&expressionChains, Pipeline_createClosureChain(TokenType_of(T_O_LOGICAL), &parseBinaryExpression));
        List_push(&expressionChains, Pipeline_createClosureChain(TokenType_of(T_O_NOT), &parseUnaryOperator));
        List_push(&expressionChains, Pipeline_createClosureChain(TokenType_of(T_O_RELATIONAL), &parseBinaryExpression));
        List_push(&expressionChains, Pipeline_createClosureChain(TokenType_of(T_O_PLUS), &parseBinaryExpression));
        List_push(&expressionChains, Pipeline_createClosureChain(TokenType_of(T_O_MINUS), &parseBinaryExpression));
        List_push(&expressionChains,
                  Pipeline_createClosureChain(TokenType_of(T_O_DECIMAL_DIVISION), &parseBinaryExpression));
        List_push(&expressionChains,
                  Pipeline_createClosureChain(TokenType_of(T_O_MULTIPLICATION), &parseBinaryExpression));
        List_push(&expressionChains, Pipeline_createClosureChain(TokenType_of(T_O_MINUS), &parseUnaryOperator));
    }
}

ScopeRef parseBlock(TokenizerRef tokenizer, Bool enforceEol) {

    Tokenizer_step(tokenizer, 2, T_K_SCOPE, T_EOL);
    ScopeRef scope = parseScope(tokenizer, NULL);
    Tokenizer_step(tokenizer, 2, T_K_END, T_K_SCOPE);
    if (enforceEol) Tokenizer_step(tokenizer, 1, T_EOL);

    return scope;
}

FunctionDefRef parseFunctionDefinition(TokenizerRef tokenizer) {
    String name = (String) Tokenizer_step(tokenizer, 2, T_K_FUNCTION, T_IDENTIFIER)->value;
    Tokenizer_step(tokenizer, 1, T_LEFT_PARENTHESIS);
    ListRef  parameters = parseParameters(tokenizer);
    DataType type       =
                     *((DataTypeRef) Tokenizer_step(tokenizer, 3, T_RIGHT_PARENTHESIS, T_K_AS, T_DATA_TYPE)->value);
    Tokenizer_step(tokenizer, 1, T_EOL);

    FunctionNodeRef function = AST_registerFunctionDefinition(List_last(&symbolTables), name, type, parameters);

    parsedFunction = function;
    ScopeRef scope = parseScope(tokenizer, parameters);
    Tokenizer_step(tokenizer, 3, T_K_END, T_K_FUNCTION, T_EOL);
    parsedFunction = NULL;

    return AST_createFunctionDef(scope, function, parameters);
}

ScopeRef parseScope(TokenizerRef tokenizer, ListRef parameters) {
    ListRef    statements = List_create(AST_destructASTNode);
    ASTNodeRef statement;

    List_push(&symbolTables, Table_create(List_last(&symbolTables)));
    registerScope();
    if (parameters != NULL) List_forEach(parameters, &insertParameterIntoTable, List_last(&symbolTables));

    while ((statement = parseStatement(tokenizer)) != NULL) {
        List_push(statements, statement);
    }

    ScopeRef scope = AST_createScope(statements, List_pop(&symbolTables));
    pickScopeVars(scope);

    return scope;
}

ASTNodeRef parseStatement(TokenizerRef tokenizer) {
    switch (Tokenizer_current(tokenizer)->type) {
        case T_K_DIM: return AST_createASTNode(AST_VARIABLE_DEF, parseVariable(tokenizer, false, false));
        case T_K_STATIC: return AST_createASTNode(AST_VARIABLE_DEF, parseVariable(tokenizer, false, true));
        case T_IDENTIFIER: return AST_createASTNode(AST_ASSIGNMENT_ST, parseAssignmentStatement(tokenizer));
        case T_K_INPUT: return AST_createASTNode(AST_INPUT_ST, parseInputStatement(tokenizer));
        case T_K_PRINT: return AST_createASTNode(AST_PRINT_ST, parsePrintStatement(tokenizer));
        case T_K_RETURN: return AST_createASTNode(AST_RETURN_ST, parseReturnStatement(tokenizer));
        case T_K_IF: return AST_createASTNode(AST_IF_ST, parseIfStatement(tokenizer));
        case T_K_DO: return AST_createASTNode(AST_LOOP_ST, parseLoopStatement(tokenizer));
        case T_K_SCOPE: return AST_createASTNode(AST_SCOPE_ST, parseBlock(tokenizer, true));
        case T_EOL: return (Tokenizer_next(tokenizer), parseStatement(tokenizer));
        default: return NULL;
    }
}

Address parseAssignmentStatement(TokenizerRef tokenizer) {
    String name = Tokenizer_step(tokenizer, 1, T_IDENTIFIER)->value;

    TokenRef     token        = Tokenizer_current(tokenizer);
    OperatorType operatorType = OT_NONE;
    if (!Token_hasType(token, T_O_RELATIONAL)) {
        TokenType tokenType = token->type;
        if (tokenType != T_O_PLUS && tokenType != T_O_MULTIPLICATION && tokenType != T_O_DECIMAL_DIVISION &&
            tokenType != T_O_MINUS) {
            DIE(ERR_SYNTAX);
        }
        operatorType = OperatorType_from(token->value);
        token        = Tokenizer_next(tokenizer);
    }

    IF_FALSE_DIE(Token_hasType(token, T_O_RELATIONAL) && OperatorType_from(token->value) == OT_EQ, ERR_SYNTAX)
    Tokenizer_next(tokenizer);

    ASTNodeRef expression = parseExpression(tokenizer);

    AssignmentStRef statement = AST_createAssignmentSt(expression, name, List_last(&symbolTables), operatorType);
    registerVarAssign(statement->variable);

    return statement;
}

LoopStRef parseLoopStatement(TokenizerRef tokenizer) {
    Tokenizer_step(tokenizer, 2, T_K_DO, T_K_WHILE);
    ASTNodeRef expression = parseExpression(tokenizer);
    Tokenizer_step(tokenizer, 1, T_EOL);
    ScopeRef scope = parseScope(tokenizer, NULL);
    Tokenizer_step(tokenizer, 2, T_K_LOOP, T_EOL);

    return AST_createLoopSt(expression, scope);
}

ASTNodeRef parseExpression(TokenizerRef tokenizer) {
    ClosureFinal final = {.callback = &parseAtomicExpression, .data = NULL};

    return Pipeline_run(tokenizer, &expressionChains, &final);
}

void* parseUnaryOperator(void* passable, ContextRef data, ClosurePipeRef next) {
    TokenizerRef tokenizer = passable;
    TokenType    tokenType = TokenType_from(data);
    if (Tokenizer_hasCurrent(tokenizer, tokenType)) {
        OperatorType        operator = OperatorType_from(Tokenizer_step(tokenizer, 1, tokenType)->value);
        UnaryOperatorExpRef ref      = AST_createUnaryOperatorExp(operator, parseUnaryOperator(passable, data, next));
        return AST_createASTNode(AST_UNARY_OPERATOR_EXP, ref);
    }

    return next->callback(passable, next);
}

void* parseBinaryExpression(void* passable, ContextRef data, ClosurePipeRef next) {
    TokenizerRef tokenizer = passable;
    ASTNodeRef   result    = next->callback(passable, next);
    TokenType    tokenType = TokenType_from(data);
    while (Tokenizer_hasCurrent(tokenizer, tokenType)) {
        OperatorType         operator = OperatorType_from(Tokenizer_step(tokenizer, 1, tokenType)->value);
        BinaryOperatorExpRef expr     = AST_createBinaryOperatorExp(operator, result, next->callback(passable, next));
        result = AST_createASTNode(AST_BINARY_OPERATOR_EXP, expr);
    }

    return result;
}

void* parseAtomicExpression(void* passable, ContextRef data) {
    TokenizerRef tokenizer = (TokenizerRef) passable;

    switch (Tokenizer_current(tokenizer)->type) {
        case T_LEFT_PARENTHESIS: return parseParenthesisExpression(tokenizer);
        case T_IDENTIFIER: return parseIdentifierExpression(tokenizer);
        case T_NATIVE_FUNCTION: return parseNativeFunctionCallExpression(tokenizer);
        case T_I_INTEGER: return parseImmediateExpression(tokenizer, T_I_INTEGER, DT_INTEGER);
        case T_I_DOUBLE: return parseImmediateExpression(tokenizer, T_I_DOUBLE, DT_FLOAT);
        case T_I_STRING: return parseImmediateExpression(tokenizer, T_I_STRING, DT_STRING);
        case T_I_BOOL: return parseImmediateExpression(tokenizer, T_I_BOOL, DT_BOOL);
        default: DIE(ERR_SYNTAX);
    }
}

ASTNodeRef parseIdentifierExpression(TokenizerRef tokenizer) {
    String name = Tokenizer_step(tokenizer, 1, T_IDENTIFIER)->value;

    if (Token_hasType(Tokenizer_current(tokenizer), T_LEFT_PARENTHESIS)) {
        ListRef arguments = parseArguments(tokenizer);
        return AST_createASTNode(AST_FUNCTION_CALL_EXP, AST_createFunctionCallExp(name, arguments, List_last(&symbolTables), false));
    }

    VariableNodeRef variable = AST_createVariableExp(name, List_last(&symbolTables));
    registerVarExp(variable);

    return AST_createASTNode(AST_VARIABLE_EXP, variable);
}

ASTNodeRef parseNativeFunctionCallExpression(TokenizerRef tokenizer) {
    String  name      = Tokenizer_step(tokenizer, 1, T_NATIVE_FUNCTION)->value;
    ListRef arguments = parseArguments(tokenizer);

    return AST_createASTNode(AST_FUNCTION_CALL_EXP, AST_createFunctionCallExp(name, arguments, List_last(&symbolTables), true));
}

ListRef parseArguments(TokenizerRef tokenizer) {
    Tokenizer_step(tokenizer, 1, T_LEFT_PARENTHESIS);

    ListRef arguments = List_create(AST_destructASTNode);

    while (!Tokenizer_hasCurrent(tokenizer, T_RIGHT_PARENTHESIS)) {
        List_push(arguments, parseExpression(tokenizer));

        if (Tokenizer_hasCurrent(tokenizer, T_COMMA)) {
            Tokenizer_next(tokenizer);
        }
    }

    Tokenizer_step(tokenizer, 1, T_RIGHT_PARENTHESIS);
    return arguments;
}

ASTNodeRef parseParenthesisExpression(TokenizerRef tokenizer) {
    Tokenizer_step(tokenizer, 1, T_LEFT_PARENTHESIS);
    ASTNodeRef expression = parseExpression(tokenizer);
    Tokenizer_step(tokenizer, 1, T_RIGHT_PARENTHESIS);

    return expression;
}

ASTNodeRef parseImmediateExpression(TokenizerRef tokenizer, TokenType tokenType, DataType dataType) {
    ImmediateExpRef immediateExp = AST_createImmediateExp(Tokenizer_step(tokenizer, 1, tokenType)->value, dataType);

    return AST_createASTNode(AST_IMMEDIATE_EXP, immediateExp);
}

IfStRef parseIfStatement(TokenizerRef tokenizer) {
    Tokenizer_step(tokenizer, 1, T_K_IF);
    ASTNodeRef expression = parseExpression(tokenizer);
    Tokenizer_step(tokenizer, 2, T_K_THEN, T_EOL);

    ScopeRef onTrue       = parseScope(tokenizer, NULL);
    ScopeRef onFalse      = NULL;
    ListRef  alternatives = List_create(AST_destructIfSt);

    while (Tokenizer_hasCurrent(tokenizer, T_K_ELSEIF)) {
        List_push(alternatives, parseIfAlternativeStatement(tokenizer));
    }

    if (Tokenizer_hasCurrent(tokenizer, T_K_ELSE)) {
        Tokenizer_step(tokenizer, 2, T_K_ELSE, T_EOL);
        onFalse = parseScope(tokenizer, NULL);
    }
    Tokenizer_step(tokenizer, 3, T_K_END, T_K_IF, T_EOL);

    return AST_createIfSt(expression, onTrue, onFalse, alternatives);
}

IfStRef parseIfAlternativeStatement(TokenizerRef tokenizer) {
    Tokenizer_step(tokenizer, 1, T_K_ELSEIF);
    ASTNodeRef expression = parseExpression(tokenizer);
    Tokenizer_step(tokenizer, 2, T_K_THEN, T_EOL);

    return AST_createIfSt(expression, parseScope(tokenizer, NULL), NULL, NULL);
}

ReturnStRef parseReturnStatement(TokenizerRef tokenizer) {
    Tokenizer_step(tokenizer, 1, T_K_RETURN);
    ASTNodeRef expression = parseExpression(tokenizer);
    Tokenizer_step(tokenizer, 1, T_EOL);

    IF_NULL_DIE(parsedFunction, ERR_SYNTAX);
    return AST_createReturnSt(expression, parsedFunction);
}

PrintStRef parsePrintStatement(TokenizerRef tokenizer) {
    ListRef expressions = List_create(AST_destructASTNode);
    Tokenizer_step(tokenizer, 1, T_K_PRINT);
    do {
        List_push(expressions, parseExpression(tokenizer));
        Tokenizer_step(tokenizer, 1, T_SEMICOLON);
    } while (!Token_hasType(Tokenizer_current(tokenizer), T_EOL));
    Tokenizer_step(tokenizer, 1, T_EOL);

    return AST_createPrintSt(expressions);
}

InputStRef parseInputStatement(TokenizerRef tokenizer) {
    String variableName = (String) Tokenizer_step(tokenizer, 2, T_K_INPUT, T_IDENTIFIER)->value;
    Tokenizer_step(tokenizer, 1, T_EOL);

    InputStRef inputSt = AST_createInputSt(variableName, List_last(&symbolTables));
    registerInputSt(inputSt->variable);
    return inputSt;
}

void parseFunctionDeclaration(TokenizerRef tokenizer) {
    String name = (String) Tokenizer_step(tokenizer, 3, T_K_DECLARE, T_K_FUNCTION, T_IDENTIFIER)->value;
    Tokenizer_step(tokenizer, 1, T_LEFT_PARENTHESIS);
    ListRef  parameters = parseParameters(tokenizer);
    DataType type       = DataType_from(Tokenizer_step(tokenizer, 3, T_RIGHT_PARENTHESIS, T_K_AS, T_DATA_TYPE)->value);
    Tokenizer_step(tokenizer, 1, T_EOL);

    AST_registerFunctionDeclaration(List_last(&symbolTables), name, type, parameters);
}

ListRef parseParameters(TokenizerRef tokenizer) {
    ListRef list = List_create(&Table_destructParameter);
    while (Tokenizer_hasCurrent(tokenizer, T_IDENTIFIER)) {
        String   name = (String) Tokenizer_current(tokenizer)->value;
        DataType type = DataType_from(Tokenizer_step(tokenizer, 3, T_IDENTIFIER, T_K_AS, T_DATA_TYPE)->value);

        List_push(list, Table_createParameter(name, type));
        if (Token_hasType(Tokenizer_current(tokenizer), T_COMMA)) {
            Tokenizer_next(tokenizer);
        }
    }

    return list;
}

VariableDefRef parseVariable(TokenizerRef tokenizer, Bool isShared, Bool isStatic) {
    TokenType firstToken = isStatic ? T_K_STATIC : T_K_DIM;
    isShared ? Tokenizer_step(tokenizer, 2, firstToken, T_K_SHARED) : Tokenizer_step(tokenizer, 1, firstToken);

    String   name  = (String) Tokenizer_step(tokenizer, 1, T_IDENTIFIER)->value;
    DataType type  = DataType_from(Tokenizer_step(tokenizer, 2, T_K_AS, T_DATA_TYPE)->value);
    TokenRef token = Tokenizer_current(tokenizer);

    ASTNodeRef node = Token_hasType(token, T_O_RELATIONAL) && OperatorType_from(token->value) == OT_EQ
                      ? (Tokenizer_next(tokenizer), parseExpression(tokenizer))
                      : NULL;

    Tokenizer_step(tokenizer, 1, T_EOL);
    VariableDefRef variableDef = AST_createVariableDef(name, node, type, isStatic, List_last(&symbolTables));
    registerVarDef(variableDef->variable, variableDef->isStatic);

    return variableDef;
}

Bool insertParameterIntoTable(DataRef data, ContextRef context) {
    ParameterRef param = (ParameterRef) data;

    VariableNodeRef variableNode = Table_insertVariable(context, param->name, param->type);
    registerVarDef(variableNode, false);

    return true;
}

/** End of parser.external.c */
