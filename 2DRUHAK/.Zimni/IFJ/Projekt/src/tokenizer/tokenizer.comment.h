// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.comment.h
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TOKENIZER_COMMENT_H
#define IFJ2017_TOKENIZER_COMMENT_H

#include "tokenizer.external.h"

/**
 * Skip any type of comment.
 *
 * @param buffer - buffer
 * @param buffer - comment token
 */
void Tokenizer_skipComment(BufferRef buffer, TokenRef token);

#endif //IFJ2017_TOKENIZER_COMMENT_H

/** End of tokenizer.comment.h */
