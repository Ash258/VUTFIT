// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            token.external.h
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TOKEN_EXTERNAL_H
#define IFJ2017_TOKEN_EXTERNAL_H

#include "../helpers.h"

typedef enum TokenType {
    T_K_AS,
    T_K_DECLARE,
    T_K_DIM,
    T_K_DO,
    T_K_ELSE,
    T_K_END,
    T_K_FUNCTION,
    T_K_IF,
    T_K_INPUT,
    T_K_LOOP,
    T_K_PRINT,
    T_K_RETURN,
    T_K_SCOPE,
    T_K_THEN,
    T_K_WHILE,

    // reserved

    T_K_CONTINUE,
    T_K_ELSEIF,
    T_K_EXIT,
    T_K_FOR,
    T_K_NEXT,
    T_K_SHARED,
    T_K_STATIC,

    T_I_INTEGER,
    T_I_DOUBLE,
    T_I_STRING,
    T_I_BOOL,

    T_COMMENT,
    T_IDENTIFIER,
    T_NATIVE_FUNCTION,
    T_DATA_TYPE,
    T_EOL,
    T_LEFT_PARENTHESIS,
    T_RIGHT_PARENTHESIS,
    T_COMMA,
    T_SEMICOLON,

    T_O_NOT,
    T_O_LOGICAL,
    T_O_RELATIONAL,
    T_O_MULTIPLICATION,
    T_O_DECIMAL_DIVISION,
    T_O_PLUS,
    T_O_MINUS,

    // Other token types goes here

    T_END_OF_FILE
} * TokenTypeRef, TokenType;

typedef struct Token {
    TokenType type;
    Address   value;
} ** TokenRefArr, * TokenRef, Token;

/**
 * @param type - value
 *
 * @return instance
 */
TokenTypeRef TokenType_of(TokenType type);

/**
 * @param value - instance
 *
 * @return value
 */
TokenType TokenType_from(Address value);

/**
 * Create new token.
 *
 * @param TokenType type  - type of token.
 * @param Address   value - pointer to value.
 *
 * @return TokenRef
 */
TokenRef Token_create(TokenType type, Address value);

/**
 * Destroy token.
 *
 * @param TokenRef token - token to destroy.
 */
void Token_delete(TokenRef token);

/**
 * @return TokenRef - eof token
 * @throws NULL
 */
TokenRef Token_eof();

/**
 * @param Token - Token to check
 * @param type - Type to check token against
 *
 * @return True if token is of given type, false otherwise
 */
bool Token_hasType(TokenRef token, TokenType type);

#endif //IFJ2017_TOKEN_EXTERNAL_H

/** End of token.external.h */
