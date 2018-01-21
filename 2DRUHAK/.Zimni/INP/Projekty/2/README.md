# Zadání 2017 Procesor s Harvardskou architekturou

- Datum zadání: 23.10.2017
- Datum a forma odevzdání: do 22.12.2017 23:59, POUZE přes IS FIT, 4 soubory
- Počet bodů: max. 23 bodů
- Poznámka: součástí zadání je archiv [INP-proj2.zip](https://wis.fit.vutbr.cz/FIT/st/course-files-st.php?file=%2Fcourse%2FINP-IT%2Fprojects%2FProjekt2%2FINP-proj2.zip "INP-proj2.zip")
- Dotazy odhledně projektu: v případě nejasností využijte email `vasicek@fit.vutbr.cz` nebo osobní konzultace (Zdeněk Vašíček, L307)

## Komentář k hodnocení

### Odevzdane (validni) soubory

- cpu.vhd ano
- login.b ano
- inp.png ano
- inp.srp ano

### Overeni cinnosti kodu CPU

| #   | testovany program (kod)    | vysledek |
| --- | -------------------------- | -------- |
| 1.  | ++++++++++                 | ok       |
| 2.  | ----------                 | ok       |
| 3.  | +>++>+++                   | ok       |
| 4.  | <+<++<+++                  | ok       |
| 5.  | .+.+.+.                    | ok       |
| 6.  | ,+,+,+,                    | ok       |
| 7.  | [........]noLCD[.........] | chyba    |
| 8.  | +++[.-]                    | ok       |
| 9.  | +++++[>++[>+.<-]<-]        | ok       |
| 10. | +[+~------------]+         | ok       |
| 11. | +[+~[-----]-----]+         | ok       |

Podpora jednoduchych cyklu: ano
Podpora vnorenych cyklu: ano

### Poznamky k implementaci

Mozne problematicke rizeni nasledujicich signalu: **OUT_DATA**

Celkem bodu za CPU implementaci: **16** (z 17)

## Úvod

> Cílem tohoto projektu je implementovat pomocí VHDL procesor s Harvardskou architekturou, který bude schopen vykonávat program napsaný v jazyce [Brainlove](https://esolangs.org/wiki/Brainlove "Popis instrukční sady").
Jazyk Brainlove je rozšířením jazyka BrainFuck, který používá pouze **8** jednoduchých příkazů (instrukcí), o **5** nových instrukcí.
V obou případech se však jedná o výpočetně úplnou sadu, pomocí které je možné realizovat libovolný algoritmus.

### Činnost procesoru

Jazyk Brainlove definuje **13** příkazů zakódovaných pomocí tisknutelných 8-bitových znaků. Implementovaný procesor bude zptracovávat přímo tyto znaky (tzn. operační kód procesoru bude sestávat vždy z 8 bitů). Pro jednoduchost budeme uvažovat pouze **9** příkazů uvedených v tabulce níže. Program sestává ze sekvence těchto příkazů. neznámé příkazy jsou ignorovány, což umožňuje vkládat komentáře přímo do programu.

Vykonávání programu začíná první instrukcí a končí jakmile je detekován konec sekvence (ASCII hodnota 0). Program je uložen v nemodifikovatelné paměti programu (**ROM**) od adresy **0** a je vykonáván nelinárné (obsahuje skoky). Data jsou uložena v paměti **RAM** o kapacitě 1024 8-bitových položek. Obsah paměti nechť je pro jednoduchost inicializován na hodnotu 0. Pro přístup do paměti se používá ukazatel (**ptr**), který je možné přesouvat o pozici doleva či doprava. Paměť je chápána jako kruhový buffer uchovávající 8-bitová čísla bez znaménka. Posun doleva z adresy 0 tedy znamená přesun ukazatele na konec paměti (tj. pozici 1023).

Implementovaný procesor nechť podporuje příkazy definované v následující tabulce. Operační kódy, které se v tabulce nenacházejí jsou procesorem ignorovány.

| příkaz | operační kód | význam                                                                                                           | ekvivalent v C    |
| :----: | :----------: | :--------------------------------------------------------------------------------------------------------------- | :---------------- |
| >      | 0x3E         | Inkrementace hodnoty ukazatele                                                                                   | ptr+=1;           |
| <      | 0x3C         | Dekrementace hodnoty ukazatele                                                                                   | ptr-=1;           |
| +      | 0x2B         | Inkrementace hodnoty aktuální buňky                                                                              | *ptr+=1;          |
| -      | 0x2D         | Dekrementace hodnoty aktuální buňky                                                                              | *ptr-=1;          |
| [      | 0x5B         | Je-li hodnota aktuální buňku nulová, skoč za odpovídající příkaz <br /> `]` jinak pokračuj následujícím znakem   | while (*ptr) {    |
| ~      | 0x7E         | Ukončí právě prováděnou smyčku while                                                                             | break;            |
| ]      | 0x5D         | Je-li hodnota aktuální buňku nenulová, skoč za odpovídající příkaz <br /> `[` jinak pokračuj následujícím znakem | }                 |
| .      | 0x2E         | Vytiskne hodnotu aktuální buňky                                                                                  | putchar(*ptr);    |
| ,      | 0x2C         | Načti hodnotu a ulož ji do aktuální buňky                                                                        | *ptr = getchar(); |
| null   | 0x00         | Zastav vykonávání programu                                                                                       | return;           |

V případě příkazů `[` a `]` manipulujíích s ukazatelem do programového kódu (instrukčním čítačem PC) je zapotřerbí detekovat odpovídající pravou, respektive levou, závorku. Možností je několik, nejjednodušší je porstupně inkrementovat (respektive dekrementovat) ukazatel a počítat počet závorek (viz. dále).

### Mikrokontroler

Aby bylo možné vykonávat smysluplný program, je procesor připojen ke dvěma odděleným pamětem, paměti programu (pouze pro čtení, kapacita 4kB) a paměti dat (dovoluje čtení i zápis, kapacita 1kB). Výsledný mikrokontroler je součástí zip archivu jakožto projekt pro FITkit.

Vstup dat je řešen pomocí maticové klávesnice. Jakmile procesor narazí na instrukci načtení hodnoty (oprační kód 0x2C), vykonávání se pozastaví do té doby, než je stiknuto některé z tlačítek klávesnice. Tlačítka 0-9 jsou interpretována jako znaky `0` až `9` s ASCII <48;57>. Tlačítko `*` a `#` je interpretováno jako konec řádku s ASCII hodnotou 10.

Výstup dat je řešen pomocí LCD displeje, posun kurzoru na displeji je řešen automaticky. Při zápisu většího počtu znamů, než-li dovoluje kapacita aktivní části displeje, dojde k návratu na první znak a dříve zapsané znaky se postupně přepisují.

## Úkoly

1. [x] Obsah souboru **login.b** obsahujícího program v jazyce Brainlove, který tiskne řetězec xlogin01, zkopírujte do debuggeru na této [adrese](http:/www.fit.vutbr.cz/~vasicek/inp17/ "adrese"). Tlačítkem "Start debugger" spusťte krokování a sledujte, co způsobuje která instrukce, jak se pohybuje programový čítač a ukaztel do paměti dat. Vytvořte program, který vytiskne na displej Váš login (na velikosti písmen nezáleží). Snažte se v programu využít všechny dostupné příkazy s výjimkou příkazu načtení. Pokuste se vytvořit co nejkratší program.
1. [x] Seznamte se s kódem v souborech **ram.vhd** (pamět dat), **rom.vhd** (pamět programu), **cpu.vhd** (rozhraní procesoru) a **top.vhd** (strukturální popis mikrokontroleru). Povšimněte si, kde je definován program v jazyce Brainlove a jak jej lze modifikovat.
1. [x] Do souboru **cpu.vhd** doplňte vlastní VHDL kód, který bude syntetizovatelným způsobem popisovat implementaci procesoru vykonávajícího program zapsaný v jazyce Brainlove.
    1. Rozhraní procesoru je pevně dané a skládá se z 5 skupin signálů:
        - Synchronizace
        - Rozhraní pro paměť programu
        - Rozhraní pro paměť dat
        - Vstupní rozhraní
        - Výstupní rozhraní
    1. Synchronizační rozhraní tvoři 3 signály:
        - **CLK** - Hodinový synchronizační signál. Procesor vždy pracuje při vzestupné hraně hodinového signálu.
        - **RESET** - asynchronní nulovací signál. Je-li `RESET=1`, procesor znicializuje svůj stav (`PTR=0, PC=0`)
        - **EN** - Povolení činnosti procesoru. Pokud je signál RESET uvolněn (`RESET=0`) a `EN=1`, procesor postupně začne vykonávat program od adresy 0.
    1. Rozhraní _synchronní_ paměti ROM uchovávající program je tvořeno 3 signály.
        - **CODE_ADDR** - Udává adresu buňky.
        - **CODE_DATA** - Obsahuje 8-bitové instrukční slovo nacházející se na adrese `CODE_ADDR`.
        - **CODE_EN**
        - Hodnota signálu `CODE_ADDR` a `CODE_EN` je čtena a hodnota signálu `CODE_DATA` aktualizována vždy při vezstupné hraně hodinového signálu. K aktualizaci hodnoty signálu `CODE_DATA` dochází pouze pokud `CODE_EN = 1`.
    1. Rozhraní _asynchronní_ paměti RAM uchovávajicí data je tvořeno 3 datovými a 2 řídícími signály:
        - **DATA_ADDR** - Slouží k adresaci konkrétní buňky paměti.
        - **DATA_RDATA** - (načtená data) Obsahuje 8-bitovou hodnotu buňky na adrese `DATA_ADDR`.
        - **DATA_WDATA** - (zapisovaná data) nechť obsahuje 8-bitovou hodnotu, kterou má přepsat buňka na adrese `DATA_ADDR`.
        - Podobně jako v předchozím případě jsou signály `DATA_ADDR`, `DATA_EN` a `DATA_WDATA` čteny a signál `DATA_RDATA` aktualizován při vzestupné hraně hodinového signálu.
        - Rozhraní pracuje následovně.
            - Platí-li `DATA_EN=1` a `DATA_RDWR=0` signál `DATA_RDATA` je aktualizován hodnotou buňky na adrese `DATA_ADDR`.
            - Je-li `DATA_EN=1` a `DATA_RDWR=1` hodnota buňky na adrese `DATA_ADDR` je přepsána hodnotou signálu `DATA_WDATA` a signál `DATA_RDATA` je aktualizován hodnotou `DATA_WDATA`.
            - K aktualizaci hodnoty signálu `DATA_RDATA` dochází pouze pokud `DATA_EN=1`.
        - Vstupní rozhraní, které je připojeno na řadič klávesnice pracuje následovně:
            - Při požadavku na data procesor nastaví signál `IN_REQ` na `1` a čeká tak dlouho, dokud signál `IN_VLD` (input valid) není roven `1`. Jamile se tak stane, může procesor přečíst signál `IN_DATA`, který obsahuje ASCII hodnotu stisknuté klávesy a deaktivoat signál `IN_REQ`.
        - Výstupní rozhraní napojené na LCD displej pracuje následovně:
            - Při požadavku na zápis dat procesor nejdříve musí otestovat stav signálu `OUT_BUSY`. Tento signál indikuje, že je LCD displej zaneprázdněn vyřizováním předchozího požadavku.
            - Jakmile je `OUT_BUSY=0`, procesor inicializuje signál `OUT_DATA` zapisovanou ASCII hodnotou a současně na jeden hodinový takt nastavý signál `OUT_WE` na 1.
        - Činnost procesoru důkadně ověřte pomocí simulace a následně na přípravku FITkit. K ověření použijte dodané testovací programy případně použijte vlastní.
1. [x] Do souboru **top.vhd** vložte program vytvořený v prvním bode zadání vypisující Váš login. Projekt vysyntetizujte (přeložete v prostředí Xilinx ISE) a odsimilujte.
    Poznámka: Hlášek během syntézy (info, warning) vznkiklých mimo entitu CPU si nevšímejte, nelze je bohužel jednodušše potlačit.

## Odevzdává se

Do IS FIT se odevzdávají následující **4 soubory** (nikoliv ZIP či jiný archív).

- [x] **login.b**
    - Obsahující program v jazyce Brainlove vypisující Váš login (jedná se o výsledek bodu 1 zadání).
- [x] **cpu.vhd**
    - Obsahující implementaci procesoru (jedná se o výsledek bodu 3 zadání).
- [x] **inp.srp**
    - Výsledek 4. bodu zadání.
    - Výsledek syntézy nacházející se v souboru `build/fpga/inp.srp`.
- [x] **inp.png**
    - Printscreen ze simulace zachycující stav signálů kolem okamžiku, kdy se narazí na instrukci **HALT** (konec programu).
    - Není potřeba uvádět všechny signály detailně, avšak na obrázku by měl být vidět měnící se stav automatu, čitelně signálu určující stav automatu procesoru a signál Display zachycující obsah LCD displeje.

## Hodnocení

- Za kompletní implementaci procesoru (Splnění bodu 3) lze získat až **17 bodů**.
- Za implementaci procesoru podporujícího pouze jednoduchý while cyklus (nepodporující vnořené while cykly) lze získat až **12 bodů**.
- Za první a poslední bod zadání lze získat až **6 bodů**.
- Odevzdání po termínu je penalizováno bodovou srážkou ve výši **10 bodů** a to za každý započatý den.

## Upozornění

Pracujte samostatné, nikomu nedávejte svoji práci k opsání.

Platigátorství se hodnotý 0 body, neudělením zápočtu a případně dalším adekvátním postihem dle platného disciplinárního řádu VUT v Brně. Přejmenování proměnných, změna pořadí jednotlivých bloků či modifikace komentářů není považováno za autorské dílo a na řešení bude nahlíženo jako na plagiát.

# Návod

Následující řádky jsou určeny těm, kteří doposud netuší jak procesor naimplementovat. Obecně platí, že procesor se skládá z datové cesty obsahující registry, ALU, apod. a řídící cesty obsahující automat. Stejně tak je tomu i v tomto případě. Blokové schoma možné implementace je uvedeno na obrázku 1.

Abychom. mohli vykonávat program, bosahuje datová cesta 3 registry s možností inkrementace a dekrementace. Registr **PC** slouží jako programový čítač (ukazatel do paměti programu), registr **PTR** jako ukazatel do paměti dat a registr **CNT** slouží ke korektnímu určení odpovídajícího začátku / konce příkazu while (počítání otevíracích / uzavíracích závorek). Mimo to datová cesta obsahuje multiplexor **MX**, který slouží k volbě hodnoty zapisované do paměti dat. Zapsat je možné buď hodnotu načtenou ze vstupu, hodnotu v aktuální buňce sníženou o jedničku nebo hodnotu aktuální buńky zvýšenou o jedničku. V případě, že se rozhodnete NEimplementovat podporu vnořených while cyklů, registr CNT nepotřebujete.

Všechny řídící signály jsou ovládány automatem, tak jak je uvedeno ve schematu. Při tvorbě VHDL kódu se inspirujte procesorem probíraným na cvičeních. V prvním kroku implementujte registry a poté postupujte od jednodušších insturkcí ke složitejším. Implementaci smyček si ponechte až úplně na závěr. Korektní činnost ověřte pomocí simulace a vlastních či přiložených programů (pozor v simulaci není podpora pro vstup z klávesnice).

![Blokové schéma mikrokontroleru](https://image.prntscr.com/image/exmjnIckTkaRbh_B3APPqw.png "Blokové schéma mikrokontroleru")

Nevíte-li jak implementovat automat, podívejte se do materiálů ke cvičením INP. Jako návod pro implementaci automatu by měl posloužit pseudokód popisující chování jednotlivých instrukcí uvedených v tabulce 1. Máte-li s implmentací problémy, vytvořte jednodušší verzi automatu, který nepodporuje vnořené smyčky. (tabulka 2.)

## Projekt pro FITkit

Zdrojové soubory využívají kommponenty a překladové skripty, které se používají v rámci projektu FITkit. K usnadnění práce doporučujeme využít image pro VirtualBox, který obsahuje všechny potřebné nástroje. Po stažení image a spuštení v aplikaci VirtualBox nezapomeňte aktivovat licenci pro Xilinx ISE (spuštením průvodce `xlcm`).

Po spuštění QDevKitu stáhněte aktuální zdrojové kódu a podaresáře apps rozbalte obsah souboru `INP-proj2.zip`. Při následném spuštění QDevKitu se ve stromu dostupných aplikací objeví položka INP a pod ní tento projekt. Pomocí kontextového menu případně dvojklikem na této položce lze připojený FITkit naprogramovat případně projekt přeložit či spusti simalaci. Celým procesem lze projít i v příkazové řádce.
`fcmake gmake, gmake load, gmake isim, gmake term`.

Součástí zadání je vysyntetizované vzorové řešení (soubor `build/inp.bin`) obsahující program, který po spuštení očekává na vstupu číslo (tj. sekvence číslic ukončena stiskem klávesy `#`), které je následně rozloženo na prvočísla. Pokud FITkit naprogramuete (pozor nesmíte projekt přeložit) dodaným kódem a spusťte terminál, procesor bude čekat na stisk klávesy. Tento stav je indikovaná svitem LED diody `D4`. Vzorové řešení je určeno pro FITkit s dvouřádkovým displejem (verze 2.X). Pro ověření funkce na FITKitu s jednořádkovým displejem je zapotřebí nakopíravat obsah adresáře `build/tkit v1` do adresáře `build` jinak v důsledku nekompatability nebudou vidět znaky na druhé polovině displeje.

Projekt je možné simulovat pomocí přeložitelného test bench souboru (`fpga/sim/tb.vhd`) a simulátori Xilinx ISIM. Simulaci lze vyvolat z aplikace QDevKit případně zadáním příkazu `gmake isim` v adresáři s projektem. Skript starající se o vložení signálu do simulace a její spuštění je umístěn v souboru `fpga/sim/isim.tcl`. Skript lze modifikovat dle potřeb. Test bench (VHDL kód v souboru `tb.vhd`) obsahuej FPGA entitu, generátor hodinového a resetovacího signálu a emulátor LCD displeje.
