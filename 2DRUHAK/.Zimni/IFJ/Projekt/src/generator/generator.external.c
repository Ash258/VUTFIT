// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.external.c
// Assignment:      125, I
// Date:            21/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.instruction_set.h"
#include "generator.structures.h"
#include "generator.internal.h"

static String MAIN = "main";

static GeneratorRef Generator_create() {
    GeneratorRef generator = HeapRegister_allocate(G_GLOBAL, sizeof(Generator));

    generator->inst = generator->instructionLists + IL_CODE;
    List_init(generator->instructionLists + IL_INIT, NULL);
    List_init(generator->instructionLists + IL_CODE, NULL);

    List_init(&generator->scopes, NULL);
    Trie_init(&generator->variables);

    return generator;
}

static ListRef Generator_destruct(GeneratorRef generator) {
    ListRef res = copyInstance(sizeof(List), generator->inst);

    List_dispose(generator->instructionLists + IL_INIT, false);

    List_dispose(&generator->scopes, NULL);
    Trie_dispose(&generator->variables, NULL);
    HeapRegister_free(G_GLOBAL, generator);
    return res;
}

static void printVariable(OperandVariable var) {
    switch (var.scope) {
        case VS_GLOBAL:printf("GF@%s", var.name);
            break;
        case VS_LOCAL:printf("LF@%s", var.name);
            break;
        case VS_TEMP:printf("TF@%s", var.name);
            break;
        default:DIE(ERR_OTHER);
    }
}

static void printImmediate(OperandImmediate imm) {
    switch (imm.dataType) {
        case DT_STRING: {
            printf("string@");
            String value = imm.value;
            for (; *value != '\0'; value++) {
                if ((0 <= *value && *value <= 32) || *value == 35 || *value == 92) { printf("\\%03d", *value); }
                else { printf("%c", *value); }
            }
            break;
        }
        case DT_INTEGER:printf("int@%d", Int_from(imm.value));
            break;
        case DT_FLOAT:printf("float@%g", Real_from(imm.value));
            break;
        case DT_BOOL:printf("bool@%s", Bool_from(imm.value) ? "true" : "false");
            break;
        default:DIE(ERR_OTHER);
    }
}

static void printLabel(String label) {
    printf("%s", label);
}

static void printDataType(DataType dataType) {
    switch (dataType) {
        case DT_STRING:printf("string");
            break;
        case DT_INTEGER:printf("int");
            break;
        case DT_FLOAT:printf("float");
            break;
        case DT_BOOL:printf("bool");
            break;
        default:DIE(ERR_OTHER);
    }
}

static void printOperand(Operand operand) {
    IF_TRUE_RETURN_VOID(operand.type == O_NULL)
    switch (operand.type) {
        case O_IMMEDIATE:printImmediate(operand.immediate);
            break;
        case O_VARIABLE:printVariable(operand.variable);
            break;
        case O_LABEL:printLabel(operand.label);
            break;
        case O_DATATYPE:printDataType(operand.dataType);
            break;
        default:DIE(ERR_OTHER);
    }
}

static void printInstructions(InstructionSet instruction) {
    switch (instruction) {
        case I_MOVE: printf("MOVE");
            break;
        case I_CREATEFRAME: printf("CREATEFRAME");
            break;
        case I_PUSHFRAME: printf("PUSHFRAME");
            break;
        case I_POPFRAME: printf("POPFRAME");
            break;
        case I_DEFVAR: printf("DEFVAR");
            break;
        case I_CALL: printf("CALL");
            break;
        case I_RETURN: printf("RETURN");
            break;
        case I_PUSHS: printf("PUSHS");
            break;
        case I_POPS: printf("POPS");
            break;
        case I_CLEARS: printf("CLEARS");
            break;
        case I_ADD: printf("ADD");
            break;
        case I_SUB: printf("SUB");
            break;
        case I_MUL: printf("MUL");
            break;
        case I_DIV: printf("DIV");
            break;
        case I_ADDS: printf("ADDS");
            break;
        case I_SUBS: printf("SUBS");
            break;
        case I_MULS: printf("MULS");
            break;
        case I_DIVS: printf("DIVS");
            break;
        case I_LT: printf("LT");
            break;
        case I_GT: printf("GT");
            break;
        case I_EQ: printf("EQ");
            break;
        case I_LTS: printf("LTS");
            break;
        case I_GTS: printf("GTS");
            break;
        case I_EQS: printf("EQS");
            break;
        case I_AND: printf("AND");
            break;
        case I_OR: printf("OR");
            break;
        case I_ANDS: printf("ANDS");
            break;
        case I_NOT: printf("NOT");
            break;
        case I_ORS: printf("ORS");
            break;
        case I_NOTS: printf("NOTS");
            break;
        case I_INT2FLOAT: printf("INT2FLOAT");
            break;
        case I_FLOAT2INT: printf("FLOAT2INT");
            break;
        case I_FLOAT2R2EINT: printf("FLOAT2R2EINT");
            break;
        case I_FLOAT2R2OINT: printf("FLOAT2R2OINT");
            break;
        case I_INT2CHAR: printf("INT2CHAR");
            break;
        case I_STRI2INT: printf("STRI2INT");
            break;
        case I_INT2FLOATS: printf("INT2FLOATS");
            break;
        case I_FLOAT2INTS: printf("FLOAT2INTS");
            break;
        case I_FLOAT2R2EINTS: printf("FLOAT2R2EINTS");
            break;
        case I_FLOAT2R2OINTS: printf("FLOAT2R2OINTS");
            break;
        case I_INT2CHARS: printf("INT2CHARS");
            break;
        case I_STRI2INTS: printf("STRI2INTS");
            break;
        case I_READ: printf("READ");
            break;
        case I_WRITE: printf("WRITE");
            break;
        case I_CONCAT: printf("CONCAT");
            break;
        case I_STRLEN: printf("STRLEN");
            break;
        case I_GETCHAR: printf("GETCHAR");
            break;
        case I_SETCHAR: printf("SETCHAR");
            break;
        case I_TYPE: printf("TYPE");
            break;
        case I_LABEL: printf("LABEL");
            break;
        case I_JUMP: printf("JUMP");
            break;
        case I_JUMPIFEQ: printf("JUMPIFEQ");
            break;
        case I_JUMPIFNEQ: printf("JUMPIFNEQ");
            break;
        case I_JUMPIFEQS: printf("JUMPIFEQS");
            break;
        case I_JUMPIFNEQS: printf("JUMPIFNEQS");
            break;
        case I_BREAK: printf("BREAK");
            break;
        case I_DPRINT: printf("DPRINT");
            break;
        default:DIE(ERR_OTHER);
    }
}

static Bool print(InstructionRef instruction, DataRef _ignored) {
    printInstructions(instruction->instruction);
    printf(" ");
    printOperand(instruction->dest);
    printf(" ");
    printOperand(instruction->first);
    printf(" ");
    printOperand(instruction->second);
    printf("\n");
    return true;
}

void Generator_generate(ListRef instructions) {
    printf(".IFJcode17\n");
    List_forEach(instructions, (ListCallback) print, NULL);
}

static Bool handleInitialization(InstructionRef inst, GeneratorRef generator) {
    List_unshift(generator->instructionLists + IL_CODE, inst);
    return true;
}

static Bool handleVariable(VariableDefRef node, GeneratorRef generator) {
    VariableInfoRef var = VariableInfo_create(generator, node->variable, VIT_GLOBAL);

    if (node->initialization) {
        Location value = Generator_expression(generator, node->initialization);
        Generator_ensureSymbolFor(generator, var, value, false);
    }

    VariableInfo_register(generator, node->variable, var);

    return true;
}

static Bool handleFunction(FunctionDefRef node, GeneratorRef generator) {
    Generator_functionDef(generator, node);
    return true;
}

ListRef Generator_convert(RootRef ast) {
    assertNotNull(ast);

    GeneratorRef generator = Generator_create();

    Generator_instructionList(generator, IL_INIT);
    List_push(generator->inst, Instruction_createframe());
    List_push(generator->inst, Instruction_pushframe());
    List_push(generator->inst, Instruction_createframe());
    List_forEach(ast->variables, (ListCallback) handleVariable, generator);
    Generator_instructionList(generator, IL_CODE);

    List_forEach(ast->functions, (ListCallback) handleFunction, generator);

    List_unshift(generator->inst, Instruction_jump(MAIN));
    List_push(generator->inst, Instruction_label(MAIN));
    Generator_nestedScope(generator, ast->main);

    List_forEachReverse(generator->instructionLists + IL_INIT, (ListCallback) handleInitialization, generator);

    Generator_instructionList(generator, IL_CODE);
    return Generator_destruct(generator);
}

/** End of generator.external.c */
