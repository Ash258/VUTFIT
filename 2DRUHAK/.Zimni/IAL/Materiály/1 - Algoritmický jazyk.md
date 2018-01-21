# Syntax

Soubor pravidel, která určují správnost jazykové konstrukce.

# Sémantika

Popis účinků, které jsou výsledkem provedení jazykové konstrukce v době výpočtu.

# Příkaz

Nejmenší samostatný prvek programu, který vyjadřuje vykonání nějaké činnosti. <br />
Pokyn k akci během vykonávání programu.

# Pseudopříkaz

Pokyn k akci během překladu.

# Dyadické == Binární

# Algoritmus

Konečná, uspořádaná množina úplně definovaných pravidel pro vyřešení specifického problému.

## Správnost algoritmu

Pro libovolný vstup skončí s korektním výstupem.

## Vlastnosti algoritmu

- Konečnost
- Obecnost
- Determinovanost
- Resultativnost
- Elementárnost

# Datové typy a struktury

**Datové typy** se dělí na **jednoduché**, **strukturované** a **typ ukazatel**.
Způsob uložení a organizace dat za účelem umožnění přístupu k datům a jejich modifikaci.
Usnadnění řešení problémů.

## Ordinální typ

Jednoduchý typ, pro jehož každou hodnotu (s výjimkou největší) existuje právě jedna následující a (s výjimkou nejmenší) právě jedna předcházející hodnota.

### Operace

> Ekvivalence, přiřazení

## Skalární typ

Jednoduchý typ, pro jehož každé dva prvky lze stavot, zda jsou si rovny nebo zda je jeden z nich menší nebo větší.

## Strukturovaný datový typ

Skládá se z komponent jiného typu (kompoziční typ). Pokud jsou všechny komponenty stejného kompozičního typu jedná se o homogenní typ.
Komponenty homogenního typu jsou **položky (items)**, heterogenního typu **složky (components)**
**Strukturovaná hodnota** je definovaná tehdy, když jsou definované hodnoty všech komponent dané struktury.

# Pole

Homogenní ortogonální (provoúhlý) datový typ. Jednorozměrné == **Vektor**, dvojrozměrné == **Matice**.

# Příkazy

## Jednoduché

## Strukturované

### Složený příkaz

Sekvence příkazů oddělených středníky, uzavřená mezi příkazové závorky _begin_ a _end_.

> Podmíněný příkaz, alternativní příkaz (úplný podmíněný příkaz), vícečetný alternativní příkaz case.

### Příkazy cyklu

- Počítané == **Explicitní**
- Nepočítané == **Implicitní**
- Nekonečné

## Příkaz procedury

### Vedlejší jev

Změna hodnoty globální proměnné uvnitř těla procedury.

# Složitosti algoritmů

## Asymptotická časová složitost

Vyjadřuje se porovnáním algoritmu s jistou funkcí pro N blížícímu se nekonečnu.

### Omikron

Vyjadřuje horní hranici časového chování algoritmu.

### Omega

Vyjadřuje dolní hranici časového chování algoritmu.

### Theta

Vyjadřuje třídu časového chování algoritmu.
