
/* Hlavičkový soubor pro c402.c - nerekurzívní implementace operací nad BVS
obsahuje jednak nutné knihovny a externí proměnné, ale rovněž definici datových
typů, se kterými se pracuje v příslušných úlohách. Nemodifikovat! */

/* ********************** SOUBOR S HLAVIČKOU ********************** */
/* ********************** ------------------ ********************** */

/*  Předmět: Algoritmy (IAL) - FIT (Fakulta Informačních Technologií)
    Hlavička pro soubor: c402.c
    Vytvořil: Martin Tuček, září 2005
    Upravil: Bohuslav Křena, listopad 2009                           
    upravil: Karel Masařík, říjen 2013                               
    upravil: Radek Hranický, říjen 2014                              
    upravil: Radek Hranický, říjen 2015                              
    upravil: Radek Hranický, říjen 2016                              */
/* ***************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdbool.h>

#define FALSE 0
#define TRUE 1
#define MAXSTACK 30                      /* maximální počet prvků v zásobníku */

extern int solved; 			                  /* indikace, zda byla funkce řešena */

typedef struct tBTNode	{                                      /* uzel stromu */
    int Cont;                                         /* užitečný obsah uzlu  */
    struct tBTNode * LPtr;                                  /* levý podstrom  */
    struct tBTNode * RPtr; 	  	                            /* pravý podstrom */
} *tBTNodePtr;                                     /* ukazatel na uzel stromu */

/* pomocné zásobníky */
typedef struct	{                          /* zásobník hodnot typu tBTNodePtr */
    tBTNodePtr a[MAXSTACK];
    int top;
} tStackP;

typedef struct {                                 /* zásobník hodnot typu bool */
    bool a[MAXSTACK];
    int top;
} tStackB;

/***prototypes***/
void BTInit (tBTNodePtr * );
void BTInsert (tBTNodePtr *, int );

void Leftmost_Preorder(tBTNodePtr, tStackP *);
void BTPreorder(tBTNodePtr );

void Leftmost_Inorder(tBTNodePtr, tStackP *);
void BTInorder(tBTNodePtr );

void Leftmost_Postorder(tBTNodePtr, tStackP *, tStackB *);
void BTPostorder(tBTNodePtr );

void BTDisposeTree(tBTNodePtr *);
/********end of prototypes******/

/* konec c402.h */
