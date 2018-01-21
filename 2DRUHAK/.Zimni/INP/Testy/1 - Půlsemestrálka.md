# Zadání 2017

## Skupina B

1. _(2b)_ Uvažte datovou cestu, která je na obrázku. A, B, C a D jsou vstupní registry. Y je výstupní registr. Do obrázku dokreslete **co nejmenší** počet registrů tak, aby obvod mohl pracovat na frekvenci alespoň 20 MHz.
    - ![Schéma](https://image.prntscr.com/image/mVTlPUWrT1Wd6TWBtMR8zQ.png "Schéma")
1. _(2b)_ Nakreslete co nejúspornější implementaci násobičky **W = X \* Y**, která operand X (na 8 bitech) násobí konstantou 15, tj. Y je vždy 15.
1. _(2b)_ Překédujte 6-bitové násobitele **B = -13** (v doplňkovém kódu) s využitím Boothova algoritmu s radixem 8. Uveďte všechny pomocné výpočty.
1. _(2b)_ V jazyce symbolických instrukcí zapiště program pro stradačový počítač, který sečte hodnoty uložené v paměti na **adr1** a **adr2**. Výsledek uloží do **adr3**.
1. _(2b)_ Na obrázku je neúplná 6-bitová sčítačka s obvodem CLA. EA značí rozšířenou sčítačku. S jakým zpožděním budou vypočteny uvedené bity? Δ Označuje zpoždění jednoho logického členu.
    - G0 - Zpoždění ... Δ
    - P1 - Zpoždění ... Δ
    - S1 - Zpoždění ... Δ
    - S5 - Zpoždění ... Δ
    - ![Sčítačka](https://image.prntscr.com/image/uZeJBoa4R_GcwJ37hveN1g.png "Sčítačka")
1. _(2b)_ Pomocí časového diagramu zpracování instrukcí vysvětele, kdy nastává tzv. strukturní konflikt při řetezeném zpracování instrukcí.
1. _(1b)_ Uvažte číslo v pohyblivé řádové čárce, u kterého zvýšíme exponent o 1 a posuneme mantisu o 1 bit vpravo. Jaká bude aboslutní chyba zobrazení, pokud původní chyba byla K?
1. _(1b)_ Jakou Hammingovu vzdálenost má Hammingův kód (7,4)? Kolikanásobné chyby může detekovat?
1. _(1b)_ Uveďte příklad operandů (tj. hodnoty A, B, C_in), pro které bude výsledek s postupným přenosem k dispozici už za dobu 2T (T Je zpoždění logického členu).
    - A =
    - B =
    - C_in =

# Zadání 2016

## Skupina A

1. _(3b)_ Dva operandy na 4 bitech `-3` a `-5` (oba jsou uvedeny v dvojkovém doplňku se znaménkem). Vynásobte, uveďte postup a NEPOUŽÍVEJTE Boothovo překódování.
1. _(3b)_ Uveďte vztah pro výpočet Gi a Pi (generate a propagate). Odvoďte vztah pro výpočet přenosu C1, C2 a C3 u 4-bitové sčítačky s 4-bit obvodem CLA. Určete zpoždění získávání přenosů. Uveďte operandy jako A, B a zpoždění d.
1. _(3b)_ Mějme zapsáno číslo v pohyblivé řádové čárce. Určete binárně i dekadicky maximální a minimální možné zapisovatelné číslo. <br/>
    Znaménko - 1 bit<br/>
    Exponent - 4 bit, sudý posun, BIAS = 8<br/>
    Mantisa - 5 bit, přímý kód
1. _(3b)_ Máme obrázek procesoru (nejspíš ten výukový z přednášky). Určete 3 instrukce pro vkládání hodnot do registru přes multiplexoru ACC_MX z RŮZNÝCH ZDROJŮ, zdůvodněte.
1. _(1b)_ Proč je z hlediska kompilátorů výhodná registrová architektura počítače?
1. _(1b)_ Kolik taktů trvá vynásobení dvou 8-bit unsigned čísel na sekvenční násobičce?
1. _(1b)_ Kolik taktů bude trvat provedení zřetězených N operací? V obvodu je k uzlů. V obvodu je také zapojena instrukce skoku, která pozastaví linku na 3 takty.

## Skupina B

1. Vynásobit `-2` a `-4` v doplňkovém kódu
1. Zakreslit `y=k+(a*x - b*x)` pomocí násobičky (20ns) odčítačky (15ns) a sčítačky (15ns) na 50MHz
1. Klasické IEEE 754 do dekadického čísla
1. Procesor z 1. Přednášky. Napsat jaké řídící signály se v jakém pořadí změní pro práci s ACC
1. Co znamená CPI=5?
1. 4 nezávislé zřetězené instrukce, každá o 5 taktech, kolik taktů to vezme celkově
1. Napsat Moorův zákon

# Zadání 2015

## Skupina C

1. Nakreslit zřetězené zpracování výrazu: `y = k + (a*x + b*x)` tak, aby frekvence zpracování byla max 50mhz. K dispozici je sčítačka (15ns), odčítačka (15ns) a násobička (20ns).
1. Dáno schéma násobičky s uchováním přenosu. Určete:
    - Zpoždění úplné sčítačky.
    - Zakreslit všechny poloviční sčítačky ve schématu.
    - Zvýraznit cestu, kde je nejdelší zpoždění.
    - Určit celkové zpoždění násobičky.
1. 0 0111 1011 1000 0000 0000 .... v IEEE 754. Vyjádřete hodnotu + postup.
1. Schéma procesoru z první přednášky, instrukce 3013. Určete, co se v který čas objeví na ABUS, DBUS, IREG, ACC, IAC. Tyto instrukce:
    | adresa | obsah |
    | ------ | ----- |
    | 0010   | 3013  |
    | 0011   | 0011  |
    | 0012   | 0012  |
    | 0013   | 0010  |
1. Definujte huffmanův kód, nakreslete strom, určete kódy, střední dynamickou a teoretickou optimální: (v závorce uvedena četnost výskytu)
    - A (0,4)
    - B, C, D (0,1)
    - E, F (0,15)

## Skupina D

1. Nakreslit zřetězené zpracování výrazu: `y = 5*k + (a-b)*x`. Tak aby bylo co nejméně stupňů. Zpoždění zanedbejte.
1. Dáno schéma násobičky s uchováním přenosu. Určete:
    - Označení úplné sčítačky.
    - Kolik log. členů obsahuje poloviční sčítačka?
    - Kolik log členů obsahuje násobička (včetně část. součinů) pokud úplná sčítačka je ze 6 log. členů?
    - Jestli má základní násobička menší nebo větší zpoždění?
1. 0 01111110 11000000000000000000000 v IEEE 754. Vyjádřete hodnotu + postup.
    - Řešení: `2^(126-127) * (1 + 0,75) = 0,875`
1. Schéma procesoru z první přednášky, instrukce 3013. Určete, co se v který čas objeví na ABUS, DBUS, IREG, ACC, IAC. Tyto instrukce:
    | adresa | obsah |
    | ------ | ----- |
    | 0090   | 3092  |
    | 0091   | 0056  |
    | 0092   | 0093  |
    | 0093   | 0090  |
1. Definujte huffmanův kód, nakreslete strom, určete kódy, střední dynamickou a teoretickou optimální: (v závorce uvedena četnost výskytu)
    - A(0,3)
    - B,C,D,E(0,1)
    - G, H (0,15)
