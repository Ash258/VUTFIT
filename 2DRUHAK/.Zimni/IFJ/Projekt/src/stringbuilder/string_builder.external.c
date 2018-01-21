// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            string_builder.external.c
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include <string.h>
#include "string_builder.external.h"

StringBuilderRef StringBuilder_create() {
    StringBuilderRef builder = malloc(sizeof(StringBuilder));
    IF_NULL_DIE(builder, ERR_OTHER);

    StringBuilder_init(builder);

    return builder;
}

void StringBuilder_init(StringBuilderRef builder) {
    assertNotNull(builder);

    builder->allocated = 32;
    builder->value     = malloc(builder->allocated * sizeof(Char));
    builder->length    = 0;
}

void StringBuilder_destruct(StringBuilderRef builder) {
    assertNotNull(builder);

    StringBuilder_dispose(builder);
    free(builder);
}

void StringBuilder_dispose(StringBuilderRef builder) {
    assertNotNull(builder);

    if (builder->value != NULL) free(builder->value);
    builder->value = NULL;
}

static void StringBuilder_resize(StringBuilderRef builder, Size to) {
    assertNotNull(builder);

    Size doubleIt = builder->allocated * 2;
    builder->allocated = to > doubleIt ? to : doubleIt;
    builder->value     = realloc(builder->value, sizeof(Char) * builder->allocated);
    IF_NULL_DIE(builder->value, ERR_OTHER);
}

void StringBuilder_append(StringBuilderRef builder, Char value) {
    assertNotNull(builder);

    if (builder->length + 1 >= builder->allocated) {
        StringBuilder_resize(builder, builder->length + 1);
    }

    builder->value[builder->length++] = value;
}

void StringBuilder_removeLast(StringBuilderRef builder) {
    assertNotNull(builder);

    if (builder->length > 0) builder->length--;
}

void StringBuilder_join(StringBuilderRef builder, String value) {
    assertNotNull(builder);

    Size length = strlen(value);

    if (builder->length + length >= builder->allocated) {
        StringBuilder_resize(builder, builder->length + length);
    }

    strcpy(builder->value + builder->length, value);
    builder->length += length;
}

String StringBuilder_build(StringBuilderRef builder, Bool dispose) {
    assertNotNull(builder);

    String value = calloc(builder->length + 1, sizeof(Char));
    strncpy(value, builder->value, builder->length);

    if (dispose) StringBuilder_dispose(builder);

    return value;
}

/** End of string_builder.external.c */
