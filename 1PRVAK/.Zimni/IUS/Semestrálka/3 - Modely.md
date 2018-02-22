# Modely životního cyklu

- Definuje etapy vývoje SW a časovou následnost.
- Definuje nutné činnosti pro každou etapu.
- Definuje vstupy a výstupy pro každou etapu.

## Vodopádový model

- Lineární / Sekvenční model
- Následující etapa začne až po ukončení předcházející.
- Možnost návratu na předchozí, ale ne na začátek.
- Dekompozice a kontrola výstupů.
- Uživatel se účastní pouze při definování požadavků a zavádění.

### Výhody

- Jednoduché řízení.
- Nejlepší definice struktury výsledného produktu.

### Nevýhody

- Zákazník není schopen předem stanovit (přesně) všechny požadavky.
- Při změnách požadavků nastává dlouhá doba realizace.
- Zákazník vidí spustitelnou věc až v závěrečných fázích projektu.
    - Validace příliš pozdě.

![Vodopádový model](https://image.prntscr.com/image/DPucFDb4SayhcShCk2Uptw.png "Vodopád")

## V-Model

- Vychází z [vodopdového modelu](#vodopádový-model "vodopádového") a zachovává jeho srozumitelnost a jednoduchost.
- Název symbolizuje grafické uspořádní etap.
    - Zdůrazňuje vazby mezi návrhovou a testovací částí.
    - V => Validace, Verifikace
- **Levá část**
    - Vývojové aktivity
    - Plánování testů
- **Pravá část**
    - Testovací aktivity
    - Provádění testů podle plánů

![V-Model](https://image.prntscr.com/image/a-qnR3d2R5mnJ7cJBftjWg.png "V-Model")

## W-Model

- Vychází z [V-Modelu](#V-Model).
- Každá fáze se validuje, včetně té dokumentační.
- **Levá část**
    - Ověření výstupů etap, plánování a návrh testů
- **Pravá část**
    - Provádění testů, změny kódu, regesní testování

![W-Model](https://image.prntscr.com/image/MOwRdReASdKFmIQvIjwyIw.png "W-Model")

## Iterační model

- Systém se vyvíjí v iteracích.
- V každé iteraci se může vyvinout neúplný výsledek, který je později zlepšován.
- Možnost poučení se z předchozí iterace.
- Typické pro agilní vývoj.

### Výhody

- Zákazník má možnost validovat výsledek se svými požadavky po každé iteraci => Rychlejší odhalení chyb.

### Nevýhody

- Náročnější na řízení.
- Potencionálně horší výsledná struktura.

![Iterační model](https://image.prntscr.com/image/Wb9Q5nIzRJuW3fOt9UmXcA.png "Iterační model")

## Inkrementální model

- Kombinace lineárního a iterativního
- Celý produkt je rozdělen do několika funkcionalit, které jsou dodávany postupně.
- Každá funkcionalita je dodávána úplná.

### Výhody

- Lépe se testují jednotlivé inkrementy.
- Lépe se řídí rizika díky malým iteracím.
- Lépe se mění zadání.

### Nevýhody

- Je zapotřebí dobrý plán a návrh.
- Znalost celého systému, aby se mohl rozbít na části.

![Inkrementální model](https://image.prntscr.com/image/jk-pLpLKTCKBEnCIVVCB3g.png "Inkrementální model")

## Spirálový model

- Implementace vodopádového a iteratrivního modelu s prototypováním.
- Díky analýze rizik je vhodný na velké nebo riskantní projekty.
- Zjednodušuje zavedení změn během vývoje.

### Fáze

- **Stanovení cílů**
    - Shromáždění požadavků (SRS, BRS)
- **Vyhodnocení**
    - Analýza rizik
    - Na konci cyklu je vytvořen prototyp
- **Realizace**
    - Implementace a testování
- **Plánování**
    - Plán vývoje
    - Plán testování

### Výhody

- Kladen důraz na analýzu rizik.
- Silná kontrola dokumentace.

### Nevýhody

- Vyžaduje zkušenosti s analýzou rizik.

### Milníky

Slouží jako indikátor postupu a body závazků.

- **Life Cycle Objectives**
    - Definice technických a manažerských postupů.
- **Life Cycle Architecture**
    - Definice architektury
- **Initial Operation Capability**
    - Přípavy k distribuci

![Spirálový model](https://image.prntscr.com/image/_HaJotzMQ-CK713R5lItUg.png "Spirálový model")

## Extrémní programování

- Způsob agilního vývoje.
- Zaměřen na měnící se požadavky zákazníka.

### Hodnoty

- **Komunikace**
    - Programátoři potřebují vědět, o čem systém má být a jak ho chce uživatel používat, aby mohl správně navrhnout a implementovat funkcionalitu.
- **Jednoduchost**
    - Nedělat věci, které nejsou potřeba (**YAGNI/Kiss** princip).
- **Zpětná vazba**
    - Rychlé informace o nedostatcích.
        - Od systému, zákazníka, programátorů
- **Odvaha**
    - Odvaha odstranit / změnit zastaralý kód (systém), aby byl v budoucnu lépe rozšiřitelný.
- **Respekt**
    - Neintegrovat kód, který není funkční.
    - Nezpomalovat vývoj.

### Aktivity

- **Coding**
    - Možnost *pair programming* => lepší kvalita kódu.
- **Testing**
    - "*Pokud trocha testování eliminuje pár chyb, více testů eliminuje více chyb.*"
    - BDD, TDD...
- **Listening**
    - Programátoři musí rozumět tomu, co zákazník potřebuje.
- **Designing**
    - Smyslem je mít takovou strukturu systému, kde přidání nové funkcionality nerozbije stávající systém, ani jej nebude potřeba předělávat.

### Praktiky

- **Pair programming**
    - Programování ve dvou.
        - Obvykle jeden kódí druhý dělá *review*.
    - Zlepšení kvality kódu, snížení počtu zanesených chyb.
- **Planning game**
    - Cílem je určení doby potřebné k implementaci nějaké funkcionality.
- **Refactoring**
    - Úprava stávajícího kódu pro zlepšení kvality.
- **CI**
    - Continous integration.
- **TDD**
    - Test Driven Development
    - Nejdříve testy, poté implementace.
- **BDD**
    - Behaviour Driven Development
    - Zaměřuje se na to, co systém musí umět.
    - Využívá akceptačních testů.

![Extrémní programování](https://image.prntscr.com/image/XKY9odAHTUidwf8pF0JnZw.png "Extrémní programování")

## RAD (Rapid Application Development)

- Rychlý, iterativní a inkrementální vývoj prototypů.
- Využívá time boxing.
    - Vymezení času a určení funkcionality v něm dodané.
- Zaměřuje se více na funkcionalitu, než na dokumentaci a jiné věci.

### Fáze

- **Plánování**
    - Analýza a plánování systému
- **Návrh**
    - Modelování, prototypování
- **Provedení**
    - Implementace, testování, integrace
- **Nasazení**
    - Předání systému, zaškolení uživatelů

### Výhody

- Flexibilita, schopnost rychlé změny podle potřeb zákazníka.
- Vyšší kvalita zpracování business potřeb díky prototypování.

### Nevýhody

- Pouze pro modularizovatelné projekty.
- Nutná spolupráce se zákazníkem.

![RAD](https://image.prntscr.com/image/5uSeAJ-3Ra2xSfAwXa0q6w.png "RAD")

## RUP (Rational Unified Process)

- Iterativní a inkrementální přístup.
- Zameřený na rizika.
    - Nejrizikovější části se implementují dříve.

### Praktitky

- Udržování zákazníkových požadavků.
- Vizualizování SW modelu.
- Kontrola změn se zákazníkem.
- Kontinuální verifikace kvality.
- Využívání komponentů.

### Cyklus

- **Initial**
    - Zajištění první funkční verze.
- **Evolution**
    - Zajistí další funkční verzi.

### Fáze

- **Inception**
    - Zajištění prostředků, hranic projektu.
    - Zjištění požadavků.
- **Elaboration**
    - Návrh architektury.
    - Prozkoumání rizik aplikace.
- **Construction**
    - Systém je implementován v několika krátkých iteracích.
- **Transition**
    - Předání systému.
    - Zaškolení uživatelů.

### Mezníky

- **Life Cycle Objectives**
    - Vyhodnocení záměrů (požadavky, cena, priority), rizik a jejich odstranění.
- **Life Cycle Architecture**
    - Výběr architektury, zajistí stabilitu požadavků a architektury.
- **Initial Operation Capability**
    - Příprava a testování u uživatele.
    - Srovnání výdajů.
- **Product Release**
    - Podle spokojenosti zákazníka rozhodnout, zda je možno přejít do dalšího cyklu.

### Výhody

- Robustní (Pro velké projekty).
- Detailní propracovanost.
- Včasné odhalení rizik.
- V každé iteraci se vytvoří reálný výsledek.
    - => Zákazník má možnost validovat výsledek s požadavky.

![RUP](https://image.prntscr.com/image/p5x3wr84QTSKrCG0seqWXg.png "RUP")

## Scrum

- Iterativní a inkrementální vývoj.
- Využívá _time boxing_ (sprinty).
- Časté uvolňování verzí.
- Nedefinuje přesný postup úloh.

### Role

- **Product owner**
    - Rozumí potřebám zákazníka.
    - Nastavuje prioritu úkolům.
- **Scrum master**
    - Zlepšuje prostředí týmu.
    - Moderuje akce.
    - Chrání tým před vyrušováním.
- **Development team**
    - Skládá se z několika pozic: _analytik, programátor, tester, architekt, ..._.
    - Zajišťuje implementaci v daném čase.

### Fáze

- **Pre-game**
    - Definice základní funkcionality.
    - Upřesňuje použité technologie a architekturu.
- **Game**
    - Probíhá v iteracích.
- **Post-game**
    - Testování celého systému.
    - Príprava dokumentace.
    - Zaškolování a akceptační testy.

## Crystal

- Iterativní a inkrementální proces.
- Rodina metodologií.
- Projekty rozděleny podle kritičnosti:
    - Comfort
    - Discretionary
    - Essential
    - Life

### Výhody

- Časté uvolňování verzí.
- Zapojení uživatelů.
- Průběžná integrace.
- Požadavky se řeší "za chodu".

### Nevýhody

- Nedefinuje jasný proces.
- Nevhodný pro kritické projekty.
