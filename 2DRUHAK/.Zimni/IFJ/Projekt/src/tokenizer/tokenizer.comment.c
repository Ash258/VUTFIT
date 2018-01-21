// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.comment.c
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "string.h"
#include "tokenizer.comment.h"

static void Comment_lineComment(BufferRef buffer) {
    while (!Buffer_eof(buffer) && Buffer_current(buffer) != '\n') {
        Buffer_step(buffer);
    }
}

static void Comment_blockComment(BufferRef buffer) {
    while (true) {
        if (Buffer_current(buffer) == '\'') {
            if (Buffer_next(buffer) == '/') break;
        } else if (Buffer_eof(buffer)) {
            DIE(ERR_LEXICAL)
        } else {
            Buffer_step(buffer);
        }
    }

    Buffer_step(buffer);
}

void Tokenizer_skipComment(BufferRef buffer, TokenRef token) {
    if (strcmp(token->value, "\'") == 0) {
        Comment_lineComment(buffer);
    } else {
        Comment_blockComment(buffer);
    }
}

/** End of tokenizer.comment.c */
