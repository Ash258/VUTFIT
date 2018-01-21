#include <criterion/parameterized.h>

#include "../helpers.c"
#include "tokenizer.mock.c"
#include "../../../src/tokenizer/tokenizer.number.c"
#include "../../../src/helpers.c"

typedef struct {
    String input;
    Token  expectedOutput;
} PassingTest, * PassingTestRef;

NumberRef cr_NumberRef_of(Number number) {
    return cr_copyInstance(sizeof(Number), &number);
}

ParameterizedTestParameters(Tokenizer_String, Passing) {
    size_t count = 10;

    PassingTestRef values = cr_malloc(sizeof(PassingTest) * count);
    values[0] = (PassingTest) {cr_String_of("&b01111101011000101011100111101101"),
                               {T_I_INTEGER, cr_NumberRef_of((Number) {.integer = 2103622125})}};
    values[1] = (PassingTest) {cr_String_of("&o1234567123"),
                               {T_I_INTEGER, cr_NumberRef_of((Number) {.integer = 01234567123})}};
    values[2] = (PassingTest) {cr_String_of("&hF0CDA34C"),
                               {T_I_INTEGER, cr_NumberRef_of((Number) {.integer = 0xf0cda34c})}};
    values[3] = (PassingTest) {cr_String_of("123456"), {T_I_INTEGER, cr_NumberRef_of((Number) {.integer = 123456})}};
    values[4] =
            (PassingTest) {cr_String_of("000000123456"), {T_I_INTEGER, cr_NumberRef_of((Number) {.integer = 123456})}};
    values[5] = (PassingTest) {cr_String_of("123.456"), {T_I_DOUBLE, cr_NumberRef_of((Number) {.real = 123.456})}};
    values[6] = (PassingTest) {cr_String_of("1.1e1"), {T_I_DOUBLE, cr_NumberRef_of((Number) {.real = 1.1e1})}};
    values[7] = (PassingTest) {cr_String_of("1e2"), {T_I_DOUBLE, cr_NumberRef_of((Number) {.real = 1e2})}};
    values[8] = (PassingTest) {cr_String_of("1e+1"), {T_I_DOUBLE, cr_NumberRef_of((Number) {.real = 1e+1})}};
    values[9] = (PassingTest) {cr_String_of("1e-1"), {T_I_DOUBLE, cr_NumberRef_of((Number) {.real = 1e-1})}};

    return cr_make_param_array(PassingTest, values, count,);
}

ParameterizedTest(PassingTestRef param, Tokenizer_String, Passing) {
    BufferRef buffer = Buffer_from(param->input);

    cr_assert(Tokenizer_isNumber(buffer),);
    TokenRef  token  = Tokenizer_tokenizeNumber(buffer);
    cr_assert_eq(token->type, param->expectedOutput.type,);

    NumberRef actualValue   = token->value;
    NumberRef expectedValue = param->expectedOutput.value;
    if (param->expectedOutput.type == T_I_INTEGER) {
        cr_assert_eq(actualValue->integer, expectedValue->integer,);
    } else {
        cr_assert_double_eq(actualValue->real, expectedValue->real);
    }
}
