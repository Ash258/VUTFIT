// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.external.h
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TOKENIZER_EXTERNAL_H
#define IFJ2017_TOKENIZER_EXTERNAL_H

#include <stdbool.h>
#include <stdarg.h>
#include "../buffer/buffer.external.h"
#include "token.external.h"
#include "tokenizer.comment.h"
#include "tokenizer.digit.h"
#include "tokenizer.identificator.h"
#include "tokenizer.number.h"
#include "tokenizer.string.h"
#include "tokenizer.symbol.h"

typedef struct Tokenizer {
    Buffer   file;
    TokenRef token;
} Tokenizer, * TokenizerRef;

typedef union {
    Long integer;
    Real real;
} * NumberRef, Number;

/**
 * Create new token stream.
 *
 * @param FileRef input - file input to tokenize
 *
 * @return TokenizerRef
 */
TokenizerRef Tokenizer_create(FileRef file);

/**
 * Destroy token stream.
 *
 * @param TokenizerRef stream - instance
 */
void Tokenizer_destruct(TokenizerRef tokenizer);

/**
 * Get next token.
 *
 * @param TokenizerRef stream - instance
 *
 * @return new token or NULL.
 */
TokenRef Tokenizer_next(TokenizerRef tokenizer);

/**
 * Validate current one and get it
 * If validation fails throws exception.
 *
 * @param Tokenizer tokenizer - instance
 * @param number - number of token types
 * @param TokenType... - varargs of token types
 *
 * @return new token
 */
TokenRef Tokenizer_step(TokenizerRef tokenizer, Int number, ...);

/**
 * Validate next one and get it
 * If validation fails throws exception.
 *
 * @param Tokenizer tokenizer - instance
 * @param number - number of token types
 * @param TokenType... - varargs of token types
 *
 * @return bew token
 */
TokenRef Tokenizer_gain(TokenizerRef tokenizer, Int number, ...);

/**
 * Get current token.
 *
 * @param TokenizerRef stream - instance
 *
 * @return current token or NULL
 */
TokenRef Tokenizer_current(TokenizerRef tokenizer);

/**
 * @param tokenizer - instance
 * @param type - type to check
 *
 * @return True if current token has given type, false otherwise
 */
Bool Tokenizer_hasCurrent(TokenizerRef tokenizer, TokenType type);

/**
 * Peek next token.
 * EOF Token is return at EOF.
 *
 * @param TokenizerRef stream - instance
 *
 * @see Token_eof()
 *
 * @return TokenRef peek token.
 *
 * @throws NULL.
 */
TokenRef Tokenizer_peekOne(TokenizerRef tokenizer);

/**
 * Peek next token. Empty array (filled with NULL) is returned at EOF.
 *
 * @param TokenizerRef stream - instance
 * @param Size count - count of tokens to peek, max: BUFSIZ
 *
 * @return TokenRefArr - Array of pointers to tokens.
 *
 * @throws NULL.
 */
TokenRefArr Tokenizer_peek(TokenizerRef tokenizer, Size count);

/**
 * Checks if token is at the end of file.
 *
 * @param TokenizerRef tokenizer - instance
 *
 * @return bool
 */
Bool Tokenizer_eof(TokenizerRef tokenizer);

#endif //IFJ2017_TOKENIZER_EXTERNAL_H

/** End of tokenizer.external.h */
