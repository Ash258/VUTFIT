// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            generator.statement.c
// Assignment:      125, I
// Date:            28/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include "generator.internal.h"
#include "generator.instruction_set.h"

void Generator_assignment(GeneratorRef generator, AssignmentStRef node) {
    VariableInfoRef var   = VariableInfo_use(generator, node->variable);
    Location        value = Generator_expression(generator, node->expression);
    value = Generator_convertDataType(generator, value, var->variable.dataType);
    Generator_ensureSymbolFor(generator, var, value, true);
}

static Bool handleExpression(ASTNodeRef node, GeneratorRef generator) {
    Location      expression = Generator_expression(generator, node);
    OperandSymbol symbol     = Generator_ensureSymbol(generator, expression);
    List_push(generator->inst, Instruction_first(I_WRITE, Operand_symbol(symbol)));
    return true;
}

void Generator_print(GeneratorRef generator, PrintStRef node) {
    List_forEach(node->expressions, (ListCallback) handleExpression, generator);
}

void Generator_input(GeneratorRef generator, InputStRef node) {
    OperandVariable var      = VariableInfo_use(generator, node->variable)->variable;
    Operand         variable = Operand_variable(var);
    Operand         dataType = Operand_dataType(var.dataType);
    List_push(generator->inst, Instruction_destFirst(I_READ, variable, dataType));
}

void Generator_statement(GeneratorRef generator, ASTNodeRef node) {
    switch (node->type) {
        case AST_SCOPE_ST: Generator_nestedScope(generator, node->ref);
            break;
        case AST_VARIABLE_DEF: Generator_variableDef(generator, node->ref);
            break;
        case AST_ASSIGNMENT_ST: Generator_assignment(generator, node->ref);
            break;
        case AST_RETURN_ST: Generator_return(generator, node->ref);
            break;
        case AST_LOOP_ST: Generator_loop(generator, node->ref);
            break;
        case AST_PRINT_ST: Generator_print(generator, node->ref);
            break;
        case AST_IF_ST: Generator_if(generator, node->ref);
            break;
        case AST_INPUT_ST: Generator_input(generator, node->ref);
            break;
        default: DIE(ERR_OTHER);
    }
}

/** End of generator.statement.c */
