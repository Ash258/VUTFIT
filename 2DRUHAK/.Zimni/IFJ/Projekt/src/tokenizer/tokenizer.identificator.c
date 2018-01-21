// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.identificator.c
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "tokenizer.identificator.h"

static TrieNode keywords;
static Bool     keywordsInitialized = false;

static void initializeKeyword() {
    if (!keywordsInitialized) {
        keywordsInitialized = true;
        //TODO - register trie to heap register

        Trie_insert(&keywords, "AS", Token_create(T_K_AS, NULL));
        Trie_insert(&keywords, "ASC", Token_create(T_NATIVE_FUNCTION, "ASC"));
        Trie_insert(&keywords, "DECLARE", Token_create(T_K_DECLARE, NULL));
        Trie_insert(&keywords, "DIM", Token_create(T_K_DIM, NULL));
        Trie_insert(&keywords, "DO", Token_create(T_K_DO, NULL));
        Trie_insert(&keywords, "DOUBLE", Token_create(T_DATA_TYPE, DataType_of(DT_FLOAT)));
        Trie_insert(&keywords, "ELSE", Token_create(T_K_ELSE, NULL));
        Trie_insert(&keywords, "END", Token_create(T_K_END, NULL));
        Trie_insert(&keywords, "CHR", Token_create(T_NATIVE_FUNCTION, "CHR"));
        Trie_insert(&keywords, "FUNCTION", Token_create(T_K_FUNCTION, NULL));
        Trie_insert(&keywords, "IF", Token_create(T_K_IF, NULL));
        Trie_insert(&keywords, "INPUT", Token_create(T_K_INPUT, NULL));
        Trie_insert(&keywords, "INTEGER", Token_create(T_DATA_TYPE, DataType_of(DT_INTEGER)));
        Trie_insert(&keywords, "LENGTH", Token_create(T_NATIVE_FUNCTION, "LENGTH"));
        Trie_insert(&keywords, "LOOP", Token_create(T_K_LOOP, NULL));
        Trie_insert(&keywords, "PRINT", Token_create(T_K_PRINT, NULL));
        Trie_insert(&keywords, "RETURN", Token_create(T_K_RETURN, NULL));
        Trie_insert(&keywords, "SCOPE", Token_create(T_K_SCOPE, NULL));
        Trie_insert(&keywords, "STRING", Token_create(T_DATA_TYPE, DataType_of(DT_STRING)));
        Trie_insert(&keywords, "SUBSTR", Token_create(T_NATIVE_FUNCTION, "SUBSTR"));
        Trie_insert(&keywords, "THEN", Token_create(T_K_THEN, NULL));
        Trie_insert(&keywords, "WHILE", Token_create(T_K_WHILE, NULL));

        //reserved
        Trie_insert(&keywords, "AND", Token_create(T_O_LOGICAL, OperatorType_of(OT_AND)));
        Trie_insert(&keywords, "BOOLEAN", Token_create(T_DATA_TYPE, DataType_of(DT_BOOL)));
        Trie_insert(&keywords, "NOT", Token_create(T_O_NOT, OperatorType_of(OT_NOT)));
        Trie_insert(&keywords, "OR", Token_create(T_O_LOGICAL, OperatorType_of(OT_OR)));
        Trie_insert(&keywords, "TRUE", Token_create(T_I_BOOL, Bool_of(true)));
        Trie_insert(&keywords, "FALSE", Token_create(T_I_BOOL, Bool_of(false)));
        Trie_insert(&keywords, "CONTINUE", Token_create(T_K_CONTINUE, NULL));
        Trie_insert(&keywords, "ELSEIF", Token_create(T_K_ELSEIF, NULL));
        Trie_insert(&keywords, "EXIT", Token_create(T_K_EXIT, NULL));
        Trie_insert(&keywords, "FOR", Token_create(T_K_FOR, NULL));
        Trie_insert(&keywords, "NEXT", Token_create(T_K_NEXT, NULL));
        Trie_insert(&keywords, "SHARED", Token_create(T_K_SHARED, NULL));
        Trie_insert(&keywords, "STATIC", Token_create(T_K_STATIC, NULL));
    }
}

Bool Tokenizer_isIdentificator(BufferRef buffer) {
    int c = Buffer_current(buffer);
    return isalpha(c) || c == '_';
}

static inline Bool Identificator_allowed(Char c) {
    return isalnum(c) || c == '_';
}

static String Identificator_value(BufferRef buffer) {
    IF_TRUE_DIE(!Tokenizer_isIdentificator(buffer), ERR_LEXICAL)

    StringBuilder builder;
    StringBuilder_init(&builder);

    do { StringBuilder_append(&builder, toupper(Buffer_current(buffer))); }
    while (Identificator_allowed((Char) Buffer_next(buffer)));

    return StringBuilder_build(&builder, true);
}

TokenRef Tokenizer_tokenizeIdentificator(BufferRef buffer) {
    initializeKeyword();
    String value = Identificator_value(buffer);

    TokenRef keyword = Trie_search(&keywords, value);
    return keyword != NULL ? (free(value), keyword) : Token_create(T_IDENTIFIER, value);
}

/** End of tokenizer.identificator.c */
