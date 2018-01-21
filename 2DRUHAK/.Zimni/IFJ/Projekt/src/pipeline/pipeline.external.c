// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            pipeline.external.c
// Assignment:      125, I
// Date:            13/11/17
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "pipeline.external.h"

//region Declarations

Bool Pipeline_carry(DataRef data, ContextRef context);

void* Pipeline_handlePipe(void* passable, ClosurePipeRef pipe);

void* Pipeline_handleFinal(void* passable, ClosurePipeRef pipe, void* closure);

void* Pipeline_handleChain(void* passable, ClosurePipeRef pipe, void* closure);

void Pipeline_destruct(ClosurePipeRef pipe);

//endregion Declarations

void* Pipeline_run(void* passable, ListRef pipes, ClosureFinalRef then) {
    assertNotNull(then);
    assertNotNull(pipes);

    ClosurePipeRef pipe = NULL;
    List_push(pipes, then);
    List_forEachReverse(pipes, &Pipeline_carry, &pipe);

    void* result = pipe->callback(passable, pipe);
    List_pop(pipes);
    Pipeline_destruct(pipe);

    return result;
}

ClosureChainRef Pipeline_createClosureChain(ContextRef data, void* (* callback)(void*, ContextRef, ClosurePipeRef)) {
    ClosureChainRef ref = malloc(sizeof(ClosureChain));
    ref->data     = data;
    ref->callback = callback;

    return ref;
}

ClosureFinalRef Pipeline_createClosureFinal(ContextRef data, void* (* callback)(void* passable, ContextRef data)) {
    ClosureFinalRef ref = malloc(sizeof(ClosureFinal));
    ref->data     = data;
    ref->callback = callback;

    return ref;
}

Bool Pipeline_carry(DataRef data, ContextRef context) {
    ClosurePipeRef* carry = (ClosurePipeRef*) context;

    ClosurePipeRef pipe = malloc(sizeof(ClosurePipe));
    pipe->chain    = data;
    pipe->callback = &Pipeline_handlePipe;
    pipe->next     = *carry;

    *carry = pipe;

    return true;
}

void* Pipeline_handlePipe(void* passable, ClosurePipeRef pipe) {
    return (pipe->chain == NULL ? Pipeline_handleFinal : Pipeline_handleChain)(passable, pipe, pipe->chain);
}

void* Pipeline_handleChain(void* passable, ClosurePipeRef pipe, void* closure) {
    ClosureChainRef chain = (ClosureChainRef) closure;
    ClosurePipeRef  next  = pipe->next;

    return chain->callback(passable, chain->data, next);
}

void* Pipeline_handleFinal(void* passable, ClosurePipeRef pipe, void* closure) {
    ClosureFinalRef final = (ClosureFinalRef) closure;

    return final->callback(passable, final->data);
}

void Pipeline_destruct(ClosurePipeRef pipe) {
    while (pipe != NULL) {
        ClosurePipeRef aux = pipe;
        pipe = pipe->next;

        free(aux);
    }
}

/** End of pipeline.external.c */
