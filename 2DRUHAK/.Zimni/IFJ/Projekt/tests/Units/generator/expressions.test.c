#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include "mocks/utils.mock.c"

//TestSuite(Generator_Expression, .init = setup, .fini = teardown);

//region Expression Function call

//Test(Generator_Expression, FunctionCall_NoArguments_WithoutUsed) {
//    GEN();
//    DataType type = DT_STRING;
//    String   dest = "test";
//    String   name = "doMagic";
//
//    Generator_functionCall(gen, ASTMock_call(type, name, 0)->ref);
//
//    cr_assert_inst(next(list), InstMock_empty(I_CREATEFRAME));
//    cr_assert_inst(next(list), InstMock_empty(I_PUSHFRAME));
//    cr_assert_inst(next(list), InstMock_first(I_CALL, Operand_label(name)));
//    cr_assert_inst(next(list), InstMock_empty(I_POPFRAME));
//    cr_assert_inst(next(list), InstMock_empty(I_CREATEFRAME));
//    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, OperMock_opVarTemp(type, dest)));
//    cr_assert_inst(next(list), InstMock_dest(I_POPS, OperMock_opVarTemp(type, dest)));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Expression, Expression_FunctionCall_OneArgument_WithoutUsed) {
//    GEN();
//    DataType type  = DT_STRING;
//    String   name  = "doMagic";
//    String   dest  = "test";
//    int      value = 42;
//
//    FunctionCallExpRef node = ASTMock_call(type, name, 1, ASTMock_int(&value))->ref;
//    Generator_functionCall(gen, node);
//
//    cr_assert_inst(next(list), InstMock_empty(I_CREATEFRAME));
//    cr_assert_inst(next(list), InstMock_first(I_PUSHS, OperMock_opImmInt(&value)));
//    cr_assert_inst(next(list), InstMock_empty(I_CREATEFRAME));
//    cr_assert_inst(next(list), InstMock_empty(I_PUSHFRAME));
//    cr_assert_inst(next(list), InstMock_first(I_CALL, OperMock_opLabel(name)));
//    cr_assert_inst(next(list), InstMock_empty(I_POPFRAME));
//    cr_assert_inst(next(list), InstMock_empty(I_CREATEFRAME));
//    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, OperMock_opVarTemp(type, dest)));
//    cr_assert_inst(next(list), InstMock_dest(I_POPS, OperMock_opVarTemp(type, dest)));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Expression, Expression_FunctionCall_TwoArguments_WithoutUsed) {
//    GEN();
//    DataType type   = DT_INTEGER;
//    String   dest   = "test";
//    String   name   = "doMagic";
//    int      first  = 5;
//    int      second = 6;
//
//    Generator_functionCall(gen, ASTMock_call(type, name, 2, ASTMock_int(&first), ASTMock_int(&second))->ref);
//
//    cr_assert_inst(next(list), InstMock_empty(I_CREATEFRAME));
//    cr_assert_inst(next(list), InstMock_first(I_PUSHS, OperMock_opImmInt(&second)));
//    cr_assert_inst(next(list), InstMock_first(I_PUSHS, OperMock_opImmInt(&first)));
//    cr_assert_inst(next(list), InstMock_empty(I_CREATEFRAME));
//    cr_assert_inst(next(list), InstMock_empty(I_PUSHFRAME));
//    cr_assert_inst(next(list), InstMock_first(I_CALL, Operand_label(name)));
//    cr_assert_inst(next(list), InstMock_empty(I_POPFRAME));
//    cr_assert_inst(next(list), InstMock_empty(I_CREATEFRAME));
//    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, OperMock_opVarTemp(type, dest)));
//    cr_assert_inst(next(list), InstMock_dest(I_POPS, OperMock_opVarTemp(type, dest)));
//    cr_assert(List_isEmpty(list),);
//}

//endregion

//region Expression Binary Structure

//Test(Generator_Expression, Expression_Binary_TwoImm_Inlined) {
//    GEN();
//    // Expression: 5 + 6
//    DataType type      = DT_INTEGER;
//    String   dest      = "dest";
//    int      values[3] = {5, 6, 11};
//
//    ASTNodeRef left  = ASTMock_immediate(type, values + 0);
//    ASTNodeRef right = ASTMock_immediate(type, values + 1);
//    Generator_binaryExpression(gen, OperMock_varTemp(type, dest), ASTMock_binary(type, OT_ADD, left, right)->ref);
//
//    cr_assert_inst(next(list), InstMock_destFirst(I_MOVE, OperMock_opVarTemp(type, dest),
//                                                  OperMock_opImmInt(values + 2)));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Expression, Expression_Binary_ImmAndBinaryOfTwoImm_Inlined) {
//    GEN();
//    // Expression: (5 * 6) + 2
//    DataType type      = DT_INTEGER;
//    String   dest      = "dest";
//    int      values[4] = {5, 6, 2, 32};
//
//    ASTNodeRef leftGroup = ASTMock_binary(DT_INTEGER, OT_MUL, ASTMock_int(values + 0), ASTMock_int(values + 1));
//    ASTNodeRef node      = ASTMock_binary(DT_INTEGER, OT_ADD, leftGroup, ASTMock_int(values + 2));
//    Generator_binaryExpression(gen, OperMock_varTemp(type, dest), node->ref);
//
//    cr_assert_inst(next(list), InstMock_destFirst(I_MOVE, OperMock_opVarTemp(type, dest),
//                                                  OperMock_opImmInt(values + 3)));
//    cr_assert(List_isEmpty(list),);
//}

//Test(Generator_Expression, Expression_Binary_TwoBinaryOfTwoImm_Inlined) {
//    GEN();
//    // Expression: (5 * 2) + (8 * 7)
//    DataType type      = DT_INTEGER;
//    String   dest      = "dest";
//    int      values[5] = {5, 2, 8, 7, 66};
//
//    ASTNodeRef firstEx  = ASTMock_binary(type, OT_MUL, ASTMock_int(values + 0), ASTMock_int(values + 1));
//    ASTNodeRef secondEx = ASTMock_binary(type, OT_MUL, ASTMock_int(values + 2), ASTMock_int(values + 3));
//    Generator_binaryExpression(gen, OperMock_varTemp(type, dest), ASTMock_binary(type, OT_ADD, firstEx, secondEx)->ref);
//
//    cr_assert_inst(next(list), InstMock_destFirst(I_MOVE, OperMock_opVarTemp(type, dest),
//                                                  OperMock_opImmInt(values + 4)));
//}

//endregion



