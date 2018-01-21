// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            buffer.external.c
// Assignment:      125, I
// Date:            14/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "buffer.external.h"

BufferRef Buffer_create(FileOrString input) {
    BufferRef buffer = HeapRegister_allocate(G_GLOBAL, sizeof(Buffer));
    Buffer_init(buffer, input);

    return buffer;
}

void Buffer_init(BufferRef buffer, FileOrString input) {
    assertNotNull(buffer);

    buffer->input = input;
    Buffer_next(buffer);
}

void Buffer_delete(BufferRef buffer) {
    assertNotNull(buffer);

    free(buffer);
}

Char Buffer_current(BufferRef buffer) {
    assertNotNull(buffer);

    return (Char) buffer->character;
}

Int Buffer_next(BufferRef buffer) {
    assertNotNull(buffer);

    return !Buffer_eof(buffer)
           ? buffer->character = fgetc(buffer->input.file)
           : EOF;
}

BufferRef Buffer_step(BufferRef buffer) {
    assertNotNull(buffer);

    Buffer_next(buffer);
    return buffer;
}

Bool Buffer_eof(BufferRef buffer) {
    assertNotNull(buffer);

    return buffer->character == EOF;
}

/** End of buffer.external.c */
