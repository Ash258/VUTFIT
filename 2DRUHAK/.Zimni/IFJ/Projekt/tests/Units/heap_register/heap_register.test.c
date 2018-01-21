#include <criterion/criterion.h>
#include "../../../src/heapregister/heap_register.external.c"
#include "../../../src/list/list.external.c"

#define hr_empty(i) do { \
    cr_assert_eq(List_size(heap + i), 0,); \
    cr_assert_null(List_first(heap + i),); \
    cr_assert_null(List_last(heap + i),); \
} while(0)

#define hr_not_empty(i) cr_assert_neq(List_size(heap + i), 0,)

#define hr_none() do { \
    for (UnsignedInt i = 0; i < G_HEAP_SIZE; ++i) { \
        hr_empty(i); \
    } \
} while(0)

Size    some;
Group   group;
Address address1, address2;

void setup(void) {
    some  = 1024;
    group = G_GLOBAL;
}

void teardown(void) { address2 = address1 = NULL; }

TestSuite(Heap_init, .init = setup, .fini = teardown);
TestSuite(Heap_Insert, .init = setup, .fini = teardown);
TestSuite(Heap_Free, .init = setup, .fini = teardown);
TestSuite(Heap_Sweep, .init = setup, .fini = teardown);
TestSuite(Heap_Destructor, .init = setup, .fini = teardown);

Test(Heap_Init, Internal) {
    cr_assert_eq(sizeof(heap) / sizeof(List), G_HEAP_SIZE,);

    hr_none();
}

Test(Heap_Insert, BasicAndInternal) {
    cr_assert_not_null(HeapRegister_allocate(group, some),);

    for (UnsignedInt i = 0; i < G_HEAP_SIZE; ++i) {
        if (i != group) hr_empty(i);
        else {
            hr_not_empty(i);
        }
    }
}

Test(Heap_Insert, TwoIntoSameGroupAndInternal) {
    cr_assert_not_null(address1 = HeapRegister_allocate(group, some),);
    cr_assert_not_null(address2 = HeapRegister_allocate(group, some),);
    cr_assert_neq(address1, address2,);

    for (UnsignedInt i = 0; i < G_HEAP_SIZE; ++i) {
        if (i != group) hr_empty(i);
        else {
            hr_not_empty(i);
            cr_assert_not_null(List_first(heap + i),);
        }
    }
}

Test(Heap_Free, BasicInternal) {
    cr_assert_not_null(address1 = HeapRegister_allocate(group, some),);
    HeapRegister_free(group, address1);

    hr_none();
}

Test(Heap_Free, TwoBasicFirstInternal) {
    cr_assert_not_null(address1 = HeapRegister_allocate(group, some),);
    cr_assert_not_null(address2 = HeapRegister_allocate(group, some),);

    HeapRegister_free(group, address1);

    for (UnsignedInt i = 0; i < G_HEAP_SIZE; ++i) {
        if (i != group) hr_empty(i);
        else {
            hr_not_empty(i);
            cr_assert_eq(List_first(heap + i), address2,);
            cr_assert_eq(List_last(heap + i), address2,);
        }
    }

    HeapRegister_free(group, address2);

    hr_none();
}

Test(Heap_Free, TwoBasicSecondInternal) {
    cr_assert_not_null(address1 = HeapRegister_allocate(group, some),);
    cr_assert_not_null(address2 = HeapRegister_allocate(group, some),);

    HeapRegister_free(group, address2);

    for (UnsignedInt i = 0; i < G_HEAP_SIZE; ++i) {
        if (i != group) hr_empty(i);
        else {
            hr_not_empty(i);
            cr_assert_eq(List_first(heap + i), address1,);
            cr_assert_eq(List_last(heap + i), address1,);
        }
    }

    HeapRegister_free(group, address1);

    hr_none();
}

Test(Heap_Free, TwoBasicSameInternal) {
    cr_assert_not_null(address1 = HeapRegister_allocate(group, some),);
    cr_assert_not_null(address2 = HeapRegister_allocate(group, some),);

    HeapRegister_free(group, address1);
    HeapRegister_free(group, address1);

    for (UnsignedInt i = 0; i < G_HEAP_SIZE; ++i) {
        if (i != group) hr_empty(i);
        else {
            hr_not_empty(i);
            cr_assert_eq(List_first(heap + i), address2,);
            cr_assert_eq(List_last(heap + i), address2,);
        }
    }

    HeapRegister_free(group, address2);

    hr_none();
}

Test(Heap_Sweep, Empty) {
    HeapRegister_sweep();
    hr_none();
}

Test(Heap_Sweep, OneGroupOneItem) {
    cr_assert_not_null(HeapRegister_allocate(group, some),);

    HeapRegister_sweep();

    hr_none();
}

Test(Heap_Sweep, OneGroupTwoItems) {
    cr_assert_not_null(HeapRegister_allocate(group, some),);
    cr_assert_not_null(HeapRegister_allocate(group, some),);

    HeapRegister_sweep();

    hr_none();
}

Test(Heap_Sweep, TwoGroupsOneItems) {
    cr_assert_not_null(HeapRegister_allocate(group, some),);
    cr_assert_not_null(HeapRegister_allocate(group + 1, some),);

    HeapRegister_sweep();

    hr_none();
}

Test(Heap_Sweep, TwoGroupsTwoItems) {
    cr_assert_not_null(HeapRegister_allocate(group, some),);
    cr_assert_not_null(HeapRegister_allocate(group, some),);
    cr_assert_not_null(HeapRegister_allocate(group + 1, some),);
    cr_assert_not_null(HeapRegister_allocate(group + 1, some),);

    HeapRegister_sweep();

    hr_none();
}

static int value = EXIT_FAILURE;

static void destructor(Address ignored) { value = EXIT_SUCCESS; }

Test(Heap_Destructor, Basic) {
    HeapRegister_setDestructor(group, &destructor);
    cr_assert_not_null(address1 = HeapRegister_allocate(group, some),);
    HeapRegister_free(group, address1);

    cr_assert_eq(value, EXIT_SUCCESS,);

    hr_none();
}

Test(Heap_Destructor, Sweep) {
    HeapRegister_setDestructor(group, &destructor);
    cr_assert_not_null(HeapRegister_allocate(group, some),);
    HeapRegister_sweep();

    cr_assert_eq(value, EXIT_SUCCESS,);

    hr_none();
}
