// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            helpers.h
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_HELPERS_H
#define IFJ2017_HELPERS_H

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "c_alias.h"
#include "error.h"
#include "heapregister/heap_register.external.h"

void simpleDestructor(DataRef data);

/**
 * @param size - size of instance
 * @param source - instance to copy
 *
 * @return new instance
 */
void* copyInstance(size_t size, const void* source);

/**
 * @param value - instance value
 *
 * @return instance
 */
Int* Int_of(Int value);

/**
 * @param value - instance
 *
 * @return value
 */
Int Int_from(Address value);

/**
 * @param value - instance value
 *
 * @return instance
 */
Real* Real_of(Real value);

/**
 * @param value - instance
 *
 * @return value
 */
Real Real_from(Address value);

/**
 * @param value - instance value
 *
 * @return instance
 */
Bool* Bool_of(Bool value);

/**
 * @param value - instance
 *
 * @return value
 */
Bool Bool_from(Address value);

/**
 * @param value - instance
 *
 * @return value
 */
String String_from(Address value);

#define assertNotNull(value) assert(((value)) != NULL)

// region Function checkers

#define IF_TRUE_RETURN_NULL(value) \
    if ((value)) return NULL;

#define IF_TRUE_RETURN_VALUE(condition, value) \
    if ((condition)) {return value;}

#define IF_TRUE_RETURN_DFLT(value, default) \
    if ((value)) return (default);

#define IF_TRUE_RETURN_VOID(value) \
    if ((value)) return;

#define IF_FALSE_RETURN_NULL(value) \
    if (! (value)) return NULL;

#define IF_FALSE_RETURN_DFLT(value, default) \
    if (! (value)) return (default);

#define IF_FALSE_RETURN_VOID(value) \
    if (! (value)) return;

#define IF_NULL_RETURN_NULL(value) \
    if ((value) == NULL) return NULL;

#define IF_NULL_RETURN_DFLT(value, default) \
    if ((value) == NULL) return (default);

#define IF_NULL_RETURN_VOID(value) \
    if ((value) == NULL) return;

// endregion

#endif //IFJ2017_HELPERS_H

/** End of helpers.h */
