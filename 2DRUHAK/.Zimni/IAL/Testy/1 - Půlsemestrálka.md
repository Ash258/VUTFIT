# Zadání 2016

1. _(5b)_ Doplňte kód

    ```text
    var PomUk:TUkPrv;

    begin
    if ________
    then begin
      PomUk:= L.Frst;

      if ________
      then L.Act:= nil;

      if ________
      then begin
        L.Lst:=nil;
        L.Frst := nil
      end else begin
        L.Frst:= L.Frst^.PUk;
        L.Frst^.LUk:= nil;
      end;
    Dispose(PomUk)
    end;
    end;
    ```

1. _(3b)_ Nakreslete diagram signatury pro zásobník.
1. _(3b)_ Napište rekurzivní definici délky seznamu (max 30 slov).
1. _(1b + 1b + 1b)_ Jak by vypadal řetězec při projití tohoto binárního stromu

    ```text
    1
     \
      9
     /
    2
     \
      8
     /
    3
     \
      7
     /
    4
    ```
    PreOrder: 1928374 <br/>
    InOrder: 1234789 <br/>
    PostOrder: 4738291 <br/>

    InvPreOrder: 4738291 <br/>
    InvInOrder: 9874321 <br/>
    InvPostOrder: 1928374 <br/>

## Řešení

1. 1
    - L.Frst<>nil
    - L.Act=L.Frst
    - L.Frst=L.Lst

# Zadání 2014/2015

## Skupina A

1. Průchod binárním stromem, napsat PreOrder, InOrder, PostOrder a InvPreOrder

    ```text
      I
     /
    A
     \
      H
     /
    B
     \
      G
     /
    C
     \
      E
    ```
   PreOrder: IAHBGCE <br/>
   InOrder: ABCEGHI <br/>
   PostOrder: ECGBHAI <br/>

   InvPreOrder: IAHBGCE <br/>
   InvInOrder: IHGECBA <br/>
   InvPostOrder: ECGBHAI <br/>

1. Převedení infixového zápisu na postfix `(A-B)/(C+D)*(E-F)+(G+H)*I/J=` == `AB- CD+ / EF- * GH + I * J / +`
1. Definice příkazu
1. Sekvenční vyhledávání v poli Tab s adaptivním uspořádáním podle četnosti vyhledávání se zarážkou. Počet prvků pole N, pro výměnu prvků použíte ":=:" . Všechny prázdné kolonky nemusí být použity!

    ```text
    begin
      i:=1;
      ___________
        while K<>T.Tab[i].Klic do i:=i+1;
        _vynechaný řáděk_
        if i<>(N+1)
          if i<>1
            ________________
          end
          Search := true;
        end
        ________________
    end;
    ```

## Skupina B

1. Doplnit kód Queu a Remove (přednáška 5, strana 27)
1. Převedení příkladu z infixu do postfixu (přednáška 5, strana 6)
1. Popsat pseudopříkaz vlastními slovy, max 30 slov
1. Průchod binárním stromem, napsat PreOrder, InOrder, PostOrder a InvPreOrder (přednáška 5, strana 62)

## Skupina C

1. _(4b)_ Doplnit části kódu dijsktrova algoritmu pro řazení. 2 podmínky pro klíče pro nalezení prvku nejvíce vlevo.
1. _(3b)_ Z infixu na postfixu `((N+M*I)*(O*P-Q)+(R*S+T*U))/V=` == `NMI *+ OP* Q - * RS* TU* + + V /`
1. _(3b)_ Definice zaslepení v tabulce s rozptýlenými položkami.
1. _(4b)_

    ```text
         J
       /   \
      I     K
     / \   / \
    H   G  L  M
       / \    /
      F   E  N
    ```

   PreOrder: JIHGFEKLMN <br/>
   InOrder: HIFGEJLKNM <br/>
   PostOrder: HFEGILNMKJ <br/>

   InvPreOrder: JKMNLIGEFH <br/>
   InvInOrder: MNKLJEGFIH <br/>
   InvPostOrder: NMLKEFGHIJ <br/>
