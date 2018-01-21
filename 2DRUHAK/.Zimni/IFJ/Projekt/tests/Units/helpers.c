#include <criterion/criterion.h>
#include "../../src/c_alias.h"

void cr_assert_double_eq(double actual, double expected) {
    cr_assert_float_eq(actual, expected, 0.0001, "The expression %g == %g is false!", actual, expected);
}

void cr_assert_int_eq(int actual, int expected) {
    cr_assert_eq(actual, expected, "The expression %d == %d is false!", actual, expected);
}

void cr_assert_string_eq(String actual, String expected) {
    cr_assert_str_eq(actual, expected, "The expression `%s` == `%s` is false!", actual, expected);
}

char* cr_String_of(char* str) {
    char* ptr = cr_malloc(strlen(str) + 1);
    if (ptr) strcpy(ptr, str);

    return ptr;
}

void* cr_copyInstance(size_t size, void* source) {
    void* destination = cr_malloc(size);
    memcpy(destination, source, size);

    return destination;
}

double* cr_Real_of(Real value) {
    return cr_copyInstance(sizeof(double), &value);
}

int* cr_Int_of(Int value) {
    return cr_copyInstance(sizeof(int), &value);
}

Bool* cr_Bool_of(Bool value) {
    return cr_copyInstance(sizeof(Bool), &value);
}
