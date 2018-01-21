// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            buffer.external.h
// Assignment:      125, I
// Date:            14/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_BUFFER_EXTERNAL_H
#define IFJ2017_BUFFER_EXTERNAL_H

#include "../helpers.h"

typedef union {
    FileRef file;
    String  string;
} FileOrString;

typedef struct _Buffer {
    FileOrString input;
    Int          character;
} Buffer, * BufferRef;

/**
 * Create buffer.
 *
 * @param input - file or string to buffer
 * @return File buffer reference
 */
BufferRef Buffer_create(FileOrString input);

/**
 * Initialize buffer.
 *
 * @param input - file or string to buffer
 * @return File buffer reference
 */
void Buffer_init(BufferRef buffer, FileOrString input);

/**
 * Delete buffer.
 *
 * @param buffer - instance
 */
void Buffer_delete(BufferRef buffer);

/**
 * Get current character
 *
 * @param buffer
 * @return Current character
 */
Char Buffer_current(BufferRef buffer);

/**
 * Get next character and save it as current
 *
 * @param buffer
 * @return
 */
Int Buffer_next(BufferRef buffer);

/**
 * Step current character
 *
 * @param buffer
 * @return buffer
 */
BufferRef Buffer_step(BufferRef buffer);

/**
 * Check the end of file
 *
 * @param buffer - instance
 * @return true if it is at end, false otherwise
 */
Bool Buffer_eof(BufferRef buffer);

#endif //IFJ2017_BUFFER_EXTERNAL_H

/** End of buffer.external.h */
