#include <criterion/criterion.h>
#include <stdio.h>
#include "tokenizer.mock.c"
#include "../../../src/tokenizer/tokenizer.comment.c"
#include "../../../src/helpers.c"

Test(Tokenizer_Comment, Line) {
    TokenRef  token  = Token_create(T_COMMENT, "\'");
    BufferRef buffer = Buffer_from("\'asdfasdf\nsy");
    Tokenizer_skipComment(buffer, token);
    cr_assert_eq(Buffer_current(buffer), '\n',);
    Buffer_step(buffer);
    cr_assert_eq(Buffer_current(buffer), 's',);
    Buffer_step(buffer);
    cr_assert_eq(Buffer_current(buffer), 'y',);
}

Test(Tokenizer_Comment, Block) {
    TokenRef  token  = Token_create(T_COMMENT, "/\'");
    BufferRef buffer = Buffer_from("/'asdfasdf\nasdfasdf\nasdfasdf'/sy");
    Tokenizer_skipComment(buffer, token);
    cr_assert_eq(Buffer_current(buffer), 's',);
    Buffer_step(buffer);
    cr_assert_eq(Buffer_current(buffer), 'y',);
}
