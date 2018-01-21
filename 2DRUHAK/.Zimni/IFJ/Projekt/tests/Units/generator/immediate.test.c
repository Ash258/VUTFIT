#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include "mocks/utils.mock.c"

#define AST_STR(value) ASTMock_string(value)->ref
#define OP_STR(value) OperMock_opImmStr(value)

#define AST_INT(value) ASTMock_int(&value)->ref
#define OP_INT(value) OperMock_opImmInt(&value)

#define AST_DOUBLE(value) ASTMock_double(&value)->ref
#define OP_DOUBLE(value) OperMock_opImmDouble(&value)

#define AST_BOOL(value) ASTMock_bool(&value)->ref
#define OP_BOOL(value) OperMock_opImmBool(&value)

Test(Generator_Immediate, Expression_Immediate_String) {
    GEN();
    DataType type  = DT_STRING;
    String   value = "Ahoj";

    Location symbol = Generator_immediate(AST_STR(value));
    cr_assert_oper(Operand_symbol(symbol.symbol), OP_STR(value));
    cr_assert(List_isEmpty(list),);
}

Test(Generator_Immediate, Expression_Immediate_Int) {
    GEN();
    DataType type  = DT_INTEGER;
    int      value = 5;

    Location symbol = Generator_immediate(AST_INT(value));
    cr_assert_oper(Operand_symbol(symbol.symbol), OP_INT(value));
    cr_assert(List_isEmpty(list),);
}

Test(Generator_Immediate, Expression_Immediate_Float) {
    GEN();
    DataType type  = DT_FLOAT;
    double   value = 5.5;

    Location symbol = Generator_immediate(AST_DOUBLE(value));
    cr_assert_oper(Operand_symbol(symbol.symbol), OP_DOUBLE(value));
    cr_assert(List_isEmpty(list),);
}

Test(Generator_Immediate, Expression_Immediate_Bool) {
    GEN();
    DataType type  = DT_BOOL;
    bool     value = true;

    Location symbol = Generator_immediate(AST_BOOL(value));
    cr_assert_oper(Operand_symbol(symbol.symbol), OP_BOOL(value));
    cr_assert(List_isEmpty(list),);
}
