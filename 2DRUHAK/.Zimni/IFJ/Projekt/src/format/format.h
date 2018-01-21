// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            format.h
// Assignment:      125, I
// Date:            22/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#ifndef IFJ2017_FORMAT_H
#define IFJ2017_FORMAT_H

#include "../config.h"

UnsignedLong Format_id();

String Format_address(UnsignedLong address);

String Format_generateAddress();

String Format_generateSimple(String value);

String Format_name(Size count, ...);

#endif //IFJ2017_FORMAT_H

/** End of format.h */
