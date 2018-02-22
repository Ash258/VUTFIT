# Vzory

## Návrhové vzory

- Sada řešení, které řeší určité problémy.
- Usnadňují znovupoužitelnost, rošiřitelnost.

### Singleton

- Zajišťuje, že v systému je pouze jediná instance objektu.
- Zapouzdření konstruktoru a vytvoření statické metody, která vrátí **vždy stejnou instanci**.

### Abstract factory

- Vytváření příbuzných nebo závislých objektů bez specifikace konkrétní třídy.
- Možnost výměny celé rodiny objektů bez změny kódu, jen výměnou implementací.

### Command

- Zapouzdřit požadavek jako objekt.
- Oddělené logiky pro provedení akce, `invoker` pouze invokuje `command`, který deleguje akci na `recievera`.

## Architektonické vzory

> Zaměřují se na organizaci systému.

### MVC

- Oddělení dat od jejich prezentace.

### Multitier architecture

- Rozdělení systému do vrstev, kde každá má svou zodpovědnost.

#### Výhody

- Výměna jednotlivých vrstev.

#### Nevýhody

- Větší závislost objektů, více objektů.

### Klient-Server

> Funkcionalita je schována za serverem ==> Lze poskytnout aktuální data všem účastníkům.
