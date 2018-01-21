#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include <setjmp.h>

jmp_buf buf;

#undef DIE
#define DIE(signal) longjmp(buf, signal)

#include "mocks/utils.mock.c"
#include "../../../src/symtable/symtable.external.h"
#include "../../../src/list/list.external.h"

typedef struct TestData {
    VariableNode     var;
    VariableInfoType type;
}       TestData;

Test(Generator_VariableInfo, Creation) {
    GEN();
    int             size        = 4;
    TestData        data[4]     = {
            {.var = (VariableNode) {.name = "a", .type = DT_INTEGER}, .type = VIT_GLOBAL},
            {.var = (VariableNode) {.name = "b", .type = DT_STRING}, .type = VIT_STATIC},
            {.var = (VariableNode) {.name = "c", .type = DT_FLOAT}, .type = VIT_LOCAL},
            {.var = (VariableNode) {.name = "d", .type = DT_BOOL}, .type = VIT_AUXILIARY},
    };
    OperandVariable expected[4] = {
            {.scope = VS_GLOBAL, .dataType = DT_INTEGER,
                    .name = FORMAT_MARK GENERATOR_GLOBAL_PREFIX FORMAT_SEPARATOR "a" FORMAT_MARK},
            {.scope = VS_GLOBAL, .dataType = DT_STRING,
                    .name = FORMAT_MARK GENERATOR_STATIC_PREFIX FORMAT_SEPARATOR "b" FORMAT_MARK},
            {.scope = VS_LOCAL, .dataType = DT_FLOAT,
                    .name = FORMAT_MARK "c" FORMAT_SEPARATOR "&0000" FORMAT_MARK},
            {.scope = VS_TEMP, .dataType = DT_BOOL,
                    .name = FORMAT_MARK "d" FORMAT_SEPARATOR "&0000" FORMAT_MARK},
    };

    for (int i = 0; i < size; ++i) {
        VariableInfoRef var   = VariableInfo_create(gen, &data[i].var, data[i].type);
        ListRef         check = data[i].type == VIT_STATIC || data[i].type == VIT_GLOBAL ? init : list;
        cr_assert_inst(next(check), InstMock_first(I_DEFVAR, Operand_variable(expected[i])));
    }
}

Test(Generator_VariableInfo, CreationInNestedScope) {
    GEN();
    DataRef          simulateScope = &(Int) {0};
    DataType         type          = DT_INTEGER;
    VariableInfoType varType       = VIT_LOCAL;
    VariableScope    varScope      = VS_LOCAL;

    VariableNodeRef node = &(VariableNode) {.name = "cosi", .type = type};

    VariableInfoRef first = VariableInfo_create(gen, node, varType);
    VariableInfo_register(gen, node, first);
    OperandVariable exp1 = {.name = "$cosi-&0000$", .scope = varScope, .dataType = type};
    cr_assert_oper(Operand_variable(first->variable), Operand_variable(exp1));
    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, Operand_variable(first->variable)));

    List_push(&gen->scopes, ScopeMock()); // simulate change of stack

    VariableInfoRef second = VariableInfo_create(gen, node, varType);
    OperandVariable exp2   = {.name = "$cosi-&0001$", .scope = varScope, .dataType = type};
    cr_assert_oper(Operand_variable(second->variable), Operand_variable(exp2));
    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, Operand_variable(second->variable)));
}

Test(Generator_VariableInfo, CreationInNestedScopeWithOneSkipped) {
    GEN();
    DataRef          simulateScope = &(Int) {0};
    DataType         type          = DT_INTEGER;
    VariableInfoType varType       = VIT_LOCAL;
    VariableScope    varScope      = VS_LOCAL;

    VariableNodeRef node = &(VariableNode) {.name = "cosi", .type = type};

    VariableInfoRef first = VariableInfo_create(gen, node, varType);
    VariableInfo_register(gen, node, first);
    OperandVariable exp1 = {.name = "$cosi-&0000$", .scope = varScope, .dataType = type};
    cr_assert_oper(Operand_variable(first->variable), Operand_variable(exp1));
    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, Operand_variable(first->variable)));

    List_push(&gen->scopes, ScopeMock()); // simulate change of stack
    List_push(&gen->scopes, ScopeMock()); // simulate second change

    VariableInfoRef second = VariableInfo_create(gen, node, varType);
    OperandVariable exp2   = {.name = "$cosi-&0002$", .scope = varScope, .dataType = type};
    cr_assert_oper(Operand_variable(second->variable), Operand_variable(exp2));
    cr_assert_inst(next(list), InstMock_first(I_DEFVAR, Operand_variable(second->variable)));
}

Test(Generator_VariableInfo, CreationTwoInSameScope) {
    GEN();
    DataRef          simulateScope = &(Int) {0};
    DataType         type          = DT_INTEGER;
    VariableInfoType varType       = VIT_LOCAL;
    VariableScope    varScope      = VS_LOCAL;

    int value = setjmp(buf);
    if (value != 0) {
        cr_assert_eq(value, ERR_OTHER,);
        return;
    }

    VariableNodeRef node = &(VariableNode) {.name = "cosi", .type = type};

    VariableInfo_register(gen, node, VariableInfo_create(gen, node, varType));

    VariableInfo_create(gen, node, varType); // error

    cr_assert_fail();
}

Test(Generator_VariableInfo, UseUnknown) {
    GEN();
    DataRef          simulateScope = &(Int) {0};
    DataType         type          = DT_INTEGER;
    VariableInfoType varType       = VIT_LOCAL;
    VariableScope    varScope      = VS_LOCAL;

    int value = setjmp(buf);
    if (value != 0) {
        cr_assert_eq(value, ERR_OTHER,);
        return;
    }

    VariableNodeRef node = &(VariableNode) {.name = "cosi", .type = type};

    VariableInfo_use(gen, node, false); // error

    cr_assert_fail();
}

Test(Generator_VariableInfo, UseWithValue) {
    GEN();
    String           var      = "cosi";
    DataType         type     = DT_INTEGER;
    VariableInfoType varType  = VIT_LOCAL;
    VariableScope    varScope = VS_LOCAL;

    VariableNodeRef node = &(VariableNode) {.name = var, .type = type};

    VariableInfoRef a = VariableInfo_create(gen, node, varType);
    VariableInfo_register(gen, node, a);
    next(list); // ignored defvar

    OperandVariable exp = {.name = "$cosi-&0000$", .scope = varScope, .dataType = type};
    VariableInfoRef act = VariableInfo_use(gen, node);
    cr_assert_oper(Operand_variable(act->variable), Operand_variable(exp));

    cr_assert(List_isEmpty(list),);
}

Test(Generator_VariableInfo, UseWithImplicit) {
    GEN();
    String           var      = "cosi";
    DataType         type     = DT_INTEGER;
    VariableInfoType varType  = VIT_LOCAL;
    VariableScope    varScope = VS_LOCAL;

    VariableNodeRef node = &(VariableNode) {.name = var, .type = type};

    VariableInfoRef a = VariableInfo_create(gen, node, varType);
    VariableInfo_register(gen, node, a);
    next(list); // ignored defvar

    OperandVariable exp = {.name = "$cosi-&0000$", .scope = varScope, .dataType = type};
    VariableInfoRef act = VariableInfo_use(gen, node);
    cr_assert_oper(Operand_variable(act->variable), Operand_variable(exp));
    cr_assert_inst(next(list), Instruction_move(exp, Symbol_immediate(Generator_implicitValue(type))));

    cr_assert(List_isEmpty(list),);
}

Test(Generator_VariableInfo, UseInNestedScope) {
    GEN();
    String           var      = "cosi";
    DataType         type     = DT_INTEGER;
    VariableInfoType varType  = VIT_LOCAL;
    VariableScope    varScope = VS_LOCAL;

    VariableNodeRef node = &(VariableNode) {.name = var, .type = type};

    VariableInfo_register(gen, node, VariableInfo_create(gen, node, varType));
    next(list); // ignored defvar

    List_push(&gen->scopes, ScopeMock_withVar(var, type)); // simulate change of stack

    VariableInfo_register(gen, node, VariableInfo_create(gen, node, varType));
    next(list); // ignored defvar

    OperandVariable exp   = {.name = "$cosi-&0001$", .scope = varScope, .dataType = type};
    VariableInfoRef first = VariableInfo_use(gen, node);
    cr_assert_oper(Operand_variable(first->variable), Operand_variable(exp));

    cr_assert(List_isEmpty(list),);
}

Test(Generator_VariableInfo, UseAfterNestedScope) {
    GEN();
    String           var      = "cosi";
    DataType         type     = DT_INTEGER;
    VariableInfoType varType  = VIT_LOCAL;
    VariableScope    varScope = VS_LOCAL;

    VariableNodeRef node = &(VariableNode) {.name = var, .type = type};

    VariableInfo_register(gen, node, VariableInfo_create(gen, node, varType));
    next(list); // ignored defvar

    List_push(&gen->scopes, ScopeMock_withVar(var, type)); // simulate change of stack

    VariableInfo_register(gen, node, VariableInfo_create(gen, node, varType));
    next(list); // ignored defvar

    VariableInfo_clear(gen);
    List_pop(&gen->scopes);

    OperandVariable exp   = {.name = "$cosi-&0000$", .scope = varScope, .dataType = type};
    VariableInfoRef first = VariableInfo_use(gen, node);
    cr_assert_oper(Operand_variable(first->variable), Operand_variable(exp));

    cr_assert(List_isEmpty(list),);
}

Test(Generator_VariableInfo, Temporary) {
    GEN();

    OperandVariable var1      = VariableInfo_temporary(gen, DT_INTEGER)->variable;
    OperandVariable expected1 = (OperandVariable) {.dataType = DT_INTEGER, .name = "&0000", .scope = VS_TEMP};
    cr_assert_oper(Operand_variable(var1), Operand_variable(expected1));
    next(list); // ignore defvar

    OperandVariable expected2 = (OperandVariable) {.dataType = DT_INTEGER, .name = "&0001", .scope = VS_TEMP};
    OperandVariable var2      = VariableInfo_temporary(gen, DT_INTEGER)->variable;
    cr_assert_oper(Operand_variable(var2), Operand_variable(expected2));
    next(list); // ignore defvar

    cr_assert(List_isEmpty(list),);
}
