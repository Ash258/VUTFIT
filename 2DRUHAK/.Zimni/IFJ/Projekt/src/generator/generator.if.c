// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.if.c
// Assignment:      125, I
// Date:            23/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "../c_alias.h"
#include "../trie/trie.external.h"
#include "generator.operand.h"
#include "../format/format.h"
#include "generator.instruction_set.h"
#include "generator.internal.h"

typedef struct IfData {
    GeneratorRef generator;
    UnsignedLong address;
    UnsignedLong counter;
} IfData, * IfDataRef;

static String makeId(IfDataRef data, Bool new) {
    String address = Format_address(data->address);
    if (new) data->counter++;
    String counter = Format_address(data->counter);
    String result  = Format_name(3, GENERATOR_IF_PREFIX, address, counter);
    free(address);
    free(counter);
    return result;
}

static String makeEnd(IfDataRef data) {
    String address = Format_address(data->address);
    String result  = Format_name(3, GENERATOR_IF_PREFIX, address, "end");
    free(address);
    return result;
}

static void handleCondition(IfDataRef data, IfStRef node) {
    String        next     = makeId(data, true);
    OperandSymbol trueSym  = Symbol_immediate(Immediate_bool(true));
    Location      location = Generator_expression(data->generator, node->condition);
    OperandSymbol symbol   = Generator_ensureSymbol(data->generator, location);
    List_push(data->generator->inst, Instruction_jumpifneq(next, symbol, trueSym));
}

static void handleIf(IfStRef node, IfDataRef data) {
    handleCondition(data, node);
    Generator_nestedScope(data->generator, node->onTrue);
    List_push(data->generator->inst, Instruction_jump(makeEnd(data)));
}

static Bool handleElseIf(IfStRef node, IfDataRef data) {
    IF_NULL_RETURN_DFLT(node, false)

    List_push(data->generator->inst, Instruction_label(makeId(data, false)));
    handleCondition(data, node);
    Generator_nestedScope(data->generator, node->onTrue);

    List_push(data->generator->inst, Instruction_jump(makeEnd(data)));
    return true;
}

static void handleElse(IfStRef node, IfDataRef data) {
    List_push(data->generator->inst, Instruction_label(makeId(data, false)));
    if (node->onFalse != NULL) {
        Generator_nestedScope(data->generator, node->onFalse);
    }
}

void Generator_if(GeneratorRef generator, IfStRef node) {
    IfDataRef data = &(IfData) {
            .generator = generator, .address = Format_id(), .counter = 0};

    handleIf(node, data);
    if (node->alternatives != NULL) {
        List_forEach(node->alternatives, (ListCallback) handleElseIf, data);
    }
    handleElse(node, data);
    List_push(data->generator->inst, Instruction_label(makeEnd(data)));
}

/** End of generator.if.c */
