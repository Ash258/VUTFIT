#include <stdbool.h>
#include <setjmp.h>

bool dieCalled = false;

jmp_buf env_buffer;

#define DIE(x) dieCalled = true; longjmp(env_buffer, 1);

#include "../helpers.c"
#include <criterion/parameterized.h>
#include "../../../src/helpers.c"
#include "../../../src/parser/parser.external.c"
#include "../../../src/parser/parser.variable_register.c"
#include "../../../src/ast/ast.external.c"
#include "../../../src/ast/typing.ast.c"
#include "../../../src/list/list.external.c"
#include "../../../src/heapregister/heap_register.external.c"
#include "../../../src/binarytree/binary_tree.external.c"
#include "../../../src/binarytree/tree.binary_tree.c"
#include "../../../src/symtable/symtable.external.c"
#include "../../../src/pipeline/pipeline.external.c"
#include "../../../src/tokenizer/tokenizer.external.c"
#include "../../../src/tokenizer/token.external.c"
#include "../../../src/trie/trie.external.c"
#include "../../../src/tokenizer/tokenizer.symbol.c"
#include "../../../src/tokenizer/tokenizer.comment.c"
#include "../../../src/tokenizer/tokenizer.digit.c"
#include "../../../src/tokenizer/tokenizer.identificator.c"
#include "../../../src/tokenizer/tokenizer.number.c"
#include "../../../src/tokenizer/tokenizer.string.c"
#include "../tokenizer/buffer.mock.c"
#include "../../../src/stringbuilder/string_builder.external.c"
#include "../../../src/ast/ast.external.h"
#include "../../../src/symtable/symtable.external.h"

typedef struct {
    String  input;
    ASTNode expectedOutput;
} * ExpressionPassingRef, ExpressionPassing;

ImmediateExpRef cr_createImmediate(void* data, DataType type) {
    ImmediateExpRef ref = cr_malloc(sizeof(ImmediateExp));

    ref->value = data;
    ref->type  = type;

    return ref;
}

BinaryOperatorExpRef cr_createBinaryOperator(OperatorType operator, DataType type) {
    BinaryOperatorExpRef ref = cr_malloc(sizeof(BinaryOperatorExp));

    ref->operator = operator;
    ref->type     = type;

    return ref;
}

UnaryOperatorExpRef cr_createUnaryOperator(OperatorType operator, DataType type) {
    UnaryOperatorExpRef ref = cr_malloc(sizeof(UnaryOperatorExp));

    ref->operator = operator;
    ref->type     = type;

    return ref;
}

ParameterizedTestParameters(Parser, ExpressionPassing) {
    size_t count = 17;

    ExpressionPassingRef values = cr_malloc(sizeof(ExpressionPassing) * count);

    values[0] =
            (ExpressionPassing) {cr_String_of("1"), {AST_IMMEDIATE_EXP, cr_createImmediate(cr_Int_of(1), DT_INTEGER)}};
    values[1]  = (ExpressionPassing) {cr_String_of("!\"papa\""),
                                      {AST_IMMEDIATE_EXP, cr_createImmediate(cr_String_of("papa"), DT_STRING)}};
    values[2]  = (ExpressionPassing) {cr_String_of("5.26"),
                                      {AST_IMMEDIATE_EXP, cr_createImmediate(cr_Real_of(5.26), DT_FLOAT)}};
    values[3]  = (ExpressionPassing) {cr_String_of("95625+251177"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_ADD, DT_INTEGER)}};
    values[4]  = (ExpressionPassing) {cr_String_of("95625-251177"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_SUB, DT_INTEGER)}};
    values[5]  = (ExpressionPassing) {cr_String_of("95625*251177"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_MUL, DT_INTEGER)}};
    values[6]  = (ExpressionPassing) {cr_String_of("95625\\251177"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_IDIV, DT_INTEGER)}};
    values[7]  = (ExpressionPassing) {cr_String_of("95625//\'asd\'/251177"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_DIV, DT_FLOAT)}};
    values[8]  = (ExpressionPassing) {cr_String_of("/\'asd\'/5/2"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_DIV, DT_FLOAT)}};
    values[9]  = (ExpressionPassing) {cr_String_of("95625*(251177+66)"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_MUL, DT_INTEGER)}};
    values[10] = (ExpressionPassing) {cr_String_of("95625+25117*766"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_ADD, DT_INTEGER)}};
    values[11] =
            (ExpressionPassing) {cr_String_of("true"),
                                 {AST_IMMEDIATE_EXP, cr_createImmediate(cr_Bool_of(true), DT_BOOL)}};
    values[12] = (ExpressionPassing) {cr_String_of("false"),
                                      {AST_IMMEDIATE_EXP, cr_createImmediate(cr_Bool_of(false), DT_BOOL)}};
    values[13] = (ExpressionPassing) {cr_String_of("b AND true"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_AND, DT_BOOL)}};
    values[14] = (ExpressionPassing) {cr_String_of("false OR b"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_OR, DT_BOOL)}};
    values[15] =
            (ExpressionPassing) {cr_String_of("not b"),
                                 {AST_UNARY_OPERATOR_EXP, cr_createUnaryOperator(OT_NOT, DT_BOOL)}};
    values[16] = (ExpressionPassing) {cr_String_of("not b OR b"),
                                      {AST_BINARY_OPERATOR_EXP, cr_createBinaryOperator(OT_OR, DT_BOOL)}};
    values[16] =
            (ExpressionPassing) {cr_String_of("-5"),
                                 {AST_UNARY_OPERATOR_EXP, cr_createUnaryOperator(OT_SUB, DT_INTEGER)}};

    return cr_make_param_array(ExpressionPassing, values, count,);
}

ParameterizedTest(ExpressionPassingRef param, Parser, ExpressionPassing) {
    SymbolTableRef root = Table_create(NULL);
    List_push(&symbolTables, root);
    Table_insertVariable(root, "B", DT_BOOL);

    initializeExpressionChains();
    BufferRef buffer    = Buffer_from(param->input);
    Tokenizer tokenizer = {.file = *buffer};
    Tokenizer_next(&tokenizer);

    ASTNodeRef expression = parseExpression(&tokenizer);
    cr_assert_eq(expression->type, param->expectedOutput.type,);

    if (param->expectedOutput.type == AST_IMMEDIATE_EXP) {
        ImmediateExpRef actual = expression->ref, expected = param->expectedOutput.ref;
        cr_assert_eq(actual->type, expected->type,);
        if (expected->type == DT_STRING) {
            cr_assert_str_eq(actual->value, expected->value,);
        } else if (expected->type == DT_FLOAT) {
            cr_assert_float_eq(Real_from(actual->value), Real_from(expected->value), 0.001,);
        } else { //int and bool
            cr_assert_eq(Int_from(actual->value), Int_from(expected->value),);
        }
    } else if (param->expectedOutput.type == AST_BINARY_OPERATOR_EXP) {
        BinaryOperatorExpRef actual = expression->ref, expected = param->expectedOutput.ref;
        cr_assert_eq(actual->type, expected->type,);
        cr_assert_eq(actual->operator, expected->operator,);
    } else if (param->expectedOutput.type == AST_UNARY_OPERATOR_EXP) {
        UnaryOperatorExpRef actual = expression->ref, expected = param->expectedOutput.ref;
        cr_assert_eq(actual->type, expected->type,);
        cr_assert_eq(actual->operator, expected->operator,);
    }
}

Test(Parser, VariableDeclaration) {
    SymbolTableRef local = Table_create(NULL);

    List_push(&symbolTables, local);

    initializeExpressionChains();
    BufferRef buffer    = Buffer_from("Dim foo As Integer\n");
    Tokenizer tokenizer = {.file = *buffer};
    Tokenizer_next(&tokenizer);
    VariableDefRef def = parseVariable(&tokenizer, false, false);
    cr_assert_str_eq(def->variable->name, "FOO",);
    cr_assert_not(def->isStatic,);
    cr_assert_null(def->initialization,);

    buffer = Buffer_from("Dim Shared  La As Integer\n");
    tokenizer.file = *buffer;
    Tokenizer_next(&tokenizer);
    def = parseVariable(&tokenizer, true, false);
    cr_assert_str_eq(def->variable->name, "LA",);
    cr_assert_not(def->isStatic,);
    cr_assert_null(def->initialization,);

    buffer = Buffer_from("Static lala As Integer = 5+3\n");
    tokenizer.file = *buffer;
    Tokenizer_next(&tokenizer);
    def = parseVariable(&tokenizer, false, true);
    cr_assert_str_eq(def->variable->name, "LALA",);
    cr_assert_not_null(def->initialization,);
    cr_assert(def->isStatic,);
    cr_assert_eq(def->initialization->type, AST_BINARY_OPERATOR_EXP,);
}

Test(Parser, Parameters) {
    BufferRef buffer    = Buffer_from("a As Integer, B as Double");
    Tokenizer tokenizer = {.file = *buffer};
    Tokenizer_next(&tokenizer);

    ListRef      params    = parseParameters(&tokenizer);
    cr_assert_eq(List_size(params), 2,);
    ParameterRef parameter = List_shift(params);
    cr_assert_str_eq(parameter->name, "A",);
    cr_assert_eq(parameter->type, DT_INTEGER,);

    parameter = List_shift(params);
    cr_assert_str_eq(parameter->name, "B",);
    cr_assert_eq(parameter->type, DT_FLOAT,);
}

ParameterizedTestParameters(Parser, Statement) {
    size_t count = 11;

    ExpressionPassingRef values = cr_malloc(sizeof(ExpressionPassing) * count);
    values[0]  = (ExpressionPassing) {cr_String_of("Input a\n"), {AST_INPUT_ST, NULL}};
    values[1]  = (ExpressionPassing) {cr_String_of("Print 5;\n"), {AST_PRINT_ST, NULL}};
    values[2]  = (ExpressionPassing) {cr_String_of("IF 5 > 3 then \n Print a; \n End IF\n"), {AST_IF_ST, NULL}};
    values[3]  = (ExpressionPassing) {cr_String_of("IF 5 > 3 then \n  Else \n Dim a as Integer\n End IF\n"),
                                      {AST_IF_ST, NULL}};
    values[4]  = (ExpressionPassing) {cr_String_of("Do while 5 > 3 \n Print a; \n Loop \n"), {AST_LOOP_ST, NULL}};
    values[5]  = (ExpressionPassing) {cr_String_of("A = 5\n"), {AST_ASSIGNMENT_ST, NULL}};
    values[6]  = (ExpressionPassing) {cr_String_of("A *= 5\n"), {AST_ASSIGNMENT_ST, NULL}};
    values[7]  = (ExpressionPassing) {cr_String_of("A += 5\n"), {AST_ASSIGNMENT_ST, NULL}};
    values[8]  = (ExpressionPassing) {cr_String_of("A /= 5\n"), {AST_ASSIGNMENT_ST, NULL}};
    values[9]  = (ExpressionPassing) {cr_String_of("A -= 5\n"), {AST_ASSIGNMENT_ST, NULL}};
    values[10] = (ExpressionPassing) {cr_String_of("A \\= 5\n"), {AST_ASSIGNMENT_ST, NULL}};

    return cr_make_param_array(ExpressionPassing, values, count,);
}

ParameterizedTest(ExpressionPassingRef param, Parser, Statement) {
    initializeExpressionChains();
    BufferRef buffer    = Buffer_from(param->input);
    Tokenizer tokenizer = {.file = *buffer};
    Tokenizer_next(&tokenizer);

    SymbolTableRef local = Table_create(NULL);
    List_push(&symbolTables, local);
    Table_insertVariable(local, "A", DT_INTEGER);
    Table_insertVariable(local, "B", DT_STRING);
    Table_insertVariable(local, "C", DT_FLOAT);

    ASTNodeRef expression = parseStatement(&tokenizer);
    cr_assert_eq(expression->type, param->expectedOutput.type,);
}
