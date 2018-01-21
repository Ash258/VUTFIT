#include <criterion/criterion.h>
#include "../../../src/list/list.external.c"
#include "../../../src/heapregister/heap_register.external.c"

List emptyList;

void setupList(void) {
    List_init(&emptyList, NULL);
}

void tearDownList(void) {
    List_dispose(&emptyList, false);
}

TestSuite(List, .init = setupList, .fini = tearDownList);

Test(List, Init) {
    cr_assert_null(List_first(&emptyList),);
    cr_assert_null(List_last(&emptyList),);
    cr_assert_eq(List_size(&emptyList), 0,);
    cr_assert(List_isEmpty(&emptyList),);
}

Test(List, Push) {
    int firstValue = 5, secondValue = 6;

    List_push(&emptyList, &firstValue);
    cr_assert_eq(List_size(&emptyList), 1,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);
    cr_assert_eq(List_last(&emptyList), &firstValue,);

    List_push(&emptyList, &secondValue);
    cr_assert_eq(List_size(&emptyList), 2,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);
    cr_assert_eq(List_last(&emptyList), &secondValue,);
}

Test(List, Unshift) {
    int firstValue = 5, secondValue = 6;

    List_unshift(&emptyList, &firstValue);
    cr_assert_eq(List_size(&emptyList), 1,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);
    cr_assert_eq(List_last(&emptyList), &firstValue,);

    List_unshift(&emptyList, &secondValue);
    cr_assert_eq(List_size(&emptyList), 2,);
    cr_assert_eq(List_first(&emptyList), &secondValue,);
    cr_assert_eq(List_last(&emptyList), &firstValue,);
}

Test(List, Pop) {
    int firstValue = 5, secondValue = 6, thirdValue = 7;

    List_push(&emptyList, &firstValue);
    List_push(&emptyList, &secondValue);
    List_push(&emptyList, &thirdValue);

    cr_assert_eq(List_pop(&emptyList), &thirdValue,);
    cr_assert_eq(List_last(&emptyList), &secondValue,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);

    cr_assert_eq(List_pop(&emptyList), &secondValue,);
    cr_assert_eq(List_last(&emptyList), &firstValue,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);

    cr_assert_eq(List_pop(&emptyList), &firstValue,);
    cr_assert_null(List_last(&emptyList),);
    cr_assert_null(List_first(&emptyList),);
}

Test(List, Shift) {
    int firstValue = 5, secondValue = 6, thirdValue = 7;

    List_push(&emptyList, &firstValue);
    List_push(&emptyList, &secondValue);
    List_push(&emptyList, &thirdValue);

    cr_assert_eq(List_shift(&emptyList), &firstValue,);
    cr_assert_eq(List_last(&emptyList), &thirdValue,);
    cr_assert_eq(List_first(&emptyList), &secondValue,);

    cr_assert_eq(List_shift(&emptyList), &secondValue,);
    cr_assert_eq(List_last(&emptyList), &thirdValue,);
    cr_assert_eq(List_first(&emptyList), &thirdValue,);

    cr_assert_eq(List_shift(&emptyList), &thirdValue,);
    cr_assert_null(List_last(&emptyList),);
    cr_assert_null(List_first(&emptyList),);
}

Test(List, Empty) {
    cr_assert(List_isEmpty(&emptyList),);

    List_push(&emptyList, NULL);
    cr_assert_not(List_isEmpty(&emptyList),);

    List_pop(&emptyList);
    cr_assert(List_isEmpty(&emptyList),);
}

Test(List, Has) {
    int firstValue = 5, secondValue = 6;

    cr_assert_not(List_has(&emptyList, &secondValue),);

    List_push(&emptyList, &firstValue);
    cr_assert_not(List_has(&emptyList, &secondValue),);

    List_push(&emptyList, &secondValue);
    cr_assert(List_has(&emptyList, &secondValue),);
}

Bool comparator(void *value, void *searched) {
    return (int*) value == (int*) searched;
}

Test(List, Contains) {
    int firstValue = 5, secondValue = 6;

    cr_assert_not(List_contains(&emptyList, &comparator, &secondValue),);

    List_push(&emptyList, &firstValue);
    cr_assert_not(List_contains(&emptyList, &comparator, &secondValue),);

    List_push(&emptyList, &secondValue);
    cr_assert(List_contains(&emptyList, &comparator, &secondValue),);
}

Test(List, Remove) {
    int firstValue, secondValue;
    List_push(&emptyList, &firstValue);
    List_push(&emptyList, &firstValue);
    List_push(&emptyList, &firstValue);
    List_push(&emptyList, &secondValue);

    //remove unique entry
    List_remove(&emptyList, &secondValue);
    cr_assert_eq(List_size(&emptyList), 3,);
    cr_assert_eq(List_last(&emptyList), &firstValue,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);

    //remove non-existing entry
    List_remove(&emptyList, &secondValue);
    cr_assert_eq(List_size(&emptyList), 3,);
    cr_assert_eq(List_last(&emptyList), &firstValue,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);

    //remove duplicated entry
    List_remove(&emptyList, &firstValue);
    cr_assert_eq(List_size(&emptyList), 2,);
    cr_assert_eq(List_last(&emptyList), &firstValue,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);
}

Test(List, RemoveAll) {
    int firstValue, secondValue, thirdValue;
    List_push(&emptyList, &firstValue);
    List_push(&emptyList, &firstValue);
    List_push(&emptyList, &firstValue);
    List_push(&emptyList, &secondValue);
    List_push(&emptyList, &thirdValue);

    //remove unique entry
    List_removeAll(&emptyList, &thirdValue);
    cr_assert_eq(List_size(&emptyList), 4,);
    cr_assert_eq(List_last(&emptyList), &secondValue,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);

    //remove non-existing entry
    List_removeAll(&emptyList, &thirdValue);
    cr_assert_eq(List_size(&emptyList), 4,);
    cr_assert_eq(List_last(&emptyList), &secondValue,);
    cr_assert_eq(List_first(&emptyList), &firstValue,);

    //remove duplicated entries
    List_removeAll(&emptyList, &firstValue);
    cr_assert_eq(List_size(&emptyList), 1,);
    cr_assert_eq(List_last(&emptyList), &secondValue,);
    cr_assert_eq(List_first(&emptyList), &secondValue,);
}
