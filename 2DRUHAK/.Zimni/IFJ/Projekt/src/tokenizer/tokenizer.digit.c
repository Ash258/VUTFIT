// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.digit.c
// Assignment:      125, I
// Date:            13/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "tokenizer.digit.h"

Int Digit_binary(Char c) {
    if (c == '1' || c == '0') return c - '0';
    return INVALID_DIGIT;
}

Int Digit_octal(Char c) {
    if (c >= '0' && c <= '7') return c - '0';
    return INVALID_DIGIT;
}

Int Digit_decimal(Char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return INVALID_DIGIT;
}

Int Digit_hexadecimal(Char c) {
    c = toupper(c);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return INVALID_DIGIT;
}

Long Digit_positiveSequence(BufferRef buffer, DigitBase base, DigitConverter converter, Size count) {
    IF_TRUE_DIE(Buffer_eof(buffer), ERR_LEXICAL);
    assertNotNull(converter);
    UnsignedLong sequence = 0;
    Int          digit    = converter(Buffer_current(buffer)), i = 0;

    do {
        IF_TRUE_DIE(digit == INVALID_DIGIT, ERR_LEXICAL);
        sequence *= base;
        sequence += digit;
    } while (++i != count && Buffer_next(buffer) != EOF && (digit = converter(Buffer_current(buffer))) != INVALID_DIGIT);

    IF_TRUE_DIE(count > 0 && i != count, ERR_LEXICAL);
    return sequence;
}

Real Digit_negativeSequence(BufferRef buffer, DigitBase base, DigitConverter converter, Size count) {
    IF_TRUE_DIE(Buffer_eof(buffer), ERR_LEXICAL);

    Real fraction = 1, sequence = 0;
    Int  digit    = converter(Buffer_current(buffer)), i = 0;

    do {
        IF_TRUE_DIE(digit == INVALID_DIGIT, ERR_LEXICAL);
        fraction *= base;
        sequence += digit / fraction;
    } while (++i != count && Buffer_next(buffer) != EOF && (digit = converter(Buffer_current(buffer))) != INVALID_DIGIT);

    IF_TRUE_DIE(count > 0 && i != count, ERR_LEXICAL);
    return sequence;
}

/** End of tokenizer.digit.c */
