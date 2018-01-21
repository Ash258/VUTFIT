/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, říjen 2017                                        */
/* ************************************************************************** */
/**
 * Implementujte proceduru pro převod infixového zápisu matematického výrazu do postfixového tvaru. Pro převod
 * využijte zásobník (tStack), který byl implementován v rámci příkladu c202. Bez správného vyřešení příkladu c202 se
 * o řešení tohoto příkladu nepokoušejte.
 *
 * Implementujte následující funkci:
 *
 *    infix2postfix .... konverzní funkce pro převod infixového výrazu
 *                       na postfixový
 *
 * Pro lepší přehlednost kódu implementujte následující pomocné funkce:
 *
 *    untilLeftPar .... vyprázdnění zásobníku až po levou závorku
 *    doOperation .... zpracování operátoru konvertovaného výrazu
 *
 * Své řešení účelně komentujte.
 *
 * Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
 * Proto zde používáme pojem funkce i pro operace, které by byly v algoritmickém jazyce Pascalovského typu
 * implementovány jako procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
 */

#include "c204.h"

int solved;

/**
 * Pomocná funkce untilLeftPar.
 * Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka bude také odstraněna. Pokud je zásobník
 * prázdný, provádění funkce se ukončí.
 *
 * Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole znaků postExpr. Délka převedeného výrazu
 * a též ukazatel na první volné místo, na které se má zapisovat, představuje parametr postLen.
 *
 * Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde nadeklarovat a používat pomocnou proměnnou
 * typu char.
 */
void untilLeftPar(tStack* s, char* postExpr, unsigned* postLen) {
	char topChar;
	while (!stackEmpty(s) && (stackTop(s, &topChar), topChar) != '(') {
		postExpr[(*postLen)++] = topChar;
		stackPop(s);
	}
	stackPop(s);
}

/**
 * Pomocná funkce doOperation.
 * Zpracuje operátor, který je předán parametrem c po načtení znaku ze vstupního pole znaků.
 *
 * Dle priority předaného operátoru a případně priority operátoru na vrcholu zásobníku rozhodneme o dalším postupu.
 * Délka převedeného výrazu a taktéž ukazatel na první volné místo, do kterého se má zapisovat, představuje parametr
 * postLen, výstupním polem znaků je opět postExpr.
 */
void doOperation(tStack* s, char c, char* postExpr, unsigned* postLen) {
	char topChar = 0;
	if (!stackEmpty(s)) stackTop(s, &topChar);

	if (stackEmpty(s) ||
	    (topChar == '(') ||
	    (topChar == '+' && c != '-' && c != '+') ||
	    (topChar == '-' && c != '-' && c != '+')) {
		stackPush(s, c);
	} else {
		postExpr[(*postLen)++] = topChar;
		stackPop(s);
		doOperation(s, c, postExpr, postLen);
	}
}

/**
 * Konverzní funkce infix2postfix.
 * Čte infixový výraz ze vstupního řetězce infExpr a generuje odpovídající postfixový výraz do výstupního řetězce
 * (postup převodu hledejte v přednáškách nebo ve studijní opoře). Paměť pro výstupní řetězec (o velikosti MAX_LEN)
 * je třeba alokovat. Volající funkce, tedy příjemce konvertovaného řetězce, zajistí korektní uvolnění zde alokované
 * paměti.
 *
 * Tvar výrazu:
 * 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání, násobení a dělení. Sčítání má stejnou prioritu
 * 		jako odčítání, násobení má stejnou prioritu jako dělení. Priorita násobení je větší než priorita sčítání.
 * 		Všechny operátory jsou binární (neuvažujte unární mínus).
 *
 * 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory a číslicemi - 0..9, a..z, A..Z (velikost
 * 		písmen se rozlišuje).
 *
 * 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých závorek. Uvažujte, že vstupní výraz je zapsán
 * 		správně (neošetřujte chybné zadání výrazu).
 *
 * 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen ukončovacím znakem '='.
 *
 * 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
 *
 * Poznámky k implementaci
 * -----------------------
 * Jako zásobník použijte zásobník znaků tStack implementovaný v příkladu c202.
 * Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
 *
 * Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
 *
 * Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu char, jenž je korektně ukončeno nulovým
 * znakem dle zvyklostí jazyka C.
 *
 * Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka nepřesáhne MAX_LEN-1 (MAX_LEN i s
 * nulovým znakem) a tedy i výsledný výraz by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
 * ověřte, že se alokace skutečně zdařila.
 * V případě chyby alokace vraťte namísto řetězce konstantu NULL.
 */
char* infix2postfix(const char* infExpr) {
	char c, * postExpr = (char*) malloc(MAX_LEN);
	unsigned postfixLength = 0;
	tStack* s = (tStack*) malloc(sizeof(tStack));

	if (postExpr == NULL) return NULL;
	stackInit(s);

	// 1. Zpracovávej vstupní řetězec položku po položce zleva doprava a vytvářej postupně výstupní řetězec.
	while ((c = *(infExpr++)) != '\0') {
		if ((c >= '0' && c <= '9') ||
		    (c >= 'A' && c <= 'Z') ||
		    (c >= 'a' && c <= 'z')) {
			// 2. Je-li zpracovávanou položkou operand,přidej ho na konec vznikajícího výstupního řetězce
			postExpr[postfixLength] = c;
			postfixLength++;
		} else if (c == '(') {
			// 3. Je-li zpracovávanou položkou levá závorka, vlož ji na vrchol zásobníku
			stackPush(s, c);
		} else if (c == ')') {
			// 5. Je-li zpracovávanou položkou pravá závorka, odebírej z vrcholu položky a dávej je na konec výstupního
			// řetězce, až narazíš na levou závorku. Tím je pár závorek zpracován.
			untilLeftPar(s, postExpr, &postfixLength);
		} else if (c == '=') {
			// 6. Je-li zpracovávanou položkou omezovač ‘=’, pak postupně odstraňuj prvky z vrcholu zásobníku a
			// přidávej je na konec řetězce, až zásobník zcela vyprázdníš, a na konec přidej rovnítko.
			while (!stackEmpty(s)) {
				stackTop(s, &postExpr[postfixLength]);
				postfixLength++;
				stackPop(s);
			}
			postExpr[postfixLength] = '=';
			postfixLength++;
			postExpr[postfixLength] = '\0';
		} else {
			//4. Je-li zpracovávanou položkou operátor, pak ho na vrchol zásobníku vlož v případě, že:
			doOperation(s, c, postExpr, &postfixLength);
		}
	}
	free(s);

	return postExpr;
}

/* Konec c204.c */
