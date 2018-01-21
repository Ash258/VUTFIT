// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.loop.c
// Assignment:      125, I
// Date:            21/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "../ast/ast.external.h"
#include "generator.internal.h"
#include "../format/format.h"
#include "generator.instruction_set.h"

typedef struct LoopData {
    GeneratorRef generator;
    String       start, end;
    LoopStRef    node;
} LoopData, * LoopDataRef;

void Loop_expanded(LoopDataRef data, OperandSymbol condition) {
    OperandSymbol trueValue = Symbol_immediate(Immediate_bool(true));
    List_push(data->generator->inst, Instruction_jumpifneq(data->end, condition, trueValue));
    Generator_nestedScope(data->generator, data->node->scope);
    List_push(data->generator->inst, Instruction_jump(data->start));
}

void Generator_loop(GeneratorRef generator, LoopStRef node) {
    String id    = Format_generateAddress();
    String start = Format_name(3, GENERATOR_LOOP_PREFIX, id, "start");
    String end   = Format_name(3, GENERATOR_LOOP_PREFIX, id, "end");
    free(id);

    LoopDataRef data = &(LoopData) {.generator = generator, .start = start, .end = end, .node = node};

    List_push(generator->inst, Instruction_label(data->start));

    Location condition = Generator_expression(generator, node->condition);
    Loop_expanded(data, Generator_ensureSymbol(generator, condition));

    List_push(generator->inst, Instruction_label(end));
}

/** End of generator.loop.c */
