#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include "mocks/utils.mock.c"

#define ENSURE(x) VarMock_ensure(gen, DT_INTEGER, x, true)

#define VAR(x) ASTMock_varExp(DT_INTEGER, x)
#define DEST(dest) OperMock_varTemp(DT_INTEGER, dest)
#define BINARY(oper, left, right) ASTMock_binary(DT_INTEGER, (oper), VAR(left), VAR(right))->ref
#define UNARY(oper, op) ASTMock_unary(DT_INTEGER, (oper), VAR(op))->ref

#define OP_TEMP(x) OperMock_opVarTemp(DT_INTEGER, (x))
#define OP_LOCAL(x) OperMock_opVarLocal(DT_INTEGER, (x))

#define INST_TEMP(inst, dest, left, right) InstMock((inst), OP_TEMP(x), OP_LOCAL(left), OP_LOCAL(right))
#define INST(inst, dest, left, right) InstMock((inst), OP_LOCAL(dest), OP_LOCAL(left), OP_LOCAL(right))
#define INST3(inst, dest, first) InstMock_destFirst((inst), OP_LOCAL(dest), OP_LOCAL(first))

//region Arithmetic

//Test(Generator_Operator, Arithmetic_Addition) {
//    GEN();
//    String name = "dest";
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_ADD, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_ADD, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Arithmetic_Substraction) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_SUB, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_SUB, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Arithmetic_Division) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_DIV, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_DIV, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Arithmetic_IntegerDivision) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_IDIV, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_DIV, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Arithmetic_Multiplication) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_MUL, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_MUL, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//endregion

//region Relational

//Test(Generator_Operator, Relation_GreaterThan) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_GT, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_GT, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Relation_GreaterThanOrEqualTo) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_GEQ, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_LT, "dest", "$x-&0000$", "$y-&0000$"));
//    cr_assert_inst(next(list), INST3(I_NOT, "dest", "dest"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Relation_LowerThan) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_LT, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_LT, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Relation_LowerThanOrEqualTo) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_LEQ, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_GT, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert_inst(next(list), INST3(I_NOT, "&0000", "&0000"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Relation_EqualTo) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_EQ, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_EQ, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Relation_NotEqualTo) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_NEQ, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_EQ, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert_inst(next(list), INST3(I_NOT, "&0000", "&0000"));
//    cr_assert(List_isEmpty(list),);
//}

//endregion

//region Logical

//Test(Generator_Operator, Logical_And) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_AND, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_AND, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Logical_Not) {
//    GEN();
//
//    ENSURE("x");
//
//    Generator_unaryExpression(gen, UNARY(OT_NOT, "x"));
//
//    cr_assert_inst(next(list), INST3(I_NOT, "&0000", "$x-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Operator, Logical_Or) {
//    GEN();
//
//    ENSURE("x");
//    ENSURE("y");
//
//    Generator_binaryExpression(gen, BINARY(OT_OR, "x", "y"));
//
//    cr_assert_inst(next(list), INST(I_OR, "&0000", "$x-&0000$", "$y-&0000$"));
//    cr_assert(List_isEmpty(list),);
//}

//endregion
