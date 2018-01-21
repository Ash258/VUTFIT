// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.external.c
// Assignment:      125, I
// Date:            09/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "tokenizer.external.h"

static inline void Tokenizer_skipWhiteSpaces(BufferRef buffer) {
    while (!Buffer_eof(buffer) && isspace(Buffer_current(buffer)) && Buffer_current(buffer) != '\n') {
        Buffer_next(buffer);
    }
}

static TokenRef Tokenizer_gainToken(TokenizerRef tokenizer) {
    BufferRef buffer = &tokenizer->file;

    Tokenizer_skipWhiteSpaces(buffer);

    tokenizer->token =
            Buffer_eof(buffer) ? Token_create(T_END_OF_FILE, NULL) :
            Tokenizer_isSymbol(buffer) ? Tokenizer_tokenizeSymbol(buffer) :
            Tokenizer_isIdentificator(buffer) ? Tokenizer_tokenizeIdentificator(buffer) :
            Tokenizer_isNumber(buffer) ? Tokenizer_tokenizeNumber(buffer) :
            Tokenizer_isString(buffer) ? Tokenizer_tokenizeString(buffer) :
            NULL;

    IF_NULL_DIE(tokenizer->token, ERR_LEXICAL);

    return Token_hasType(tokenizer->token, T_COMMENT)
           ? (Tokenizer_skipComment(buffer, tokenizer->token)), Tokenizer_gainToken(tokenizer)
           : tokenizer->token;
}

TokenizerRef Tokenizer_create(FileRef file) {
    assertNotNull(file);

    TokenizerRef tokenizer = HeapRegister_allocate(G_GLOBAL, sizeof(Tokenizer));
    Buffer_init(&tokenizer->file, (FileOrString) {.file = file});
    Tokenizer_gainToken(tokenizer);

    return tokenizer;
}

void Tokenizer_destruct(TokenizerRef tokenizer) {
    assertNotNull(tokenizer);
    HeapRegister_free(G_GLOBAL, tokenizer);
}

TokenRef Tokenizer_next(TokenizerRef tokenizer) {
    assertNotNull(tokenizer);

    return Tokenizer_gainToken(tokenizer);
}

TokenRef Tokenizer_step(TokenizerRef tokenizer, Int number, ...) {
    assertNotNull(tokenizer);

    va_list vaList;
    va_start(vaList, number);
    TokenRef token = NULL;
    for (int i     = 0; i < number; ++i) {
        IF_FALSE_DIE(Token_hasType(token = Tokenizer_current(tokenizer), va_arg(vaList, TokenType)), ERR_SYNTAX)
        Tokenizer_next(tokenizer);
    }

    va_end(vaList);
    return token;
}

TokenRef Tokenizer_gain(TokenizerRef tokenizer, Int number, ...) {
    assertNotNull(tokenizer);

    va_list vaList;
    va_start(vaList, number);

    for (int i = 0; i < number; ++i) {
        IF_FALSE_DIE(Token_hasType(Tokenizer_next(tokenizer), va_arg(vaList, TokenType)), ERR_SYNTAX)
    }

    va_end(vaList);
    return Tokenizer_current(tokenizer);
}

TokenRef Tokenizer_current(TokenizerRef tokenizer) {
    assertNotNull(tokenizer);

    return tokenizer->token;
}

Bool Tokenizer_eof(TokenizerRef tokenizer) {
    assertNotNull(tokenizer);

    return Buffer_eof(&tokenizer->file) != 0;
}

Bool Tokenizer_hasCurrent(TokenizerRef tokenizer, TokenType type) {
    assertNotNull(tokenizer);

    return Token_hasType(Tokenizer_current(tokenizer), type);
}

/** End of tokenizer.external.c */
