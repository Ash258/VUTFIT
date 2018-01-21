// ********************************************************************
// Project:         Implementace překladače imperativního jazyka IFJ17.
// File:            format.c
// Assignment:      125, I
// Date:            22/11/2017
// Authors:
//                  Pavel Parma         xparma02
//                  Vojtěch Bargl       xbargl01
//                  Jakub Čábera        xcaber00
//                  Tomáš Vondráček     xvondr23
// ********************************************************************

#include <stdarg.h>
#include "format.h"
#include "../stringbuilder/string_builder.external.h"

static UnsignedLong address = 0;

static inline void joinAddress(StringBuilderRef builder, UnsignedLong address) {
    char addr[ADDRESS_LENGTH + 1] = {0};
    sprintf(addr, ADDRESS_FORMAT, ADDRESS_SIZE, address);
    StringBuilder_join(builder, addr);
}

UnsignedLong Format_id() {
    return address++;
}

String Format_address(UnsignedLong address) {
    StringBuilderRef builder = &(StringBuilder) {0};
    StringBuilder_init(builder);
    joinAddress(builder, address);
    return StringBuilder_build(builder, true);
}

String Format_generateAddress() {
    return Format_address(address++);
}

String Format_generateSimple(String prefix) {
    StringBuilderRef builder = &(StringBuilder) {0};
    StringBuilder_init(builder);

    StringBuilder_join(builder, FORMAT_MARK);
    StringBuilder_join(builder, prefix);
    StringBuilder_join(builder, FORMAT_SEPARATOR);
    joinAddress(builder, address++);
    StringBuilder_join(builder, FORMAT_MARK);

    return StringBuilder_build(builder, true);
}

String Format_name(Size count, ...) {
    StringBuilderRef builder = &(StringBuilder) {0};
    StringBuilder_init(builder);

    StringBuilder_join(builder, FORMAT_MARK);

    va_list list;
    va_start(list, count);
    while (--count) {
        StringBuilder_join(builder, va_arg(list, String));
        StringBuilder_join(builder, FORMAT_SEPARATOR);
    }
    StringBuilder_join(builder, va_arg(list, String));
    va_end(list);

    StringBuilder_join(builder, FORMAT_MARK);

    return StringBuilder_build(builder, true);
}

/** End of format.c */
