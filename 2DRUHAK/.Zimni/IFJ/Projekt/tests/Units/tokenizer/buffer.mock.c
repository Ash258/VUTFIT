#include <malloc.h>
#include "../../../src/buffer/buffer.external.h"

BufferRef Buffer_from(String string) {
    FileOrString input;
    input.string = string;
    return Buffer_create(input);
}

BufferRef Buffer_create(FileOrString input) {
    BufferRef buffer = calloc(1, sizeof(BufferRef));
    Buffer_init(buffer, input);
    return buffer;
}

void Buffer_init(BufferRef buffer, FileOrString input) {
    buffer->input = input;
    Buffer_next(buffer);
}

void Buffer_delete(BufferRef buffer) {
    free(buffer);
}

Char Buffer_current(BufferRef buffer) {
    return (Char) buffer->character;
}

Int Buffer_next(BufferRef buffer) {
    if (buffer->character == EOF) return EOF;

    int character = *buffer->input.string++;
    return buffer->character = character == '\0' ? EOF : character;
}

BufferRef Buffer_step(BufferRef buffer) {
    Buffer_next(buffer);
    return buffer;
}

bool Buffer_eof(BufferRef buffer) {
    return buffer->character == EOF;
}
