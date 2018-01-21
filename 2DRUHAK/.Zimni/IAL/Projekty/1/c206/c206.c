/** c206.c **********************************************************}
 {* Téma: Dvousměrně vázaný lineární seznam
 *
 *                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
 *                            Přepracované do jazyka C: Martin Tuček, říjen 2004
 *                                            Úpravy: Kamil Jeřábek, říjen 2017
 *
 * Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
 * Užitečným obsahem prvku seznamu je hodnota typu int.
 * Seznam bude jako datová abstrakce reprezentován proměnnou typu tDLList (DL znamená Double-Linked a slouží pro
 * odlišení jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního seznamu). Definici konstant a typů
 * naleznete v hlavičkovém souboru c206.h.
 *
 * Vaším úkolem je implementovat následující operace, které spolu s výše uvedenou datovou částí abstrakce tvoří
 * abstraktní datový typ obousměrně vázaný lineární seznam:
 *
 *  	DLInitList ...... inicializace seznamu před prvním použitím,
 *  	DLDisposeList ... zrušení všech prvků seznamu,
 *  	DLInsertFirst ... vložení prvku na začátek seznamu,
 *  	DLInsertLast .... vložení prvku na konec seznamu,
 *  	DLFirst ......... nastavení aktivity na první prvek,
 *  	DLLast .......... nastavení aktivity na poslední prvek,
 *  	DLCopyFirst ..... vrací hodnotu prvního prvku,
 *  	DLCopyLast ...... vrací hodnotu posledního prvku,
 *  	DLDeleteFirst ... zruší první prvek seznamu,
 *  	DLDeleteLast .... zruší poslední prvek seznamu,
 *  	DLPostDelete .... ruší prvek za aktivním prvkem,
 *  	DLPreDelete ..... ruší prvek před aktivním prvkem,
 *  	DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
 *  	DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
 *  	DLCopy .......... vrací hodnotu aktivního prvku,
 *  	DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
 *  	DLSucc .......... posune aktivitu na další prvek seznamu,
 *  	DLPred .......... posune aktivitu na předchozí prvek seznamu,
 *  	DLActive ........ zjišťuje aktivitu seznamu.
 *
 * Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí implementovaných v rámci tohoto příkladu, není-li u
 * funkce explicitně uvedeno něco jiného.
 *
 * Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam předá někdo jako parametr hodnotu NULL.
 *
 * Svou implementaci vhodně komentujte!
 *
 * Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
 * Proto zde používáme pojem funkce i pro operace, které by byly v algoritmickém jazyce Pascalovského typu
 * implemenovány jako procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
*/

#include "c206.h"

int solved;
int errflg;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void DLError() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
	return;
}

/**
 * Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná z následujících funkcí nebude volána nad
 * neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným seznamem, a proto tuto možnost neošetřujte.
 * Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
 */
void DLInitList(tDLList* L) {
	L->First = L->Act = L->Last = NULL;
}

/**
 * Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém se nacházel po inicializaci. Rušené prvky seznamu
 * budou korektně uvolněny voláním operace free.
 */
void DLDisposeList(tDLList* L) {
	while (L->First != NULL) {
		L->Act = L->First->rptr;
		free(L->First);
		L->First = L->Act;
	}
	L->Last = NULL;
}

/**
 * Vloží nový prvek na začátek seznamu L.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc, volá funkci DLError().
 */
void DLInsertFirst(tDLList* L, int val) {
	tDLElemPtr elem = malloc(sizeof(struct tDLElem));
	if (elem == NULL) DLError();

	elem->data = val;
	elem->rptr = L->First;
	if (L->First != NULL) L->First->lptr = elem;

	elem->lptr = NULL;
	L->First   = elem;
	if (L->Last == NULL) L->Last = elem;
}

/**
 * Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc, volá funkci DLError().
 */
void DLInsertLast(tDLList* L, int val) {
	tDLElemPtr elem = malloc(sizeof(struct tDLElem));
	if (elem == NULL) DLError();

	elem->data = val;
	elem->rptr = NULL;
	if (L->Last != NULL) L->Last->rptr = elem;

	elem->lptr = L->Last;
	L->Last    = elem;
	if (L->First == NULL) L->First = elem;
}

/**
 * Nastaví aktivitu na první prvek seznamu L.
 * Funkci implementujte jako jediný příkaz (nepočítáme-li return), aniž byste testovali, zda je seznam L prázdný.
 */
void DLFirst(tDLList* L) {
	L->Act = L->First;
}

/**
 * Nastaví aktivitu na poslední prvek seznamu L.
 * Funkci implementujte jako jediný příkaz (nepočítáme-li return), aniž byste testovali, zda je seznam L prázdný.
 */
void DLLast(tDLList* L) {
	L->Act = L->Last;
}

/**
 * Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
 * Pokud je seznam L prázdný, volá funkci DLError().
 */
void DLCopyFirst(tDLList* L, int* val) {
	if (L->First == NULL) DLError();
	*val = L->First->data;
}

/**
 * Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
 * Pokud je seznam L prázdný, volá funkci DLError().
 */
void DLCopyLast(tDLList* L, int* val) {
	if (L->First == NULL) DLError();
	*val = L->Last->data;
}

/**
 * Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita se ztrácí. Pokud byl seznam L prázdný, nic se
 * neděje.
 */
void DLDeleteFirst(tDLList* L) {
	if (L->First == NULL) return;
	if (L->Act == L->First) L->Act   = NULL;
	if (L->Last == L->First) L->Last = NULL;

	tDLElemPtr tmp = L->First->rptr;
	free(L->First);
	L->First = tmp;
	if (L->First == NULL) return;
	L->First->lptr = NULL;
}

/**
 * Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí. Pokud byl seznam L
 * prázdný, nic se neděje.
 */
void DLDeleteLast(tDLList* L) {
	if (L->First == NULL) return;
	if (L->Act == L->First) L->Act   = NULL;
	if (L->Last == L->First) L->Last = NULL;

	tDLElemPtr tmp = L->Last->lptr;
	free(L->Last);
	L->Last = tmp;
	if (L->Last == NULL) return;
	L->Last->rptr = NULL;
}

/**
 * Zruší prvek seznamu L za aktivním prvkem.
 * Pokud je seznam L neaktivní nebo pokud je aktivní prvek posledním prvkem seznamu, nic se neděje.
 */
void DLPostDelete(tDLList* L) {
	if (L->Act == NULL || L->Act == L->Last) return;

	tDLElemPtr tmp = L->Act->rptr->rptr;
	free(L->Act->rptr);

	if (tmp == NULL) { L->Last = L->Act; }
	else { tmp->lptr = L->Act; }

	L->Act->rptr = tmp;
}

/**
 * Zruší prvek před aktivním prvkem seznamu L .
 * Pokud je seznam L neaktivní nebo pokud je aktivní prvek prvním prvkem seznamu, nic se neděje.
 */
void DLPreDelete(tDLList* L) {
	if (L->Act == NULL || L->Act == L->First) return;

	tDLElemPtr tmp = L->Act->lptr->lptr;
	free(L->Act->lptr);

	if (tmp == NULL) { L->First = L->Act; }
	else { tmp->rptr = L->Act; }

	L->Act->lptr = tmp;
}

/**
 * Vloží prvek za aktivní prvek seznamu L.
 * Pokud nebyl seznam L aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc, volá funkci DLError().
 */
void DLPostInsert(tDLList* L, int val) {
	if (L->Act == NULL) return;
	tDLElemPtr new = malloc(sizeof(struct tDLElem));
	if (new == NULL) {
		DLError();
		return;
	}

	new->data    = val;
	if (L->Act == L->Last) {
		L->Last   = new;
		new->rptr = NULL;
	} else {
		L->Act->rptr->lptr = new;
		new->rptr          = L->Act->rptr;
	}
	new->lptr    = L->Act;
	L->Act->rptr = new;
}

/**
 * Vloží prvek před aktivní prvek seznamu L.
 * Pokud nebyl seznam L aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc, volá funkci DLError().
 */
void DLPreInsert(tDLList* L, int val) {
	if (L->Act == NULL) return;

	tDLElemPtr new = malloc(sizeof(struct tDLElem));
	if (new == NULL) {
		DLError();
		return;
	}

	new->data    = val;
	if (L->Act == L->First) {
		L->First  = new;
		new->lptr = NULL;
	} else {
		new->lptr          = L->Act->lptr;
		L->Act->lptr->rptr = new;
	}
	new->rptr    = L->Act;
	L->Act->lptr = new;
}

/**
 * Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
 * Pokud seznam L není aktivní, volá funkci DLError ().
 */
void DLCopy(tDLList* L, int* val) {
	if (L->Act == NULL) { DLError(); }
	else { *val = L->Act->data; }
}

/**
 * Přepíše obsah aktivního prvku seznamu L.
 * Pokud seznam L není aktivní, nedělá nic.
 */
void DLActualize(tDLList* L, int val) {
	if (L->Act == NULL) return;
	L->Act->data = val;
}

/**
 * Posune aktivitu na následující prvek seznamu L.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
 */
void DLSucc(tDLList* L) {
	if (L->Act == NULL) return;
	L->Act = L->Act->rptr;
}

/**
 * Posune aktivitu na předchozí prvek seznamu L.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
 */
void DLPred(tDLList* L) {
	if (L->Act == NULL) return;
	L->Act = L->Act->lptr;
}

/**
 * Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 */
int DLActive(tDLList* L) {
	return L->Act != NULL;
}

/* Konec c206.c*/
