#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include "mocks/utils.mock.c"

TestSuite(Generator, .fini = teardown);

Test(Generator_Statement, Assignment) {
    GEN();
    DataType type  = DT_BOOL;
    String   name  = "jojo";
    String   exp   = "$jojo-&0000$";
    bool     value = true;

    VarMock_ensure(gen, type, name, false);
    Generator_assignment(gen, ASTMock_assignment(type, name, ASTMock_bool(&value))->ref);

    cr_assert_inst(next(list), InstMock_destFirst(I_MOVE, OperMock_opVarLocal(type, exp), OperMock_opImmBool(&value)));
    cr_assert(List_isEmpty(list),);
}

Test(Generator_Statement, Input) {
    GEN();
    DataType type = DT_STRING;
    String   name = "asdf";
    String   exp  = "$asdf-&0000$";

    VarMock_ensure(gen, type, name, false);
    Generator_input(gen, ASTMock_input(type, name)->ref);

    cr_assert_inst(next(list), InstMock_destFirst(I_READ, OperMock_opVarLocal(type, exp), Operand_dataType(type)));
    cr_assert(List_isEmpty(list),);
}

Test(Generator_Statement, Print_OneExpression) {
    GEN();
    int value = 5;

    Generator_print(gen, ASTMock_print(1, ASTMock_int(&value))->ref);

    cr_assert_inst(next(list), InstMock_first(I_WRITE, OperMock_opImmInt(&value)));
    cr_assert(List_isEmpty(list),);
}

Test(Generator_Statement, Print_TwoExpression) {
    GEN();
    int      first         = 5;
    DataType secondType    = DT_STRING;
    String   secondName    = "x";
    String   secondNameExp = "$x-&0000$";

    VarMock_ensure(gen, secondType, secondName, true);

    Generator_print(gen, ASTMock_print(2, ASTMock_int(&first), ASTMock_varExp(secondType, secondName))->ref);

    cr_assert_inst(next(list), InstMock_first(I_WRITE, OperMock_opImmInt(&first)));
    cr_assert_inst(next(list), InstMock_first(I_WRITE, OperMock_opVarLocal(secondType, secondNameExp)));
    cr_assert(List_isEmpty(list),);
}
