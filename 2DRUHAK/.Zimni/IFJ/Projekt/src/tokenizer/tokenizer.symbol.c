// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.symbol.c
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "tokenizer.symbol.h"

static TrieNode symbols;
static Bool     symbolsInitialized = false;

static void initializeSymbols() {
    if (!symbolsInitialized) {
        symbolsInitialized = true;
        //TODO - register trie to heap register

        Trie_insert(&symbols, "\n", Token_create(T_EOL, NULL));
        Trie_insert(&symbols, "(", Token_create(T_LEFT_PARENTHESIS, NULL));
        Trie_insert(&symbols, ")", Token_create(T_RIGHT_PARENTHESIS, NULL));
        Trie_insert(&symbols, ",", Token_create(T_COMMA, NULL));
        Trie_insert(&symbols, ";", Token_create(T_SEMICOLON, NULL));
        Trie_insert(&symbols, "+", Token_create(T_O_PLUS, OperatorType_of(OT_ADD)));
        Trie_insert(&symbols, "-", Token_create(T_O_MINUS, OperatorType_of(OT_SUB)));
        Trie_insert(&symbols, "/", Token_create(T_O_MULTIPLICATION, OperatorType_of(OT_DIV)));
        Trie_insert(&symbols, "*", Token_create(T_O_MULTIPLICATION, OperatorType_of(OT_MUL)));
        Trie_insert(&symbols, "\\", Token_create(T_O_DECIMAL_DIVISION, OperatorType_of(OT_IDIV)));
        Trie_insert(&symbols, "<", Token_create(T_O_RELATIONAL, OperatorType_of(OT_LT)));
        Trie_insert(&symbols, "<=", Token_create(T_O_RELATIONAL, OperatorType_of(OT_LEQ)));
        Trie_insert(&symbols, ">", Token_create(T_O_RELATIONAL, OperatorType_of(OT_GT)));
        Trie_insert(&symbols, ">=", Token_create(T_O_RELATIONAL, OperatorType_of(OT_GEQ)));
        Trie_insert(&symbols, "=", Token_create(T_O_RELATIONAL, OperatorType_of(OT_EQ)));
        Trie_insert(&symbols, "<>", Token_create(T_O_RELATIONAL, OperatorType_of(OT_NEQ)));
        Trie_insert(&symbols, "/\'", Token_create(T_COMMENT, "/\'"));
        Trie_insert(&symbols, "\'", Token_create(T_COMMENT, "\'"));
    }
}

static String Tokenizer_symbol(BufferRef buffer) {

    StringBuilder builder;
    StringBuilder_init(&builder);
    StringBuilder_append(&builder, Buffer_current(buffer));

    while (!Buffer_eof(buffer) && Trie_hasKey(&symbols, StringBuilder_build(&builder, false))) {
        StringBuilder_append(&builder, (Char) Buffer_next(buffer));
    }

    StringBuilder_removeLast(&builder);
    return StringBuilder_build(&builder, true);
}

TokenRef Tokenizer_tokenizeSymbol(BufferRef buffer) {
    initializeSymbols();

    TokenRef token = Trie_search(&symbols, Tokenizer_symbol(buffer));
    IF_NULL_DIE(token, ERR_LEXICAL);

    return token;
}

Bool Tokenizer_isSymbol(BufferRef buffer) {
    initializeSymbols();

    char search[] = {Buffer_current(buffer), '\0'};
    return Trie_hasKey(&symbols, search);
}

/** End of tokenizer.symbol.c */
