// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            string_builder.external.h
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_STRING_BUILDER_EXTERNAL_H
#define IFJ2017_STRING_BUILDER_EXTERNAL_H

#include "../helpers.h"

typedef struct StringBuilder {
    String value;
    Size   length;
    Size   allocated;
} StringBuilder, * StringBuilderRef;

/**
 * Create instance.
 *
 * @return String builder reference
 */
StringBuilderRef StringBuilder_create();

/**
 * Initialize instance.
 *
 * @return String builder reference
 */
void StringBuilder_init(StringBuilderRef builder);

/**
 * Join to builder.
 *
 * @param builder - instance
 * @param value   - value to join
 */
void StringBuilder_join(StringBuilderRef builder, String value);

/**
 * Append to builder.
 *
 * @param builder - instance
 * @param value   - value to append
 */
void StringBuilder_append(StringBuilderRef builder, Char value);

/**
 * Build given string.
 *
 * @param builder - instance
 * @paraam dispose - if true, builder data will be disposed.
 *
 * @return built String
 */
String StringBuilder_build(StringBuilderRef builder, Bool dispose);

/**
 * @param builder - instance
 */
void StringBuilder_dispose(StringBuilderRef builder);

/**
 * Pop last character in builder.
 *
 * @param builder - instance
 */
void StringBuilder_removeLast(StringBuilderRef builder);

#endif //IFJ2017_STRING_BUILDER_EXTERNAL_H

/** End of string_builder.external.h */
