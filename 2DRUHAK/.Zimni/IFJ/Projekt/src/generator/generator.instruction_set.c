// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.instruction_set.c
// Assignment:      125, I
// Date:            17/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.instruction_set.h"

//region Generic

InstructionRef Instruction_create(InstructionSet instruction, Operand dest, Operand first, Operand second) {
    InstructionRef instr = HeapRegister_allocate(G_INSTRUCTIONS, sizeof(Instruction));

    instr->instruction = instruction;
    instr->dest        = dest;
    instr->first       = first;
    instr->second      = second;

    return instr;
}

InstructionRef Instruction_destFirst(InstructionSet is, Operand d, Operand o1) {
    return Instruction_create(is, d, o1, EMPTY_OPERAND);
}

InstructionRef Instruction_first(InstructionSet is, Operand o1) {
    return Instruction_create(is, EMPTY_OPERAND, o1, EMPTY_OPERAND);
}

InstructionRef Instruction_dest(InstructionSet is, Operand d) {
    return Instruction_create(is, d, EMPTY_OPERAND, EMPTY_OPERAND);
}

InstructionRef Instruction_empty(InstructionSet is) {
    return Instruction_create(is, EMPTY_OPERAND, EMPTY_OPERAND, EMPTY_OPERAND);
}

//endregion Generic

InstructionRef Instruction_move(OperandVariable dest, OperandSymbol first) {
    return Instruction_destFirst(I_MOVE, Operand_variable(dest), Operand_symbol(first));
}

InstructionRef Instruction_createframe() {
    return Instruction_empty(I_CREATEFRAME);
}

InstructionRef Instruction_pushframe() {
    return Instruction_empty(I_PUSHFRAME);
}

InstructionRef Instruction_popframe() {
    return Instruction_empty(I_POPFRAME);
}

InstructionRef Instruction_defvar(OperandVariable variable) {
    return Instruction_first(I_DEFVAR, Operand_variable(variable));
}

InstructionRef Instruction_call(String name) {
    return Instruction_first(I_CALL, Operand_label(name));
}

InstructionRef Instruction_return() {
    return Instruction_empty(I_RETURN);
}

InstructionRef Instruction_pushs(OperandSymbol symbol) {
    return Instruction_first(I_PUSHS, Operand_symbol(symbol));
}

InstructionRef Instruction_pops(OperandVariable variable) {
    return Instruction_dest(I_POPS, Operand_variable(variable));
}

InstructionRef Instruction_label(String name) {
    return Instruction_first(I_LABEL, Operand_label(name));
}

InstructionRef Instruction_jump(String label) {
    return Instruction_dest(I_JUMP, Operand_label(label));
}

InstructionRef Instruction_jumpifeq(String label, OperandSymbol first, OperandSymbol second) {
    return Instruction_create(I_JUMPIFEQ, Operand_label(label), Operand_symbol(first), Operand_symbol(second));
}

InstructionRef Instruction_jumpifneq(String label, OperandSymbol first, OperandSymbol second) {
    return Instruction_create(I_JUMPIFNEQ, Operand_label(label), Operand_symbol(first), Operand_symbol(second));
}

/** End of generator.instruction_set.c */
