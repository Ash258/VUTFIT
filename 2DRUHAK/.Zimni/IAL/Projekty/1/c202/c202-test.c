
/****************************** c202-test.c ***********************************/
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c202 - Zásobník znaků v poli                                        */
/*  Vytvořil: Václav Topinka, září 2005                                       */
/*  Úpravy: Kamil Jeřábek, říjen 2017                                         */
/* ************************************************************************** */

/* Základní testy pro c202.c */

#include "c202.h"

#include <stdio.h>
#include <stdlib.h>

tStack* ptrstack;                                        /* pracovní zásobník */
int STACK_SIZE;                               /* efektivní velikost zásobníku */
int err_flag;                                              /* indikátor chyby */
int solved;                                        /* indikátor řešení funkce */

/******************************************************************************
 * Speciální ošetření testovaných funkcí.                                     *
 ******************************************************************************/

                                                 /* Vytiskne obsah zásobníku. */
void stackPrint( tStack* ptrstack) {
	if ( solved ) {
		int maxi = ptrstack->top;
		if ( ptrstack->top > STACK_SIZE-1 ) {
			printf ( "Warning: ptrstack->top (value: %i) is out of range STACK_SIZE (%i).\n", ptrstack->top, STACK_SIZE );
			maxi = STACK_SIZE-1;
		}
		printf ("--- BOTTOM [ ");
		for ( int i=0; i<=maxi; i++ )
			putchar ( ptrstack->arr[i] );
		printf (" ] TOP ---\n");
	}
}

         /* Zavolá funkci stackInit a v případě, že nebyla řešena, ohlásí to. */
void use_stack_init ( tStack* ptrstack ) {
	solved = 1;
	stackInit( ptrstack );
	if ( ! solved )
		printf("[W] Funkce stackInit nebyla implementována.\n");
}

                             /* Zavolá funkci stackEmpty a vytiskne výsledek. */
void use_stack_empty ( tStack* ptrstack ) {
	solved = 1;
	int i =stackEmpty( ptrstack );
	if ( ! solved )
		printf("[W] Funkce stackEmpty nebyla implementována.\n");
	else
		printf("stackEmpty returned '%s'\n", i ? "TRUE" : "FALSE" );
}

                              /* Zavolá funkci stackFull a vytiskne výsledek. */
void use_stack_full ( tStack* ptrstack ) {
	solved = 1;
	int i = stackFull( ptrstack );
	if ( ! solved )
		printf("[W] Funkce stackFull nebyla implementována.\n");
	else
		printf("stackFull returned '%s'\n", i ? "TRUE" : "FALSE" );
}

                               /* Zavolá funkci stackTop a vytiskne výsledek. */
void use_stack_top ( tStack* ptrstack ) {
	solved = 1;
	err_flag = 0;
	char c;
  stackTop( ptrstack, &c );
	if ( ! solved )
		printf("[W] Funkce stackTop nebyla implementována.\n");
	else if ( !err_flag )
		printf("stackTop returned '%c'\n", c );
}

                                                   /* Zavolá funkci stackPop. */
void use_stack_pop ( tStack* ptrstack ) {
	solved = 1;
	stackPop( ptrstack );
	if ( ! solved )
		printf("[W] Funkce stackPop nebyla implementována.\n");
}

                                                  /* Zavolá funkci stackPush. */
void use_stack_push ( tStack* ptrstack, char c ) {
	solved = 1;
	stackPush( ptrstack, c );
	if ( ! solved )
		printf("[W] Funkce stackPush nebyla implementována.\n");
}

/******************************************************************************
 * Vlastní testování                                                          *
 ******************************************************************************/

int main (int argc, char* argv[]) {
	printf ("C202 - Stack Implemented Using an Array - Basic Tests\n");
	printf ("-----------------------------------------------------\n");

	STACK_SIZE = 8;
	ptrstack = (tStack*) malloc(sizeof(tStack));

	printf("\n[TEST01] Stack initialization\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_init(ptrstack);
	stackPrint(ptrstack);

	printf("\n[TEST02] Checking a state of the stack\n" );
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);

	printf("\n[TEST03] Pushing a first item 'A'\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_push (ptrstack, 'A');
	stackPrint(ptrstack);

	printf("\n[TEST04] Checking a state of the stack again\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);

	printf("\n[TEST05] Reading and removing the top item\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_top(ptrstack);
	use_stack_pop(ptrstack);
	stackPrint(ptrstack);

	printf("\n[TEST06] Pushing items from '0' to '7'\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i=0; i<8; i++)
		use_stack_push(ptrstack, '0'+i);
	stackPrint(ptrstack);

	printf("\n[TEST07] Checking a state of the stack\n" );
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);

	printf("\n[TEST08] Removing all items one by one\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i=0; i<8; i++) {
    use_stack_top(ptrstack);
  	use_stack_pop(ptrstack);
  }
	stackPrint(ptrstack);

	printf("\n[TEST09] Final check of the stack\n" );
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);

	printf("\n\n----- C202 - The End of Basic Tests -----\n");

	free(ptrstack);
	return(0);
}

/* Konec c202-test.c */
