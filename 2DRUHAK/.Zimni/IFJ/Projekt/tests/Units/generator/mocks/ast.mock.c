#include <stdarg.h>
#include "../../../../src/heapregister/heap_register.external.h"
#include "../../../../src/ast/ast.external.h"

ASTNodeRef ASTMock_of(ASTNodeType type, Address addr) {
    ASTNodeRef node = HeapRegister_allocate(G_GLOBAL, sizeof(ASTNode));
    node->type = type;
    node->ref  = addr;
    return node;
}

//region Expression Immediate, Variable

ASTNodeRef ASTMock_varExp(DataType type, String name) {
    VariableNodeRef variable = HeapRegister_allocate(G_GLOBAL, sizeof(VariableNode));
    variable->type = type;
    variable->name = name;
    return ASTMock_of(AST_VARIABLE_EXP, variable);
}

ASTNodeRef ASTMock_immediate(DataType type, Address value) {
    ImmediateExpRef immediate = HeapRegister_allocate(G_GLOBAL, sizeof(ImmediateExp));
    immediate->type  = type;
    immediate->value = value;
    return ASTMock_of(AST_IMMEDIATE_EXP, immediate);
}

ASTNodeRef ASTMock_string(String value) {
    return ASTMock_immediate(DT_STRING, value);
}

ASTNodeRef ASTMock_int(int* value) {
    return ASTMock_immediate(DT_INTEGER, value);
}

ASTNodeRef ASTMock_double(double *value) {
    return ASTMock_immediate(DT_FLOAT, value);
}

ASTNodeRef ASTMock_bool(bool* value) {
    return ASTMock_immediate(DT_BOOL, value);
}
//endregion

//region Statements

ASTNodeRef ASTMock_assignment(DataType type, String name, ASTNodeRef value) {
    AssignmentStRef node = HeapRegister_allocate(G_GLOBAL, sizeof(AssignmentSt));
    node->variable = HeapRegister_allocate(G_GLOBAL, sizeof(VariableNode));

    node->variable->name = name;
    node->variable->type = type;
    node->expression     = value;

    return ASTMock_of(AST_ASSIGNMENT_ST, node);
}

ASTNodeRef ASTMock_input(DataType type, String name) {
    InputStRef node = HeapRegister_allocate(G_GLOBAL, sizeof(InputSt));
    node->variable = HeapRegister_allocate(G_GLOBAL, sizeof(VariableNode));

    node->variable->name = name;
    node->variable->type = type;

    return ASTMock_of(AST_INPUT_ST, node);
}

ASTNodeRef ASTMock_print(Size argc, ...) {
    PrintStRef node = HeapRegister_allocate(G_GLOBAL, sizeof(PrintSt));
    node->expressions = HeapRegister_allocate(G_GLOBAL, sizeof(List));

    va_list list;
    va_start(list, argc);
    for (Size i = 0; i < argc; ++i) {
        List_push(node->expressions, va_arg(list, ASTNodeRef));
    }
    va_end(list);

    return ASTMock_of(AST_PRINT_ST, node);
}
//endregion

ASTNodeRef ASTMock_binary(DataType type, OperatorType operator, ASTNodeRef left, ASTNodeRef right) {
    BinaryOperatorExpRef node = HeapRegister_allocate(G_GLOBAL, sizeof(BinaryOperatorExp));
    node->type     = type;
    node->operator = operator;

    node->left  = left;
    node->right = right;

    return ASTMock_of(AST_BINARY_OPERATOR_EXP, node);
}

ASTNodeRef ASTMock_unary(DataType type, OperatorType operator, ASTNodeRef expression) {
    UnaryOperatorExpRef node = HeapRegister_allocate(G_GLOBAL, sizeof(UnaryOperatorExp));
    node->type     = type;
    node->operator = operator;

    node->expression = expression;

    return ASTMock_of(AST_UNARY_OPERATOR_EXP, node);
}

ASTNodeRef ASTMock_call(DataType type, String name, Size argc, ...) {
    FunctionCallExpRef node = HeapRegister_allocate(G_GLOBAL, sizeof(FunctionCallExp));
    node->calledFunction = HeapRegister_allocate(G_GLOBAL, sizeof(FunctionNode));
    node->arguments      = HeapRegister_allocate(G_GLOBAL, sizeof(List));

    node->calledFunction->type = type;
    node->calledFunction->name = name;

    if (argc > 0) {
        va_list list;
        va_start(list, argc);
        for (Size i = 0; i < argc; ++i) {
            List_push(node->arguments, va_arg(list, ASTNodeRef));
        }
        va_end(list);
    }

    return ASTMock_of(AST_FUNCTION_CALL_EXP, node);
}

ASTNodeRef ASTMock_var(DataType type, String name, Bool isStatic, ASTNodeRef value) {
    VariableDefRef node = HeapRegister_allocate(G_GLOBAL, sizeof(VariableDef));
    node->variable       = HeapRegister_allocate(G_GLOBAL, sizeof(VariableNode));
    node->variable->name = name;
    node->variable->type = type;
    node->initialization = value;
    node->isStatic       = isStatic;
    return ASTMock_of(AST_VARIABLE_DEF, node);
}
