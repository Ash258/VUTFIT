/** c402.c: ********************************************************************}
 {* Téma: Nerekurzivní implementace operací nad BVS
 * 								         Implementace: Petr Přikryl, prosinec 1994
 * 								               Úpravy: Petr Přikryl, listopad 1997
 * 								                         Petr Přikryl, květen 1998
 * 								       Převod do jazyka C: Martin Tuček, srpen 2005
 * 								             Úpravy: Bohuslav Křena, listopad 2009
 * 								             Úpravy: Karel Masařík, říjen 2013
 * 								             Úpravy: Radek Hranický, říjen 2014
 * 								             Úpravy: Radek Hranický, listopad 2015
 * 								             Úpravy: Radek Hranický, říjen 2016
 *
 * S využitím dynamického přidělování paměti, implementujte NEREKURZIVNĚ následující operace nad binárním vyhledávacím
 * stromem (předpona BT znamená Binary Tree a je u identifikátorů uvedena kvůli možné kolizi s ostatními příklady):
 *
 * 	BTInit .......... inicializace stromu
 * 	BTInsert ........ nerekurzivní vložení nového uzlu do stromu
 * 	BTPreorder ...... nerekurzivní průchod typu pre-order
 * 	BTInorder ....... nerekurzivní průchod typu in-order
 * 	BTPostorder ..... nerekurzivní průchod typu post-order
 * 	BTDisposeTree ... zruš všechny uzly stromu
 *
 * U všech funkcí, které využívají některý z průchodů stromem, implementujte pomocnou funkci pro nalezení
 * nejlevějšího uzlu v podstromu.
 *
 * Přesné definice typů naleznete v souboru c402.h. Uzel stromu je typu tBTNode, ukazatel na něj je typu tBTNodePtr.
 * Jeden uzel obsahuje položku int Cont, která současně slouží jako užitečný obsah i jako vyhledávací klíč a
 * ukazatele na levý a pravý podstrom (LPtr a RPtr).
 *
 * Příklad slouží zejména k procvičení nerekurzivních zápisů algoritmů nad stromy. Než začnete tento příklad
 * řešit, prostudujte si důkladně principy převodu rekurzivních algoritmů na nerekurzivní. Programování
 * je především inženýrská disciplína, kde opětné objevování Ameriky nemá místo. Pokud se Vám zdá, že by něco šlo
 * zapsat optimálněji, promyslete si všechny detaily Vašeho řešení. Povšimněte si typického umístění akcí pro různé
 * typy průchodů. Zamyslete se nad modifikací řešených algoritmů například pro výpočet počtu uzlů stromu, počtu listů
 * stromu, výšky stromu nebo pro vytvoření zrcadlového obrazu stromu (pouze popřehazování ukazatelů bez vytváření
 * nových uzlů a rušení starých).
 *
 * Při průchodech stromem použijte ke zpracování uzlu funkci BTWorkOut().
 * Pro zjednodušení práce máte předem připraveny zásobníky pro hodnoty typu bool a tBTNodePtr. Pomocnou funkci
 * BTWorkOut ani funkce pro práci s pomocnými zásobníky neupravujte
 * Pozor! Je třeba správně rozlišovat, kdy použít dereferenční operátor * (typicky při modifikaci) a kdy budeme
 * pracovat pouze se samotným ukazatelem (např. při vyhledávání). V tomto příkladu vám napoví prototypy funkcí.
 * Pokud pracujeme s ukazatelem na ukazatel, použijeme dereferenci.
*/

#include "c402.h"

int solved;

//region DoNotEdit

/**
 * Pomocná funkce, kterou budete volat při průchodech stromem pro zpracování uzlu určeného ukazatelem Ptr.
 * Tuto funkci neupravujte.
*/
void BTWorkOut(tBTNodePtr Ptr) {
	if (Ptr == NULL) {
		printf("Chyba: Funkce BTWorkOut byla volána s NULL argumentem!\n");
	} else {
		printf("Výpis hodnoty daného uzlu> %d\n", Ptr->Cont);
	}
}

//region tBTNodePtr types

/** Funkce pro zásobník hodnot typu tBTNodePtr. Tyto funkce neupravujte. */

/** Inicializace zásobníku. */
void SInitP(tStackP* S) {
	S->top = 0;
}

/** Vloží hodnotu na vrchol zásobníku. */
void SPushP(tStackP* S, tBTNodePtr ptr) {
	/* Při implementaci v poli může dojít k přetečení zásobníku. */
	if (S->top == MAXSTACK) {
		printf("Chyba: Došlo k přetečení zásobníku s ukazateli!\n");
	} else {
		S->top++;
		S->a[S->top] = ptr;
	}
}

/** Odstraní prvek z vrcholu zásobníku a současně vrátí jeho hodnotu. */
tBTNodePtr STopPopP(tStackP* S) {
	/* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top == 0) {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return (NULL);
	} else {
		return (S->a[S->top--]);
	}
}

/** Je-li zásobník prázdný, vrátí hodnotu true. */
bool SEmptyP(tStackP* S) {
	return (S->top == 0);
}

//endregion tBTNodePtr types

//region bool types

/** --------------------------------------------------------------------------
 * Funkce pro zásobník hodnot typu bool. Tyto funkce neupravujte.
*/

/** Inicializace zásobníku. */
void SInitB(tStackB* S) {
	S->top = 0;
}

/** Vloží hodnotu na vrchol zásobníku. */
void SPushB(tStackB* S, bool val) {
	/* Při implementaci v poli může dojít k přetečení zásobníku. */
	if (S->top == MAXSTACK) {
		printf("Chyba: Došlo k přetečení zásobníku pro boolean!\n");
	} else {
		S->top++;
		S->a[S->top] = val;
	}
}

/** Odstraní prvek z vrcholu zásobníku a současně vrátí jeho hodnotu. */
bool STopPopB(tStackB* S) {
	/* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top == 0) {
		printf("Chyba: Došlo k podtečení zásobníku pro boolean!\n");
		return (NULL);
	} else {
		return (S->a[S->top--]);
	}
}

/** Je-li zásobník prázdný, vrátí hodnotu true. */
bool SEmptyB(tStackB* S) {
	return (S->top == 0);
}

//endregion bool types

//endregion DoNotEdit

/** --------------------------------------------------------------------------
 * Následuje jádro domácí úlohy - funkce, které máte implementovat.
*/

/** Provede inicializaci binárního vyhledávacího stromu.
 *
 * Inicializaci smí programátor volat pouze před prvním použitím binárního stromu, protože neuvolňuje uzly
 * neprázdného stromu (a ani to dělat nemůže, protože před inicializací jsou hodnoty nedefinované, tedy libovolné).
 * Ke zrušení binárního stromu slouží procedura BTDisposeTree.
 *
 * Všimněte si, že zde se poprvé v hlavičce objevuje typ ukazatel na ukazatel, proto je třeba při práci s RootPtr
 * použít dereferenční operátor *.
*/
void BTInit(tBTNodePtr* RootPtr) { *RootPtr = NULL; }

/** Vloží do stromu nový uzel s hodnotou Content.
 *
 * Z pohledu vkládání chápejte vytvářený strom jako binární vyhledávací strom, kde uzly s hodnotou menší než má otec
 * leží v levém podstromu a uzly větší leží vpravo.
 * Pokud vkládaný uzel již existuje, neprovádí se nic (daná hodnota se ve stromu může vyskytnout nejvýše jednou).
 * Pokud se vytváří nový uzel, vzniká vždy jako list stromu. Funkci implementujte nerekurzivně.
*/
void BTInsert(tBTNodePtr* RootPtr, int Content) {
	while (RootPtr) {
		if (!*RootPtr) {
			*RootPtr = malloc(sizeof(struct tBTNode));
			if (*RootPtr == NULL) return;

			(*RootPtr)->LPtr = (*RootPtr)->RPtr = NULL;
			(*RootPtr)->Cont = Content;
			return;
		}
		if (Content == (*RootPtr)->Cont) {
			return;
		}
		if (Content > (*RootPtr)->Cont) {
			RootPtr = &(*RootPtr)->RPtr;
		} else {
			RootPtr = &(*RootPtr)->LPtr;
		}
	}
}

//region Orders

//region PREORDER

/**                                  PREORDER                                  */

/**
 * Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
 *
 * Při průchodu Preorder navštívené uzly zpracujeme voláním funkce BTWorkOut() a ukazatele na ně is uložíme do
 * zásobníku.
*/
void Leftmost_Preorder(tBTNodePtr ptr, tStackP* Stack) {
	while (ptr) {
		SPushP(Stack, ptr); // Should be node pushed first or processed first?
		BTWorkOut(ptr);
		ptr = ptr->LPtr;
	}
}

/**
 * Průchod stromem typu preorder implementovaný nerekurzivně s využitím funkce Leftmost_Preorder a zásobníku
 * ukazatelů. Zpracování jednoho uzlu stromu realizujte jako volání funkce BTWorkOut().
*/
void BTPreorder(tBTNodePtr RootPtr) {
	tStackP stackP;
	SInitP(&stackP);
	//tBTNodePtr aux = RootPtr;
	//Leftmost_Preorder(aux, &stackP);
	Leftmost_Preorder(RootPtr, &stackP);

	while (!SEmptyP(&stackP)) {
		RootPtr = STopPopP(&stackP);
		Leftmost_Preorder(RootPtr->RPtr, &stackP); // Process the most left nodes of right subtree
	}
}

//endregion Preorder

//region INORDER

/**                                  INORDER                                   */

/**
 * Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
 *
 * Při průchodu Inorder ukládáme ukazatele na všechny navštívené uzly do zásobníku.
*/
void Leftmost_Inorder(tBTNodePtr ptr, tStackP* Stack) {
	while (ptr) {
		SPushP(Stack, ptr);
		ptr = ptr->LPtr;
	}
}

/**
 * Průchod stromem typu inorder implementovaný nerekurzivně s využitím funkce Leftmost_Inorder a zásobníku ukazatelů.
 * Zpracování jednoho uzlu stromu realizujte jako volání funkce BTWorkOut().
*/
void BTInorder(tBTNodePtr RootPtr) {
	tStackP stackP;
	SInitP(&stackP);
	//tBTNodePtr aux = RootPtr;
	//Leftmost_Inorder(aux, &stackP);
	Leftmost_Inorder(RootPtr, &stackP);

	while (!SEmptyP(&stackP)) {
		RootPtr = STopPopP(&stackP);
		BTWorkOut(RootPtr);
		Leftmost_Inorder(RootPtr->RPtr, &stackP); // Save the most left nodes to right subtree
	}
}

//endregion

//region POSTORDER

/**                                 POSTORDER                                  */

/**
 * Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
 *
 * Při průchodu Postorder ukládáme ukazatele na navštívené uzly do zásobníku a současně do zásobníku bool hodnot
 * ukládáme informaci, zda byl uzel navštíven poprvé a že se tedy ještě nemá zpracovávat.
*/
void Leftmost_Postorder(tBTNodePtr ptr, tStackP* StackP, tStackB* StackB) {
	while (ptr) {
		SPushP(StackP, ptr); // Save pointer
		SPushB(StackB, true); // Visited ==> save flag "from left"
		ptr = ptr->LPtr; // To left
	}
}

/**
 * Průchod stromem typu postorder implementovaný nerekurzivně s využitím funkce Leftmost_Postorder, zásobníku
 * ukazatelů a zásobníku hodnot typu bool.
 * Zpracování jednoho uzlu stromu realizujte jako volání funkce BTWorkOut().
*/
void BTPostorder(tBTNodePtr RootPtr) {
	tStackP stackP;
	tStackB stackB;
	SInitP(&stackP);
	SInitB(&stackB);

	Leftmost_Postorder(RootPtr, &stackP, &stackB); // Save all the most left nodes and their flags

	while (!SEmptyP(&stackP)) {
		RootPtr = STopPopP(&stackP); // Load top
		SPushP(&stackP, RootPtr); // Return it back

		if (STopPopB(&stackB)) { // From left or right??
			SPushB(&stackB, false); // Next from left
			Leftmost_Postorder(RootPtr->RPtr, &stackP, &stackB);
		} else {
			STopPopP(&stackP);
			BTWorkOut(RootPtr);
		}
	}
}

//endregion POSTORDER

//endregion Orders

/**
 * Zruší všechny uzly stromu a korektně uvolní jimi zabranou paměť.
 *
 * Funkci implementujte nerekurzivně s využitím zásobníku ukazatelů.
*/
void BTDisposeTree(tBTNodePtr* RootPtr) {
	tStackP StackP;
	SInitP(&StackP);

	tBTNodePtr auxTree = *RootPtr, aux = NULL;
	if (!auxTree) { return; }

	do {
		if (!auxTree && !SEmptyP(&StackP)) { // Nothing to cancel
			auxTree = STopPopP(&StackP);
		} else { // Something to cancel
			if (auxTree->RPtr) SPushP(&StackP, auxTree->RPtr); // Save pointer (right tree) on stack
			aux     = auxTree; // To delete
			auxTree = auxTree->LPtr; // To left
			free(aux);
		}
	} while (auxTree || !SEmptyP(&StackP)); // Until tree delete

	free(auxTree);
	*RootPtr = NULL;
}

/* konec c402.c */
