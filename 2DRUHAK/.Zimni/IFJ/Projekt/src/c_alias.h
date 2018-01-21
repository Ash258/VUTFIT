// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            c_alias.h
// Assignment:      125, I
// Date:            04/10/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_C_ALIAS_H
#define IFJ2017_C_ALIAS_H

#include <stdio.h>
#include <stdbool.h>

typedef int Int;
typedef int* IntArr;
typedef unsigned int UnsignedInt;

typedef long long          Long;
typedef unsigned long long UnsignedLong;

typedef double Real;

typedef _Bool Bool;

typedef char Char;
typedef char* String;
typedef char** StringArr;

typedef char Byte;
typedef char* ByteArr;

typedef size_t Size;

typedef FILE* FileRef;

typedef void Void;
typedef void* Address, * DataRef, * ContextRef;

typedef void (* SimpleDestructor)(DataRef);

typedef void (* SimpleCallback)(DataRef, ContextRef);

#endif //IFJ2017_C_ALIAS_H

/** End of c_alias.h */
