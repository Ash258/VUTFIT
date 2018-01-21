// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.instruction_set.h
// Assignment:      125, I
// Date:            17/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_GENERATOR_INSTRUCTION_SET_H
#define IFJ2017_GENERATOR_INSTRUCTION_SET_H

#include "generator.operand.h"

typedef enum {
    I_MOVE,
    I_CREATEFRAME,
    I_PUSHFRAME,
    I_POPFRAME,
    I_DEFVAR,
    I_CALL,
    I_RETURN,

    I_PUSHS,
    I_POPS,
    I_CLEARS,

    I_ADD,
    I_SUB,
    I_MUL,
    I_DIV,
    I_ADDS,
    I_SUBS,
    I_MULS,
    I_DIVS,

    I_LT,
    I_GT,
    I_EQ,
    I_LTS,
    I_GTS,
    I_EQS,

    I_AND,
    I_OR,
    I_ANDS,
    I_NOT,
    I_ORS,
    I_NOTS,

    I_INT2FLOAT,
    I_FLOAT2INT,
    I_FLOAT2R2EINT,
    I_FLOAT2R2OINT,
    I_INT2CHAR,
    I_STRI2INT,
    I_INT2FLOATS,
    I_FLOAT2INTS,
    I_FLOAT2R2EINTS,
    I_FLOAT2R2OINTS,
    I_INT2CHARS,
    I_STRI2INTS,

    I_READ,
    I_WRITE,

    I_CONCAT,
    I_STRLEN,
    I_GETCHAR,
    I_SETCHAR,

    I_TYPE,

    I_LABEL,
    I_JUMP,
    I_JUMPIFEQ,
    I_JUMPIFNEQ,
    I_JUMPIFEQS,
    I_JUMPIFNEQS,

    I_BREAK,
    I_DPRINT,

    I_UNDEFINED,
} InstructionSet;

typedef struct TAInstruction {
    InstructionSet instruction;
    Operand        dest;
    Operand        first;
    Operand        second;
} Instruction, * InstructionRef;

InstructionRef Instruction_create(InstructionSet instruction, Operand dest, Operand first, Operand second);

InstructionRef Instruction_destFirst(InstructionSet instruction, Operand dest, Operand first);

InstructionRef Instruction_first(InstructionSet instruction, Operand first);

InstructionRef Instruction_dest(InstructionSet instruction, Operand dest);

InstructionRef Instruction_empty(InstructionSet instruction);

InstructionRef Instruction_move(OperandVariable dest, OperandSymbol first);

InstructionRef Instruction_createframe();

InstructionRef Instruction_pushframe();

InstructionRef Instruction_popframe();

InstructionRef Instruction_defvar(OperandVariable variable);

InstructionRef Instruction_call(String name);

InstructionRef Instruction_return();

InstructionRef Instruction_pushs(OperandSymbol symbol);

InstructionRef Instruction_pops(OperandVariable variable);

InstructionRef Instruction_label(String name);

InstructionRef Instruction_jump(String label);

InstructionRef Instruction_jumpifeq(String label, OperandSymbol first, OperandSymbol second);

InstructionRef Instruction_jumpifneq(String label, OperandSymbol first, OperandSymbol second);

void Instruction_print(InstructionRef instruction, FileRef file);

#endif //IFJ2017_GENERATOR_INSTRUCTION_SET_H

/** End of generator.instruction_set.h */
