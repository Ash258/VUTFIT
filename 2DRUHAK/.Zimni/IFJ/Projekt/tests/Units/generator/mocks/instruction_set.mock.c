#include "../../../../src/heapregister/heap_register.external.h"
#include "../../../../src/generator/generator.instruction_set.h"

InstructionRef InstMock(InstructionSet is, Operand d, Operand o1, Operand o2) {
    InstructionRef inst = HeapRegister_allocate(G_GLOBAL, sizeof(Instruction));
    inst->instruction = is;
    inst->dest        = d;
    inst->first       = o1;
    inst->second      = o2;
    return inst;
}

InstructionRef InstMock_empty(InstructionSet is) {
    return InstMock(is, EMPTY_OPERAND, EMPTY_OPERAND, EMPTY_OPERAND);
}

InstructionRef InstMock_dest(InstructionSet is, Operand d) {
    return InstMock(is, d, EMPTY_OPERAND, EMPTY_OPERAND);
}

InstructionRef InstMock_first(InstructionSet is, Operand o1) {
    return InstMock(is, EMPTY_OPERAND, o1, EMPTY_OPERAND);
}

InstructionRef InstMock_destFirst(InstructionSet is, Operand d, Operand o1) {
    return InstMock(is, d, o1, EMPTY_OPERAND);
}
