# Hodnocení

Login hodnoceného studenta: **xcaber00**
Identifikátor týmu: **team_125**
Procentuální podíl pro xcaber00: **25%**

Následující procentuální hodnocení je **FINÁLNÍ** hodnocení Vašeho projektu.

Projekt byl nejdříve automaticky přeložen a na výsledném binárním souboru byly spuštěny testy. Testy jsou rozděleny do několika kategorií. Podle výsledků jednotlivých testů byla stanovena procentuální úspěšnost Vašeho překladače v jednotlivých kategoriích a z těchto hodnot odvozeny body. Do WIS se importují body zaokrouhlené na jednotky. Testovací příklady nebudou uveřejněny.

Hodnocení je individuálně vygenerováno pro každého studenta a následně automaticky rozesláno na školní email.

## Hodnocené části

1. Automatické testy a manuální hodnocení implementace:
    - Zahrnuje automatické testy včetně testů registrovaných rozšíření
        - Hodnocení implementace předepsané metody syntaktické analýzy.
        - Dodržení varianty zadání v implementaci (ial.c).
        - Přehlednost a kvalita kódu.
    - Následuje orientační ceník za nejčastější chyby a prohřešky včetně několika zkratek, které se mohou vyskytovat v komentářích hodnocení implementace:
        - `NOHEAD` = chybí záhlaví ve zdroj. souborech: **-0,50 b**
        - `NOAUTHORS` = chybí jména autorů v záhlaví: **-0,20 b**
        - `PMGP` = nadměrné množství globálních proměnných: **-0,20 b** (tolerována globální proměnná pro chybu, tabulku symbolů a seznam instrukcí)
        - `HEADCODE` = kód v hlavičkových souborech místo v .c souborech: **-0,15 b**
        - `LCOM++` = téměř žádné komentáře: **-0,30 b**
        - `LCOM` = málo komentářů: **-0,10 b**
        - `GCOM` = příliš mnoho komentářů: **-0,10 b**
        - `VUL` = vulgarismy: **-0,30 b**
        - `NORS/PA` = SA analýza chybí: **-0,60 b**
        - `NOPSA` = SA analýza výrazů chybí: **-0,60 b**
        - `SYA` = použitý Shunting-Yardův algoritmus: bez postihu
        - `PC` = analýza výrazů pomocí metody precedence-climbing: bez postihu
        - `IAL+` = TS v jiném souboru než symtable.(c|h): **-0,10 b**
        - `NOTS/IAL++` = chybí TS dle zadání: **-0,60 b**
1. Prémiové body, korekce, malus: rychlostní soutěž, aktivita na fóru, pozdní odevzdání, formální nedostatky.
1. Dokumentace (viz zadání a seznam zkratek níže).
    - Následuje seznam zkratek, které se mohou vyskytnout v komentářích k hodnocení dokumentace:
        - `KA` = chyby v KA, především větší míra nedeterminismu, chybějící důležité lexémy (např. ošetření komentářů atp.)
        - `strukt.` = nedostatky ve struktuře dokumentu (nejčastěji chybějící závěr)
        - `PSA` = chybějící nebo nedostatečný popis precedenční syntaktické analýzy
        - `RP` = chybějící popis rozdělení práce
        - `GK` = chybějící popis generování kódu
        - `1S` = formální nedostatky na titulní straně
        - `LL` = chyby a nedostatky v LL tabulce
        - `typ.` = typografické nedostatky (nejčastěji text nebyl zarovnán do bloku)
        - `stručnost` = přílišná stručnost (informační strohost) dokumentace
        - `ref.` = připomínky ke způsobu uvedení zdrojů/literatury
        - `SA (SyA)` = nedostatečný/chybějící popis syntaktické analýzy
        - `gram.` = gramatické chyby
        - `ČJ+SJ` = míchání češtiny a slovenštiny v dokumentaci
    - Za většinu prohřešků bylo podle závažnosti strhnuto 0,2 až 0,7 bodu.
    - Poznámky k hodnocení dokumentací jsou vesměs řazeny dle klesající závažnosti.

V případě, že nebyl Váš projekt přeložen úspěšně, je přiložen log dekomprimace odevzdáného archivu a kompilace projektu.

Termíny reklamací budou vypsány ve WIS.

- Vaše hodnocení části 1): **19,6 bodů**
    - Komentář hodnocení části 1): Bez komentáře
- Vaše hodnocení části 2): **0 bodů**
    - Komentář hodnocení části 2): Bez komentáře.
- Vaše hodnocení části 3): **3 bodů**
    - Komentář hodnocení části 3): KA, SA, typ., strukt., LL

Pokud jste obdrželi výsledek částí 1) + 2) mimo interval <0,15+5> bodů, tak bude oříznut, tak že získáte za implementaci alespoň 0 a ne více jak 15+5 bodů.

## Procentuální hodnocení modulů překladače

- Lexikální analýza (detekce chyb): **100% (204/204)**
- Syntaktická analýza (detekce chyb): **98% (209/213)**
- Sémantická analýza (detekce chyb): **98% (311/316)**
- Běhové chyby (detekce): **100% (20/20)**
- Interpretace přeloženého kódu: **78% (642/813)**
- CYCLES 0% (0/150)
- UNARY **100% (50/50)**
- BASE **100% (50/50)**
- FUNEXP **100% (150/150)**
- BOOLOP **100% (100/100)**
- IFTHEN **100% (50/50)**
- GLOBAL **84% (84/100)**
- SCOPE **100% (100/100)**
- Celkem bez rozšíření: **88% (1366/1546)**

# Info

>>>
Překladač bude načítat řídicí probram v jazyce IFJ17 ze standardního vstupu a generovat výsledný mezikód v jazyce IFJcode17 na standardní výstup.

Všechna chybová hlášení, varování a ladicí výpisy provádějte na standardní chybový výstup
>>>

## Návratové hodnoty

- 0 - Překlad bez chyb.
- 1 - Chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému).
- 2 - Chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu).
- 3 - Sémantická chyba v programu – nedefinovaná funkce/proměnná, pokus o redefinici funkce/proměnné, atd.
- 4 - Sémantická chyba typové kompatibility v aritmetických, řetězcových a relačních výrazech, příp. špatný počet či typ parametrů u volání funkce.
- 6 - Ostatní sémantické chyby.
- 99 - Interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti, atd.).

## Jazyk IFJ17

> Case-insensitive!!

### Klíčová slova

> As, Asc, Declare, Dim, Do, Double, Else, End, Chr, Function, If, Input, Integer, Length, Loop, Print, Return, Scope, String, SubStr, Then, While.

#### Reserved

> And, Boolean, Continue, Elseif, Exit, False, For, Next, Not, Or, Shared, Static, True.

### Proměnné

> Mají předem určený datový typ svou deklarací / definicí.

### Identifikátor

> Je definován jako neprázdná posloupnost číslic, písmen (malých i velkých) a znaku podtržítka (’_’) začínající písmenem nebo podtržítkem.

### Číselný literál

> Jsou sice nezáporné, ale výsledek výrazu přiřazený do proměnné již záporný být může.

### Celočíselný literál

- **C-int**
- Neprázdná posloupnost číslic.
- Vyjadřuje hodnotu celého nezáporného čísla v desítkové soustavě.
    - Přebytečné počáteční číslice 0 jsou ignorovány.

### Desetinný literál

- C-double
- Vyjadřuje nezáporná čísla v desítkové soustavě.
    - Přebytečné počáteční číslice 0 jsou ignorovány. (Pro celou část desetinného literálu)
- Je tvoře celou a destinnou částí || Celou a exponentem || Celou, desetinou a exponentem
- Celá i desetinná část je tvořena neprázdnou posloupností číslic.
- Oddělovač == desetinná tečka **`.`**
- **Exponent**
    - Celočíselný
    - Začíná znakem **`e`** nebo **`E`**
    - Následuje nepovinné znaménko **'+'** nebo **'-'**
    - Poslední část je neprázdná posloupnost číslic.
- Mezi jednotlivými částmi nezmí být jiný znak.

### Řetězcový literál

- Začíná `!` (ASCII = 33) a následuje samotný řetězec oboustranně ohraničen dvojitými uvozovkami `""` (ASCII = 34)
- Tvoří jej libovolný počet znaků zapsaných na jediném řádku programu.
- Lze i prázdný `!""`
- Znaky, s ACII s hodnotou větší než 31 (mimo `"`), lze zapisovat přímo.
    - Některé další znaky lze escapovat
        - Jejich význam se shoduje s odpovídajícími znakovými konstantami jazyka FreeBASIC
        - `\"`
        - `\n`
        - `\t`
        - `\\`
- Znak v řetězci může být zadán také pomocí obecné escape sekvence `\ddd`, kde **ddd** je třímístné dekadické číslo od 001 do 255
- Délka řetězce není omezena (pouze pamětí)

`!"Ahoj\nSve'te\\\034"` se interpretuje jako:

```text
Ahoj
Sve'te\".
```

> Neuvažujte řetězce, které obsahují vícebajtové znaky.

### Datové typy

- Pro jednotlivé uvedené literály jsou označeny **Integer**, **Double**, **String**.
- Typy se používají v definicích proměnných a funkcí a u sémantických kontrol.

### Term

> Libovolný literál (int, double, string) nebo identifikátor proměnné.

### Komentáře

#### Řádkové

- Začíná znakem apostrof `'` (ASCII = 39)
- Za komentář je považováno vše, co následuje až do konce řádku

#### Blokové

- Začíná dvojicí znaků `/'` a je ukončen první následující dvojicí znaků `/'` ==> Hierarchické vnoření blokových komentářů není podporováno.

## Struktura IFJ17

> IFJ17 je strukturovaný programovací jazyk podporující deklarace a definice proměnných a uživatelských funkcí, základní řídicí příkazy a příkaz přiřazení a volání funkce včetně rekurzivního. Vstupním bodem řídicího programu je hlavní tělo programu.

### Základní struktura

> Program se zkládá ze sekvence deklrací a definic užřivatelských funkcí a jako jeho **poslední sekce** následuje hlavní tělo programu. V těe definice funkce i v hlavním těle programu se pak může nacházet libovolný (i nulový) počet definic lokální proměnných a příkazů jazyka IFJ17.

- Konstrukce jsou (až na výjimky) jednořádkové a jsou vždy ukončeny znakem konce řádku (**EOL**).
    - U víceřádkových jsou dodatečné znaky EOL explicitně uvedeny.
        - Vně zmíněných konstrukcí je znak EOL brán jako tzv. bílý znak. Je tedy například možné pro zpřehlednění kódu vložit mezi dva příkazy prázdný řádek.
- Ostatní bílé znaky (mezery, tabulátory, komentáře) se mohou vyskytovat v libovolném množství mezi všemi lexémy, i na začátku a na konci zdrojového textu.

### Hlavní tělo programu

- Hlavní tělo je uvozeno klíčovým slovem **Scope**
- Následují sekvence definic proměnných a dílčích příkazů ukončených koncem řádku (může být i prázdná).
- Celá sekvence je ukončena pomocí **End Scope**
    - V rámci základního zadání není třeba podporovat zanořování bloků.

### Definice proměnných

- Jsou pouze lokální!!
    - Proměnné a parametry funkcí mají rozsah v daném bloku / funkci, kde byly definovány
- Pro každou definici proměnné se používá: **Dim** _id_ **As** _datový\_typ_ || **Dim** _id_ **As** _datový\_typ_
- Definice obsahuje identifikátor, určení datového typu a případně nepovinnou inicializaci pomocí výrazu.
- Číselné proměnné jsou implicintě inicializovány na hodnotu 0 (0.0)
    - Řětězcové na prázdný řetězec `!""`
- Nelze definovat proměnnou stejného jména, jako má jiná proměnná v tomtéž bloku nebo některá již deklarovaná/definovaná funkce.
- Každá v programu použitá proměnná musí být definována, jinak se jedná o sémantickou chybu 3.

### Deklarace a definice uživatelských funkcí

- Každá funkce musí být definovná právě jednou.
    - Deklarovaná maximálně jednou.
- Deklarace funkcí slouží pro vzájemné rekurzivní volání dvou či více funkcí.
- Definice nebo alespoň dekrlarace funkce musí být vždy k dispozici před prvním voláním.
- Deklarace/definice jednotlivých formálních parametrů jsou odděleny čárkou (`,`), za poslední z nich se čárka neuvádí.
    - Seznam může být i prázdný.
    - Deklarace parametru má tvar: `id As datový_typ`
- Identifikátor formálního parametru v deklaraci funkce a v definici funkce se může lišit, ale počty a typy parametrů musí souhlasit.
- Parametry jsou vždy předávány hodnotou.

#### Deklarace

> **Declare Function** _id_ (seznam parametrů) As _návratový\_typ\_funkce_

#### Definice

```Basic
Function id (seznam_parametrů) As návratový_typ_funkce EOL
    sekvence_definic_proměnných_a_příkazů
End Function
```

### Syntaxe a sémantika příkazů

#### Příkaz přiřazení

`id = výraz`

- Příkaz provádí přiřazení hodnoty pravého operandu _výraz_ do levého operandu _id_.
- Levý operand musí být vždy pouze proměnná (l-hodnota).
- Oba operandy musí být stejného nebo kompatibilního typu dle implicitních konverzí.

#### Příkaz pro načtení hodnot

`Input id`

- Nejprve se na standardní výstup vypíše řetězec `!"? "`.
- Ze standardního vstupu se našte hodnota dle typu proměnné.
    - Úvodní bílé znaky ignorovány
- Vstup je ukončen odřádkováním, které není součástí načtené hodnoty.
    - Jsou ignorovány stejně jako znaky vyskytující se za prvním nevhodným znakem (včetně) pro daný typ.
- Načtená hodnota je uložena do proměnné (po případných konverzích).
    - Je-li id typu Integer, ale načtená hodnota je desetinné číslo, tak je načtená hodnota implicitně zkonvertována místo načtení pouze celočíselné části vstupu.
- Hodnota typu String může být ohraničena uvozovkami, přičemž ohraničující uvozovky do řetězce nepatří a znaky za ukončující ovozovkou jsou ignorovány.
    - Načítaný řetězec nepodporuje escape sekvence.
- V případě chybějící hodnoty na vstupu nebo jejícho špatného formátu bude uložena výchozí hodnota (viz. [Definice](#definice-prom%C4%9Bnn%C3%BDch "Definice"))

#### Příkaz pro výpis hodnot

`Print výraz1; výraz2;...; výrazn;`

- Postupné vyhodnoceníjednotlivých výrazů.
- Vypisuje jejich hodnoty na standardní výstup ihned za sebe, bez jakýchkoliv oddělovačů, v patřičném formátu.
    - Integer == '% d'
    - Double == '% g'
- Musí obsahovat aspoň jeden výraz

#### Podmíněný příkaz

```Basic
If výraz Then EOL
    sekvence_1
Else EOL
    sekvence_2
End If
```

- Nejdříve se vyhodnotí daný výraz.
- Pokud je pravdivý vykoná se sekvence\_1, jinak sekvence\_2
    - Pokud se nejedná o pravdu či nepravdu ==> Chyba 4

#### Příkaz cyklu

```Basic
Do While výraz EOL
    sekvence
Loop
```

- Opakuje provádění sekvence příkazů sekvence tak dlouho, dokud je hodnota výrazu pravdivá.

#### Volání vestavěné či užeivatelem definované funkce

`id = název_funkce(seznam_vstupní_parametrů)`

- Seznam\_vstupních\_parametrů je seznam _termů_ oddělených čárkami.
    - Může být i prázdný
- Příkaz zajistí předání parametrů hodnotou (včetně případných implicitních konverzí) a předání řízení do těla funkce.
- Pokud se liší počet parametrů == Chyba 4
- Po návratu z těla funkce dojde k uložení výsledku a pokračování běhu programu bezprostředně za příkazem volání právě provedené funkce.

#### Příkaz návratu z funkce

`Return výraz`

- Příkaz může být použit pouze v těle funkcí.
- Dojde k vyhodnocení výrazu, okamžitému ukončení provádění těla funkce a návratu do místa volání, kam funkce vrátí návratovou hodnotu.
    - Pokud typ výsledku neodpovídá návratovému typu funkce, dojde k implicitní konverzi.
        - V případě nekompatibility se jedná o sémantickou chybu.
    - Není-li proveden příkaz Return před dokončením provádění funkce, vrací se implicitní hodnota dle návratového typu funkce.

### Výrazy

> Jsou tvořeny **závorkami, termy a binárními aritmetickými, řetězcovým a relačními operátory**.

- Je-li nutné, jsou prováděny implicitní konverze operandů, parametrů funkcí i výsledků výrazů či funkcí.
- Možné implicitní konverze datových typů jsou:
    - Integer -> Double
    - Double -> Integer (zakrouhlení s preferencí sudé číslice)
- Nesprávné kombinace datových typů (včetně případných povolených konverzí) jsou považovány za chybu 4.

#### Aritmetické, řetězcové a relační operátory

> **+, -, \*, /, \\, <, >, <=, >=, =, <>**

- Jsou-li oba operandy typu **Integer**, je i výsledek typu **Integer**.
- Je-li jeden či oba operandy typu Double, výsledek je též typu Double.
- Operátor `+` navíc provádí se dvěma operandy typu **String** jejich konkantenaci.
- Operátor `/` značí dělení dvou číselných operandů, jehož výsledek je bez ohledu na případnou celočíselnost oprerandů vždy **Double**.
- U operátoru `\` se jedná o celočíselné dělení stejně jako v jazyce FreeBASIC.
    - Pracuje pouze s operandy typu **Integer**
    - Výsledek je také Integer
- Pro operátory `<, >, <=, >=, =, <>` platí, že výsledkem porovnání je pravdivostní hodnota.
    - Pracují s operandy stejného typu (Integer, Double nebo String)
    - Je-li jeden operand Iteger a druhý Double, tak je Integer konvertován na Double.
    - U řetězců se porovnání provádí **lexikograficky**
        - Bez rozšíření **BOOLOP** není s výsledkem porovnání možné dále pracovat a lze jej využít poze up `If` a `Do While`

#### Priorita operátorů

> Lze upravit závorkováním.

| Priorita | Operátor             | Asociativita |
| -------- | -------------------- | ------------ |
| 1        | *, /                 | levá         |
| 2        | \                    | levá         |
| 3        | +, -                 | levá         |
| 4        | =, <>, <>, <=, >, >= | žádná        |

### Vestavěné funkce

> Překladač bude poskytovat některé základní vestavěné funkce, které bude možné využít v programech jazyka IFJ17.

- Pro generování kódu vestavěných funkcí lze výhodně využít specializovaných instrukcí jazyka IFJcode17.

#### Length(s As String) As Integer

> Vrátí dělku (počet znaků) řetězce s. `Length(!"x\nz") = 3`

#### SubStr(s As String, i As Integer, n As Integer) As String

- Vrátí podřetězec
- _i_ - začátek požadovaného podřetězce (počítáno od 1)
- _n_ - délka podřetězce
- Je-li _s_ prázdné nebo `i<=0`, vrací prázdný řetězec.
- Je-li `n < 0` nebo `n > Length(s) - i`, jsou jako řetězec vráceny od i-tého znaku všechny zvývající řetězce.

#### Asc(s As String, i As Integer) As Integer

> Vrátí ordinální hodnotu (ASCII) znaku na pozici _i_ v řetězci. Je-li pozice mimo, vrací se 0

#### Chr(i As Integer) As String

> Vrátí jednoznakový řetězec se znakem, jehož ASCII kód je zadán parametrem i. Nedefinováno pro  _i_ mimo <0;255>

### Tabulka symbolů

- Implementace abstraktní datové stuktury, která je ve variantě zadání
    - I) Pomocí binárního vyhledávacího stromu
    - II) Pomocí tabulky s roptýlenými položkami
- Implementace tabulky bude uložena v souboru `symtable.c` (popřípadě `symtable.h`)

### Příklady

#### Faktoriál iterativně

```Basic
/' Program 1: Vypocet faktorialu (iterativne) '/
/' Vcetne ukazky case-insensitive vlastnosti jazyka IFJ17 '/

scope 'Hlavni telo programu
        Dim a As Integer
        DIM vysl AS INTEGER

        PrinT !"Zadejte cislo pro vypocet faktorialu";
        InpuT A
        If a < 0 THEN
                print !"\nFaktorial nelze spocitat\n";
        ELSE
                Vysl = 1
                Do WHile A > 0
                        VYSL = vysl * a
                        a = A - 1
                LooP
                Print !"\nVysledek je:" ; vYsl ; !"\n";
        end IF
END SCOPE
```

#### Faktoriál rekurzivně

```Basic
/' Program 2: Vypocet faktorialu (rekurzivne) '/

Declare Function factorial (n As Integer) As Integer
Function factorial (n As Integer) As Integer
        Dim temp_result As Integer
        Dim decremented_n As Integer
        Dim result As Integer
        If n < 2 Then
                result = 1
        Else
                decremented_n = n - 1
                temp_result = factorial(decremented_n)
                result = n * temp_result
        End If
        Return result
End Function

Scope 'Hlavni telo programu
        Dim a As Integer
        Dim vysl As Integer

        Print !"Zadejte cislo pro vypocet faktorialu";
        Input a
        If a < 0 Then
                Print !"\nFaktorial nelze spocitat\n";
        Else
                vysl = factorial(a)
                Print !"\nVysledek je:" ; vysl ; !"\n";
        End If
End Scope
```

#### Práce s řetězci a vestavěnými funkcemi

```Basic
/' Program 3: Prace s retezci a vestavenymi funkcemi '/

Scope 'Hlavni telo programu
Dim s1 As String
Dim s2 As String
Dim s1len As Integer

s1 = !"Toto je nejaky text"
s2 = s1 + !", ktery jeste trochu obohatime"
Print s1; !"\n"; s2; !"\n";
s1len = Length(s1)
s1len = s1len - 4 + 1
s1 = SubStr(s2, s1len, 4)
Print !"4 znaky od "; s1len; !". znaku v \""; s2; !"\":"; s1; !"\n";
Print !"Zadejte serazenou posloupnost vsech malych pismen a-h, ";
Print !"pricemz se pismena nesmeji v posloupnosti opakovat";
Input s1
Do While (s1 <> !"abcdefgh")
        Print !"\nSpatne zadana posloupnost, zkuste znovu";
        Input s1
Loop
End Scope
```

### Testování

- Stáhnout ze skladu dokumentů [IFJ17.bas](https://wis.fit.vutbr.cz/FIT/st/course-files-st.php?file=%2Fcourse%2FIFJ-IT%2Fprojects%2Fifj17.bas&cid=12153 "IFJ17.bas")
- Odlišnosti IFJ17 a Basicu budou na wiki IFJ
- V dockeru nebo na marlinu něco jako:

```bash
cat ifj17.bas program.ifj > tmp.bas
fbc tmp.bas
./tmp < test.in > test.out
```

### Cílový jazyk IFJcode17

- IFJcode17 je mezikód.
- Zahrnuje instrukce tříadresné (3 argumenty) a zásobníkové (typicky bez parametrů a pracují s hodnotami na datovém zásobníku)
- Každá instrukce se skládá z operačního kódu (klíčové slovo as názvem instrukce)
    - Case insensitive
- Zbytek instrukce tvoří operandy, které jsou case sensitive
- Operandy odděluje libovolným nenulovým počtem mezer či tabulátorů.
- Odřádkování slouží pro oddělení jednotlivých instrukcí, takže na každém řádku je maximálně jedna instrukce a není povolenu jednu instruckci zapisovat na více řádků.
- Každý operand je tvořen proměnnou, konstantou nebo návěštím.
- Jsou podporovány jednořádkové komentáře začínající `#`.
- Kód v IFJcode17 začíná řádkem s tečkou následovanou jménem jazyka: `.IFJcode17`

#### Interpret ic17int

`ic17int`

##### Návratovky

- 0 - Bez chyb
- 50 - Chybně zadané vstupní parametry na příkazovém řádku při spouštění interpretu.
- 51 - Chyba při analýze (lexikální, syntaktická) vstupního kódu v IFJcode17.
- 52 - Chyba při sémantických kontrolách vstupního kódu v IFJcode17.
- 53 - Běhová chyba interpretace – špatné typy operandů.
- 54 - Běhová chyba interpretace – přístup k neexistující proměnné (rámec existuje).
- 55 - Běhová chyba interpretace – rámec neexistuje (např. čtení z prázdného zásobníku rámců).
- 56 - Běhová chyba interpretace – chybějící hodnota (v proměnné nebo na datovém zásobníku).
- 57 - Běhová chyba interpretace – dělení nulou.
- 58 - Běhová chyba interpretace – chybná práce s řetězcem.
- 60 - Interní chyba interpretu tj. neovlivněná vstupním programem (např. chyba alokace paměti, chyba při otvírání souboru s řídicím programem atd.).

#### Paměťový model

- Hodnoty během interpretace se nejčastěji ukládají do pojmenovaných proměnných, které se sdružují do "rámců" (slovník proměnných s jejich hodnotami)
- K dříve přiloženým lokálním rámcům nelze přistoupit dokud se nevyjmou později přidané rámce.
- 3 druhy rámců:
    - **Globální**
        - Na začátku interpretace automaticky inicializován jako prázdný.
        - Slouží pro ukládání globálních proměnných.
    - **Lokální**
        - Na začátku interpretace nedefinován.
        - Odkazuje na vrcholový/aktuální rámec na zásobníku rámců.
        - Zásobník rámců lze využít při zanořeném či rekurzivním volání funkcí.
            - Slouží pro ukládání lokálních proměnných funkcí.
    - **Dočasný**
        - Na začátku interpretace nedefinován.
        - Slouží pro chystání nového nebo úklid starého rámce, jenž může být přesunut na zásobník rámců == stát se aktuálním lokálním rámcem.
- Další možností pro ukládání nepojmenovaných hodnot je datový zásobník využívaný zásobníkovými instrukcemi.

#### Datové typy mezikódu

- S operandy se pracuje dynamicky.
    - Typ proměnné (paměťové místo) je dáno obsaženou hodnotou.
- Není-li řečeno jinak jsou implicitní koverze zakázány.
- Podporuje 4 základní datový typy (**int, bool, float, string**)
    - Rozsahy kompatibilní s IFJ17
- Zápis každé konstanty v IFJcode17 se zkládá ze 3 částí `float@1.15, bool@true nebo int@-5`.
    - Označení typu konstanty
    - Oddělovač `@`
    - Samotné konstanty (číslo, literál)
- Int
    - Reprezentuje 32-bitové celé číslo (C-int)
- Bool
    - Pravdivostní hodnota (true, false)
- Float
    - Desetinné číslo (C-double)
    - V případě zápisu konstant používejte v jazyce C formátovací řetězec `%g`.
- String
    - v případě konstanty zapsán jako sekvence tisknutelných ASCII znaků (mimo bílých znaků, #, \\), escape sekvencí, takže není ohraničen uvozvokami.
    - Escape sekvence, která je nezbytná pro znaky s ASCII odem 000-032, 035, 092 je ve tvaru `\xyz`, kde xyz je dekadické číslo <000;255>.
        - `string@retezec\032s\032lomitkem\032\092\032a\010novym\035radkem` == retezec s lomitkem \ a <br /> novym#radkem
- Pokus o práci s neexistující proměnnou (čtení, zápis) vede na chybu 54.
- Pokus o interpretaci instrukce s operandy nevhodných typů dle popisu dané instrukce vede na chybu 53.

#### Instrukční sada

- U popisu instrukcí se sází oprační kód tučně a operandy se zapisují pomocí neterminálnch symbolů (případně číslovaných) v úhlových závorkách.
- Neterminál `<var>` značí proměnnou, `<symb>` konstantu nebo proměnnou, `<label>` značí návěští.
- Identifikátor proměnné se zkládá ze dvou částí oddělených `@`, označení rámce (LF, TF nebo GF) a samotné proměnné (sekvence libovolných alfanumerických a sspeciálních znaků bez bílých začínající písmenem nebo speciálním znakem, kde speciální znaky jsou **_, -, $, %, &, \***)
    - `GF@_x` == Proměnná _x uložená v globálním rámci.
- Na záis návěští se vztahují stejná pravidla jako na jména proměnných.
- Instrukční sada nabízí instrukce pro práci s proměnnými v rámcích
    - Různé skoky, operace s datovým zásobníkem, aritmetické, logické a relační operace, dále také konverzní, vstupně/výstupní a ladicí instrukce.

##### Práce s rámci, volání funkcí

###### MOVE <var> <symb>

- Přiřazení hodnoty do proměnné.
- Zkopíruje hodnotu `<symb>` do `<var>`.
- `MOVE LF@par GF@var` == zkopírování hodnoty _var_ v globáním rámci do proměnné _par_ v lokálním rámci.

###### CREATEFRAME

- Vytvoření nového dočasného rámce a případné zahození obsahu původního dočasného rámce.

###### PUSHFRAME

- Přesun dočasného rámce na zásobník rámců.
- Rámec bude k dispozici přes LF a překryje původní rámce na zásobníku rámců.
- TF bude po provedení instrukce nedefinován a je třeba jej před dalším použitím vytvoři pomocí `CREATEFRAME`.
- Pokus o přístup k nedefinovanému rámci == Chyba 55.

###### POPFRAME

- Přesune vrcholový rámec LF ze zásobníku rámců do TF.
- Pokud žádný rámec v LF není k dispozici == Chyba 55.

###### DEFVAR <var>

- Defunej proměnnou v určeném rámci dle `<var>`.
- Proměnná je zatím neinicializovaná a bez určení typu, který bude určen až přiřazením nějaké hodnoty.

###### CALL <label>

- Skok na návěští s podporou návratu.
- Uloží inkrementovanou aktualní pozici z interního čítače insrukcí do zásobníku volání a provede skok na zadané návěští. (případnou přípravu rámce musí zajistit další instrukce).

###### RETURN

- Návrat na pozici uloženou instrukcí `CALL`.
- Vyjme pozici ze zásobníku volání a skočí na tuto pozici nastavením interního čítače instrukcí (úklid lokálních rámců musí zajistit další instrukce).

##### Práce s datovým zásobníkem

- Operační kód zásobníkových funkcí je zakončen písmenem "S".
- Zásobníkové insrukce načítají chybějící operandy z datového zásobníku a výslednou hodnotu operace ukládají zpět na datový zásobník.

###### PUSHS <symb>

- Uloží hodnotu `<symb>` na datový zásobník.

###### POPS <var>

- Není-li zásobník prázdný, vyjme z něj hodnotu a uloží ji do proměnné `<var>`, jinak Chyba 56

###### CLEARS

- Pomocná instrukce.
- Maže celý obsah datového zásobníku, aby neobsahoval zapomenuté hodnoty z předchozích výpočtů.

##### Aritmetické, relační, booleovské a konverzní instrukce

- Tříadresné i zásobníkové verze instrukcí pro klasické operace pro výpočet výrazu.
- Zásobníkové verze instrukcí z datového zásobníku vybírají operandy se vstupními hodnotami dle popisu tříadresné insturukce od konce.
    - Nejprve `<symb2>` poté `<symb1>`.

###### ADD <var> <symb1> <symb2>

- Sečte `<symb1>` a `<symb2>`.
- Musí být stejného číselného typu (int nebo float) a výslednou hodnotu téhož typu uloží do proměnné `<var>`.

###### SUB <var> <symb1> <symb2>

- Odečte `<symb2>` a `<symb1>`.
- Musí být stejného číselného typu (int nebo float) a výslednou hodnotu téhož typu uloží do proměnné `<var>`.

###### MUL <var> <symb1> <symb2>

- Vynásobí `<symb1>` a `<symb2>`.
- Musí být stejného číselného typu (int nebo float) a výslednou hodnotu téhož typu uloží do proměnné `<var>`.

###### DIV <var> <symb1> <symb2>

- Dělení dvou desetinných číselných hodnot.
- Podělí desetinnou hodnotu za `<symb1>` druhou desetinnou hodnout ze `<symb2>`.
- Výsledek typu float přiřadí do proměnné `<var>`.
- Použití celočíselného operandu == Chyba 53; Dělení 0 == Chyba 57

###### ADDS/SUBS/MULS/DIVS

- Zásobníkové verze instrukcí.

###### LT/GT/EQ <var> <symb1> <symb2>

- Relační operátory menší, větší, rovno.
- Instrukce vyhodnotí relační oeprátor mezi `<symb1>` a `<symb2>` (stejného typu).
- Do booleovské proměnné `<var>` zapíše false při neplatnosti nebo true v případě platnosti odpovídající relace.
- Řětězcové jsou porovnány lexikograficky.
- False je menší než true.
- Pro výpočet neostrých nerovností lze použít AND/OR/NOT.

###### LTS/GTS/EQS

- Zásobníkové verze instrukcí.

###### AND/OR/NOT <var> <symb1> <symb2>

- Aplikuje konjunkci na `<symb1>` a `<symb2>`.
- Not má pouze 2 operandy ==> Negace na `<symb1>`
- Výsledek se zapíše do `<var>`

###### ANDS/ORS/NOTS

- Zásobníkové verze instrukcí.

###### INT2FLOAT <var> <symb>

- Převod celošíselné hodnoty `<symb>` na celočíselnou hodnotu.

###### FLOAT2INT <var> <symb>

- Převede desetinnou hodnotu `<symb>` na celočíselnou.
- Oseknutí desetinné části a uložení do `<var>`

###### FLOAT2R2EINT <var> <symb>

- Převede desetinnou hodnotu `<symb>` na celočíselnou.
- Zaokrouhlení s preferencí sudé číslice a uložení do `<var>`.
    - 1.5, 2.5 == 2

###### FLOAT2R2OINT <var> <symb>

- Převede desetinnou hodnotu `<symb>` na celočíselnou.
- Zaokrouhlení s preferencí liché číslice a uložení do `<var>`.
    - 1.5 == 1
    - 2.5 == 3

###### INT2CHAR <var> <symb>

- Číselná hodnota `<symb>` je dle ASCII převedena na znak, který tvoří jednoznakový řetězec přiřazený do `<var>`.
- Je-li mimo <0;255> == Chyba 58

###### STRI2INT <var> <symb1> <symb2>

- Ordinální hodnota znaku (dle ASCII) v řetězci `<symb1>` na pozici `<symb2>` (od 0) je uložona do `<var>`.
- Indexace mimo řetězec == Chyba 58.

###### INT2FLOATS/FLOAT2INTS/FLOAT2R2EINTS/FLOAT2R2OINTS/INT2CHARS/STRI2INTS

- Zásobníkové verze instrukcí.

##### Vstupně / výstupní instrukce

###### READ <var> <type>

- Načte jednu hodnotu dle zadaného typu `<type> ∈ {int, float, string, bool}` a je uložena do `<var>`.
    - Včetně případně konverze vstupní hodnoty float do proměnné typu int.
- Formát hodnot je kompatibilní s chováním příkazu [Input](#p%C5%99%C3%ADkaz-pro-na%C4%8Dten%C3%AD-hodnot "Input").
- V případě chybného vstupu bude do proměnné `<var>` uložena implicitní hodnota dle typu (0.00, 0, false, prázdný řetězec).

###### WRITE <symb>

- Vypíše hodnotu `<symb>` na standardní výstup.
- Formát hodnot je kompatibilní s chováním příkazu [Print](#p%C5%99%C3%ADkaz-pro-v%C3%BDpis-hodnot "Print").

##### Práce s řetězci

###### CONCAT <var> <symb1> <symb2>

- Do proměnné `<var>` uloží řetězec vzniklý konkatenací dvou řetězcových operandů `<symb1>` a `<symb2>`.
    - Jiné typy nejsou povoleny.

###### STRLEN <var> <symb>

- Zjistí délku řetězce v `<symb>`.
- Dělka je uložena do `<var>`.

###### GETCHAR <var> <symb1> <symb2>

- Do `<var>` se uloží řětězec z jednoho znaku v rětězci `<symb1>` na pozici `<symb2>` (indexováno od 0).
- Indexace mimo řetězec == Chyba 58

###### SETCHAR <var> <symb1> <symb2>

- Zmodifikuje znak řetězce uloženého v proměnné `<var>` na pozici `<symb1>` (indexováno od 0) na znak v rětězci `<symb2>`.
    - Na první znak, pokud obsahuje `<symb2>` více znaků.
- Výsledný řetězec je opět uložen do `<var>`.
- Při indexaci mimo řetězec `<var>` nebo při prázdném `<symb2>` == Chyba 58

##### Práce s typy

###### TYPE <var> <symb>

- Dynamicky zjistí typ `<symb>`.
- Do `<var>` zapíše řetězec značící tento typ (int, bool, float, string).
- Je-li `<symb>` neinicializovaná proměnná, označí její typ prázdným rětězcem.

##### Instrukce pro řízení toku programu

- Neterminál `<label>` označuje návěští, které slouží pro označení pozice v kódu IFJcode17.
- Při skoku na neexistující návěští == Chyba 52.

###### LABEL <label>

- Speciální intrukce označující pomocí návěští `<label>` důležitou pozici v kódu jako potenciální cíl libovolné skokové instrukce.
- Pokud o redefinici existujícího návětší == Chyba 52

###### JUMP <label>

- Provede nepodmíněný skok na základě návěští `<label>`.

###### JUMPIFEQ <label> <symb1> <symb2>

- Pokud jsou `<symb1>` a `<symb2>` stejného typu (jinak Chyba 53) a zároveň se jejich hodnoty rovnají, tak se provede skok na návěští `<label>`.

###### JUMPIFNEQ <label> <symb1> <symb2>

- Pokud jsou `<symb1>` a `<symb2>` stejného typu (jinak Chyba 53), ale různé hodnoty, tak se provede skok na návěští `<label>`.

###### JUMPIFEQS/JUMPIFNEQS <label>

- Zásobníkové skokové instrukce.
- Mají i jeden operand mimo datový zásobník a to návěští `<label>`, na které se případně provede skok.

##### Ladící instrukce

###### BREAK

- Na standardní chybový výstup (stderr) vypíše stav interpretu v danou chvíli.
    - Během vykonávání této instrukce.
- Stav se mimo jiné skládá z pozice v kódu, výpisu globáního, aktuálního lokálního a dočasného rámce a počtu již vykonaných intrukcí.

###### DPRINT <symb>

- Vypíše zadanou hodnotu `<symb>` na standardní chybový výstup (stderr).
- Výpisy touto instrukcí bude možné vypnout pomocí volby interpretu.

## Požadavky na řešení

### Závazné metody pro implementaci interpretu

>>>
Projekt bude pouze hodnocen jako celek, a nikoli jako soubor separátních, sposlečné nekooperujících modulů.
Při tvorbě lexikální analýzy využijte znalosti konečných automatů.
Při konstrukci syntaktické analýzy založené na LL-gramatice (vše kromě výrazů) **povinně** využijte buď **metodu rekurzivního sestupu (doporučeno)**, nebo prediktivní analýzu řeízenou LL-tabulkou.
Výrazy zpracujte pouze pomocí **precedenční syntaktické analýzy**.
Implementace bude provedna v jazyce C.
Není dovoleno spouštět další procesy a vytvářet nové či modifikovat existující soubory (ani /tmp).
>>>

### Programová část řešení

- Vypracování bez generátorů (lex/flex, yacc/bison).
- Přeložitelné pomocí `gcc`.
- Přeložitelné na Merlinu (=hodnotící server)
- Makefile součástí řešení
    - Přeložitelný pouze pomocí `make`
    - Finální jméno není rozhodující
- Úvod všech zdrojových textů musí obsahovat zakomentovaný název projektu, přihlašovací jména a jména studentů, kteří se na něm skutečně autorsky podíleli.
- Veškerá chybová hlášení --> stderr
- Veškeré texty tištěně řídícím programem --> stdout
    - Pokud není řečeno jinak
- Kromě chybových/ladicích hlášení vypisovaných na stderr nebude generovaný mezikód přikazovat výpis žádných znaků či dokonce celých textů, které nejsou přímo předepsány řídícím programem.
- Jediný neočekávaný znak rozbije hodnocení.

## Rozšíření

### SCOPE

- Podporujte libovolné zanořování bloků
    - Sekvence definic proměnných a příkazů uvozených klíčovým slovem **Scope** a ukončených dvojicí **End Scope**
- Včetně správně práce s viditelností lokálních proměnných dle jazyka FreeBASIC.
- Při definici lokální proměnné stejného jména, jako má již některá proměnná na vyšší úrovni, je pod daným identifikátorem viditelná ona lokální proměnná.
- Umožněte také definice proměnných přímo ve větvích podmíněného příkazu a v sekvenci příkazů příkazu cyklu.
- **+1,0 bodu**

### GLOBAL

- Podporuje statické proměnné (**Static**) a globální proměnné (**Shared**).
- Kolize jmen proměnných řeší analogicky jako překladač FreeBASIC.
- **+1.0 bodu**

### UNARY

- Rozšíření zavádí podporu pro unární operátor **-** (unární mínus) a přiřazovací příkazy **+=, -=, *=, \=, /=**.
- Priorita a asociativita unárního mínus odpovídá jazyku FreeBASIC
- **+0.5 bodu**

### BASE

- celočíselné konstanty je možné zadávat v soustavách:
    - Dvojkové číslo začíná znaky: `&B`
    - Osmičkové číslo začíná znaky: `&O`
    - Šestnáckové číslo začíná znaky: `&H`
- **+0.5 bodu**

### CYCLES

- Podpora cyků ve tvaru.
    - **For** ... **Next**
    - Kompletní podpora **Do** ... **Loop** včetně příkazů **Continue** a **Exit**
- Při definici iterační proměnné stejného jména v příkazu **For**, jako má již některá proměnná na vyšší úrovni, je pod daným identifikátorem v rámci těla cyklu viditelná ona iterační proměnná.
- **+1.5 bodu**

### FUNEXP

- Volání funkce může být součástí výrazu.
- Zároveň mohou být výrazy v parametrech volání funkce.
- **+1.5 bodu**

### IFTHEN

- Podpora zjednodušený podmíněný příkaz **If-Then** bez části **Else** a rozšířený podmíněný příkaz s volitelným vícenásobným výskytem **Elseif-Then**.
- **+0.5 bodu**

### BOOLOP

- Podpora **Boolean**
    - **True** a **False**
    - Podpora booleovských výrazů všetně kulatých závorek.
    - Základních booleovských operátorů (**NOT**, **AND**, **OR**).
    - Jejich priorita a asociativita odpovídá jazyku FreeBASIC.
    - Pravdivostní hodnoty lze porovnávat jen operátory `=`, `<>`.
    - Podpora výpisu definic proměnných typu **Boolean**.
    - Implicitní hodnota == `False`
- **+1.0 bodu**

## Soubory

- [x] **rozdeleni**
    - Obsahuje 4 řádky (+prázdný poslední). `login:%bodů`
    - 100% bude rozděleno mezi každého podle zásluh.
        xnovak01:30
        xnovak02:40
        xnovak03:30
        xnovak04:00
- [x] **symtable.c + .h**
    - Implementace tabulky symbolů podle postupů z IAL.
            - Pokud se bude lišit == Zdůvodnit v dokumentaci a uvést zdroje.
- [x] **dokumentace.pdf**
    - Česky, slovensky nebo anglicky
    - Cca 3-5 A4 stran.
        - _Popsání návrhu_
            - Část překladače
            - Předávání informace mezi nimi
        - _Popsání implementace_
            - Použité datové struktury
            - Tabulka symbolů
            - Generování kódu
        - Vývojový cyklus, způsob práce v týmu, speciální použité techniky, algoritmy a různé odchylky od přednášené látky či tradičních přístupů.
    - Citace literatury a uvádění referencí na zdroje
        - Včetně převzaných částí (obrázky, magické konstanty, vzorce)
    - Nepopisovat obecně známé záležitosti, či přednášené na fakultě
    - **POVINNĚ MUSÍ OBSAHOVAT:**
        - Povinné tabulky (Nepočítáno do rozsahu)
        - Diagramy (Nepočítáno do rozsahu)
        - Jak jsou implementované rozšíření
    - Rozložení:
        - \1. strana
            - Jména
            - Příjmení
            - Loginy
            - Označení vedoucího
            - Údaje o rozdělení bodů
            - Identifikace varianty a zadání ve tvaru `Tým XXX, varianta X`
            - Výčet identifikátorů rozšíření
        - Rozdělení práce mezi členy týmu
            - Uvedeno, kdo a jak se podílel na jednotlivých částech projektu
            - Povinně zdůvodnění odchylky od rovnoměrného rozdělení bodů.
        - Diagram konečného automatu, který specifikuje lexikální analyzátor.
        - LL-gramatiku, LL-tabulku a precedenční tabulku, která jsou jádrem syntaktického analyzátoru.
    - **DOKUMENTAFCE NESMÍ**:
        - Obsahovat kopie zadání, obrázky nebo diagramy, kterou nejsou naše původní (kopie přednášek, WWW...)
        - Být založena pouze na výčtu a obecném popisu jednotlivých použitých metod.
            - Jde o náš vlastní přístup k řešení ==> Dokumentace postupu, který jsme při řešení aplikovali
            - Překážky
            - Problémy
    - V rámci dokumentace bude rovněž vzat v úvahu stav kódu
        - Čitelnost
        - Srozumitelnost
        - Dostatečné, ale nikoli přehnané komentáře
- [x] **rozsireni**
    - Nepovinný soubor
    - Na každém řádku identifikátor jednoho implementovaného rozšíření

## Zip

- Odevzdává jenom jeden
- Jméno vedoucího: xlogin00.tgz | xlogin00.zip | xloginOO.tbz
- Všechny soubory malými písmeny, číslice, tečka, podtržítko (mimo Makefile)
    - Žádná adresářová struktura. Pouze soubory.
