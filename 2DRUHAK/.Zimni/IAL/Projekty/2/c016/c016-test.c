
/* ************************ s016-test.c **************************** */

#include "c016.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


tHTItem* UNDEFPTR;
tHTable* ptrht;

/* tiskne tData ze struktury */
void htPrintData ( tData* ptrdata ) {
	if ( ptrdata )
		printf ("%.2f\n", *ptrdata );
	else
		printf ("NULL\n");
}

/* tiskne tItem ze struktury */
void htPrintItem ( tHTItem* ptritem ) {
	if ( ptritem )
		printf ("%s - %.2f\n", ptritem->key, ptritem->data );
	else
		printf ("NULL\n");
}

/* tiskne celou tabulku */
void htPrintTable( tHTable* ptrht ) {
	int maxlen = 0;
	int sumcnt = 0;
	
	printf ("------------HASH TABLE--------------\n");
	for ( int i=0; i<HTSIZE; i++ ) {
		printf ("%i:",i);
		int cnt = 0;
		tHTItem* ptr = (*ptrht)[i];
		while ( ptr != NULL ) {
			printf (" (%s,%.2f)",ptr->key,ptr->data);
			if ( ptr != UNDEFPTR )
				cnt++;
			ptr = ptr->ptrnext;
		}
		printf ("\n");
	
		if (cnt > maxlen)
			maxlen = cnt;
		sumcnt+=cnt;
	}
	
	printf ("------------------------------------\n");
	printf ("Items count %i   The longest list %i\n",sumcnt,maxlen);
	printf ("------------------------------------\n");
}

/* vola funkci htInit a v pripade ze neni resena tiskne chybu */
void use_init ( tHTable* ptrht ) {
	solved = 1;
	htInit( ptrht );
	if ( ! solved )
		printf("[W] Funkce HTInit nebyla implementovana...\n");
}

/* vola funkci htSearch a tiskne vysledek,
 v pripade ze neni resena tiskne chybu */
void use_search( tHTable* ptrht, tKey key ) {
	solved = 1;
	tHTItem* ptritem = htSearch ( ptrht, key );
	if ( ! solved )
		printf("[W] Funkce HTSearch nebyla implementovana...\n");
	else 
		htPrintItem ( ptritem );
}

/* vola funkci htInsert a v pripade ze neni resena tiskne chybu */
void use_insert ( tHTable* ptrht, tKey key, tData data ) {
	solved = 1;
	htInsert( ptrht, key, data);
	if ( ! solved )
		printf("[W] Funkce HTInsert nebyla implementovana...\n");
}

/* vola funkci htRead a tiskne vysledek,
 v pripade ze neni resena tiskne chybu */
void use_read( tHTable* ptrht, tKey key ) {
	solved = 1;
	tData* ptrdata = htRead ( ptrht, key );
	if ( ! solved )
		printf("[W] Funkce HTSearch nebyla implementovana...\n");
	else 
		htPrintData ( ptrdata );
}

/* vola funkci htDelete a v pripade ze neni resena tiskne chybu */
void use_delete ( tHTable* ptrht, tKey key ) {
	solved = 1;
	htDelete( ptrht, key );
	if ( ! solved )
		printf("[W] Funkce HTDelete nebyla implementovana...\n");
}

/* vola funkci htClearAll a v pripade ze neni resena tiskne chybu */
void use_clear_all ( tHTable* ptrht  ) {
	solved = 1;
	htClearAll( ptrht );
	if ( ! solved )
		printf("[W] Funkce HTClearAll nebyla implementovana...\n");
}

/* Hlavni funkce pro testovani */
int main(int argc, char* argv[] ) {
	UNDEFPTR = (tHTItem*) malloc ( sizeof(tHTable) );
	UNDEFPTR->key = "*UNDEF*";
	UNDEFPTR->data = -1;
	UNDEFPTR->ptrnext = NULL;
	ptrht = (tHTable*) malloc ( sizeof(tHTable) );
	for ( int i=0; i<MAX_HTSIZE; (*ptrht)[i++] = UNDEFPTR );

/********************* SCRIPT START ******************************************/
	printf ("Hash Table - testing script\n");
	printf ("---------------------------\n");
	printf ("\nLet's set HTSIZE to 19 ( must be prvocislo )\n");
	HTSIZE = 19;
	htPrintTable(ptrht);


	printf ("\n[TEST01] Table initialization\n");
	use_init ( ptrht );
	htPrintTable(ptrht);

	printf ("\n[TEST02] Let's try htInsert()\n");
	use_insert ( ptrht, "krusovice", 21.50 );
	htPrintTable(ptrht);

	printf ("\n[TEST03] Search for existing item\n");
	use_search (ptrht,"krusovice");

	printf ("\n[TEST04] Let's insert next items\n");
	use_insert ( ptrht, "korgon", 18.00 );
	use_insert ( ptrht, "zlaty bazant", 20.00);
	use_insert ( ptrht, "gambrinus", 18.50);
	use_insert ( ptrht, "starobrno", 16.50);
	use_insert ( ptrht, "plzen", 25.00);
	use_insert ( ptrht, "velvet", 28.00);
	use_insert ( ptrht, "kelt", 30.00);
	use_insert ( ptrht, "kofola", 16.00);
	htPrintTable(ptrht);

	printf ("\n[TEST05] htSearch for \"starobrno\"\n");
	use_search ( ptrht, "starobrno" );
	htPrintTable(ptrht);

	printf ("\n[TEST06] Let's change korgon price to 12.50\n");
	use_insert ( ptrht, "korgon", 12.50);
	use_search ( ptrht, "korgon" );
	htPrintTable(ptrht);

	printf ("\n[TEST07] Is \"starobahno\" in table?\n");
	use_search ( ptrht, "starobahno" );
	htPrintTable(ptrht);

	printf ("\n[TEST08] How much is korgon?\n");
	use_read ( ptrht, "korgon" );

	printf ("\n[TEST09] Lets delete gambrinus and kofola\n");
	use_delete( ptrht, "gambrinus" );
	use_delete( ptrht, "kofola" );
	htPrintTable ( ptrht );

	printf ("\n[TEST10] Let's delete whole table\n");
	use_clear_all ( ptrht );
	htPrintTable ( ptrht );

	printf ("\n[TEST11] And search for non-existing velvet\n");
	use_search ( ptrht, "velvet" );
	htPrintTable(ptrht);

	printf ("\n[TEST12] And insert velvet again\n");
	use_insert ( ptrht, "velvet", 28.00);
	htPrintTable(ptrht);

	free ( UNDEFPTR );
	free ( ptrht );
	
	return 0;	
}
