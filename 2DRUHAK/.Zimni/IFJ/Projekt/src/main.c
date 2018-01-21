// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            main.c
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include <stdio.h>
#include "helpers.h"
#include "tokenizer/tokenizer.external.h"
#include "parser/parser.external.h"
#include "generator/generator.external.h"

Int main(Int argc, StringArr argv) {
    if (argc > 1) return 0;

    HeapRegister_setDestructor(G_IMMEDIATE, simpleDestructor);
    HeapRegister_setDestructor(G_INSTRUCTIONS, simpleDestructor);
    HeapRegister_setDestructor(G_GLOBAL, simpleDestructor);
    HeapRegister_setDestructor(G_TOKENS, simpleDestructor);
    HeapRegister_setDestructor(G_VARIABLES, simpleDestructor);

    TokenizerRef tokenizer    = Tokenizer_create(stdin);
    RootRef      ast          = Parser_parse(tokenizer);
    ListRef      instructions = Generator_convert(ast);
    Generator_generate(instructions);
    HeapRegister_sweep();
}

/** End of main.c */
