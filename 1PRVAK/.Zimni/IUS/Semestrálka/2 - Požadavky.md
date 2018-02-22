# Analýza a specifikace požadavků / problémů

## Postup při specifikaci požadavků

- Studie vhodnosti
    - Prvotní odhad, zda jsme schopni splnit požadované zadání v navrhovaném rozsahu, čase a s jakými náklady.
- Analýza požadavků
    - Analýza představuje zkoumání požadavků zákazníka.
- Definování požadavků
    - Transformace informací z analýzy požadavků do dokumentu určeného především pro uživatele a zákazníka.
- Specifikace požadavků
    - Transformace informací z analýzy požadavků a definice požadavků do pokud možno formálního, strukturovaného dokumentu určeného pro vývojáře.
- Specifikace SW
    - Dokument popisující architektutu vyvíjeného SW.

![Postup při specifikaci požadavků](https://image.prntscr.com/image/vMm5CSyVTyC0FfIt2ZCJBQ.png "Postup")

## Typy požadavků

### Obchodní požadavky (Business requirements)

- Zjištění, proč zákazník potřebuje systém.
    - Pochopení a definice cílů projektu.
- Zaměření na obchodní cíle.
    - Úspora nákladů, času.

### Uživatelské požadavky (User requirements)

- Úlohy, které uživatel se systémem provádí.
    - Co se systémem lze dělat.
- `Use cases`

### Funkční požadavky (Functional requirements)

- Chování systému v různých podmínkách.
- Co musí být realizováno, aby byly vykonány `User requirements` a tím splněny `Business requirements`.
- `Activity Diagram`

### Nefunkční požadavky (Nonfunctional requirements)

- Vlastnosti, které musí SW splňovat a omezení, které musí respektovat.
- Duležitá je `měřitelnost požadavků`, jak z pohledu vývojáře, tak zákazníka.
- _Příklady:_
    - Požadavky na provoz systému
        - Statické
            - Počet uživatelů.
            - ...
        - Dynamické
            - Čas odezvy.
            - Počet transakcí na jednotku
            - ...
    - Požadavky na výsledný systém
        - Počítačové vybavení
            - RAM
            - CPU
            - ...
        - Programové vybavení
            - OS
            - Programovací jazyky
            - ...
        - Vyvíjený SW
            - Efektivnost
            - Spolehlivost
            - ...

## Metody získávání informací

### Interview (orientační, strukturované)

- Základní běžná forma zjišťování potřeb zákazníka.
- _Orientační_
    - První setkání.
    - Získat základní přehled potřeb.
- _Strukturované_
    - Připravené otázky.
    - Získat hlubší představu.
- Nejen naslouchat, ale navrhovat alternativy, popostrkovat zákazníka.

### Dotazník

- Lze obsáhnout velkou skupinu lidí.
- Dobře připravené otázky s předem definovaným způsobem vyhodnocení.

### Pracovní setkání (Workshop)

- Skupina lidí (`Stakeholders`) vyjednává o požadavcích a pracuje společně na specifikaci požadavků.
- Během workshopu se všichni "stakeholdeři" seznamují se systémem, cíli, ...
- Jedná se o strukturovanou techniku, je důležité mít zkušeného moderátora.

### Prozorování prací u zákazníka

- Umožňuje lépe pochopit aktivity a procesy.
- Ověřit získané informace.
- Odhalit dosud neznámé informace.

## Problémy při specifikaci požadavků

### Přirozená neúplnost a nepřesnost

- Nejasná a neúplná formulace požadavků zákazníkem.
- Neucelená představa uživatelem o výsledném SW.

### Nedostatek znalostí

- Vývojář (Analytik) se neorientuje v doménové problematice.
- Zákazník se neorientuje v problematice vývoje SW.
    - Nemá představu, co je a co není technicky možné.

### Nekonzistentnost požadavků

- Různí uživatelé mají různé požadavky a priority.
- Často rozporné požadavky.

![Zapojení uživatele do procesu](https://image.prntscr.com/image/xnxUUZtxTDaDDJOqlacqOg.png "Zapojení uživatele do procesu")

## Prototypování

- Uživatelům se lépe formulují požadavky v relaci s reálným produktem.
- Prototypování dokáže ověřit správnost návrhu. (`Validace požadavků`)
- Může nastínit různé alternativy návrhu.

### Prototyp

- Částečná implementace produktu.
- Prezentuje vnější rozhraní systému.
- Většinou je implementován rychle za účelem demonstrace.
- Není kladen důraz na kvalitu návrhu a programování.

## Dobrá specifikace požadavků

### Seřazení dle důležitosti

- Datum vytvoření požadavků.
- Seskupení požadavků do tříd podle priorit.

### Sledovatelná

- Původ (smysl) požadavků musí být jasný.
- Na každý požadavek je možné se odkazovat v další dokumentaci.

### Modifikovatelná

- Konzistentní struktura a styl.
- Žádné redundance.
- Snadné úpravy a doplňování požadavků.

### Jednoznačná

- Neumožňuje více interpretací.
- Pozor na přirozený jazyk.

### Verifikovatelná

- Existuje proces kontroly, zda SW splňuje požadavek.
- Měřitelnost splnění požadavků (`DOD` - `D`escription `O`f `D`one).

## Určení spolehlivosti a dostupnosti

![Funkce](https://image.prntscr.com/image/Pz5VUeP7RWOgAtuNFEGEVg.png "Funkce")

Střední doba do následujícího výpadku `MTTF` <br />
Střední doba opravy `MTTR` <br/>
Střední doba mezi výpadky systému `MTBF` <br />
`MTTF` = (3 + 3 + 5 + 7) / 4 = 18 / 4 = **4,5 dne** <br />
`MTTR` = (2 + 3 + 1 + 1) / 4 = 7 / 4 = **1,75 dne** <br />
`MTBF` = `MTTF` + `MTTR` = 25 / 4 = **6,25 dne** <br />
dostupnost = `MTTF` * 100 / `MTBF` = 18 * 100 / 25 = **72%**
