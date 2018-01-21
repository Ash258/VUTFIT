/* ******************** s016-advanced-test.c *********************** */
/*  p�edm�t: Algoritmy (IAL) - FIT VUT Brno                          */
/*  �kol: c202 - Tabulka s rozpt�len�mi polo�kami                    */
/*  vytvo�il: V�clav Topinka                                         */
/*  datum: z��� 2005                                                 */
/*  k�dov�n�: iso-8859-2                                             */
/* ***************************************************************** */

/* Testy pro dom�c� �kol na t�ma z�sobn�k znak� (c202.c).
Obsahuje procedury a funkce, kter� testuj� studentsk� verze jejich vol�n�m.
Toto je roz���en� verze, obsahuj�c� komplexn� testov�n�.
Slou�� pro lektory ke kontrole p��slu�n� dom�c� �lohy. */

#include "c016.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

tHTItem* UNDEFPTR;
tHTable* ptrht;

/* tiskne tData ze struktury */
void htPrintData(tData* ptrdata) {
	if (ptrdata) {
		printf("%.2f\n", *ptrdata);
	} else {
		printf("NULL\n");
	}
}

/* tiskne tItem ze struktury */
void htPrintItem(tHTItem* ptritem) {
	if (ptritem) {
		printf("%s - %.2f\n", ptritem->key, ptritem->data);
	} else {
		printf("NULL\n");
	}
}

/* tiskne celou tabulku */
void htPrintTable(tHTable* ptrht) {
	int maxlen  = 0;
	int sumcnt  = 0;
	int sumcnt2 = 0;
	int n       = 0;

	printf("------------HASH TABLE--------------\n");
	for (int i = 0; i < HTSIZE; i++) {
		printf("%i:", i);
		int cnt = 0;
		tHTItem* ptr = (*ptrht)[i];
		while (ptr != NULL) {
			printf(" (%s,%.2f)", ptr->key, ptr->data);
			if (ptr != UNDEFPTR) {
				cnt++;
			}
			ptr = ptr->ptrnext;
		}
		printf("\n");

		if (cnt > maxlen) {
			maxlen = cnt;
		}
		n += cnt;
		sumcnt += cnt;
		sumcnt2 += cnt * cnt;
	}

	printf("------------------------------------\n");
	printf("Items count %i   The longest list %i\n", sumcnt, maxlen);
	if (n < 2) {
		n = 2;
	}
}

/* vola funkci htInit a v pripade ze neni resena tiskne chybu */
void use_init(tHTable* ptrht) {
	solved = 1;
	htInit(ptrht);
	if (!solved) {
		printf("[W] Funkce HTInit nebyla implementovana...\n");
	}
}

/* vola funkci htSearch a tiskne vysledek,
 v pripade ze neni resena tiskne chybu */
void use_search(tHTable* ptrht, tKey key) {
	solved = 1;
	tHTItem* ptritem = htSearch(ptrht, key);
	if (!solved) {
		printf("[W] Funkce HTSearch nebyla implementovana...\n");
	} else {
		htPrintItem(ptritem);
	}
}

/* vola funkci htInsert a v pripade ze neni resena tiskne chybu */
void use_insert(tHTable* ptrht, tKey key, tData data) {
	solved = 1;
	htInsert(ptrht, key, data);
	if (!solved) {
		printf("[W] Funkce HTInsert nebyla implementovana...\n");
	}
}

/* vola funkci htRead a tiskne vysledek,
 v pripade ze neni resena tiskne chybu */
void use_read(tHTable* ptrht, tKey key) {
	solved = 1;
	tData* ptrdata = htRead(ptrht, key);
	if (!solved) {
		printf("[W] Funkce HTSearch nebyla implementovana...\n");
	} else {
		htPrintData(ptrdata);
	}
}

/* vola funkci htDelete a v pripade ze neni resena tiskne chybu */
void use_delete(tHTable* ptrht, tKey key) {
	solved = 1;
	htDelete(ptrht, key);
	if (!solved) {
		printf("[W] Funkce HTDelete nebyla implementovana...\n");
	}
}

/* vola funkci htClearAll a v pripade ze neni resena tiskne chybu */
void use_clear_all(tHTable* ptrht) {
	solved = 1;
	htClearAll(ptrht);
	if (!solved) {
		printf("[W] Funkce HTClearAll nebyla implementovana...\n");
	}
}

/* Hlavni funkce pro testovani */
int main(int argc, char* argv[]) {
	UNDEFPTR = (tHTItem*) malloc(sizeof(tHTable));
	UNDEFPTR->key     = "*UNDEF*";
	UNDEFPTR->data    = -1;
	UNDEFPTR->ptrnext = NULL;
	ptrht      = (tHTable*) malloc(sizeof(tHTable));
	for (int i = 0; i < MAX_HTSIZE; (*ptrht)[i++] = UNDEFPTR);

/********************* SCRIPT START ******************************************/
	printf("Hash Table - testing script\n");
	printf("---------------------------\n");
	printf("\nLet's set HTSIZE to 19 ( must be prvocislo )\n");
	HTSIZE = 19;
	htPrintTable(ptrht);

	printf("\n[TEST01] Table initialization\n");
	use_init(ptrht);
	htPrintTable(ptrht);

	printf("\n[TEST02] Search for non-existing item\n");
	use_search(ptrht, "rohlik");

	printf("\n[TEST03] Let's try htInsert()\n");
	use_insert(ptrht, "rohlik", 1.50);
	htPrintTable(ptrht);

	printf("\n[TEST04] Search for existing item\n");
	use_search(ptrht, "rohlik");

	printf("\n[TEST05] Let's insert next items\n");
	use_insert(ptrht, "chleba", 20.00);
	use_insert(ptrht, "pepsi", 30.00);
	use_insert(ptrht, "kecup", 28.90);
	use_insert(ptrht, "spagety", 14.60);
	use_insert(ptrht, "debrecinka", 19.60);
	use_insert(ptrht, "ryze", 26.10);
	use_insert(ptrht, "vajicko", 2.50);
	use_insert(ptrht, "olej", 32.50);
	use_insert(ptrht, "", 14.60);
	use_insert(ptrht, "jogurt", 8.50);
	use_insert(ptrht, "fish", 99.90);
	use_insert(ptrht, "korgon", 18.00);
	use_insert(ptrht, "zlaty bazant", 20.00);
	use_insert(ptrht, "gambrinus", 18.50);
	use_insert(ptrht, "starobrno", 16.50);
	use_insert(ptrht, "plzen", 25.00);
	use_insert(ptrht, "velvet", 26.00);
	use_insert(ptrht, "kelt", 30.00);
	use_insert(ptrht, "kofola", 15.00);
	use_insert(ptrht, "graham", 4.50);
	use_insert(ptrht, "fernet", 95.00);
	use_insert(ptrht, "sul", 10.00);
	use_insert(ptrht, "cukr", 25.50);
	htPrintTable(ptrht);

	printf("\n[TEST06] htSearch for \"kecup\"\n");
	use_search(ptrht, "kecup");

	printf("\n[TEST07] Let's change kecup price to 12.50\n");
	use_insert(ptrht, "kecup", 12.50);
	use_search(ptrht, "kecup");

	printf("\n[TEST08] Is \"kiwi\" in table?\n");
	use_search(ptrht, "kiwi");
	htPrintTable(ptrht);

	printf("\n[TEST09] How much is the fish?\n");
	use_read(ptrht, "fish");

	printf("\n[TEST10] Change fish price to 105.50\n");
	use_insert(ptrht, "fish", 105.50);
	use_search(ptrht, "fish");

	printf("\n[TEST11] How much is the fish?\n");
	use_read(ptrht, "fish");

	printf("\n[TEST12] How much is kiwi?\n");
	use_read(ptrht, "kiwi");

	printf("\n[TEST13] Let's delete non-existing \"kiwi\"\n");
	use_delete(ptrht, "kiwi");
	htPrintTable(ptrht);

	printf("\n[TEST14] How much is the fish?\n");
	use_read(ptrht, "fish");

	printf("\n[TEST15] Lets delete fish twice\n");
	use_delete(ptrht, "fish");
	use_delete(ptrht, "fish");
	htPrintTable(ptrht);

	printf("\n[TEST16] How much is the fish?\n");
	use_read(ptrht, "fish");

	printf("\n[TEST17] Lets delete next items\n");
	use_delete(ptrht, "zlaty bazant");
	use_delete(ptrht, "gambrinus");
	use_delete(ptrht, "starobrno");
	use_delete(ptrht, "plzen");
	use_delete(ptrht, "velvet");
	use_delete(ptrht, "kelt");
	use_delete(ptrht, "");
	htPrintTable(ptrht);

	printf("\n[TEST18] Let's delete whole table\n");
	use_clear_all(ptrht);
	htPrintTable(ptrht);

	printf("\n[TEST19] And try delete in empty table\n");
	use_delete(ptrht, "zlaty bazant");
	use_delete(ptrht, "gambrinus");
	use_delete(ptrht, "starobrno");
	htPrintTable(ptrht);

	printf("\n[TEST20] htSearch for \"kecup\" in empty table\n");
	use_search(ptrht, "kecup");
	htPrintTable(ptrht);

	free(UNDEFPTR);
	free(ptrht);
	return 0;
}
