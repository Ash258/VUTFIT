#include "../../../../src/helpers.h"
#include "../../../../src/generator/generator.operand.h"

Operand OperMock_opLabel(String label) {
    return (Operand) {.type = O_LABEL, .label = label};
}

Operand OperMock_opDataType(DataType type) {
    return (Operand) {.type = O_DATATYPE, .dataType = type};
}

OperandVariable OperMock_varGlobal(DataType type, String name) {
    return (OperandVariable) {.dataType = type, .name = name, .scope = VS_GLOBAL};
}

OperandVariable OperMock_varLocal(DataType type, String name) {
    return (OperandVariable) {.dataType = type, .name = name, .scope = VS_LOCAL};
}

OperandVariable OperMock_varTemp(DataType type, String name) {
    return (OperandVariable) {.dataType = type, .name = name, .scope = VS_TEMP};
}

Operand OperMock_opVarGlobal(DataType type, String name) {
    return (Operand) {.type = O_VARIABLE, .variable = OperMock_varGlobal(type, name)};
}

Operand OperMock_opVarLocal(DataType type, String name) {
    return (Operand) {.type = O_VARIABLE, .variable = OperMock_varLocal(type, name)};
}

Operand OperMock_opVarTemp(DataType type, String name) {
    return (Operand) {.type = O_VARIABLE, .variable = OperMock_varTemp(type, name)};
}

OperandImmediate OperMock_immInt(int* value) {
    return (OperandImmediate) {.dataType = DT_INTEGER, .value = value};
}

OperandImmediate OperMock_immStr(String value) {
    return (OperandImmediate) {.dataType = DT_STRING, .value = value};
}

OperandImmediate OperMock_immDouble(double *value) {
    return (OperandImmediate) {.dataType = DT_FLOAT, .value = value};
}

OperandImmediate OperMock_immBool(Bool *value) {
    return (OperandImmediate) {.dataType = DT_BOOL, .value = value};
}

Operand OperMock_opImmInt(int* value) {
    return (Operand) {.type = O_IMMEDIATE, .immediate = OperMock_immInt(value)};
}

Operand OperMock_opImmStr(String value) {
    return (Operand) {.type = O_IMMEDIATE, .immediate = OperMock_immStr(value)};
}

Operand OperMock_opImmDouble(double *value) {
    return (Operand) {.type = O_IMMEDIATE, .immediate = OperMock_immDouble(value)};
}

Operand OperMock_opImmBool(bool* value) {
    return (Operand) {.type = O_IMMEDIATE, .immediate = OperMock_immBool(value)};
}

OperandSymbol OperMock_symGlobal(DataType type, String name) {
    return (OperandSymbol) {.type = O_VARIABLE, .variable = OperMock_varGlobal(type, name)};
}

OperandSymbol OperMock_symLocal(DataType type, String name) {
    return (OperandSymbol) {.type = O_VARIABLE, .variable = OperMock_varLocal(type, name)};
}

OperandSymbol OperMock_symTemp(DataType type, String name) {
    return (OperandSymbol) {.type = O_VARIABLE, .variable = OperMock_varTemp(type, name)};
}

OperandSymbol OperMock_symInt(int* value) {
    return (OperandSymbol) {.type=O_IMMEDIATE, .immediate = OperMock_immInt(value)};
}

OperandSymbol OperMock_symStr(String value) {
    return (OperandSymbol) {.type=O_IMMEDIATE, .immediate = OperMock_immStr(value)};
}

OperandSymbol OperMock_symDouble(double *value) {
    return (OperandSymbol) {.type=O_IMMEDIATE, .immediate = OperMock_immDouble(value)};
}

OperandSymbol OperMock_symBool(bool* value) {
    return (OperandSymbol) {.type=O_IMMEDIATE, .immediate = OperMock_immBool(value)};
}

