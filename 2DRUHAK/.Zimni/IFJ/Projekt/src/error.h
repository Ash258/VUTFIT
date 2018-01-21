// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            error.h
// Assignment:      125, I
// Date:            27/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_ERROR_H
#define IFJ2017_ERROR_H

typedef enum {
    ERR_LEXICAL                = 1,
    ERR_SYNTAX                 = 2,
    ERR_SEMANTIC_DEFINITION    = 3,
    ERR_SEMANTIC_COMPATIBILITY = 4,
    ERR_SEMANTIC_OTHER         = 6,
    ERR_OTHER                  = 99
} Error;

#ifdef NDEBUG
#ifndef DIE
#define DIE(statusCode) \
    HeapRegister_sweep(), \
    exit((statusCode));
#endif
#else
#ifndef DIE
#define DIE(statusCode) \
    HeapRegister_sweep(), \
    fprintf(stderr, "\n%s:%d\n", __FILE__, __LINE__), \
    exit((statusCode));
#endif
#endif

#define IF_NULL_DIE(value, signal) \
    if ((value) == NULL) { DIE(signal); }

#define IF_TRUE_DIE(value, signal) \
    if ((value)) { DIE(signal); }

#define IF_FALSE_DIE(value, signal) \
    if (! (value)) { DIE(signal); }

#endif //IFJ2017_ERROR_H

/** End of error.h */