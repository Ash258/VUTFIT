#include <stdbool.h>
#include <setjmp.h>

bool dieCalled = false;

jmp_buf env_buffer;

#define DIE(x) dieCalled = true; longjmp(env_buffer, 1);

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../helpers.c"
#include "../../../src/ast/ast.external.c"
#include "../../../src/ast/typing.ast.c"
#include "../../../src/binarytree/binary_tree.external.c"
#include "../../../src/binarytree/tree.binary_tree.c"
#include "../../../src/heapregister/heap_register.external.c"
#include "../../../src/helpers.c"
#include "../../../src/list/list.external.c"
#include "../../../src/symtable/symtable.external.c"

Test(AST, ImmediateExp) {
    cr_assert_not_null(AST_createImmediateExp(NULL, DT_INTEGER),);
    cr_assert_not_null(AST_createImmediateExp(NULL, DT_FLOAT),);
    cr_assert_not_null(AST_createImmediateExp(NULL, DT_STRING),);
}

Test(AST, VariableExp) {
    SymbolTableRef parent = Table_create(NULL);
    SymbolTableRef local  = Table_create(parent);

    Table_insertVariable(local, "a", DT_INTEGER);
    Table_insertVariable(parent, "b", DT_INTEGER);

    cr_assert_not_null(AST_createVariableExp("a", local),);
    cr_assert_not_null(AST_createVariableExp("b", local),);

    int val = setjmp(env_buffer);
    if (val == 0) AST_createVariableExp("c", local);
    cr_assert_eq(dieCalled, true,);
}

Test(AST, FunctionCallExp) {
    SymbolTableRef parent = Table_create(NULL);
    SymbolTableRef local  = Table_create(parent);

    ListRef parameters = List_create(NULL);
    List_push(parameters, Table_createParameter("number", DT_INTEGER));
    List_push(parameters, Table_createParameter("text", DT_STRING));
    Table_insertFunction(parent, "foo", DT_INTEGER, parameters, true, true);

    ListRef arguments = List_create(NULL);
    List_push(arguments, AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_INTEGER)));
    List_push(arguments, AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_STRING)));

    cr_assert_not_null(AST_createFunctionCallExp("foo", arguments, local, false),);

    int val = setjmp(env_buffer);
    if (val == 0) AST_createFunctionCallExp("none", arguments, local, false);
    cr_assert_eq(dieCalled, true,);

    List_shift(arguments);
    List_push(arguments, AST_createASTNode(AST_IMMEDIATE_EXP,
                                           AST_createImmediateExp(NULL, DT_INTEGER))); //difference type of arguments
    dieCalled = false;
    val       = setjmp(env_buffer);
    if (val == 0) AST_createFunctionCallExp("foo", arguments, local, false);
    cr_assert_eq(dieCalled, true,);

    List_shift(arguments); //difference number of arguments
    dieCalled = false;
    val       = setjmp(env_buffer);
    if (val == 0) AST_createFunctionCallExp("foo", arguments, local, false);
    cr_assert_eq(dieCalled, true,);
}

void cr_assert_binary_operator_fail(OperatorType operator, ASTNodeRef left, ASTNodeRef right) {
    int val = setjmp(env_buffer);
    if (val == 0) AST_createBinaryOperatorExp(operator, left, right);
    cr_assert_eq(dieCalled, true,);
    dieCalled = false;
}

void cr_assert_binary_operator_pass(OperatorType operator, ASTNodeRef left, ASTNodeRef right, DataType expectedType, Bool immediate) {
    BinaryOperatorExpRef ref = AST_createBinaryOperatorExp(operator, left, right);
    cr_assert_not_null(ref,);
    cr_assert_eq(ref->type, expectedType,);
    cr_assert_eq(ref->isImmediate, immediate,);
}

Test(AST, BinaryOperatorExp) {
    SymbolTableRef parent = Table_create(NULL);
    SymbolTableRef local  = Table_create(parent);
    Table_insertVariable(local, "a", DT_INTEGER);
    ASTNodeRef varNode    = AST_createASTNode(AST_VARIABLE_EXP, AST_createVariableExp("a", local));
    ASTNodeRef stringNode = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_STRING));
    ASTNodeRef intNode    = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_INTEGER));
    ASTNodeRef floatNode  = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_FLOAT));

    OperatorType baseMath[] = {OT_ADD, OT_SUB, OT_MUL};
    for (int     i          = 0; i < sizeof(baseMath) / sizeof(OperatorType); ++i) {
        OperatorType current = baseMath[i];

        cr_assert_binary_operator_pass(current, stringNode, stringNode, DT_STRING, true);
        cr_assert_binary_operator_pass(current, intNode, intNode, DT_INTEGER, true);
        cr_assert_binary_operator_pass(current, floatNode, floatNode, DT_FLOAT, true);
        cr_assert_binary_operator_pass(current, floatNode, intNode, DT_FLOAT, true);
        cr_assert_binary_operator_pass(current, intNode, floatNode, DT_FLOAT, true);

        cr_assert_binary_operator_fail(current, stringNode, intNode);
        cr_assert_binary_operator_fail(current, intNode, stringNode);
        cr_assert_binary_operator_fail(current, stringNode, floatNode);
        cr_assert_binary_operator_fail(current, floatNode, stringNode);
    }

    OperatorType baseRelation[] = {OT_GT, OT_GEQ, OT_LT, OT_LEQ, OT_EQ, OT_NEQ};
    for (int     i              = 0; i < sizeof(baseRelation) / sizeof(OperatorType); ++i) {
        OperatorType current = baseRelation[i];

        cr_assert_binary_operator_pass(current, stringNode, stringNode, DT_BOOL, true);
        cr_assert_binary_operator_pass(current, intNode, intNode, DT_BOOL, true);
        cr_assert_binary_operator_pass(current, floatNode, floatNode, DT_BOOL, true);
        cr_assert_binary_operator_pass(current, floatNode, intNode, DT_BOOL, true);
        cr_assert_binary_operator_pass(current, intNode, floatNode, DT_BOOL, true);

        cr_assert_binary_operator_fail(current, stringNode, intNode);
        cr_assert_binary_operator_fail(current, intNode, stringNode);
        cr_assert_binary_operator_fail(current, stringNode, floatNode);
        cr_assert_binary_operator_fail(current, floatNode, stringNode);
    }

    //OT_IDIV
    cr_assert_binary_operator_pass(OT_IDIV, intNode, intNode, DT_INTEGER, true);
    cr_assert_binary_operator_pass(OT_IDIV, floatNode, floatNode, DT_INTEGER, true);
    cr_assert_binary_operator_pass(OT_IDIV, floatNode, intNode, DT_INTEGER, true);
    cr_assert_binary_operator_pass(OT_IDIV, intNode, floatNode, DT_INTEGER, true);

    cr_assert_binary_operator_fail(OT_IDIV, stringNode, stringNode);
    cr_assert_binary_operator_fail(OT_IDIV, stringNode, intNode);
    cr_assert_binary_operator_fail(OT_IDIV, intNode, stringNode);
    cr_assert_binary_operator_fail(OT_IDIV, stringNode, floatNode);
    cr_assert_binary_operator_fail(OT_IDIV, floatNode, stringNode);

    //OT_DIV
    cr_assert_binary_operator_pass(OT_DIV, intNode, intNode, DT_FLOAT, true);
    cr_assert_binary_operator_pass(OT_DIV, floatNode, floatNode, DT_FLOAT, true);
    cr_assert_binary_operator_pass(OT_DIV, floatNode, intNode, DT_FLOAT, true);
    cr_assert_binary_operator_pass(OT_DIV, intNode, floatNode, DT_FLOAT, true);

    cr_assert_binary_operator_fail(OT_DIV, stringNode, stringNode);
    cr_assert_binary_operator_fail(OT_DIV, stringNode, intNode);
    cr_assert_binary_operator_fail(OT_DIV, intNode, stringNode);
    cr_assert_binary_operator_fail(OT_DIV, stringNode, floatNode);
    cr_assert_binary_operator_fail(OT_DIV, floatNode, stringNode);

    //IsImmediate
    cr_assert_binary_operator_pass(OT_ADD, intNode, varNode, DT_INTEGER, false);
}

Test(AST, InputSt) {
    SymbolTableRef parent = Table_create(NULL);
    SymbolTableRef local  = Table_create(parent);

    Table_insertVariable(local, "a", DT_INTEGER);
    Table_insertVariable(parent, "b", DT_INTEGER);

    cr_assert_not_null(AST_createInputSt("a", local),);
    cr_assert_not_null(AST_createInputSt("b", local),);

    int val = setjmp(env_buffer);
    if (val == 0) AST_createVariableExp("c", local);
    cr_assert_eq(dieCalled, true,);
}

void cr_assert_if_fail(ASTNodeRef expression) {
    int val = setjmp(env_buffer);
    if (val == 0) AST_createIfSt(expression, NULL, NULL, NULL);
    cr_assert_eq(dieCalled, true,);
    dieCalled = false;
}

Test(AST, IfSt) {
    ASTNodeRef stringNode = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_STRING));
    ASTNodeRef intNode    = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_INTEGER));
    ASTNodeRef floatNode  = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_FLOAT));
    ASTNodeRef boolNode   = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_BOOL));

    cr_assert_if_fail(intNode);
    cr_assert_if_fail(floatNode);
    cr_assert_if_fail(stringNode);
    cr_assert_not_null(AST_createIfSt(boolNode, NULL, NULL, NULL),);
}

void cr_assert_loop_fail(ASTNodeRef expression) {
    int val = setjmp(env_buffer);
    if (val == 0) AST_createLoopSt(expression, NULL);
    cr_assert_eq(dieCalled, true,);
    dieCalled = false;
}

Test(AST, LoopSt) {
    ASTNodeRef stringNode = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_STRING));
    ASTNodeRef intNode    = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_INTEGER));
    ASTNodeRef floatNode  = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_FLOAT));
    ASTNodeRef boolNode   = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_BOOL));

    cr_assert_loop_fail(intNode);
    cr_assert_loop_fail(floatNode);
    cr_assert_loop_fail(stringNode);
    cr_assert_not_null(AST_createLoopSt(boolNode, NULL),);
}

void cr_assert_return_fail(FunctionNodeRef function, ASTNodeRef expression) {
    int val = setjmp(env_buffer);
    if (val == 0) AST_createReturnSt(expression, function);
    cr_assert_eq(dieCalled, true,);
    dieCalled = false;
}

Test(AST, ReturnSt) {
    FunctionNode function   = {.type = DT_INTEGER};
    ASTNodeRef   stringNode = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_STRING));
    ASTNodeRef   intNode    = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_INTEGER));
    ASTNodeRef   floatNode  = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_FLOAT));

    cr_assert_return_fail(&function, stringNode);
    cr_assert_not_null(AST_createReturnSt(intNode, &function),);
    cr_assert_not_null(AST_createReturnSt(floatNode, &function),);

    function.type = DT_FLOAT;
    cr_assert_return_fail(&function, stringNode);
    cr_assert_not_null(AST_createReturnSt(intNode, &function),);
    cr_assert_not_null(AST_createReturnSt(floatNode, &function),);

    function.type = DT_STRING;
    cr_assert_return_fail(&function, floatNode);
    cr_assert_return_fail(&function, intNode);
    cr_assert_not_null(AST_createReturnSt(stringNode, &function),);
}

void
cr_assert_assignment_fail(ASTNodeRef expression, String variable, SymbolTableRef table, OperatorType operatorType) {
    int val = setjmp(env_buffer);
    if (val == 0) AST_createAssignmentSt(expression, variable, table, operatorType);
    cr_assert_eq(dieCalled, true,);
    dieCalled = false;
}

Test(AST, AssignmentSt) {
    ASTNodeRef stringNode = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_STRING));
    ASTNodeRef intNode    = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_INTEGER));
    ASTNodeRef floatNode  = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_FLOAT));

    SymbolTableRef root  = Table_create(NULL);
    SymbolTableRef local = Table_create(root);

    Table_insertVariable(local, "a", DT_INTEGER);
    Table_insertVariable(root, "b", DT_FLOAT);
    Table_insertVariable(root, "d", DT_STRING);

    cr_assert_assignment_fail(stringNode, "c", local, OT_NONE);
    cr_assert_assignment_fail(intNode, "c", local, OT_NONE);
    cr_assert_assignment_fail(intNode, "c", local, OT_NONE);

    cr_assert_assignment_fail(stringNode, "b", local, OT_NONE);
    cr_assert_not_null(AST_createAssignmentSt(floatNode, "b", local, OT_NONE),);
    cr_assert_not_null(AST_createAssignmentSt(intNode, "b", local, OT_NONE),);

    cr_assert_assignment_fail(stringNode, "a", local, OT_NONE);
    AST_createAssignmentSt(floatNode, "a", local, OT_NONE);
    cr_assert_not_null(AST_createAssignmentSt(intNode, "a", local, OT_NONE),);

    cr_assert_assignment_fail(floatNode, "d", local, OT_NONE);
    cr_assert_assignment_fail(intNode, "d", local, OT_NONE);
    cr_assert_not_null(AST_createAssignmentSt(stringNode, "d", local, OT_NONE),);

    AssignmentStRef ref = AST_createAssignmentSt(stringNode, "d", local, OT_ADD);
    cr_assert_eq(getExpressionType(ref->expression), AST_BINARY_OPERATOR_EXP,);

    cr_assert_assignment_fail(stringNode, "d", local, OT_SUB);
}

Test(AST, Root) {
    SymbolTableRef root  = Table_create(NULL);
    Scope          scope = {.symbolTable = root};

    Table_insertFunction(root, "foo", DT_INTEGER, NULL, true, true);
    cr_assert_not_null(AST_createRoot(&scope, NULL, NULL),);

    Table_insertFunction(root, "foo2", DT_INTEGER, NULL, false, true);

    int val = setjmp(env_buffer);
    if (val == 0) AST_createRoot(&scope, NULL, NULL);
    cr_assert_eq(dieCalled, true,);
}

Test(AST, FunctionDef) {
    SymbolTableRef parent = Table_create(NULL);

    ListRef parameters = List_create(NULL);
    List_push(parameters, Table_createParameter("number", DT_INTEGER));
    List_push(parameters, Table_createParameter("text", DT_STRING));
    FunctionNodeRef declaredFunction = Table_insertFunction(parent, "foo", DT_INTEGER, parameters, true, true);
    FunctionNodeRef definedFunction  = Table_insertFunction(parent, "foo2", DT_INTEGER, parameters, true, false);

    ListRef arguments = List_create(NULL);
    List_push(arguments, Table_createParameter("a", DT_INTEGER));
    List_push(arguments, Table_createParameter("b", DT_STRING));

    cr_assert_not_null(AST_createFunctionDef(NULL, declaredFunction, arguments),);
    cr_assert_not_null(AST_createFunctionDef(NULL, definedFunction, arguments),);

    List_shift(arguments);
    List_push(arguments, AST_createASTNode(AST_IMMEDIATE_EXP,
                                           AST_createImmediateExp(NULL, DT_INTEGER))); //difference type of arguments
    dieCalled = false;
    int val = setjmp(env_buffer);
    if (val == 0) AST_createFunctionDef(NULL, declaredFunction, arguments);
    cr_assert_eq(dieCalled, true,);
    cr_assert_not_null(AST_createFunctionDef(NULL, definedFunction, arguments),);

    List_shift(arguments); //difference number of arguments
    dieCalled = false;
    val       = setjmp(env_buffer);
    if (val == 0) AST_createFunctionDef(NULL, declaredFunction, arguments);
    cr_assert_eq(dieCalled, true,);
    cr_assert_not_null(AST_createFunctionDef(NULL, definedFunction, arguments),);
}

void cr_assert_register_function_declaration_fail(String name, SymbolTableRef table) {
    int val = setjmp(env_buffer);
    if (val == 0) AST_registerFunctionDeclaration(table, name, DT_INTEGER, NULL);
    cr_assert_eq(dieCalled, true,);
    dieCalled = false;
}

Test(AST, RegisterFunctionDeclaration) {
    SymbolTableRef root = Table_create(NULL);
    Table_insertVariable(root, "a", DT_INTEGER);
    Table_insertFunction(root, "b", DT_INTEGER, NULL, true, true);
    Table_insertFunction(root, "c", DT_INTEGER, NULL, true, false);
    Table_insertFunction(root, "d", DT_INTEGER, NULL, false, true);

    cr_assert_register_function_declaration_fail("a", root);
    cr_assert_register_function_declaration_fail("b", root);
    cr_assert_register_function_declaration_fail("c", root);
    cr_assert_register_function_declaration_fail("d", root);
    cr_assert_not_null(AST_registerFunctionDeclaration(root, "e", DT_INTEGER, NULL),);
}

void cr_assert_register_function_definition_fail(String name, SymbolTableRef table) {
    int val = setjmp(env_buffer);
    if (val == 0) AST_registerFunctionDefinition(table, name, DT_INTEGER, NULL);
    cr_assert_eq(dieCalled, true,);
    dieCalled = false;
}

Test(AST, RegisterFunctionDefinition) {
    SymbolTableRef root = Table_create(NULL);
    Table_insertVariable(root, "a", DT_INTEGER);
    Table_insertFunction(root, "b", DT_INTEGER, NULL, true, true);
    Table_insertFunction(root, "c", DT_INTEGER, NULL, true, false);
    Table_insertFunction(root, "d", DT_INTEGER, NULL, false, true);

    cr_assert_register_function_definition_fail("a", root);
    cr_assert_register_function_definition_fail("b", root);
    cr_assert_register_function_definition_fail("c", root);
    cr_assert_not_null(AST_registerFunctionDefinition(root, "d", DT_INTEGER, NULL),);
    cr_assert_not_null(AST_registerFunctionDefinition(root, "e", DT_INTEGER, NULL),);
}

void cr_assert_variable_definition_fail(String name, DataType type, ASTNodeRef initialization, SymbolTableRef table) {
    int val = setjmp(env_buffer);
    if (val == 0) AST_createVariableDef(name, initialization, type, NULL, table);
    cr_assert_eq(dieCalled, true,);
    dieCalled = false;
}

Test(AST, VariableDefinition) {
    SymbolTableRef root = Table_create(NULL);
    Table_insertFunction(root, "m", DT_INTEGER, NULL, false, true);
    Table_insertVariable(root, "a", DT_INTEGER);

    ASTNodeRef stringNode = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_STRING));
    ASTNodeRef intNode    = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_INTEGER));
    ASTNodeRef floatNode  = AST_createASTNode(AST_IMMEDIATE_EXP, AST_createImmediateExp(NULL, DT_FLOAT));

    cr_assert_variable_definition_fail("a", DT_INTEGER, intNode, root);
    cr_assert_variable_definition_fail("m", DT_FLOAT, floatNode, root);
    cr_assert_variable_definition_fail("b", DT_INTEGER, stringNode, root);
    cr_assert_variable_definition_fail("b", DT_FLOAT, stringNode, root);

    cr_assert_not_null(AST_createVariableDef("b", intNode, DT_INTEGER, false, root),);
    cr_assert_not_null(AST_createVariableDef("c", intNode, DT_FLOAT, false, root),);
    cr_assert_not_null(AST_createVariableDef("d", floatNode, DT_INTEGER, false, root),);
    cr_assert_not_null(AST_createVariableDef("e", floatNode, DT_FLOAT, false, root),);
    cr_assert_not_null(AST_createVariableDef("f", stringNode, DT_STRING, false, root),);
}
