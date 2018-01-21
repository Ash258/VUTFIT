
/*
 *  Předmět: Algoritmy (IAL) - FIT VUT v Brně
 *  Základní testy pro příklad c206.c (Dvousměrně vázaný lineární seznam)
 *  Vytvořil: Martin Tuček, září 2005
 *  Úprava: Kamil Jeřábek, říjen 2017
 */

#include "c206.h"
                                                         /* pracovní proměnné */
tDLList TEMPLIST;
int ElemValue=1;
int MaxListLength = 100;                     /* Handles wrongly linked lists. */


/*******************************************************************************
 * Pomocné funkce usnadňující testování vlastní implementace.
 ******************************************************************************/

void print_elements_of_list(tDLList TL)	{

	tDLList TempList=TL;
	int CurrListLength = 0;
	printf("-----------------");
	while ((TempList.First!=NULL) && (CurrListLength<MaxListLength))	{
		printf("\n \t%d",TempList.First->data);
		if ((TempList.First==TL.Act) && (TL.Act!=NULL))
			printf("\t <= toto je aktivní prvek ");
		TempList.First=TempList.First->rptr;
		CurrListLength++;
	}
    if (CurrListLength>=MaxListLength) printf("\nList exceeded maximum length!");
	printf("\n-----------------\n");
}

int test_DLInitList()	{
	solved=TRUE;
	DLInitList(&TEMPLIST);
	if (!solved)	{
		printf("Operace InitList nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLDisposeList()	{
	solved=TRUE;
	DLDisposeList(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDisposeList nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLInsertFirst()	{
	solved=TRUE;
	DLInsertFirst(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLInsertFirst nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLInsertLast()	{
	solved=TRUE;
	DLInsertLast(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLInsertLast nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLFirst()	{
	solved=TRUE;
	DLFirst(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLFirst nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLLast()	{
	solved=TRUE;
	DLLast(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLLast nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLCopyFirst()	{
	solved=TRUE;
    int temp;
    DLCopyFirst(&TEMPLIST,&temp);
	if (!solved)	{
		printf("Operace DLCopyFirst nebyla implementována!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopyFirst volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}
		else	{
			printf("Operace DLCopyFirst vrací obsah %d.\n",temp);
			return(TRUE);
		}
	}
}

int test_DLCopyLast()	{
	solved=TRUE;
    int temp;
    DLCopyLast(&TEMPLIST,&temp);
	if (!solved)	{
		printf("Operace DLCopyLast nebyla implementována!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopyLast volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}
		else	{
			printf("Operace DLCopyLast vrací obsah %d.\n",temp);
			return(TRUE);
		}
	}
}

int test_DLDeleteFirst ()	{
	solved=TRUE;
	DLDeleteFirst(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDeleteFirst nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLDeleteLast ()	{
	solved=TRUE;
	DLDeleteLast(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDeleteLast nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPostDelete()	{
	solved=TRUE;
	DLPostDelete(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPostDelete nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPreDelete()	{
	solved=TRUE;
	DLPreDelete(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPreDelete nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPostInsert()	{
	solved=TRUE;
	DLPostInsert(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLPostInsert nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPreInsert()	{
	solved=TRUE;
	DLPreInsert(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLPreInsert nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLCopy()	{
	solved=TRUE;
	int temp;
  DLCopy(&TEMPLIST,&temp);

	if (!solved)	{
		printf("Operace DLCopy nebyla implementována!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopy volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}
		else	{
			printf("Operace DLCopy vrací obsah %d.\n",temp);
			return(TRUE);
		}
	}
}

int test_DLActualize()	{
	solved=TRUE;
	DLActualize(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLActualize nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLSucc()	{
	solved=TRUE;
	DLSucc(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLSucc nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPred()	{
	solved=TRUE;
	DLPred(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPred nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLActive()	{
	solved=TRUE;
	int tmp=DLActive(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLActive nebyla implementována!\n");
		return(FALSE);
	}
	else	{
		if (tmp)
			printf("Operace DLActive vrací hodnotu true.\n");
		else
			printf("Operace DLActive vrací hodnotu false.\n");
		return(TRUE);
	}
}

/*******************************************************************************
 * ZÁKLADNÍ TESTY
 * --------------
 * Za jejich úspěšné projítí získá student první část bodů za příklad.
 * Při hodnocení však budou použity rozšířené testy, které se zaměří
 * i na okrajové situace. Doporučujeme proto, aby si každý student
 * zkusitl tyto základní testy rozšířit o další zajímavé situace.
 *
 ******************************************************************************/

int main(int argc, char *argv[])	{

    printf("Dvousměrně vázaný lineární seznam\n");
    printf("=================================\n");

    printf("\n[TEST01]\n");
    printf("Inicializace seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    test_DLInitList();

    printf("\n[TEST02]\n");
    printf("Zavoláme 2x operaci DLInsertFirst a 2x operaci DLInsertLast.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    ElemValue=1;
    test_DLInsertFirst();
    ElemValue=2;
    test_DLInsertFirst();
    ElemValue=3;
    test_DLInsertLast();
    ElemValue=4;
    test_DLInsertLast();

    printf("\n[TEST03]\n");
    printf("Otestujeme funkci DLFirst při neaktivním seznamu a funkci DLActive.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLActive();

    printf("\n[TEST04]\n");
    printf("Otestujeme funkci DLLast.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    test_DLActive();

    printf("\n[TEST05]\n");
    printf("Test funkce DLCopy při aktivitě na posledním prvku\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopy();

    printf("\n[TEST06]\n");
    printf("Test funkce DLPred -- voláme 3x, aktivita zůstane na prvním prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPred();
    test_DLPred();
    test_DLPred();
    test_DLActive();

    printf("\n[TEST07]\n");
    printf("Aktualizujeme obsah aktivního prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    ElemValue=5;
    test_DLActualize();
    test_DLActive();
    test_DLCopy();

    printf("\n[TEST08]\n");
    printf("Test funkce DLSucc -- voláme 3x, aktivita zůstane na posledním prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLSucc();
    test_DLSucc();
    test_DLSucc();
    test_DLActive();

    printf("\n[TEST09]\n");
    printf("Provedeme ještě jednou DLSucc - aktivita se ztratí.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLSucc();
    test_DLActive();

    printf("\n[TEST10]\n");
    printf("Nastavíme aktivitu na začátek a pak ji zrušíme operací DLPred.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLPred();
    test_DLActive();

    printf("\n[TEST11]\n");
    printf("Pokus o DLCopy při neaktivním seznamu => ošetřená chyba.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopy();

    printf("\n[TEST12]\n");
    printf("Použití operace DLCopyFirst při neaktivním seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyFirst();

    printf("\n[TEST13]\n");
    printf("Použití operace DLCopyLast při neaktivním seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyLast();

    printf("\n[TEST14]\n");
    printf("Použití operace DLDeleteFirst při neaktivním seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteFirst();
    test_DLActive();

    printf("\n[TEST15]\n");
    printf("Použití operace DLDeleteLast při neaktivním seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteLast();
      test_DLActive();

    printf("\n[TEST16]\n");
    printf("Zkusíme DLPostDelete při aktivitě na posledním prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    test_DLPostDelete();
    test_DLActive();

    printf("\n[TEST17]\n");
    printf("Operace DLPreDelete nyní smaže první prvek.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPreDelete();
    test_DLActive();

    printf("\n[TEST18]\n");
    printf("Seznam nakonec zrušíme.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDisposeList();
    test_DLActive();

    printf("\n----------------------- konec příkladu c206 -------------------------\n");

    return(0);
}
