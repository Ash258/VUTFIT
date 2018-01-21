// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            debug.h
// Assignment:      125, I
// Date:            24/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_DEBUG_H
#define IFJ2017_DEBUG_H

#include <stdio.h>
#include "ast/ast.external.h"
#include "tokenizer/token.external.h"

void die(String format, ...);

String tokenTypeName(TokenType type);

void printTokenName(TokenRef token);

String ASTNodeTypeName(ASTNodeType type);

String operatorTypeName(OperatorType type);

String dataTypeName(DataType type);

Bool printTrieKey(DataRef key, ContextRef context);

#endif //IFJ2017_DEBUG_H

/** End of debug.h */
