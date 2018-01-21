// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.function_call.c
// Assignment:      125, I
// Date:            28.11.2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "../c_alias.h"
#include "../ast/ast.external.h"
#include "generator.internal.h"
#include "generator.instruction_set.h"
#include "../format/format.h"

static Location nativeLength(GeneratorRef generator, FunctionCallExpRef node) {
    Location      string = Generator_expression(generator, List_pop(node->arguments));
    OperandSymbol symbol = Generator_ensureSymbol(generator, string);

    VariableInfoRef var   = VariableInfo_temporary(generator, DT_INTEGER);
    InstructionRef  instr = Instruction_destFirst(I_STRLEN, Operand_variable(var->variable), Operand_symbol(symbol));
    List_push(generator->inst, instr);
    return (Location) {.type = LT_SYMBOL, .symbol = Symbol_var(var->variable)};
}

static Bool secondArg(ASTNodeRef node, int* i) {
    return ++(*i) != 1;
}

static Location nativeSubstr(GeneratorRef gen, FunctionCallExpRef node) {
    String        address = Format_generateAddress();
    OperandSymbol empty   = Symbol_immediate(Immediate_string(""));
    OperandSymbol zero    = Symbol_immediate(Immediate_int(0));
    OperandSymbol one     = Symbol_immediate(Immediate_int(1));
    OperandSymbol True    = Symbol_immediate(Immediate_bool(true));

    String labelEnd   = Format_name(3, GENERATOR_SUBSTR_PREFIX, address, "end");
    String labelLogic = Format_name(3, GENERATOR_SUBSTR_PREFIX, address, "logic");

    OperandSymbol s     = Generator_ensureSymbol(gen, Generator_expression(gen, List_first(node->arguments)));
    Location      i_loc = Generator_expression(gen, List_search(node->arguments, (ListCallback) secondArg, &(Int) {0}));
    OperandSymbol i     = Generator_ensureSymbol(gen, i_loc);
    OperandSymbol n     = Generator_ensureSymbol(gen, Generator_expression(gen, List_last(node->arguments)));

    // String res = "";
    Operand res = Operand_variable(VariableInfo_temporary(gen, DT_STRING)->variable);
    List_push(gen->inst, Instruction_move(res.variable, empty));

    // int strlen = strlen(res);
    Operand strlen = Operand_variable(VariableInfo_temporary(gen, DT_INTEGER)->variable);
    List_push(gen->inst, Instruction_destFirst(I_STRLEN, strlen, Operand_symbol(s)));

    // if (strlen == 0) return res;
    List_push(gen->inst, Instruction_jumpifeq(labelEnd, Symbol_var(strlen.variable), zero));

    Operand con = Operand_variable(VariableInfo_temporary(gen, DT_BOOL)->variable);

    // if (i < 1) return res;
    List_push(gen->inst, Instruction_create(I_LT, con, Operand_symbol(i), Operand_symbol(one)));
    List_push(gen->inst, Instruction_jumpifeq(labelEnd, Symbol_var(con.variable), True));

    // if (i > strlen) return res;
    List_push(gen->inst, Instruction_create(I_GT, con, Operand_symbol(i), strlen));
    List_push(gen->inst, Instruction_jumpifeq(labelEnd, Symbol_var(con.variable), True));

    // if (n == 0) return res;
    List_push(gen->inst, Instruction_jumpifeq(labelEnd, n, zero));

    Operand         counter = Operand_variable(VariableInfo_temporary(gen, DT_INTEGER)->variable);
    Operand         ch      = Operand_variable(VariableInfo_temporary(gen, DT_STRING)->variable);
    OperandVariable end     = VariableInfo_temporary(gen, DT_STRING)->variable;

    // int counter = i - 1;
    List_push(gen->inst, Instruction_create(I_SUB, counter, Operand_symbol(i), Operand_symbol(one)));
    // end = n + i - 1
    List_push(gen->inst, Instruction_create(I_ADD, Operand_variable(end), counter, Operand_symbol(n)));

    // do {
    List_push(gen->inst, Instruction_label(labelLogic));
    //  char ch = s[counter];
    List_push(gen->inst, Instruction_create(I_GETCHAR, ch, Operand_symbol(s), counter));
    //  res += ch;
    List_push(gen->inst, Instruction_create(I_CONCAT, res, res, ch));
    //  ++counter;
    List_push(gen->inst, Instruction_create(I_ADD, counter, counter, Operand_symbol(one)));
    // } while (counter < end && counter < strlen);
    List_push(gen->inst, Instruction_jumpifeq(labelEnd, Symbol_var(counter.variable), Symbol_var(end)));
    List_push(gen->inst, Instruction_jumpifeq(labelEnd, Symbol_var(counter.variable), Symbol_var(strlen.variable)));

    List_push(gen->inst, Instruction_jump(labelLogic));
    List_push(gen->inst, Instruction_label(labelEnd));

    free(address);
    return (Location) {.type = LT_SYMBOL, .symbol = Symbol_var(res.variable)};
}

static Location nativeAsc(GeneratorRef generator, FunctionCallExpRef node) {
    Location      str   = Generator_expression(generator, List_first(node->arguments));
    Operand       strOp = Operand_symbol(Generator_ensureSymbol(generator, str));
    Location      pos   = Generator_expression(generator, List_last(node->arguments));
    Operand       posOp = Operand_symbol(Generator_ensureSymbol(generator, pos));
    Operand       oneOp = Operand_immediate(Immediate_int(1));
    OperandSymbol True  = Symbol_immediate(Immediate_bool(true));

    String address = Format_generateAddress();
    String name    = Format_name(2, GENERATOR_ASC_PREFIX, address);
    free(address);

    VariableInfoRef var = VariableInfo_temporary(generator, DT_INTEGER);
    List_push(generator->inst, Instruction_move(var->variable, Symbol_immediate(Immediate_int(0))));

    // int strlen = strlen(str);
    Operand temp = Operand_variable(VariableInfo_temporary(generator, DT_INTEGER)->variable);
    List_push(generator->inst, Instruction_destFirst(I_STRLEN, temp, strOp));

    Operand conOp = Operand_variable(VariableInfo_temporary(generator, DT_BOOL)->variable);
    // if (i < 1) return 0;
    List_push(generator->inst, Instruction_create(I_LT, conOp, posOp, oneOp));
    List_push(generator->inst, Instruction_jumpifeq(name, Symbol_var(conOp.variable), True));
    // if (i > strlen) return 0;
    List_push(generator->inst, Instruction_create(I_GT, conOp, posOp, temp));
    List_push(generator->inst, Instruction_jumpifeq(name, Symbol_var(conOp.variable), True));

    // return str[i - 1];
    List_push(generator->inst, Instruction_create(I_SUB, Operand_variable(var->variable), posOp, oneOp));
    List_push(generator->inst,
              Instruction_create(I_STRI2INT, Operand_variable(var->variable), strOp, Operand_variable(var->variable)));
    List_push(generator->inst, Instruction_label(name));
    return (Location) {.type = LT_SYMBOL, .symbol = Symbol_var(var->variable)};
}

static Location nativeChr(GeneratorRef generator, FunctionCallExpRef node) {
    Location cp = Generator_expression(generator, List_first(node->arguments));
    cp = Generator_convertDataType(generator, cp, DT_INTEGER);

    switch (cp.type) {
        case LT_STACK: {
            List_push(generator->inst, Instruction_empty(I_INT2CHARS));
            return (Location) {.type = LT_STACK, .dataType = DT_STRING};
        }
        case LT_SYMBOL: {
            VariableInfoRef var   = VariableInfo_temporary(generator, DT_STRING);
            Operand         varOp = Operand_variable(var->variable);
            InstructionRef  inst  = Instruction_destFirst(I_INT2CHAR, varOp, Operand_symbol(cp.symbol));
            List_push(generator->inst, inst);
            return (Location) {.type = LT_SYMBOL, .symbol = Symbol_var(var->variable)};
        }
        default:DIE(ERR_OTHER);
    }
}

typedef struct FunctionCallData {
    GeneratorRef       generator;
    FunctionCallExpRef node;
    ListElementRef     last;
} FunctionCallData, * FunctionCallDataRef;

static Bool Generator_handleArgument(ASTNodeRef node, FunctionCallDataRef data) {
    Location location = Generator_expression(data->generator, node);
    location = Generator_convertDataType(data->generator, location, ((ParameterRef) data->last->data)->type);
    Generator_ensureOnStack(data->generator, location);
    data->last = data->last->prev; // TODO: dangerous, but api does not provide active.
    // And what about right order? Every expression is handled at right place at right time.
    // It means it is pushed just where it should be pushed.
    return true;
}

static Location Generator_genericFunctionCall(GeneratorRef generator, FunctionCallExpRef node) {
    FunctionCallDataRef data = &(FunctionCallData) {.generator = generator, .node = node,
            .last = node->calledFunction->parameters->last};
    List_forEachReverse(node->arguments, (ListCallback) Generator_handleArgument, data);
    List_push(generator->inst, Instruction_pushframe());
    List_push(generator->inst, Instruction_call(node->calledFunction->name));
    List_push(generator->inst, Instruction_popframe());
    return (Location) {.type = LT_STACK, .dataType = node->calledFunction->type};
}

Location Generator_functionCall(GeneratorRef generator, FunctionCallExpRef node) {
    if (node->isNative) {
        if (strcmp(node->calledFunction->name, "LENGTH") == 0) { return nativeLength(generator, node); }
        else if (strcmp(node->calledFunction->name, "SUBSTR") == 0) { return nativeSubstr(generator, node); }
        else if (strcmp(node->calledFunction->name, "ASC") == 0) { return nativeAsc(generator, node); }
        else if (strcmp(node->calledFunction->name, "CHR") == 0) { return nativeChr(generator, node); }
        else
            DIE(ERR_OTHER);
    }

    return Generator_genericFunctionCall(generator, node);
}

/** End of generator.function_call.c */
