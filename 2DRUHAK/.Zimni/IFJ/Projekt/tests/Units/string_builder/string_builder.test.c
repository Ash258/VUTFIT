#include <criterion/criterion.h>
#include "../../../src/helpers.h"
#include "../tokenizer/utils.mock.c"

StringBuilder builder;
String        expected;

void setup(void) {
    StringBuilder_init(&builder);
}

TestSuite(StringBuilder, .init = setup);

Test(StringBuilder, Init) {
    StringBuilder builder1 = {.value = NULL, .allocated = 12789436, .length = 1234};
    StringBuilder_init(&builder1);

    cr_assert_not_null(builder1.value,);
    cr_assert_eq(builder1.allocated, 32,);
    cr_assert_eq(builder1.length, 0,);
}

Test(StringBuilder, Join) {
    expected = "asdf";
    StringBuilder_join(&builder, expected);
    cr_assert_str_eq(StringBuilder_build(&builder, true), expected,);
}

Test(StringBuilder, TwoJoins) {
    String part = "asdf";
    expected = "asdfasdf";
    StringBuilder_join(&builder, part);
    StringBuilder_join(&builder, part);
    cr_assert_str_eq(StringBuilder_build(&builder, true), expected,);
}

Test(StringBuilder, Append) {
    expected = "c";
    StringBuilder_append(&builder, expected[0]);
    cr_assert_str_eq(StringBuilder_build(&builder, true), expected,);
}

Test(StringBuilder, TwoAppends) {
    expected = "cc";
    StringBuilder_append(&builder, expected[0]);
    StringBuilder_append(&builder, expected[1]);
    cr_assert_str_eq(StringBuilder_build(&builder, true), expected,);
}
