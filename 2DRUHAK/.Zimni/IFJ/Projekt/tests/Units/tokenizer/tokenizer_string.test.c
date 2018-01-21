#include <stdbool.h>
#include <setjmp.h>

bool dieCalled = false;

jmp_buf env_buffer;

#define DIE(x) dieCalled = true; longjmp(env_buffer, 1);

#include <criterion/parameterized.h>
#include "../helpers.c"
#include "tokenizer.mock.c"
#include "../../../src/tokenizer/tokenizer.string.c"
#include "../../../src/helpers.c"

typedef struct {
    String input;
    String expectedOutput;
} * PassingTestRef, PassingTest;

void Passing_destructor(struct criterion_test_params* crp) {
    PassingTestRef* tests = crp->params;
    for (size_t i = 0; i < crp->length; ++i) {
        cr_free(tests[i]->expectedOutput);
        cr_free(tests[i]->input);
    }

    cr_free(tests);
}

ParameterizedTestParameters(Tokenizer_String, Passing) {
    size_t         count  = 13;
    PassingTestRef values = cr_malloc(sizeof(PassingTest) * count);
    values[0]  = (PassingTest) {cr_String_of("!\"\""), cr_String_of("")};
    values[1]  = (PassingTest) {cr_String_of("!\"asdf\""), cr_String_of("asdf")};
    values[2]  = (PassingTest) {cr_String_of("!\"AsDf\""), cr_String_of("AsDf")};
    values[3]  = (PassingTest) {cr_String_of("!\"\\\"\\n\""), cr_String_of("\"\n")};
    values[4]  = (PassingTest) {cr_String_of("!\"a\\&h6A3b\""), cr_String_of("aj3b")};
    values[5]  = (PassingTest) {cr_String_of("!\"a\\&o1523b\""), cr_String_of("aj3b")};
    values[6]  = (PassingTest) {cr_String_of("!\"a\\&b011010103b\""), cr_String_of("aj3b")};
    values[7]  = (PassingTest) {cr_String_of("!\"a\\1063b\""), cr_String_of("aj3b")};
    values[8]  = (PassingTest) {cr_String_of("!\"\\a\""), cr_String_of("\a")};
    values[9]  = (PassingTest) {cr_String_of("!\"\\b\""), cr_String_of("\b")};
    values[10] = (PassingTest) {cr_String_of("!\"\\t\""), cr_String_of("\t")};
    values[11] = (PassingTest) {cr_String_of("!\"\\n\""), cr_String_of("\n")};
    values[12] = (PassingTest) {cr_String_of("!\"\\l\""), cr_String_of("\n")};

    return cr_make_param_array(PassingTest, values, count, Passing_destructor);
}

ParameterizedTest(PassingTestRef param, Tokenizer_String, Passing) {
    BufferRef buffer = Buffer_from(param->input);

    cr_assert(Tokenizer_isString(buffer),);
    TokenRef  token  = Tokenizer_tokenizeString(buffer);

    cr_assert_eq(token->type, T_I_STRING,);
    cr_assert_str_eq(token->value, param->expectedOutput,);
}

typedef struct {
    String input;
} * FailingTestRef, FailingTest;

void Failing_destructor(struct criterion_test_params* crp) {
    FailingTestRef* tests = crp->params;
    for (size_t i = 0; i < crp->length; ++i) {
        cr_free(tests[i]->input);
    }

    cr_free(tests);
}

ParameterizedTestParameters(Tokenizer_String, Failing) {
    size_t         count  = 7;
    FailingTestRef values = cr_malloc(sizeof(FailingTest) * count);
    values[0] = (FailingTest) {cr_String_of("asdf")};
    values[1] = (FailingTest) {cr_String_of("!asdf")};
    values[2] = (FailingTest) {cr_String_of("!\"asdf")};
    values[3] = (FailingTest) {cr_String_of("!\"a\\&o159\"")};
    values[4] = (FailingTest) {cr_String_of(("!\"a\\&b201101011\""))};
    values[5] = (FailingTest) {cr_String_of("!\"a\\&h6Z\"")};
    values[5] = (FailingTest) {cr_String_of("!\"a\\&z6Z\"")};
    values[6] = (FailingTest) {cr_String_of("!\"a\\256\"")};

    return cr_make_param_array(FailingTest, values, count, Failing_destructor);
}

ParameterizedTest(FailingTestRef param, Tokenizer_String, Failing) {
    BufferRef buffer = Buffer_from(param->input);
    int       val    = setjmp(env_buffer);
    if (val == 0) Tokenizer_tokenizeString(buffer);

    cr_assert_eq(dieCalled, true,);
}
