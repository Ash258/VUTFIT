// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            token.external.c
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "token.external.h"

TokenRef Token_create(TokenType type, Address value) {
    TokenRef token = HeapRegister_allocate(G_TOKENS, sizeof(Token));

    token->type  = type;
    token->value = value;

    return token;
}

void Token_delete(TokenRef token) {
    if (token != NULL) {
        free(token);
    }
}

Bool Token_hasType(TokenRef token, TokenType type) {
    assertNotNull(token);
    return type == token->type;
}

TokenTypeRef TokenType_of(TokenType type) {
    return copyInstance(sizeof(TokenType), &type);
}

TokenType TokenType_from(Address value) {
    return *((TokenTypeRef) value);
}

/** End of token.external.c */
