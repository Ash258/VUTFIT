
/* Hlavičkový soubor pro c016.h - Tabulka s Rozptýlenými Položkami,
**  obsahuje jednak nutné includes a externované proměnné,
**  ale rovnež definici datových typů. Tento soubor neupravujte!
**  Téma:  Tabulka s explicitně zřetězenými synonymy
**                      První implementace: Petr Přikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      Úpravy: Karel Masařík, říjen 2013
**                      Úpravy: Radek Hranický, říjen 2014
**                      Úpravy: Radek Hranický, listopad 2015
**                      Úpravy: Radek Hranický, říjen 2016
**
***/


#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>

extern int solved;			/* externi promenna pouzivana v testeru */

/* Maximální velikost pole pro implementaci
   vyhledávací tabulky. Řešené procedury však
   využívají pouze HTSIZE prvků pole (viz deklarace této proměnné).
*/
#define MAX_HTSIZE 101

/* typ klíče (například identifikace zboží) */
typedef char* tKey;

/* typ obsahu (například cena zboží) */
typedef float tData;

/*Datová položka TRP s explicitně řetězenými synonymy*/
 typedef struct tHTItem{
	tKey key;				/* klíč  */
	tData data;				/* obsah */
	struct tHTItem* ptrnext;	/* ukazatel na další synonymum */
} tHTItem;

/* TRP s explicitně zřetězenými synonymy. */
typedef tHTItem* tHTable[MAX_HTSIZE];

/* Pro účely testování je vhodné mít možnost volby velikosti pole,
   kterým je vyhledávací tabulka implementována. Fyzicky je deklarováno
   pole o rozměru MAX_HTSIZE, ale při implementaci vašich procedur uvažujte
   velikost HTSIZE.  Ve skriptu se před voláním řešených procedur musí
   objevit příkaz HTSIZE N, kde N je velikost požadovaného prostoru.
   
   POZOR! Pro správnou funkci TRP musí být hodnota této proměnné prvočíslem.
*/
extern int HTSIZE;

/* Hlavičky řešených procedur a funkcí. */

int hashCode ( tKey key );

void htInit ( tHTable* ptrht );

tHTItem* htSearch ( tHTable* ptrht, tKey key );

void htInsert ( tHTable* ptrht, tKey key, tData data );

tData* htRead ( tHTable* ptrht, tKey key );

void htDelete ( tHTable* ptrht, tKey key );

void htClearAll ( tHTable* ptrht );

#endif
