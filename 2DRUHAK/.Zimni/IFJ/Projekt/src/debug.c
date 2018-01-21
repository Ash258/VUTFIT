// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            debug.c
// Assignment:      125, I
// Date:            24/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include <stdarg.h>
#include "debug.h"

void die(String format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end (args);

    exit(0);
}

void printTokenName(TokenRef token) {
    printf("%s\n", tokenTypeName(token->type));
}

String ASTNodeTypeName(ASTNodeType type) {
    switch (type) {
        case AST_VARIABLE_DEF: return "AST_VARIABLE_DEF";
        case AST_VARIABLE_EXP: return "AST_VARIABLE_EXP";
        case AST_BINARY_OPERATOR_EXP: return "AST_BINARY_OPERATOR_EXP";
        case AST_IMMEDIATE_EXP: return "AST_IMMEDIATE_EXP";
        case AST_FUNCTION_CALL_EXP: return "AST_FUNCTION_CALL_EXP";
        case AST_ASSIGNMENT_ST: return "AST_ASSIGNMENT_ST";
        case AST_RETURN_ST: return "AST_RETURN_ST";
        case AST_LOOP_ST: return "AST_LOOP_ST";
        case AST_PRINT_ST: return "AST_PRINT_ST";
        case AST_IF_ST: return "AST_IF_ST";
        case AST_INPUT_ST: return "AST_INPUT_ST";
        default: return "Unknown";
    }
}

String operatorTypeName(OperatorType type) {
    switch (type) {
        case OT_ADD: return "OT_ADD";
        case OT_SUB: return "OT_SUB";
        case OT_DIV: return "OT_DIV";
        case OT_IDIV: return "OT_IDIV";
        case OT_MUL: return "OT_MUL";

        case OT_GT: return "OT_GT";
        case OT_GEQ: return "OT_GEQ";
        case OT_LT: return "OT_LT";
        case OT_LEQ: return "OT_LEQ";
        case OT_EQ: return "OT_EQ";
        case OT_NEQ: return "OT_NEQ";

        case OT_AND: return "OT_AND";
        case OT_OR: return "OT_OR";
        case OT_NOT: return "OT_NOT";
        default: return "unknown";
    }
}

String tokenTypeName(TokenType type) {
    switch (type) {
        case T_K_AS: return "T_K_AS";
        case T_K_DECLARE: return "T_K_DECLARE";
        case T_K_DIM: return "T_K_DIM";
        case T_K_DO: return "T_K_DO";
        case T_K_ELSE: return "T_K_ELSE";
        case T_K_END: return "T_K_END";
        case T_K_FUNCTION: return "T_K_FUNCTION";
        case T_K_IF: return "T_K_IF";
        case T_K_INPUT: return "T_K_INPUT";
        case T_K_LOOP: return "T_K_LOOP";
        case T_K_PRINT: return "T_K_PRINT";
        case T_K_SCOPE: return "T_K_SCOPE";
        case T_K_THEN: return "T_K_THEN";
        case T_K_WHILE: return "T_K_WHILE";
        case T_K_CONTINUE: return "T_K_CONTINUE";
        case T_K_ELSEIF: return "T_K_ELSEIF";
        case T_K_EXIT: return "T_K_EXIT";
        case T_K_FOR: return "T_K_FOR";
        case T_K_NEXT: return "T_K_NEXT";
        case T_K_SHARED: return "T_K_SHARED";
        case T_K_STATIC: return "T_K_STATIC";
        case T_I_INTEGER: return "T_I_INTEGER";
        case T_I_DOUBLE: return "T_I_DOUBLE";
        case T_I_STRING: return "T_I_STRING";
        case T_I_BOOL: return "T_I_BOOL";
        case T_NATIVE_FUNCTION: return "T_NATIVE_FUNCTION";
        case T_COMMENT: return "T_COMMENT";
        case T_IDENTIFIER: return "T_IDENTIFIER";
        case T_DATA_TYPE: return "T_DATA_TYPE";
        case T_EOL: return "T_EOL";
        case T_LEFT_PARENTHESIS: return "T_LEFT_PARENTHESIS";
        case T_RIGHT_PARENTHESIS: return "T_RIGHT_PARENTHESIS";
        case T_COMMA: return "T_COMMA";
        case T_SEMICOLON: return "T_SEMICOLON";
        case T_O_LOGICAL: return "T_O_LOGICAL";
        case T_O_RELATIONAL: return "T_O_RELATIONAL";
        case T_O_MULTIPLICATION: return "T_O_MULTIPLICATION";
        case T_O_DECIMAL_DIVISION: return "T_O_DECIMAL_DIVISION";
        case T_O_PLUS: return "T_O_PLUS";
        case T_END_OF_FILE: return "T_END_OF_FIL";
        case T_K_RETURN: return "T_K_RETURN";
        case T_O_NOT: return "T_O_NOT";
        case T_O_MINUS: return "T_O_MINUS";
        default: return "Unknown";
    }
}

String dataTypeName(DataType type) {
    switch (type) {

        case DT_INTEGER: return "DT_INTEGER";
        case DT_FLOAT: return "DT_FLOAT";
        case DT_STRING: return "DT_STRIN";
        case DT_BOOL: return "DT_BOOL";
        default: return "Unknown";
    }
}

Bool printTrieKey(DataRef key, ContextRef context) {
    printf("%s\n", (char*) key);

    return true;
}

/** End of debug.c */
