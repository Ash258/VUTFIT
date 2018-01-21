#include <criterion/criterion.h>
#include "../../../src/binarytree/binary_tree.external.c"
#include "../../../src/binarytree/tree.binary_tree.c"
#include "../../../src/list/list.external.c"
#include "../../../src/symtable/symtable.external.c"
#include "../../../src/helpers.c"
#include "../../../src/heapregister/heap_register.external.c"
#include "../../../src/symtable/symtable.external.h"

SymbolTableRef table;
ListRef        list;

void setup(void) {
    table = Table_create(NULL);
}

void setupA(void) {
    SymbolTableRef tableA = Table_create(NULL);
    table = Table_create(tableA);
}

void tearDown(void) {
    //Table_dispose(table);
}

TestSuite(Sym_Init, .init = setup, .fini = tearDown);
TestSuite(Sym_Init2, .init = setupA, .fini = tearDown);
TestSuite(Sym_Insert, .init = setup, .fini = tearDown);
TestSuite(Sym_Search_Has, .init = setup, .fini = tearDown);
TestSuite(Sym_Search_R, .init = setupA, .fini = tearDown);
TestSuite(Sym_Dispose, .init = setupA, .fini = tearDown);

Test(Sym_Init, Basic) {
    cr_assert_null(table->parent,);
    cr_assert_null(table->values.root,);
    cr_assert_not_null(table->values.destructor,);
    cr_assert_not_null(table->values.comparator,);
}

Test(Sym_Init2, Parent) {
    cr_assert_not_null(table->parent,);
    cr_assert_null(table->parent->parent,);
}

Test(Sym_Insert, Function) {
    String   name       = "Cosi";
    DataType returnType = DT_INTEGER;
    bool     defined    = false;
    bool     declared   = false;
    Table_insertFunction(table, name, returnType, list, defined, declared);

    TreeNodeRef     func     = table->values.root;
    cr_assert_eq(func->key, name,);
    FunctionNodeRef funcData = ((TableNodeRef) func->data)->ref;
    cr_assert_eq(funcData->name, name,);
    cr_assert_eq(funcData->type, returnType,);
    cr_assert_eq(funcData->parameters, NULL,);
    cr_assert_eq(funcData->defined, false,);
    cr_assert_eq(funcData->declared, false,);
}

Test(Sym_Insert, Variable) {
    String   name = "Cosi";
    DataType type = DT_FLOAT;
    Table_insertVariable(table, name, type);

    TreeNodeRef     var     = table->values.root;
    cr_assert_eq(var->key, name,);
    VariableNodeRef varData = ((TableNodeRef) var->data)->ref;
    cr_assert_eq(varData->name, name,);
    cr_assert_eq(varData->type, type,);
}

Test(Sym_Search_Has, Function) {
    String name = "Cosi";
    Table_insertFunction(table, name, DT_INTEGER, list, false, false);

    cr_assert_not_null(Table_searchFunction(table, name),);
    cr_assert_null(Table_searchFunction(table, "NotThere"),);

    cr_assert_eq(Table_hasFunction(table, name), true,);
    cr_assert_eq(Table_hasFunction(table, "NotThere"), false,);
}

Test(Sym_Search_Has, Variable) {
    String   name = "Cosi";
    DataType type = DT_FLOAT;
    Table_insertVariable(table, name, type);

    cr_assert_not_null(Table_searchVariable(table, name, false),);
    cr_assert_null(Table_searchVariable(table, "Foo", false),);

    cr_assert_eq(Table_hasVariable(table, name, false), true,);
    cr_assert_eq(Table_hasVariable(table, "foo", false), false,);
}

Test(Sym_Search_R, VariableRipple) {
    String   name = "Cosi", name2 = "Cosi2";
    DataType type = DT_FLOAT;
    Table_insertVariable(table, name, type);
    Table_insertVariable(table->parent, name2, type);

    cr_assert_null(Table_searchVariable(table, name2, false),);
    cr_assert_not_null(Table_searchVariable(table, name2, true),);

    cr_assert_eq(Table_hasVariable(table, name2, false), false,);
    cr_assert_eq(Table_hasVariable(table, name2, true), true,);

    cr_assert_eq(Table_hasVariable(table, "NOTTHERE", true), false,);
    cr_assert_eq(Table_hasVariable(table, "NOTTHERE", false), false,);
}

Test(Sym_Dispose, Basic) {
    // TODO: Implement
}
