/**/

/* **********************SOUBOR SE ST.TESTEM  ********************** */
/* **********************-----------------   *********************** */
/*  vytvoril: Martin Tucek
    predmet: Algoritmy (IAL) - FIT (Fakulta Informacnich Technologii)
    test pro soubor: c402.c
	datum: rijen 2005

    kompletni upravy: Roman Lukas, 2006
													 */	
/* ***************************************************************** */


#include "c402.h"
#include <string.h>

tBTNodePtr TempTree;			// deklarace testovaci promenne 

int Content;

void Print_tree2(tBTNodePtr TempTree, char* sufix, char fromdir)
//vykresli sktrukturu binarniho stromu

{
     if (TempTree != NULL)
     {
	char* suf2 = (char*) malloc(strlen(sufix) + 4);
	strcpy(suf2, sufix);
        if (fromdir == 'L')
	{
	   suf2 = strcat(suf2, "  |");
	   printf("%s\n", suf2);
	}
	else
	   suf2 = strcat(suf2, "   ");
	Print_tree2(TempTree->RPtr, suf2, 'R');
        printf("%s  +-[%d]\n", sufix, TempTree->Cont);
	strcpy(suf2, sufix);
        if (fromdir == 'R')
	   suf2 = strcat(suf2, "  |");	
	else
	   suf2 = strcat(suf2, "   ");
	Print_tree2(TempTree->LPtr, suf2, 'L');
	if (fromdir == 'R') printf("%s\n", suf2);
	free(suf2);
    }
}

void Print_tree(tBTNodePtr TempTree)
{
  printf("Struktura binarniho stromu:\n");
  printf("\n");
  if (TempTree != NULL)
     Print_tree2(TempTree, "", 'X');
  else
     printf("strom je prazdny\n");
  printf("\n");
  printf("=================================================\n");
} 

int test_BTInit(tBTNodePtr *TempTree)			{
	solved=TRUE;
	BTInit(TempTree);
	if (!solved)	{
		printf("Operace InitList() nebyla implementovana \n");
		return(FALSE);
	}	
	else	
	{
	        Print_tree(*TempTree);
		return(TRUE);
	}
}

	
int test_BTInsert (tBTNodePtr* TempTree, int Content)		{
	solved=TRUE;
	BTInsert(TempTree, Content);	
	if (!solved)	{
		printf("Operace BTInsert() nebyla implementovana \n");
		return(FALSE);
	}
	else	{
		return(TRUE);
	}
}

int test_BTPreorder(tBTNodePtr TempTree)	{
	solved=TRUE;
	printf("Vypis Preorder:\n");    
	printf("===============\n");
	BTPreorder(TempTree);	
	printf("\n");
	if (!solved)	{
		printf("Operace BTPreorder() nebyla implementovana \n");
		return(FALSE);
	}
	else	
		return(TRUE);
}

int test_BTInorder(tBTNodePtr TempTree)		{
	solved=TRUE;
	printf("Vypis Inorder:\n");    
	printf("==============\n");
	BTInorder(TempTree);	
	printf("\n");
	if (!solved)	{
		printf("Operace BTInorder() nebyla implementovana \n");
		return(FALSE);
	}
	else	
		return(TRUE);
}

int test_BTPostorder(tBTNodePtr TempTree)	{
	solved=TRUE;
	printf("Vypis Postorder:\n");
	printf("================\n");
	BTPostorder(TempTree);	
	printf("\n");
	if (!solved)	{
		printf("Operace BTPostorder() nebyla implementovana \n");
		return(FALSE);
	}
	else	
		return(TRUE);
}


int test_BTDispose(tBTNodePtr* TempTree)		{
	solved=TRUE;
	BTDisposeTree(TempTree);
	if (!solved)	{
		printf("Operace BTDispose() nebyla implementovana \n");
		return(FALSE);
	}
	else	{
		Print_tree(*TempTree);
		return(TRUE);
	}
}

/* .......................... sekce volani jednotlivych testu .............................*/ 

int main(int argc, char *argv[])			{
	
	printf("Nerekurzivni operace nad binarnim stromem\n");
	printf("=========================================\n");
	
	printf("[TEST01]\n");
	printf("Test inicializace....\n");
	test_BTInit(&TempTree);
	
	printf("[TEST02]\n");
	printf("Zkusime zrusit strom\n");
	printf("~~~~~~~~~~~~~~~~~~~~\n");
	test_BTDispose(&TempTree);
	
	printf("[TEST03]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order na prazdny strom\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_BTPreorder(TempTree);
	test_BTPostorder(TempTree);
	test_BTInorder(TempTree);
	
	printf("[TEST04]\n");
	printf("Vlozime prvek s hodnotou 8\n");   
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Content=8;
	test_BTInsert(&TempTree,Content);
	Print_tree(TempTree);

	printf("[TEST05]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order na prazdny strom\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_BTPreorder(TempTree);
	test_BTPostorder(TempTree);
	test_BTInorder(TempTree);
	
	printf("[TEST06]\n");
	printf("Zkusime zrusit strom\n");
	printf("~~~~~~~~~~~~~~~~~~~~\n");
	test_BTDispose(&TempTree);

	printf("[TEST07]\n");
	printf("Vlozime prvek s hodnotou 8\n");   
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Content=8;
	test_BTInsert(&TempTree,Content);
        Print_tree(TempTree);

	printf("[TEST08]\n");
	printf("Vlozeni dalsich prvku\n");
	printf("~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Vlozime prvek 4\n");
	Content=4;
	test_BTInsert(&TempTree,Content);
	
	printf("Vlozime prvek 12\n");
	Content=12;
	test_BTInsert(&TempTree,Content);
	Print_tree(TempTree);	


	printf("[TEST09]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order na prazdny strom\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_BTPreorder(TempTree);
	test_BTPostorder(TempTree);
	test_BTInorder(TempTree);

	printf("[TEST10]\n");
	printf("Pokus o opetovne vlozeni prvku 8 (nesmi dojit ke zmene stromu) \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	Content=8;
	test_BTInsert(&TempTree, Content);
	Print_tree(TempTree);
	
	printf("[TEST11]\n");
	printf("Pokus o opetovne vlozeni prvku 12 (nesmi dojit ke zmene stromu) \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	Content=12;
	test_BTInsert(&TempTree, Content);
	Print_tree(TempTree);
	
	printf("[TEST12]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	test_BTPreorder(TempTree);
	test_BTInorder(TempTree);
	test_BTPostorder(TempTree);
	
	printf("[TEST13]\n");
	printf("Vlozeni dalsich prvku ve vhodnem poradi\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Vlozime prvek 2\n");
	Content=2;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 6\n");
	Content=6;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 10\n");
	Content=10;
	test_BTInsert(&TempTree, Content);   
	
	printf("Vlozime prvek 14\n");
	Content=14;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 1\n");
	Content=1;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 3\n");
	Content=3;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 5\n");
	Content=5;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 7\n");
	Content=7;
	test_BTInsert(&TempTree, Content);   
	
	printf("Vlozime prvek 9\n");
	Content=9;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 11\n");
	Content=11;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 13\n");
	Content=13;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 15\n");
	Content=15;
	test_BTInsert(&TempTree, Content);
	Print_tree(TempTree);	

	printf("[TEST14]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	test_BTPreorder(TempTree);
	test_BTInorder(TempTree);
	test_BTPostorder(TempTree);
	
	printf("[TEST15]\n");
	printf("Zrusime cely strom\n");
	printf("~~~~~~~~~~~~~~~~~~\n");
	test_BTDispose(&TempTree);
	
	printf("[TEST16]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	test_BTPreorder(TempTree);
	test_BTInorder(TempTree);
	test_BTPostorder(TempTree);
	
	printf("[TEST17]\n");
	printf("Nyni si vytvorime jiny strom.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	printf("Vlozime prvek 10\n");
	Content=10;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 8\n");
	Content=8;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 12\n");
	Content=12;
	test_BTInsert(&TempTree, Content);   
	
	printf("Vlozime prvek 14\n");
	Content=14;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 1\n");
	Content=1;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 2\n");
	Content=2;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 3\n");
	Content=3;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 4\n");
	Content=4;
	test_BTInsert(&TempTree, Content);   
	
	printf("Vlozime prvek 5\n");
	Content=5;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 6\n");
	Content=6;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 13\n");
	Content=13;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 15\n");
	Content=15;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 7\n");
	Content=7;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 9\n");
	Content=9;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 11\n");
	Content=11;
	test_BTInsert(&TempTree, Content);
	
	Print_tree(TempTree);


	printf("[TEST18]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	test_BTPreorder(TempTree);
	test_BTInorder(TempTree);
	test_BTPostorder(TempTree);
	
	printf("[TEST19]\n");
	printf("Pokus o opetovne vlozeni prvku 9 (nesmi dojit ke zmene stromu) \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	Content=9;
	test_BTInsert(&TempTree, Content);
	Print_tree(TempTree);
	
	printf("[TEST20]\n");
	printf("Zrusime cely strom\n");
	printf("~~~~~~~~~~~~~~~~~~\n");
	test_BTDispose(&TempTree);
		
	printf("[TEST21]\n");
	printf("Nyni si vytvorime jiny strom.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	printf("Vlozime prvek 1\n");
	Content=1;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 2\n");
	Content=2;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 3\n");
	Content=3;
	test_BTInsert(&TempTree, Content);   
	
	printf("Vlozime prvek 4\n");
	Content=4;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 5\n");
	Content=5;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 6\n");
	Content=6;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 7\n");
	Content=7;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 8\n");
	Content=8;
	test_BTInsert(&TempTree, Content);   
	
	printf("Vlozime prvek 9\n");
	Content=9;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 10\n");
	Content=10;
	test_BTInsert(&TempTree, Content);
		
	Print_tree(TempTree);


	printf("[TEST22]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	test_BTPreorder(TempTree);
	test_BTInorder(TempTree);
	test_BTPostorder(TempTree);
	
	printf("[TEST23]\n");
	printf("Pokus o opetovne vlozeni prvku 5 (nesmi dojit ke zmene stromu) \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	Content=5;
	test_BTInsert(&TempTree, Content);
	Print_tree(TempTree);
	
	printf("[TEST24]\n");
	printf("Zrusime cely strom\n");
	printf("~~~~~~~~~~~~~~~~~~\n");
	test_BTDispose(&TempTree);

	printf("[TEST25]\n");
	printf("Nyni si vytvorime jiny strom.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	printf("Vlozime prvek 10\n");
	Content=10;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 9\n");
	Content=9;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 8\n");
	Content=8;
	test_BTInsert(&TempTree, Content);   
	
	printf("Vlozime prvek 7\n");
	Content=7;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 6\n");
	Content=6;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 5\n");
	Content=5;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 4\n");
	Content=4;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 3\n");
	Content=3;
	test_BTInsert(&TempTree, Content);   
	
	printf("Vlozime prvek 2\n");
	Content=2;
	test_BTInsert(&TempTree, Content);
	
	printf("Vlozime prvek 1\n");
	Content=1;
	test_BTInsert(&TempTree, Content);
		
	Print_tree(TempTree);


	printf("[TEST26]\n");
	printf("Provedeme pruchod Pre-order, In-order a Post-order \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	test_BTPreorder(TempTree);
	test_BTInorder(TempTree);
	test_BTPostorder(TempTree);
	
	printf("[TEST27]\n");
	printf("Pokus o opetovne vlozeni prvku 5 (nesmi dojit ke zmene stromu) \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	Content=5;
	test_BTInsert(&TempTree, Content);
	Print_tree(TempTree);

	printf("[TEST28]\n");
	printf("Pokus o opetovne vlozeni prvku 10 (nesmi dojit ke zmene stromu) \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	Content=10;
	test_BTInsert(&TempTree, Content);
	Print_tree(TempTree);
	
	printf("[TEST29]\n");
	printf("Zrusime cely strom\n");
	printf("~~~~~~~~~~~~~~~~~~\n");
	test_BTDispose(&TempTree);

	printf("[TEST30]\n");
	printf("Zrusime cely strom\n");
	printf("~~~~~~~~~~~~~~~~~~\n");
	test_BTDispose(&TempTree);

	printf("------------------------------ konec -------------------------------------\n");
	
	return(0);	
}
/**/

