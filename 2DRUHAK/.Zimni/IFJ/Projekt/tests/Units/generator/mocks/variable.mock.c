

#include "../../../../src/c_alias.h"
#include "../../../../src/symtable/symtable.external.h"
#include "../../../../src/generator/generator.operand.h"
#include "../../../../src/generator/generator.variable_info.h"
#include "../../../../src/generator/generator.internal.h"

void VarMock_ensure(GeneratorRef generator, DataType type, String name, Bool value) {
    VariableNodeRef node = &(VariableNode) {.type = type, .name = name};
    VariableInfoRef var  = VariableInfo_create(generator, node, VIT_LOCAL);
    VariableInfo_register(generator, node, var);
    List_pop(generator->inst);
}
