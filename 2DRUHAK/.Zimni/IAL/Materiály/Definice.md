# Definice

## Rekurzivní definice

### Ekvivalence

Dva seznamy jsou ekvivalentní, když jsou oba prázdné nebo když se rovnají jejich první prvky a také jejich zbytky.

### Délka seznamu

Je-li seznam prázdný, má délku **0**. V jiném případě je jeho délka 1 + počet zbývajích položek.

### Relace dvou seznamů

Výsledek operace „první seznam je menší než druhý seznam“ je **true** když první seznam je prázdný a druhý neprázdný nebo když první prvek prvního seznamu je menší než první prvek druhého seznamu nebo když první prvek prvního seznamu je roven prvnímu prvku druhého seznamu a současně zbytek prvního seznamu je menší než zbytek druhého seznamu. Jinak je výsledek operace **false**.

### Binární strom

Strom je buď prázdný, nebo se sestává z jednoho uzlu znaného kořen a dvou binárních podstromů.

### Binární vyhledávací strom

Je uspořádaný binární strom pro jehož každý uzel platí, že klíče všech uzlů levého podstromu jsou menší než klíč v uzlu a klíče všech uzlů pravého podstromu jsou větší než klíč v uzlu.

## Aktualizační sémantika operace insert

**TInsert(T,K,Data)** - Vložení položky se složkami `K` a `Data` do tabulky `T`.
Pokud tabulka `T` již obsahuje položku s klíčem `K` dojde k přepisu datové složky `Data` novou hodnotou.
