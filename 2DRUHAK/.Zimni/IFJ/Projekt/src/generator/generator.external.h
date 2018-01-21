// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.external.h
// Assignment:      125, I
// Date:            16/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_GENERATOR_EXTERNAL_H
#define IFJ2017_GENERATOR_EXTERNAL_H

#include "../list/list.external.h"
#include "../symtable/symtable.external.h"
#include "../ast/ast.external.h"

/**
 * Generate instructions from AST.
 *
 * @param ast - AST instance.
 * @return list of instructions.
 */
ListRef Generator_convert(RootRef ast);

/**
 * Print instructions to stdout.
 *
 * @param instruction - instructions to print.
 */
void Generator_generate(ListRef instructions);

#endif //IFJ2017_GENERATOR_EXTERNAL_H

/** End of generator.external.h */
