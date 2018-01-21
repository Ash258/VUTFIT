#include <criterion/criterion.h>
#include "../../../src/c_alias.h"
#include "../tokenizer/buffer.mock.c"

String    string;
BufferRef buffer;

Test(Buff_Init, Basic) {
    string = "a";
    buffer = Buffer_from(string);

    cr_assert_eq(buffer->character, string[0],);
    cr_assert_eq(Buffer_current(buffer), string[0],);
    cr_assert_not(Buffer_eof(buffer),);
}

Test(Buff_Init, Empty) {
    buffer = Buffer_from("");

    cr_assert_eq(buffer->character, -1,);
    cr_assert_eq(Buffer_current(buffer), -1,);
    cr_assert(Buffer_eof(buffer),);
}

Test(Buff_Next, Basic) {
    string     = "asdf";
    buffer     = Buffer_from(string);

    cr_assert_eq(Buffer_current(buffer), string[0],);
    for (Int i = 1; i < strlen(string); ++i) {
        cr_assert_eq(Buffer_next(buffer), string[i],);
    }

    cr_assert_eq(Buffer_next(buffer), -1,);
    cr_assert(Buffer_eof(buffer),);
}
