// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            parser.external.h
// Assignment:      125, I
// Date:            15/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_PARSER_EXTERNAL_H
#define IFJ2017_PARSER_EXTERNAL_H

#include "../ast/ast.external.h"
#include "../tokenizer/tokenizer.external.h"

/**
 * Parse program with given tokenizer.
 *
 * @param tokenizer - instance
 *
 * @return AST root
 */
RootRef Parser_parse(TokenizerRef tokenizer);

#endif //IFJ2017_PARSER_EXTERNAL_H

/** End of parser.external.h */
