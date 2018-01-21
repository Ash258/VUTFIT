#include <criterion/parameterized.h>
#include "../helpers.c"

#include "tokenizer.mock.c"
#include "../../../src/tokenizer/tokenizer.symbol.c"
#include "../../../src/helpers.c"
#include "../../../src/symtable/symtable.external.c"
#include "../../../src/binarytree/binary_tree.external.c"
#include "../../../src/binarytree/tree.binary_tree.c"
#include "../../../src/trie/trie.external.c"
#include "../../../src/ast/ast.external.c"
#include "../../../src/parser/parser.variable_register.c"
#include "../../../src/ast/typing.ast.c"

typedef struct {
    String input;
    Token  expectedOutput;
} PassingTest, * PassingTestRef;

DataTypeRef cr_Opertor_of(OperatorType type) {
    return cr_copyInstance(sizeof(OperatorType), &type);
}

ParameterizedTestParameters(Tokenizer_Identificator, Passing) {
    size_t         count  = 20;
    PassingTestRef values = cr_malloc(sizeof(PassingTest) * count);
    values[0]  = (PassingTest) {cr_String_of("\n asd"), {T_EOL, NULL}};
    values[1]  = (PassingTest) {cr_String_of("( asd"), {T_LEFT_PARENTHESIS, NULL}};
    values[2]  = (PassingTest) {cr_String_of(") asd"), {T_RIGHT_PARENTHESIS, NULL}};
    values[3]  = (PassingTest) {cr_String_of(","), {T_COMMA, NULL}};
    values[4]  = (PassingTest) {cr_String_of(";"), {T_SEMICOLON, NULL}};
    values[5]  = (PassingTest) {cr_String_of("+"), {T_O_PLUS, cr_Opertor_of(OT_ADD)}};
    values[6]  = (PassingTest) {cr_String_of("-"), {T_O_MINUS, cr_Opertor_of(OT_SUB)}};
    values[7]  = (PassingTest) {cr_String_of("/"), {T_O_MULTIPLICATION, cr_Opertor_of(OT_DIV)}};
    values[8]  = (PassingTest) {cr_String_of("*"), {T_O_MULTIPLICATION, cr_Opertor_of(OT_MUL)}};
    values[9]  = (PassingTest) {cr_String_of("\\"), {T_O_DECIMAL_DIVISION, cr_Opertor_of(OT_IDIV)}};
    values[10] = (PassingTest) {cr_String_of("<"), {T_O_RELATIONAL, cr_Opertor_of(OT_LT)}};
    values[11] = (PassingTest) {cr_String_of("<="), {T_O_RELATIONAL, cr_Opertor_of(OT_LEQ)}};
    values[12] = (PassingTest) {cr_String_of(">"), {T_O_RELATIONAL, cr_Opertor_of(OT_GT)}};
    values[13] = (PassingTest) {cr_String_of(">="), {T_O_RELATIONAL, cr_Opertor_of(OT_GEQ)}};
    values[14] = (PassingTest) {cr_String_of("="), {T_O_RELATIONAL, cr_Opertor_of(OT_EQ)}};
    values[15] = (PassingTest) {cr_String_of("<>"), {T_O_RELATIONAL, cr_Opertor_of(OT_NEQ)}};
    values[16] = (PassingTest) {cr_String_of("<>)"), {T_O_RELATIONAL, cr_Opertor_of(OT_NEQ)}};
    values[17] = (PassingTest) {cr_String_of("+5"), {T_O_PLUS, cr_Opertor_of(OT_ADD)}};
    values[18] = (PassingTest) {cr_String_of("-5"), {T_O_MINUS, cr_Opertor_of(OT_SUB)}};
    values[19] = (PassingTest) {cr_String_of("/5"), {T_O_MULTIPLICATION, cr_Opertor_of(OT_DIV)}};

    return cr_make_param_array(PassingTest, values, count,);
}

ParameterizedTest(PassingTestRef param, Tokenizer_Identificator, Passing) {
    BufferRef buffer = Buffer_from(param->input);

    cr_assert(Tokenizer_isSymbol(buffer),);
    TokenRef  token  = Tokenizer_tokenizeSymbol(buffer);
    cr_assert_eq(token->type, param->expectedOutput.type,);
    if (param->expectedOutput.value == NULL) cr_assert_null(token->value,);
    else
        cr_assert_eq(*((OperatorTypeRef) token->value), *((OperatorTypeRef) param->expectedOutput.value),);
}
