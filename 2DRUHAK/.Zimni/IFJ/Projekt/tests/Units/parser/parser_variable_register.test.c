#include "../helpers.c"
#include "../../../src/parser/parser.variable_register.c"
#include "../../../src/symtable/symtable.external.h"
#include "../../../src/helpers.c"
#include "../../../src/ast/ast.external.h"
#include "../../../src/symtable/symtable.external.c"
#include "../../../src/trie/trie.external.c"
#include "../../../src/stringbuilder/string_builder.external.c"
#include "../../../src/list/list.external.c"
#include "../../../src/heapregister/heap_register.external.c"
#include "../../../src/binarytree/binary_tree.external.c"
#include "../../../src/binarytree/tree.binary_tree.c"
#include "../../../src/parser/parser.variable_register.h"

void teardown(void) {
    List_dispose(usedVarsStack, false);
}

TestSuite(Parser_Var_Register, .fini=teardown);

static VariableNodeRef createVariable(String name, DataType type) {
    VariableNodeRef ref = malloc(sizeof(VariableNode));

    ref->type = type;
    ref->name = name;

    return ref;
}

static ScopeRef createScope() {
    ScopeRef ref = malloc(sizeof(Scope));

    ref->symbolTable   = Table_create(NULL);
    ref->inheritedVars = List_create(NULL);
    ref->carryVars     = List_create(NULL);
    ref->staticVars    = List_create(NULL);

    return ref;
}

void cr_list_contains(ListRef list, int number, ...) {
    va_list vaList;
    va_start(vaList, number);

    for (int i = 0; i < number; ++i) {
        VariableNodeRef ref = va_arg(vaList, VariableNodeRef);
        cr_assert_eq((List_shift(list)), ref,);
    }

    va_end(vaList);
}

Test(Parser_Var_Register, Complet) {
    ScopeRef root  = createScope();
    ScopeRef outer = createScope();
    ScopeRef inner = createScope();

    registerScope();
    registerScope();

    //outer variables
    VariableNodeRef a = createVariable("a", DT_INTEGER);
    VariableNodeRef b = createVariable("b", DT_INTEGER);
    VariableNodeRef c = createVariable("c", DT_INTEGER);
    registerVarExp(a);
    registerVarDef(b, false);
    registerVarDef(c, true);

    registerScope();
    //inner variables
    VariableNodeRef v = createVariable("v", DT_INTEGER);
    VariableNodeRef s = createVariable("s", DT_INTEGER);
    VariableNodeRef p = createVariable("p", DT_INTEGER);
    VariableNodeRef o = createVariable("o", DT_INTEGER);
    registerVarExp(v);
    registerVarAssign(s);
    registerVarDef(p, false);
    registerVarDef(o, true);

    pickScopeVars(inner);
    cr_list_contains(inner->inheritedVars, 2, v, s);
    cr_assert(List_isEmpty(inner->inheritedVars),);
    cr_assert(List_isEmpty(inner->carryVars),);
    cr_list_contains(inner->staticVars, 1, o);
    cr_assert(List_isEmpty(inner->staticVars),);


    //outer variables
    VariableNodeRef d = createVariable("d", DT_INTEGER);
    registerVarAssign(d);
    pickScopeVars(outer);

    cr_list_contains(outer->inheritedVars, 2, a, d);
    cr_assert(List_isEmpty(outer->inheritedVars),);
    cr_list_contains(outer->carryVars, 2, v, s);
    cr_assert(List_isEmpty(outer->carryVars),);
    cr_list_contains(outer->staticVars, 1, c);
    cr_assert(List_isEmpty(outer->staticVars),);

    pickScopeVars(root);
    cr_assert(List_isEmpty(root->inheritedVars),);
    cr_list_contains(root->carryVars, 4, v, s, a, d);
    cr_assert(List_isEmpty(root->staticVars),);
}
