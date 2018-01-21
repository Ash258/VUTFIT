// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            config.h
// Assignment:      125, I
// Date:            04/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_CONFIG_H
#define IFJ2017_CONFIG_H

#include "c_alias.h"

#define FORMAT_MARK "$"
#define FORMAT_SEPARATOR "-"

#define ADDRESS_FORMAT "&%0*llX"
#define ADDRESS_SIZE 4
#define ADDRESS_LENGTH (ADDRESS_SIZE + 1)

#define GENERATOR_IF_PREFIX "%IF%"
#define GENERATOR_LOOP_PREFIX "%LOOP%"
#define GENERATOR_STATIC_PREFIX "%STATIC%"
#define GENERATOR_GLOBAL_PREFIX "%GLOBAL%"
#define GENERATOR_SUBSTR_PREFIX "%SUBSTR%"
#define GENERATOR_ASC_PREFIX "%ASC%"

#endif //IFJ2017_CONFIG_H

/** End of config.h */
