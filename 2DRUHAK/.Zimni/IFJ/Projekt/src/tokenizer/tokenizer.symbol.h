// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.symbol.h
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TOKENIZER_SYMBOL_H
#define IFJ2017_TOKENIZER_SYMBOL_H

#include "tokenizer.external.h"
#include "../trie/trie.external.h"
#include "../ast/ast.external.h"

TokenRef Tokenizer_tokenizeSymbol(BufferRef buffer);

Bool Tokenizer_isSymbol(BufferRef buffer);

#endif //IFJ2017_TOKENIZER_SYMBOL_H

/** End of tokenizer.symbol.h */
