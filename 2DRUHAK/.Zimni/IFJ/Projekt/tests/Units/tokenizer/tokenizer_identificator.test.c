#include <criterion/parameterized.h>

#include "../helpers.c"
#include "../../../src/tokenizer/tokenizer.identificator.c"
#include "tokenizer.mock.c"
#include "../../../src/helpers.c"
#include "../../../src/symtable/symtable.external.c"
#include "../../../src/binarytree/binary_tree.external.c"
#include "../../../src/binarytree/tree.binary_tree.c"
#include "../../../src/trie/trie.external.c"
#include "../../../src/ast/ast.external.c"
#include "../../../src/ast/typing.ast.c"

typedef struct {
    String input;
    Token  expectedOutput;
} PassingTest, * PassingTestRef;

DataTypeRef cr_DataType_of(DataType type) {
    return cr_copyInstance(sizeof(DataType), &type);
}

DataTypeRef cr_OperatorType_of(OperatorType type) {
    return cr_copyInstance(sizeof(OperatorType), &type);
}

ParameterizedTestParameters(Tokenizer_Identificator, Passing) {
    size_t         count  = 12;
    PassingTestRef values = cr_malloc(sizeof(PassingTest) * count);

    values[0]  = (PassingTest) {cr_String_of("_iden"), {T_IDENTIFIER, cr_String_of("_IDEN")}};
    values[1]  =
            (PassingTest) {cr_String_of("some_beautiful_name"), {T_IDENTIFIER, cr_String_of("SOME_BEAUTIFUL_NAME")}};
    values[2]  = (PassingTest) {cr_String_of("Integer"), {T_DATA_TYPE, cr_DataType_of(DT_INTEGER)}};
    values[3]  = (PassingTest) {cr_String_of("String"), {T_DATA_TYPE, cr_DataType_of(DT_STRING)}};
    values[4]  = (PassingTest) {cr_String_of("Double"), {T_DATA_TYPE, cr_DataType_of(DT_FLOAT)}};
    values[5]  = (PassingTest) {cr_String_of("As"), {T_K_AS, NULL}};
    values[6]  = (PassingTest) {cr_String_of("Asf"), {T_IDENTIFIER, cr_String_of("ASF")}};
    values[7]  = (PassingTest) {cr_String_of("Function"), {T_K_FUNCTION, NULL}};
    values[8]  = (PassingTest) {cr_String_of("Boolean"), {T_DATA_TYPE, cr_DataType_of(DT_BOOL)}};
    values[9]  = (PassingTest) {cr_String_of("false"), {T_I_BOOL, cr_Bool_of(false)}};
    values[10] = (PassingTest) {cr_String_of("True"), {T_I_BOOL, cr_Bool_of(true)}};
    values[11] = (PassingTest) {cr_String_of("And"), {T_O_LOGICAL, cr_OperatorType_of(OT_AND)}};

    return cr_make_param_array(PassingTest, values, count,);
}

ParameterizedTest(PassingTestRef param, Tokenizer_Identificator, Passing) {
    BufferRef buffer = Buffer_from(param->input);

    cr_assert(Tokenizer_isIdentificator(buffer),);
    TokenRef  token  = Tokenizer_tokenizeIdentificator(buffer);

    cr_assert_eq(token->type, param->expectedOutput.type,);
    switch (param->expectedOutput.type) {
        case T_DATA_TYPE:cr_assert_eq(DataType_from(token->value), DataType_from(param->expectedOutput.value),);
            break;
        case T_I_BOOL: cr_assert_eq(Bool_from(token->value), Bool_from(param->expectedOutput.value),);
            break;
        case T_O_LOGICAL: cr_assert_eq(OperatorType_from(token->value),
                                       OperatorType_from(param->expectedOutput.value),);
            break;
        default:
            if (param->expectedOutput.value == NULL) cr_assert_null(token->value,);
            else
                cr_assert_str_eq(token->value, param->expectedOutput.value,);
    }
}
