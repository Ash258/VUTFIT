#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/assert.h>

#include "../../../../src/generator/generator.binary.c"
#include "../../../../src/generator/generator.definition.c"
#include "../../../../src/generator/generator.expression.c"
#include "../../../../src/generator/generator.function_call.c"
#include "../../../../src/generator/generator.if.c"
#include "../../../../src/generator/generator.instruction_set.c"
#include "../../../../src/generator/generator.internal.c"
#include "../../../../src/generator/generator.loop.c"
#include "../../../../src/generator/generator.operand.c"
#include "../../../../src/generator/generator.optimizations.c"
#include "../../../../src/generator/generator.external.c"
#include "../../../../src/generator/generator.scope.c"
#include "../../../../src/generator/generator.statement.c"
#include "../../../../src/generator/generator.unary.c"
#include "../../../../src/generator/generator.variable_info.c"

#include "../../../../src/helpers.c"
#include "../../../../src/list/list.external.c"
#include "../../../../src/heapregister/heap_register.external.c"
#include "../../../../src/trie/trie.external.c"
#include "../../../../src/format/format.c"
#include "../../../../src/binarytree/binary_tree.external.c"
#include "../../../../src/binarytree/tree.binary_tree.c"
#include "../../../../src/stringbuilder/string_builder.external.c"
#include "../../../../src/symtable/symtable.external.c"

#include "../../helpers.c"
#include "ast.mock.c"
#include "instruction_set.mock.c"
#include "operator.mock.c"
#include "variable.mock.c"
#include "symtable.mock.c"

#define GEN() \
    ListRef  list = &(List) {0}; \
    GeneratorRef gen = &(Generator){.inst = list}; \
    ListRef  init = &gen->instructionLists; \
    List_init(list, NULL); \
    List_init(init, NULL);

void setup() {
    HeapRegister_setDestructor(G_GLOBAL, NULL);
}

void teardown() {
    HeapRegister_sweep();
}

void cr_assert_oper(Operand Actual, Operand Expected) {
    cr_assert_eq(Actual.type, Expected.type,);
    switch (Expected.type) {
        case O_NULL: return;
        case O_VARIABLE: {
            cr_assert_int_eq(Actual.variable.dataType, Expected.variable.dataType);
            cr_assert_string_eq(Actual.variable.name, Expected.variable.name);
            break;
        }
        case O_IMMEDIATE: {
            cr_assert_int_eq(Actual.immediate.dataType, Expected.immediate.dataType);
            switch (Expected.immediate.dataType) {
                case DT_STRING: {
                    cr_assert_string_eq(Actual.immediate.value, Expected.immediate.value);
                    break;
                }
                case DT_INTEGER: {
                    cr_assert_int_eq(Int_from(Actual.immediate.value), Int_from(Expected.immediate.value));
                    break;
                }
                case DT_FLOAT: {
                    cr_assert_double_eq(Real_from(Actual.immediate.value), Real_from(Expected.immediate.value));
                    break;
                }
                case DT_BOOL: {
                    cr_assert_int_eq(Bool_from(Actual.immediate.value), Bool_from(Expected.immediate.value));
                    break;
                }
            }
            break;
        }
        case O_LABEL: cr_assert_string_eq(Actual.label, Expected.label);
            break;
        case O_DATATYPE: cr_assert_int_eq(Actual.dataType, Expected.dataType);
            break;
    }
}

void cr_assert_inst(InstructionRef Actual, InstructionRef Expected) {
    cr_assert_int_eq(Actual->instruction, Expected->instruction);
    cr_assert_oper(Actual->dest, Expected->dest);
    cr_assert_oper(Actual->first, Expected->first);
    cr_assert_oper(Actual->second, Expected->second);
}

InstructionRef next(ListRef list) {
    cr_assert_not(List_isEmpty(list),);
    return ((InstructionRef) List_shift(list));
}


