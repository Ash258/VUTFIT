// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.string.c
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "tokenizer.string.h"

static int decimal_byte(BufferRef buffer) {
    int byte = (int) Digit_positiveSequence(buffer, BASE_DECIMAL, Digit_decimal, 3);
    IF_FALSE_DIE(byte >= 001 && byte <= 255, ERR_LEXICAL);

    return byte;
}

static int Escaped_convertToCharacter(BufferRef buffer) {
    IF_TRUE_DIE(Buffer_current(buffer) != '\\', ERR_LEXICAL)

    int c = Buffer_next(buffer);
    switch (c) {
        case 'a': return 7;
        case 'b': return 8;
        case 't': return 9;
        case 'n':
        case 'l': return 10;
        case 'v': return 11;
        case 'f': return 12;
        case 'r': return 13;

        case '\\':
        case '"':
        case '\'': return c;
        default: break;
    }
    if (isdigit(c)) return decimal_byte(buffer);
    if (c == 'u') return (int) Digit_positiveSequence(Buffer_step(buffer), BASE_HEXA, Digit_hexadecimal, 4);
    if (c == '&') {
        c = tolower(Buffer_next(buffer));
        switch (c) {
            case 'h': return (int) Digit_positiveSequence(Buffer_step(buffer), BASE_HEXA, Digit_hexadecimal, 2);
            case 'o': return (int) Digit_positiveSequence(Buffer_step(buffer), BASE_OCTAL, Digit_octal, 3);
            case 'b': return (int) Digit_positiveSequence(Buffer_step(buffer), BASE_BINARY, Digit_binary, 8);
            default: DIE(ERR_LEXICAL);
        }
    }

    DIE(ERR_LEXICAL);
}

static String String_value(BufferRef buffer) {
    StringBuilderRef builder = StringBuilder_create();

    while (Buffer_next(buffer) != EOF) {
        int c = Buffer_current(buffer), byte = c;
        if (c == '"') break;
        if (c == '\\') byte = Escaped_convertToCharacter(buffer);
        StringBuilder_append(builder, (Char) byte);
    }

    return StringBuilder_build(builder, true);
}

TokenRef Tokenizer_tokenizeString(BufferRef buffer) {
    IF_TRUE_DIE(Buffer_current(buffer) != '!', ERR_LEXICAL)
    IF_TRUE_DIE(Buffer_next(buffer) != '"', ERR_LEXICAL)

    String string = String_value(buffer);
    IF_NULL_DIE(string, ERR_OTHER);

    IF_TRUE_DIE(Buffer_current(buffer) != '"', ERR_LEXICAL)
    Buffer_step(buffer); //step terminating symbol

    return Token_create(T_I_STRING, string);
}

Bool Tokenizer_isString(BufferRef buffer) {
    return Buffer_current(buffer) == '!';
}

/** End of tokenizer.string.c */
