// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.number.h
// Assignment:      125, I
// Date:            9/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TOKENIZER_NUMBER_H
#define IFJ2017_TOKENIZER_NUMBER_H

#include "tokenizer.external.h"

/**
 * Tokenize Number.
 *
 * @param buffer
 *
 * @return
 */
TokenRef Tokenizer_tokenizeNumber(BufferRef buffer);

Bool Tokenizer_isNumber(BufferRef buffer);

#endif //IFJ2017_TOKENIZER_NUMBER_H

/** End of tokenizer.number.h */
