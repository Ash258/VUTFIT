Operační systémy
================

<!-- TODO: Lint, rework -->

Definice
--------

_Operační systém_ je kolekce programů, který zprostředkovává spojující vrstvu mezi
uživatelem (či jeho programy) a hardware výpočetní techniky.

Cíle OS
-------

* maximální využití zdrojů počitače (počítač vykonává hlavní práci, člověk je jen údržbář)
* jednoduchost použití počítačů (počítač jako zařízení ulehčující práci pro člověka)

Role operačního systému
-----------------------

**Správce prostředků** (sdílení paměti, procesoru, diskového prostoru)
**Tvůrce prostředí pro uživatele** (sdílení paměti, procesoru, diskového prostoru)

### OS zahrnuje
* jádro
* systémové knihovny
* uživatelské rozhraní



Jádro OS
========

Definice
--------

* Nejnižší a nejzákladnější část OS
* Zavádí se první a běží po celou dobu běhu počítačvého systému
* Navazuje na hardware a zapouzdřuje ho pro uživatelské potřeby
* Běží v privilegovaném režimu
    (má ochranu pro vstup ostatních aplikací do tohoto režimu, ale pomocí
    speciálního rozhraní nebo instrukcí dovoluje konstrolovaný vstup do režimu
    jádra)


Typy jader
----------

### Monolitická
Vysokoúrovňové komplexní rozhraní s řadou služeb, které běží v proviligovaném
režimu a jsou těsně provázané za účelem vysoké efektivity.

Vylepšením jsou jádra s modulární strukturou

### Mikrojádra
Malé jádra, které se snaží být co nejjednodušší s co nejmenším počtem služeb.
Jejich služby (servery) neběží v priviligovaném režimu.

#### Výhody
* Flexibilita - může běžet současně více implementací různých služeb
* Zabezpečení - Chyba služby neznamená selhání celého OS

#### Nevýhody
* Mnohem vyšší režie

### Hybridní
Mikrojádra s několika službami, které běží v režimu mikrojádra za účelem snížení
režie.

### Exo
Experimentální jádra poskytující velmi nízké rozhraní.


Historie vývoje OS
------------------

**Dávkové zpracování** postupné provádění úloh, seřazených do dávek
**Multiprogramování** zpracování více úloh současně (OS začíná zatěžovat počítač)

Klasifikace počítačů
--------------------

**Účel**
* univerzální
* specializované (vestavěné, aplikačně orientované, ...)

**Výkon**
* vestavěné
* osobní
* pracovní stanice
* servery
* mainframy
* superpočítače

Klasifikace OS
--------------

**Účel**
* univerzální
* specializované (databáze, real-time)

**Počet uživatelů**
* jednouživatelské
* víceuživatelské

**Současně běžící úlohy**
* jednoúlohové
* víceúlohové


UNIX
====

Jádro unixu obsahuje dva základní podsystémy.
* Správa souborů
* Sprava procesů
Služby těchto podsystémů lze žádat pomocí systémového volání (_system call_)

Hardware přerušení
------------------
Mechanismus, kterým HW zařízení oznamují jádru vznik událostí,
které je zapotřebí obsloužit

### Process
1. Žádosti o přerušení přichází signálem do řadiče přerušení
(APIC: advanced programmable interrupt controller).
2. Přerušení má přiřazenou prioritu, dle kterých se oznamují procesoru.
3. Po přijetí přerušení procesorem se vyvolá obslužná rutina
(_interrupt handler_ se pozná podle _innterupt vector_,
který byl k danému přerušení přidělen).

Některé přerušení lze maskovat (dokonce až po určitou prioritní úroveň).
**Non-maskable interruption (NMI)** - HW přerušení, které nelze zamaskovat

### Přerušení, které vznikají v procesoru
* **trap** - po obsluze se pokračuje dál
* **fault** - po obsluze se instrukce opakuje (výpadek stránky, dělení nulou, ...)
* **abort** - nelze určit, jak pokračovat

### Úrovně přerušení
1. úroveň
Plánuje běh 2. úrovně. Při očekávaném "kolapsu" může být zamaskován
příjem dalších přerušení.
2. úroveň
Řeší zaznamenaná přerušení.
Obsluha může běžet ve speciálních procesech

### Speciální typy přerušení
**Interprocessor interrupt (IPI)** -
    umožňuje poslat přerušení jinému procesu
**System management interrupt (SMI)** -
    způsobí přechod do `System management módu (SMM)`.
    V rámci SMM jsou prakticky vyloučena ostatní přerušení, což způsobuje
    nekonzistenci jádra (Může být využito pro regulaci spotřeby kvůli přehřátí).



Správa souborů
==============

**Alokační blok/Cluster** - nejmení adresovatelná jednotka na disku (pro OS),
    po sobě nasledující jak logicky, tak i fyzicky.
    Velikostně `2^n` pro nějaké `n`

Pevný disk
----------

### Diskový sektor
* nejmenší jednotka se kterou disk pracuje
* velikost 4096B (dříve 512B)
* adresace:
    * CHS - Cylinder,Head,Sector
    * LBA - 0..N

### Parametry pevných disků
* Přístupová doba
* kapacita
* otáčky
* přenosová rychlost (buffer a/nebo plotny)

SSD
---
Založeno na nevolatilních NAND flash.

### Výhody
* rychlý
* umožňují náhodný přístup
* daleko vyšší přenosové rychlosti (zápis většinou pomalejší než čtení)
* tichý provoz
* mechanická a magnetická odolnost
* obvykle nižší spotřeba

### Nevhody
* vyšší cena
* omozený počet přepisů
* možné komplikace se zabezpečením

### Struktura SSD
NAND flash SSD jsou organizovány do stránek (4 KiB) a ty do bloků (512 KiB)
Pro přepis je nutno načíst celý blok do vyrovnávací paměti, v ní změnit,
na disku vymazat a pak zpětně zapsat.

#### Možné řešení
* SSD může mít víc stránek než je oficiální kapacita
* `TRIM` umožnuje sdělit SSD, které stránky má považovat za prázdné
* Řadič může regulovat využití stránek

Zapezpečení disků
-----------------

Disková eletronika používá `ECC (Error Correction Code)`. Disk obsahuje data,
které umožňují detekci chyby nebo i jejich opravu.

**S.M.A.R.T. (Self monitoring Analysis and Reporting Technology)** -
    technologie, která shromažďuje statistiky o disku, podle kterých se pak
    diagnostikují chyby.

RAID pole
=========

* **RAID 0** (stripping) - bez zálohy (nedokáže opravit výpadek disku)
* **RAID 1** (mirroring) - kompletní záloha
* **RAID 2** - po bitech, jsou zvoleny ECC disky pro kontrolu chyb
* **RAID 3** - po blocích sekvenčně + paritní disk pro kontrolu a nápravu chyby
    (paritní disk je využíván nejvíce, opraví výpadek 1 disku)
* **RAID 4** - po blocích náhodně + paritní disk pro kontrolu a nápravu chyby
* **RAID 5** - po blocích, každý disk obsahuje paritní část
    (disky jsou využívány rovnoměrně, výpadek 1 disku)
* **RAID 6** - po blocích, každý disk obsahuje 2 paritná části
    (výpadek 2 disků)


Fragmentace
===========

**Interní fragmentace** - nevyužité místo v posledním alokačním bloku
    (nedá se řešit)
**Externí fragmentace** - při spojitém ukládání dat vznikají oblasti,
    které jsou příliš malé na to, aby se využili
    (prostě se to do nich nevejde)

### Řešení externí fragmentace
* defragmentace -> trvá dlouho
* ukládat data nespojitě -> složitější přístup
* Rozložení souborů po disku -> nezaručí, že nenastane, pouze minimalizuje
* předalokace -> nezaručí, že nenastane, pouze minimalizuje
* odložená alokace -> nezaručí, že nenastane, pouze minimalizuje


Logický disk
============

MBR
---

Rozděluje fyzický disk až na 4 (primární) diskové oblasti.
Jedna z nich může být nahrazena rozšířenou diskovou oblastí, která
obsahuje zřetězený seznam logickch diskových oblastí.

GPT (Globaly unique identifier partition table)
---

Rozděluje fyzický disk až do 128 logických diskových oblastí.
Tabulka je zapezpečena kontrolními součty a rezervní tabulkou.

> `Logical Volume Manage (LVM)` -
    umožňuje tvorbu logicých disků přesahující hranice fyzického disku

Žurnálování
===========

Záznam modifikovaných (meta)dat před jejich zápisem na disk.
Obvykle jako cyklicky přepisovaný buffer.
Operace jsou atomické.
Jelikož se data většinou nežurnálují existuje tzv. předřazený zápis
    (prvně data pak metadata)

**REDO implementace** - při chybě se dokončí
**UNDO implementace** - při chybě se vrátí do předchozího stavu

Alternativy k žurnálování
-------------------------

### Copy-on-write
Nejprve se zapíší data a metadata na disk, pak se zpřístupní.
Udržuje se několik verzí kořenového adresáře.
Při chybě se bere kořen s nejnovějším časovým razítkem.

#### Možnosti CoW
* Lze jednoduše snímkovat (udržují se jen kořeny)
* Klonovování (Nezměněná data existují pouze jednou)

Unixový souborový systém
========================

Schéma
------
* boot blok - pro zavedení systému
* super blok - informace o souborovém systému
* tabulka i-uzlů
* datové bloky

I-uzel
------
#### Metadata
* **stav (alokovaný, volný)**
* **typ uzlu (adrresář, obyčejný soubor)**
* **délka v bytech**
* mtime (modification)
* atime (access)
* ctime (i-node modification)
* **UID (user id / vlastník)**
* **GID (group id / skupina)**
* **přístupová práva**
* počet pevných odkazů (hardlinks)
* **tabulka odkazů na datové bloky** (10 + 1\*N + 1\*N\*N + 1\*N\*N\*N)
* odkaz na další info

> N = velikost bloku/velikost odkazu (běžně 4096B/4B)
> Někdy jsou data přímo i-uzlu (fast symlink)

B+ stromy
=========

Uzle mají na střídačku poskládaný _odkazy_ a _klíče_,
při vyhledávání se porovnávají klíče a pokud je `hledaný klíč <= klíči v uzlu` pak se bere levý link od klíče jinak se bere pravý.
Rekurzivně dokud se nedojde na úroveň datového bloku.
Poslední link navazuje na další listový uzel pro rychlejší průchod.
Při přeplnění uzlu se rozštěpí.
Při poklesu zaplnění sousedních uzlů na polovinu se spojí.

> **Extenty** -
    posloupnost proměnného počtu bloků jdoucích za sebou logicky i fyzicky


**EXT4**
* využívá strom extentů na max 5 úrovní bez vyvažování a bez zřetězení listů.

**NTFS**
* **Master File Table (MFT)** - alespoň řádek pro soubor
* Obsah souboru
    1. přímo v záznamu MFT
    2. rozdělen na extenty odkazované ze záznamu
    3. z pomocných MFT záznamů z primárního MFT záznamu

Další typy organizace
=====================

**Deduplikace** - snaha odhalit soubory, které mají stejný obsah
**Montování disků** - připojení zařízení do stromu adresářů (mount, automounter)
**Symbolické odkazy** - odkaz na soubory, zacyklení řešeno omezením počtem úrovní


Přístupová práva
----------------
* sticky bit - 0 nebo 1
    (zakazuje rušit cizí soubory v adresáři nehledě na práva, označení t místo x na konci adresáře)
* vlastník - r(4), w(2), x(1)
* skupina - r(4), w(2), x(1)
* ostatní - r(4), w(2), x(1)

Datové struktury a algoritmy pro vstup a výstup
===============================================

Čtení
------
1. přidělení vyrovnávací paměti a čtení do VP
2. kopie dat z VP do adresového prostoru procesu (RAM -> RAM)

Zápis
-----
1. přidělení vyrovnávací paměti a čtení do VP
2. zápis do VP (RAM -> RAM), nastavení dirty bitu
3. zpožděný zápis, nulování dirty bitu

Otevření souboru
----------------
1. Vyhodnocení cesty a čísla i-uzlu
2. Kopie i-uzlu do tabulky aktivních i-uzlů, vznik v-uzlu
3. Naplnění v-uzlu
4. Přidání odkazu do tabulky otevřených souborů (počítadlo nastaveno na 1)
5. Vrácení indexu položky v poli deskriptorů (-1 při chybě)

Uzavření souboru
----------------
1. Kontrola platnosti deskriptoru souborů
2. Uvolní se položka v poli deskriptorů, sníží počítadlo
3. Pokud je počítadlo 0, uvolní se položka v tabulce otevřených souborů a sníží se počítadlo ve v-uzlu
4. pokud je počítadlo v-uzlu 0, přesune se v-uzel od původního i-uzlu a VP se uvolní
5. vrací se 0 (-1 při chybě)


Procesy
=======

Správa procesu zahrnuje
1. dispatcher (přepínač kontextu)
2. scheduler (plánovač)
3. memory management (správu paměti)
4. IPC (meziprocesová komunikaci)

Definice
--------
**Proces** je běžící program
Je definován:
* identifikátorem (PID)
* stavem jeho plánování
* programem, kterým je řízen
* obsahem registrů
* daty a zásobníkem

Stavy procesu
-------------
**NEW, READY, RUNNING, WAITING, WAITING, TERMINATED**

Reprezentace procesu
--------------------

Struktura procesu se nazývá `Process Controll Block (PCB)` a zahrnuje
* identifikátor
* stav plánování
* obsah registrů
* plánovací informace
* informace spojené se správou paměti

Kontext procesu
---------------

uživatelský, registrový, systémový


Start systému
-------------

1. Firmware
2. Načtení a spuštění zavaděče, někdy v několika fázích
3. Načtení inicializačních funkcí jádra a samotného jádra
4. vytvoření `procesu jádra 0` a `procesu 1 (init)`

### Přihlašování
* GUI
    1. spuštění grafického rozhraní
* konzole
    1. spuštění `getty` pro zadání přihlašovacího jména
    2. spuštění procesu `login`
    3. spuštění `shell`u

Úrovně běhu
-----------

V unixu je 6 úrovní běhu
* **0** - halt
* **1** - single user
* **2** - Multiuser, bez NFS
* **3** - Full multiuser mode
* **4** - unused
* **5** - X11
* **6** - reboot

Inicializační skripty jsou v příslušných složkách `/etc/rcX.d/`, kde se spouští
podle pořadí (jménem).



Plánování
=========

**Plánovač** - rozhoduje, který proces poběží a případně jak dlouho
**Dispečer** - řeší přepnutí kontextu (podle plánovače)

Plánování:
* **preemptivní** - procesor může být procesu odebrán
* **nepreemptivní** - proces se procesoru vzdá

Přepínání kontextu
* Dispečer odebere procesor `procesu A` a přidělí ho `procesu B`
* Uschová stavy registrů `procesu A` do _PCB_
* obnoví  stavy registrů v `procesu B` z _PCB_
* předání říení na adresu, kde bylo dříve přerušeno provádění `procesu B`

Pláovací algoritmy
------------------

### FCFS (First come, First Served) (FIFO)
* procesy jsou zařazeny na konec fronty
* procesor se přiděluje procesům na začátku fronty
* algoritmus je `nepreemptivní`

### Round-robin (Preemtivní FCFS)
* navíc časové kvantum, které po jeho uplynutí odebere procesor procesu

### SJF (Shortest Job First)
* algoritmus je `nepreemptivní`, ale nepřerušuje proces před dokončením jeho
    aktuální výpočetní fáze
* nutno znát dobu běhu procesu (nebo mít možost dobu odhadnout)
* minimalizuje průměrnou dobu čekání
* zvyšuje propustnost systému
* Hrozí `stárnutí` (není zajištěno, že se požadovaný zdroj získá)

### SRT (Shortest Remaining Time)
* obdoba `SJF` s preempcí při vzniku či uvolnění procesu

### Víceúrovňové plánování
* procesy jsou rozděleny do skupin
* v rámci skupiny jsou různé plánovací algoritmy
* algoritmy pro vybrání skupiny

Plánovače
---------

### CFS (Completly Fair Scheduler)
* vede si údaj o tom, kolik procesorového času strávil
* procesy si udržuje ve stromové struktuře
* vybírá procesy s nejmenším stráveným časem
* obsahuje údaj o minimálním stráveném procesorovém čase
* podporuje skupiové plánování


### Windows NT
* 32 prioritních úrovní
    * 0 : nulování prázdnýc stránek
    * 1 - 15 : běžné procesy
    * 16 - 31 : procesy reálného času
* základní priorita je dána staticky nastavenou kominací pláovací třídy
    a plánovacíúrovně v rámci třídy
* tato priorita se dynamicky mění

Inverze priorit
---------------
Zajišťuje, že nízkoúrovňové procesy, které si zablokovaly zdroje, (které
budou potřebovat i vysokoúrovňové procesy) dostavají efektivně vyšší prioritu.

### Další komplikace a řešení
* **Priority ceiling** - nejvyšší priorita pro procesy v kritické sekci
* **Priority inheritance** - procesy v kritické sekci, který blokuje procesy
s vyšší prioritou, dědí nejvyšší prioritu z čekajících procesů
* **Zákaz přerušení** - zákaz přerušení procesu v kritické sekci

Vlákna
------
* odlehčený proces
* v rámci jednoho procesu může běžet více vláken
* vlastní register a zásobník
* sdílí kód, data, zdroje
### Výhdy
* rychlejší spouštění
* rychlejší přepínání


**Úloha** - skupina praralelně běžících procesů
**Skupina procesů**
* množina procesů
* signály lze zasílat skupině
* může mít vedoucího
**Sezení**
* každá skupina v jednom sezení
* může mít vedoucího
* může mít řídící terminál



Signály
=======
`Signál` je číslo zaslaní procesu.
Toto číslo se zasílá pomocí speciálního rozhraní.

Signály vznikají asynchroně, není tedy možné jednoznačně předpovědět,
kdy bude doručen.




Synchronizece procesů
=====================

Jedná se o kontrolu přístupu několika paralelních procesů ke sdíleným zdrojům.

Kritická sekce
--------------
úseky, kde je povolen běh pouze jednoho procesu

#### Problém kritické sekce
problém se zajištěním správného pořadí přístupu (synchronizace)

**vzájemné vyloučení (mutual exclusion / mutex)** -
    do kritické sekce přistupuje pouze jeden

Je zapotřebí se vyhnout
* uváznutí
* blokování
* stárnutí

Časově závislá chyba (race condition)
-------------------------------------
chyba vznikající při nesprávném pořadí přístupu ke sdíleným zdrojům.

Časově závislá chyba nad daty (data race)
-----------------------------------------
více přístupů ke zdroji (kde je potřeba pouze jeden) bez synchronizace

Blokování
---------
situace, kdy proces, který žádá o vstup do kritické sekce, musí čekat i přesto,
že je kritická sekce volná


SpinLock
========
* založen na aktivním čekání
* lze použít u kritických sekcí bez preempce.

Petersonův algoritmus
---------------------

```
bool flag[n] = {false, false, false};
int turn = 0;

// process i (i == 0 or i == 1 ... i == n)
do {
    flag[i] = true;
    turn = 1-i;

    while(flag[1-i] && turn != i)
        ;

    flag[i] = false;
} while (1)
```

Bakery algoritmus L. Lamporta
-----------------------------

```
bool flag[N] = {false};
int ticket[N] = {0};
int j, max = 0;

// process i is from 0..N
while (1) {
    flag[i] = true;
    for (j = 0; j < N; ++j)
        if (ticket[j] > max)
            max = ticket[j];
    ticket[i] = max + 1;
    flag[i] = false

    for (j = 0; j < N; ++j) {
        while(flag[j]) // wait for other processes to take ticket
            ;
        if (ticket[j] > 0 &&
            (ticket[j] < ticket[i] ||
            (ticket[j] == ticket[i] && j<i))
        )
            while(ticket[j] > 0)
                ;
    }

    // critical section
    ticket[i] = 0; max = 0;
}
```

Využití atomických instrukcí
----------------------------
### TestAndSet
```
bool TestAndSet(bool &target) {
    bool rv = target;
    target = true;
    return rv;
}

// využití
bool lock = false;
while (TestAndSet(lock))
    ;
//critical
lock = false;
```

### Swap
```
void Swap(bool &a, bool &b) {
    bool temp = a;
    a = b;
    b = temp;
}

// využití
bool lock = false;

bool key = true;
while (key) Swap(lock, key);
//critical
lock = false;
```

Semafory
========
* nevyžaduje aktivní čekání.
* využívají atomické operacef
    1. lock - obsazení semaforu
    2. unlock - uvolnění semaforu

Alternativy
-----------
* **read-write** - pro čtení lze zamknout vícenásobně
* **reentrant** - stejný zámek zamknout opakovaně
* **mutexy** - binární semafor, odemknuty pouze procesy, které je zamkly

### Linux
* **futexes**


Monitory
========
využívají `conditions` s metodami `signal` a `wait`.

Deadlock
========
`Proces A` čeká na uvolnění zdroje, který zamkl `proces B` a zároveň
`proces B` čeká na uvolnění zdroje, který zamkl `proces A`.

Coffmanovy podmínky
-------------------
1. vzájemné vyloučení při používání prostředků
2. vlastnictví alespoň jednoho zdroje, čekání na další
3. prostředky vrací proces, který je vlastní a to po dokončení jejich využití
4. cyklická závislost na sebe čekajících procesů.

Řešení
------
* prevence uváznutí
* vyhýbání se uváznutí
* detekce a zotavení
* formální verifikace (ověřit, že nemůže nastat)

### Prevence
Před čekáním uvolníme všechny zamknuté zdroje
(uvolněním, odebráním, vícenásobný přístup ke zdroji)

### Vyhýbání
Rozhodovat o uzamknutí podle toho, jaké jsou předem známé požadavky

#### Graf alokace
....


### Detekce uváznutí
Periodicky se kontroluje uváznutí.
Pokud nastalo provede se zotavení

#### Zotavení
1. Odebrání zdroj některým pozastaveným procesům
2. přidělení ostatním
3. umožnění získat odebrané zdroje
4. pokračování

### Formální verifikace
* inspekce systému
* simulace, testování
* formální verifikace (od `Sim. a test.` dokazuje správnost)
* kombinace výše uvedených

#### Process verifikace
1. vytvoření modelu
2. specifikace vlastností
3. kontrola

#### Základní přístupy
* model checking (využití poloautomatických prostředek)
* theorem proving (využití automatických prostředků)
* static analysis (na základě popisu)



Správa paměti
=============

# Typy adresového prostoru

## LAP (logický)
virtuální adresový prostor, se kterým pracuje proces
## FAP (fyzický)
reálný adresový prostor paměti

# MMU (memory management unit)
HW jednotka pro překlad logických adres na fyzické
Využívá speciálních registrů a hlavní paměti pro urychlení překladu

# Přidělování paměti

## Contiguous memory allocation (spojité bloky)
MMU má dva registry: limit (maximální dostupná logická adresa) a relocation (fyzická adresa začátku paměti)
Trpí externí i interní fragmentací
Strategie alokace
- **first fit**: vybere první dostatečně velký prostor (hole), neefektivní ale rychlé
- **best fit**: vybere nejmenší dostatečně velký prostor (hole), musí prohledat celý list volných prostorů, nebo ho udržovat seřazený
- **worst fit**: vybere největší prostor (hole) a sebere z něj kolik potřebuje, zanechá tak za sebou více větších dět, než best fit
- **binary buddy**: Zarovnává požadavky na mocniny dvou. Volné prostore vždy dělí dvěma a požadavku dá přesně kolik potřebuje. Při uvolňování slévá volné prostory

Problém s dynamickou reorganizací a zvětšováním
Při nedostatku paměti nutno odkládat na disk veškerou paměť procesu
Není možné řídit přístupová práva jednotlivých bloků a sdílet části paměti

## Segmentation (segemnty)
Operační systém udržuje segemntovou mapovací tabulku pro každý proces
Každý segment velikost, fyzickou adresu, práva a je identifikovaný číslem
Paměť přidělována po segmentech, kterou mohou být samostatně odkládány

## Paging (stránky)
Paměť přidělována po rámcích s pevnou velikostí (nevzniká tak externí fragmentace)

### Jednoúrovňová tabulka
Tabulka je udřována v hlavní paměti
v MMU CR3 registru je uložen odkaz na začátek
Každý odkaz na data/instrukce v paměti si vyžaduje 2 přístupy do paměti (zrychlení pomocí TLB - translation look-aside buffer)
TLB obsahuje dvojice (císlo stárnky, číslo rámce) + některé z příznaků (přístupová práva, modifikace, etc..), prohledává se na základě čísla stránky, případně částečné indexaci a následnému dohledání (prvních n bitů pro indexaci, následující dohledáním)
Efektivní přístupová doba: `(t+e)a+(2t+e)(1−a)` | `(t+e)a+(2t+2e)(1−a)` pokud se efektivní adresa hned nepoužije
- t: vybavovací doba RAM
- e: vybavovací doba TLB
- a: pravděpodobnost úspěšných vyhledání v TLB (závisí na lokalitě odkazů programu)

#### Ukázka
32b systém, stránky 4KiB(2^12) může mít tabulka `2^30/2^12 = 2^12 = 1,048,576` položek
Má-li položka záznam 4B, dostaneme tabulku o velikost 4MiB pro každý proces


64b systémy, stránky 4KiB(2^12) může mít tabulka `2^64/2^12 = 2^52 = 4,503,5999,627,3701,496` položek


### Dvouúrovňová tabulka
32b logická adresa:
10 horních bitů na indexaci první tabulky pro přístup do druhé, kde se použije dalších 10b a následných 12b pro offset
Příznak v první tabulce může říct, zda je použita nižší úroveň stárnkování, nebo ne
Pracujeme se stránkami o velikosti 4KiB (2^12) a 4MiB(2^22)

### Hashovací tabulka
Hash funkce spočítá index v tabulce, kde se nachází odkaz na zřetězený seznam
Při sdílených stránek se

### Invertovaná tabulka stránek
Jen  jedna tabulka, počet záznamů je počet rámců v paměti (velikost paměti děleno velikost rámce)
Číslo rámce je index v tabulce, kde leží záznam obsahující číslo procesu a stránky
Pro nalezení rámce se použije hash funkce s argumenty pid a číslo stárnky, kde výsledkem bude odkaz na záznam v tabulce. Pokud se pid a číslo stránky rovná  údajům v záznamu, číslo řádku je číslo rámce. Pokud ne, vezme se odkaz na další, kde se test provádí znovu.


## Algoritmy pro výběr odkládaných stránek
### FIFO (first in first out)
Stránky jsou řetězeny podle pořadí zavedení a odstraňuje stránku na začátku řetězce
### LRU (least recently used)
Každé stránce posune referenční bit 1x doprava
Na MSB uložíme 1 pokud je stárnka navštívena, 0 pokud ne
Při odstraňování berem tu stárnku, která má nejmenší číslo
### Second-chance
Circular-buffer s referenčním bitem
Postupujeme a nulujeme referenční bit, dokud nenajdeme prví stránku, která již nulový bit mát: tu odstraníme



