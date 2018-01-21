// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            tokenizer.digit.h
// Assignment:      125, I
// Date:            13/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_TOKENIZER_DIGIT_H
#define IFJ2017_TOKENIZER_DIGIT_H

#include "tokenizer.external.h"

#define INVALID_DIGIT (-1L)

typedef enum {
    BASE_BINARY  = 2,
    BASE_OCTAL   = 8,
    BASE_DECIMAL = 10,
    BASE_HEXA    = 16
} DigitBase;

typedef Int (* DigitConverter)(Char);

/**
 * Get binary digit or return -1.
 *
 * @param c - character to check
 * @return 0 or 1, otherwise -1
 */
Int Digit_binary(Char c);

/**
 * Get octal digit or return -1.
 *
 * @param c - character to check
 * @return 0, 1, ..., 7, otherwise -1.
 */
Int Digit_octal(Char c);

/**
 * Get decimal digit or return -1.
 *
 * @param c - character to check
 * @return 0, 1, ..., 9, otherwise -1
 */
Int Digit_decimal(Char c);

/**
 * Get hexadecimal digit or return -1.
 *
 * @param FileBufRef buffer - instance
 * @return 0, 1, ..., 9, A, B, ..., F, otherwise -1
 */
Int Digit_hexadecimal(Char c);

/**
 * Get sequence of digits in specific base.
 * The formula used for counting (n is digits count, d_i is digit):
 * sequence = base^n * d1 + base^(n-1) * d2 + ... + base * d_(n-1) + d_(n)
 *
 * @param buffer - instance
 * @param converter - method to get digit
 * @param count - 0 for infinity, otherwise how many digits you want to parse
 * @return Sequence of digit
 */
Long Digit_positiveSequence(BufferRef buffer, DigitBase base, DigitConverter converter, Size count);

/**
 * Get sequence of digits in specific base.
 * The formula used for counting (n is digits count, d_i is digit):
 * sequence = base^(-1) * d1 + base^(-2) * d2 + ... + base^(-n+1) * d_(-n+1) + base^(-n) * d_(-n)
 *
 * @param buffer - instance
 * @param converter - method to get digit
 * @param count - 0 for infinity, otherwise how many digits you want to parse
 * @return Sequence of digit
 */
Real Digit_negativeSequence(BufferRef buffer, DigitBase base, DigitConverter converter, Size count);

#endif //IFJ2017_TOKENIZER_DIGIT_H

/** End of tokenizer.digit.h */
