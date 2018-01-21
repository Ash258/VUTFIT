#include <criterion/criterion.h>

#include "../../../src/trie/trie.external.c"
#include "../../../src/list/list.external.c"
#include "../../../src/helpers.c"
#include "../../../src/stringbuilder/string_builder.external.c"
#include "../../../src/heapregister/heap_register.external.c"

TrieNode node;

void setup(void) {
    Trie_init(&node);
}

void teardown(void) {
    Trie_dispose(&node, NULL);
}

TestSuite(Trie, .init = setup, .fini = teardown);

void cr_list_contains(ListRef list, int number, ...) {
    va_list vaList;
    va_start(vaList, number);

    for (int i = 0; i < number; ++i) {
        cr_assert_str_eq(List_shift(list), va_arg(vaList, String),);
    }

    va_end(vaList);
}

Test(Trie, Insert) {
    int first  = 5;
    int second = 6;

    cr_assert_null(Trie_search(&node, "foo"),);
    cr_assert_null(Trie_search(&node, "foo-s"),);

    Trie_insert(&node, "foo-s", &second);
    cr_assert_null(Trie_search(&node, "foo"),);
    cr_assert_eq(Trie_search(&node, "foo-s"), &second,);

    Trie_insert(&node, "foo", &first);
    cr_assert_eq(Trie_search(&node, "foo"), &first,);
    cr_assert_eq(Trie_search(&node, "foo-s"), &second,);
}

Test(Trie, Delete) {
    int first  = 5;
    int second = 6;

    Trie_insert(&node, "foo-s", &second);
    Trie_insert(&node, "foo", &first);
    cr_assert_eq(Trie_search(&node, "foo"), &first,);
    cr_assert_eq(Trie_search(&node, "foo-s"), &second,);

    Trie_delete(&node, "foo");
    cr_assert_null(Trie_search(&node, "foo"),);
    cr_assert_eq(Trie_search(&node, "foo-s"), &second,);

    Trie_insert(&node, "foo", &first);
    Trie_delete(&node, "foo-s");
    cr_assert_null(Trie_search(&node, "foo-s"),);
    cr_assert_eq(Trie_search(&node, "foo"), &first,);
}

Test(Trie, Keys) {
    int value = 5;

    Trie_insert(&node, "foo-s", &value);
    Trie_insert(&node, "foo", &value);
    Trie_insert(&node, "arcam", &value);
    Trie_insert(&node, "arcamsis", &value);

    cr_list_contains(Trie_getKeys(&node), 4, "arcam", "arcamsis", "foo", "foo-s");

    Trie_delete(&node, "foo-s");
    cr_list_contains(Trie_getKeys(&node), 3, "arcam", "arcamsis", "foo");

    Trie_delete(&node, "arcam");
    cr_list_contains(Trie_getKeys(&node), 2, "arcamsis", "foo");
}

Test(Trie, HasKey) {
    int value = 5;

    Trie_insert(&node, "foo-s", &value);
    cr_assert(Trie_hasKey(&node, "f"),);
}
