// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.identificator.h
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TOKENIZER_IDENTIFICATOR_H
#define IFJ2017_TOKENIZER_IDENTIFICATOR_H

#include "tokenizer.external.h"

TokenRef Tokenizer_tokenizeIdentificator(BufferRef buffer);

Bool Tokenizer_isIdentificator(BufferRef buffer);

#endif //IFJ2017_TOKENIZER_IDENTIFICATOR_H

/** End of tokenizer.identificator.h */
