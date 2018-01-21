# Zadání 2016 / 2017

## Skupina B

1. _(5b)_ Doplnit kód sekvenčního vyhledávání v poli se zarážkou a adaptivní rekonfiguraci pole podle četnosti
    - Max 30 slov
1. _(4b)_ Aktualizační semantika funkce insert, slovy
1. _(3b)_ Co je to výraz
    - Max 20 slov
1. _(5b)_ Pole 10 prvků, vytvořit Heap a zapsat do tabulky
    - Heap pro heap sort, v kořenu největší prvek, byla tam písmenka A až J (10 prvků).
    - Aby v kořeni byl nejmenší prvek (skupina A)
    - Aby v kořeni byl největší prvek (skupina B)

    | i     | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 10    |
    | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
    | x     | G     | D     | F     | E     | A     | I     | C     | J     | H     | B     |
    | y     |       |       |       |       |       |       |       |       |       |       |

1. _(6b)_ 10 prvků, nakreslit BVS, pak překreslit po odstranění 1. uzlu
    - BVS byl se zpětnými ukazateli
    - Postupně se vkládaly prvky a měl se nakreslit utvořený strom
    - Poté se jeden prvek odstranil (měl jednoho potomka, takže se to jen propojilo podle druhého pravidla) a znovu strom zakreslit
1. _(5b)_ Doplnit kód (Rekursivní ekvivalence dvou struktur BS)
    - Sice to bylo "doplnění" - ale prakticky tam chybělo tak 90% kódu, byl tam velký čtverec, kde se to mělo doplnit. Takže radši naučit celé
1. _(8b)_ Upravit kód siftdown u heapsortu, tak aby se nepřesouvaly položky, ale indexy v pomocném poli
    - Byly tam očíslované řádky - bylo potřeba napsat číslo řádku a jak se má změnit
1. _(5b)_ Popsat slovně mechanismus odstranění prvku daného ukazatelem v jednosměrném vázaném listu bez použití cykly
    - Napsat všechny způsoby
1. _(5b)_ Máme strukturu osoba, která obsahuje - DEN, MĚSÍC a ROK narození a pohlaví (M/Ž). Našim úkolem bylo napsat pořadí jednotlivých operací třídění tak, abychom:
    - Seřadili lidi podle data narozenin (narozeniny, ne datum narození !!! čili rok nehraje roli)
    - Pokud je datum narození stejné, tak má přednost žena před mužem
    - Pokud jsou obě ženy, tak má přednost starší (s nižším rokem)
    Dále napsat, jakým typem sortu (probíraným v IAL) bychom to řešili a proč.
1. _(5b)_ Dijskrův důkaz
    - Napsat nějakou nejslabší podmínku tak, aby u x=x-1 platilo, že podmínka bude cosi na druhou.. pak tam bylo něco ve smyslu wp("x=x-1", a tu ta podmínka na druhou).
    - Něco jako: `Napsat nejslabsi podminku wp("a:=a+b; b:=a-b; a:=a-b", (a=A) and (b=B)). Vysledek (b=A) and (a=B).`
    > V opoře je napsáno, že to nebude zkoušeno a že je to na úrovni magisterského studia, tak pozor, magistrobakaláři 😂

## Skupina A

1. Opravit kód Search pro TRP (i chybějící řádky)
1. Nakreslit diagram pro TRP
1. K čemu slouží špatné šipky u stromu se špatnými ukazately
1. Doplnit kód rekurzivního kopírování stromu
1. Doplnit kód pro frontu: Remove, QFull
1. Vymazání prvku v lineárním seznamu bez použítí cyklu, které je daný ukazatelem - Popsat
1. Nakreslit strom po odstranění 3 prvků v pořadí `8, 4, 10` (Levá metoda)
    ```text
    　 　  8
    　　 / 　\
    　 6 　　 10
    　/　\ 　 　 \
    1 　 3 　　 14
    　  / \　  /
    　 4 　7　13
    ```
1. Dijkstra - teorie
1. Doplnit tabulku pro heap sort

    | i   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  |
    | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
    | x   | G   | D   | F   | E   | A   | I   | C   | J   | H   | B   |
    | y   |

# Zadání 2015/2016

## Skupina C

1. Přepsat kód Shell sortu tak, aby se nepřesouvaly hodnoty, ale indexy v poli Por[]
1. Napsat jak budou čísla seřazena po Quick sortu + kde skončily indexy i a j

    | i    | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  |
    | :--- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
    | x    | 6   | 7   | 9   | 0   | 4   | 3   | 5   | 8   | 1   | 2   |

1. Popsat BVS se zpětnými ukazateli + napsat rozdíly při implementaci oproti obyč BVS
1. Rekurzivně délka seznamu
1. Mnohacestné vyvážené setřiďování ...8 pásek, 1000 souborů
1. Doplnit EQTS (rekurzivní zápis ekvivalence struktur dvou stromů) (ne BS)
1. Slovně popsat preinsert (max 30 slov)
1. TRP pro číslo 59
    - Doplnit tabulku pro 2HASH + napsat kolik kroků provedly rozptylovací funkce
    - Brentova varianta
