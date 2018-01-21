#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma ide diagnostic ignored "UnusedImportStatement"

#include "mocks/utils.mock.c"

//typedef struct {
//    bool     terminate;
//    DataType from, to;
//    Address  actual, expected;
//} Conversion, * ConversionRef;
//
//ParameterizedTestParameters(Generator_Conversions, CompilerPassing) {
//    size_t        count = 6;
//    ConversionRef test  = cr_malloc(sizeof(Conversion) * count);
//    test[0] = (Conversion) {.from = DT_INTEGER, .to = DT_FLOAT, .actual = cr_Int_of(5), .expected = cr_Real_of(5.0)};
//    test[1] = (Conversion) {.from = DT_FLOAT, .to = DT_INTEGER, .actual = cr_Real_of(6), .expected = cr_Int_of(6)};
//    test[2] =
//            (Conversion) {.from = DT_FLOAT, .to = DT_INTEGER, .actual = cr_Real_of(12.6), .expected = cr_Int_of(12)};
//    test[3] = (Conversion) {.from = DT_FLOAT, .to = DT_INTEGER, .actual = cr_Real_of(6.4), .expected = cr_Int_of(6)};
//    test[4] =
//            (Conversion) {.from = DT_FLOAT, .to = DT_INTEGER, .actual = cr_Real_of(32.5), .expected = cr_Int_of(32)};
//    test[5] =
//            (Conversion) {.from = DT_FLOAT, .to = DT_INTEGER, .actual = cr_Real_of(45.5), .expected = cr_Int_of(46)};
//
//    return cr_make_param_array(Conversion, test, count,);
//}
//
//ParameterizedTest(ConversionRef param, Generator_Conversions, CompilerPassing) {
//    GEN();
//
//    OperandSymbol symbol   = Symbol_immediate(Immediate_of(param->from, param->actual));
//    Location      oper     = (Location) {.type = LT_SYMBOL, .symbol = symbol};
//    Location      location = Generator_convertDataType(gen, oper, param->to);
//    cr_assert_oper(Operand_symbol(location.symbol), Operand_symbol(symbol));
//    cr_assert(List_isEmpty(list),);
//}

//typedef struct {
//    bool         terminate;
//    OperatorType operator;
//    DataType     firstType, secondType, resultType;
//    Address      first, second, result;
//}                               Binary, * BinaryRef;
//
//ParameterizedTestParameters(Generator_Binary_Inlining, CompilerPassing) {
//    size_t    count = 16;
//    BinaryRef test  = cr_malloc(sizeof(Binary) * count);
//    test[0]  = (Binary) {
//            .operator = OT_ADD,
//            .firstType = DT_INTEGER, .first = cr_Int_of(5),
//            .secondType = DT_INTEGER, .second = cr_Int_of(5),
//            .resultType = DT_INTEGER, .result = cr_Int_of(10)
//    };
//    test[1]  = (Binary) {
//            .operator = OT_SUB,
//            .firstType = DT_INTEGER, .first = cr_Int_of(9),
//            .secondType = DT_INTEGER, .second = cr_Int_of(5),
//            .resultType = DT_INTEGER, .result = cr_Int_of(4)
//    };
//    test[2]  = (Binary) {
//            .operator = OT_MUL,
//            .firstType = DT_INTEGER, .first = cr_Int_of(5),
//            .secondType = DT_INTEGER, .second = cr_Int_of(6),
//            .resultType = DT_INTEGER, .result = cr_Int_of(30)
//    };
//    test[3]  = (Binary) {
//            .operator = OT_DIV,
//            .firstType = DT_INTEGER, .first = cr_Int_of(20),
//            .secondType = DT_INTEGER, .second = cr_Int_of(5),
//            .resultType = DT_INTEGER, .result = cr_Int_of(4)
//    };
//    test[4]  = (Binary) {
//            .operator = OT_IDIV,
//            .firstType = DT_INTEGER, .first = cr_Int_of(42),
//            .secondType = DT_INTEGER, .second = cr_Int_of(6),
//            .resultType = DT_INTEGER, .result = cr_Int_of(7)
//    };
//    test[5]  = (Binary) {
//            .operator = OT_ADD,
//            .firstType = DT_FLOAT, .first = cr_Real_of(5.5),
//            .secondType = DT_FLOAT, .second = cr_Real_of(5.5),
//            .resultType = DT_FLOAT, .result = cr_Real_of(11)
//    };
//    test[6]  = (Binary) {
//            .operator = OT_SUB,
//            .firstType = DT_FLOAT, .first = cr_Real_of(9.6),
//            .secondType = DT_FLOAT, .second = cr_Real_of(5.6),
//            .resultType = DT_FLOAT, .result = cr_Real_of(4)
//    };
//    test[7]  = (Binary) {
//            .operator = OT_MUL,
//            .firstType = DT_FLOAT, .first = cr_Real_of(5.1),
//            .secondType = DT_FLOAT, .second = cr_Real_of(6),
//            .resultType = DT_FLOAT, .result = cr_Real_of(30.6)
//    };
//    test[8]  = (Binary) {
//            .operator = OT_DIV,
//            .firstType = DT_FLOAT, .first = cr_Real_of(20.5),
//            .secondType = DT_FLOAT, .second = cr_Real_of(5),
//            .resultType = DT_FLOAT, .result = cr_Real_of(4.1)
//    };
//    test[9]  = (Binary) {
//            .operator = OT_DIV,
//            .firstType = DT_FLOAT, .first = cr_Real_of(5.5),
//            .secondType = DT_INTEGER, .second = cr_Int_of(5),
//            .resultType = DT_FLOAT, .result = cr_Real_of(1.1)
//    };
//    test[10] = (Binary) {
//            .operator = OT_MUL,
//            .firstType = DT_INTEGER, .first = cr_Int_of(6),
//            .secondType = DT_FLOAT, .second = cr_Real_of(6.6),
//            .resultType = DT_FLOAT, .result = cr_Real_of(39.6)
//    };
//    test[11] = (Binary) {
//            .operator = OT_ADD,
//            .firstType = DT_FLOAT, .first = cr_Real_of(6.6),
//            .secondType = DT_INTEGER, .second = cr_Int_of(21),
//            .resultType = DT_INTEGER, .result = cr_Int_of(28)
//    };
//    test[12] = (Binary) {
//            .operator = OT_ADD,
//            .firstType = DT_INTEGER, .first = cr_Int_of(6),
//            .secondType = DT_FLOAT, .second = cr_Real_of(5.5),
//            .resultType = DT_INTEGER, .result = cr_Int_of(12)
//    };
//    test[13] = (Binary) {
//            .operator = OT_AND,
//            .firstType = DT_BOOL, .first = cr_Bool_of(true),
//            .secondType = DT_BOOL, .second = cr_Bool_of(true),
//            .resultType = DT_BOOL, .result = cr_Bool_of(true)
//    };
//    test[13] = (Binary) {
//            .operator = OT_AND,
//            .firstType = DT_BOOL, .first = cr_Bool_of(true),
//            .secondType = DT_BOOL, .second = cr_Bool_of(false),
//            .resultType = DT_BOOL, .result = cr_Bool_of(false)
//    };
//    test[14] = (Binary) {
//            .operator = OT_OR,
//            .firstType = DT_BOOL, .first = cr_Bool_of(true),
//            .secondType = DT_BOOL, .second = cr_Bool_of(false),
//            .resultType = DT_BOOL, .result = cr_Bool_of(true)
//    };
//    test[15] = (Binary) {
//            .operator = OT_OR,
//            .firstType = DT_BOOL, .first = cr_Bool_of(false),
//            .secondType = DT_BOOL, .second = cr_Bool_of(false),
//            .resultType = DT_BOOL, .result = cr_Bool_of(false)
//    };
//
//    return cr_make_param_array(Binary, test, count,);
//}
//
//ParameterizedTest(BinaryRef param, Generator_Binary_Inlining, CompilerPassing) {
//    return;
//}

//typedef struct {
//    bool         terminate;
//    OperatorType operator;
//    DataType     operandType, resultType;
//    Address      operand, result;
//}                           Unary, * UnaryRef;
//
//ParameterizedTestParameters(Generator_Unary_Inlining, CompilerPassing) {
//    size_t   count = 2;
//    UnaryRef test  = cr_malloc(sizeof(Unary) * count);
//    test[0] = (Unary) {
//            .operator = OT_NOT,
//            .operandType = DT_BOOL, .operand = cr_Bool_of(true),
//            .resultType = DT_BOOL, .result = cr_Int_of(false)
//    };
//    test[1] = (Unary) {
//            .operator = OT_NOT,
//            .operandType = DT_BOOL, .operand = cr_Bool_of(false),
//            .resultType = DT_BOOL, .result = cr_Int_of(true)
//    };
//
//    return cr_make_param_array(Unary, test, count,);
//}
//
//ParameterizedTest(UnaryRef param, Generator_Unary_Inlining, CompilerPassing) {
//    return;
//}
