#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include "mocks/utils.mock.c"

TestSuite(Generator, .fini = teardown);

//region Variable
Test(Generator_Variable, Declaration) {
    GEN();
    DataType type     = DT_STRING;
    String   name     = "test";
    String   expected = "$test-&0000$";

    Generator_variableDef(gen, ASTMock_var(type, name, false, NULL)->ref);

    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, OperMock_opVarLocal(type, expected)));
    cr_assert(List_isEmpty(list),);
}

Test(Generator_Variable, Definition) {
    GEN();
    String   name     = "test";
    String   expected = "$test-&0000$";
    DataType type     = DT_INTEGER;
    int      value    = 4;

    Generator_variableDef(gen, ASTMock_var(type, name, false, ASTMock_int(&value))->ref);

    Operand dest = OperMock_opVarLocal(type, expected);
    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, dest));
    cr_assert_inst(next(list), InstMock_destFirst(I_MOVE, dest, OperMock_opImmInt(&value)));
    cr_assert(List_isEmpty(list),);
}
//endregion
