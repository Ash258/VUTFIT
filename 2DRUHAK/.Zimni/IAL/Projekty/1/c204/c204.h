
/* ******************************* c204.h *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, říjen 2017                                        */
/* ************************************************************************** */

/* TENTO SOUBOR, PROSÍME, NEUPRAVUJTE! */

#ifndef _INFIX2POSTFIX_H_
#define _INFIX2POSTFIX_H_

#include <stdio.h>
#include <stdlib.h>

//#include "c202.h"                          /* využívá příklad c202 - zásobník */
#include "../c202/c202.h"                          /* využívá příklad c202 - zásobník */

#define MAX_LEN 64                          /* maximální délka řetězce výrazu */

extern int solved;                      /* Indikuje, zda byla operace řešena. */

/* Konverzní funkce */
char* infix2postfix (const char* infExpr);

#endif

/* Konec hlavičkového souboru c204.h */
