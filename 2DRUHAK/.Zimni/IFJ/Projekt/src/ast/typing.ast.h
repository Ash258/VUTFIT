// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            typing.ast.h
// Assignment:      125, I
// Date:            19/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TYPING_AST_H
#define IFJ2017_TYPING_AST_H

#include "ast.external.h"

/**
 * @param leftOperand data type
 * @param rightOperand data type
 *
 * @return Result data type;
 */
DataType getBinaryExpressionType(DataType leftOperand, DataType rightOperand, OperatorType operator);

/**
 * @param expression data type
 *
 * @return Result data type;
 */
DataType getUnaryExpressionType(OperatorType operator, DataType expression);

/**
 * @param first
 * @param second
 *
 * @return True if two types are convertible, false otherwise
 */
Bool areConvertible(DataType first, DataType second);

/**
 * @param first
 * @param second
 *
 * @return True if two types are equal or convertible, false otherwise
 */
Bool areCompatible(DataType first, DataType second);

/**
 * @param node general ASTNode
 *
 * @return corresponding indexes structure based on node type
 */
DataType getExpressionType(ASTNodeRef node);

#endif //IFJ2017_TYPING_AST_H

/** End of typing.ast.h */
