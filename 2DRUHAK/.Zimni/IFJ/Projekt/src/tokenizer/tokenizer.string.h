// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.string.h
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TOKENIZER_STRING_H
#define IFJ2017_TOKENIZER_STRING_H

#include "tokenizer.external.h"
#include "../stringbuilder/string_builder.external.h"

/**
 * Tokenize string.
 *
 * @param buffer
 * @return Token
 */
TokenRef Tokenizer_tokenizeString(BufferRef buffer);

Bool Tokenizer_isString(BufferRef buffer);

#endif //IFJ2017_TOKENIZER_STRING_H

/** End of tokenizer.string.h */
