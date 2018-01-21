// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            pipeline.external.h
// Assignment:      125, I
// Date:            13/11/17
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_PIPELINE_EXTERNAL_H
#define IFJ2017_PIPELINE_EXTERNAL_H

#include "../list/list.external.h"

typedef struct _ClosurePipe {
    void               * chain;
    struct _ClosurePipe* next;

    void* (* callback)(void* passable, struct _ClosurePipe* next);
} * ClosurePipeRef, ClosurePipe;

typedef void* (* Callback)(void* passable, ContextRef data, ClosurePipeRef next);

typedef struct {
    ContextRef data;
    Callback   callback;
} * ClosureChainRef, ClosureChain;

typedef void* (* FinalCallback)(void* passable, ContextRef data);

typedef struct {
    ContextRef    data;
    FinalCallback callback;
} * ClosureFinalRef, ClosureFinal;

/**
 * Send passable via pipes with terminal end.
 *
 * @param passable - passable reference
 * @param pipes - list of pipes
 * @param then - terminal callback
 *
 * @return pipeline result
 */
void* Pipeline_run(void* passable, ListRef pipes, ClosureFinalRef then);

/**
 *
 * @param data - closure context
 * @param callback - closure callback
 *
 * @return instance
 */
ClosureChainRef Pipeline_createClosureChain(ContextRef data, Callback callback);

/**
 * @param data - closure context
 * @param callback - closure callback
 *
 * @return instance
 */
ClosureFinalRef Pipeline_createClosureFinal(ContextRef data, FinalCallback callback);

#endif //IFJ2017_PIPELINE_EXTERNAL_H

/** End of pipeline.external.h */
