#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/assert.h>

#include "../../../src/format/format.c"

#include "../../../src/helpers.c"
#include "../../../src/list/list.external.c"
#include "../../../src/heapregister/heap_register.external.c"
#include "../../../src/trie/trie.external.c"
#include "../../../src/binarytree/binary_tree.external.c"
#include "../../../src/binarytree/tree.binary_tree.c"
#include "../../../src/stringbuilder/string_builder.external.c"
#include "../../../src/symtable/symtable.external.c"

#include "../helpers.c"

#define PART "Something"

Test(Generator_Format, Format) {
    cr_assert_str_eq(Format_address(5), "&0005",);
    cr_assert_str_eq(Format_address(6), "&0006",);
}

Test(Generator_Format, Basic) {
    cr_assert_eq(Format_id(), 0,);
    cr_assert_eq(Format_id(), 1,);
    cr_assert_eq(Format_id(), 2,);
}

Test(Generator_Format, Address) {
    cr_assert_str_eq(Format_generateAddress(), "&0000",);
    cr_assert_str_eq(Format_generateAddress(), "&0001",);
}

Test(Generator_Format, Simple) {
    cr_assert_str_eq(Format_generateSimple(GENERATOR_IF_PREFIX),
                     FORMAT_MARK
                             GENERATOR_IF_PREFIX
                             FORMAT_SEPARATOR
                             "&0000"
                             FORMAT_MARK,);
    cr_assert_str_eq(Format_generateSimple(GENERATOR_LOOP_PREFIX),
                     FORMAT_MARK
                             GENERATOR_LOOP_PREFIX
                             FORMAT_SEPARATOR
                             "&0001"
                             FORMAT_MARK,);
}

Test(Generator_Format, ComplexId) {
    cr_assert_str_eq(Format_name(2, GENERATOR_IF_PREFIX, PART),
                     FORMAT_MARK
                             GENERATOR_IF_PREFIX
                             FORMAT_SEPARATOR
                             PART
                             FORMAT_MARK,);
    cr_assert_str_eq(Format_name(2, GENERATOR_LOOP_PREFIX, PART),
                     FORMAT_MARK
                             GENERATOR_LOOP_PREFIX
                             FORMAT_SEPARATOR
                             PART
                             FORMAT_MARK,);
}
