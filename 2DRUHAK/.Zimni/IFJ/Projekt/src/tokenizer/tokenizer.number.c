// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.number.c
// Assignment:      125, I
// Date:            9/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "tokenizer.number.h"

static TokenRef Number_create(TokenType type, Number number) {
    NumberRef value = HeapRegister_allocate(G_GLOBAL, sizeof(Number));
    *value = number;

    return Token_create(type, value);
}

TokenRef Number_decimal(BufferRef buffer) {
    Number    number;
    TokenType type = T_I_INTEGER;

    number.integer = Digit_positiveSequence(buffer, BASE_DECIMAL, Digit_decimal, 0);
    if (Buffer_current(buffer) == '.') {
        type = T_I_DOUBLE;
        number.real = number.integer + Digit_negativeSequence(Buffer_step(buffer), BASE_DECIMAL, Digit_decimal, 0);
    }

    if (tolower(Buffer_current(buffer)) == 'e') {
        if (type == T_I_INTEGER) number.real = number.integer;
        type = T_I_DOUBLE;

        Long exponent = 1;
        Int  c        = Buffer_next(buffer);

        if (c == '-') { exponent = -1, Buffer_step(buffer); }
        else if (c == '+') { Buffer_step(buffer); }
        else if (!isdigit(c)) DIE(ERR_LEXICAL);

        exponent *= Digit_positiveSequence(buffer, BASE_DECIMAL, Digit_decimal, 0);
        number.real *= pow(10, exponent);
    }

    return Number_create(type, number);
}

static TokenRef Number_integerBase(BufferRef buffer) {
    DigitBase      base;
    DigitConverter converter;

    switch (tolower(Buffer_next(buffer))) {
        case 'h': base = BASE_HEXA;
            converter  = Digit_hexadecimal;
            break;
        case 'o': base = BASE_OCTAL;
            converter  = Digit_octal;
            break;
        case 'b': base = BASE_BINARY;
            converter  = Digit_binary;
            break;
        default: DIE(ERR_SYNTAX);
    }

    buffer->character = '0'; // TODO: think about your life
    Number number;
    number.integer = Digit_positiveSequence(buffer, base, converter, 0);

    IF_TRUE_DIE(number.integer == INVALID_DIGIT, ERR_LEXICAL);
    return Number_create(T_I_INTEGER, number);
}

TokenRef Tokenizer_tokenizeNumber(BufferRef buffer) {
    TokenRef token = Buffer_current(buffer) == '&'
                     ? Number_integerBase(buffer)
                     : Number_decimal(buffer);

    return token;
}

Bool Tokenizer_isNumber(BufferRef buffer) {
    int c = Buffer_current(buffer);

    return c == '&' || isdigit(c);
}

/** End of tokenizer.number.c */
