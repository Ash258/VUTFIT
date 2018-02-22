# Softwarové inženýrství

- Systematický přístup k vývoji, nasazení a údržbě SW.
- Inženýrská disciplína zabývající se praktickými problémy vývoje SW systémů.

## Důvody vzniku SW

- Zlepšení služeb
    - Informační systémy
- Snížení nákladů
    - Řízení výroby
- Nemožnost řešení bez použití softwaru
    - Předpověď počasí
    - ...

## Klíčové úkoly SW inženýrství

- Zlepšovat vlastnosti SW
    - Spolehlivost
    - Bezpečnost
    - Použitelnost
- Zvyšovat produktivitu

## Světové katastrofy

- Přetečení 64bit čísla v plovoucí čárce => Autodestrukce rakety Ariane 5.
- Sovětstký systém pro včasné varování před nukleárním útokem nahlásil útok z USA na Moskvu. Jednalo se o odraz slunce od mraků.
- Odstranění HW zábrany a několik SW chyb v přístroji `Therac-25` => Ozářeno 6 lidí.

## SW krize

> Nastala v 60. létech 20. století. <br />
Prvními kroky k metodickému přístupu programování – `Strukturované programování`.

### Následky krize

- Neúnosné prodlužování a prodražování projektů.
- Nízká kvalita výsledných projektů.
- Problematická údržba a inovace.
- Špatná produktivita programátorů.
- Řada neúspěšných projektů.

## Problémy při vývoje SW

### Podstatné vnitřní problémy

- Složitost
    - Je náročné pochopit všechny možné stavy systému, problémy s úpravami a rozšířením.
- Nepřizpůsobivost
    - SW se neumí přizpůsobit na změny (požadavky, prostředí).
- Nestálost
    - Změny prostředí zapříčiní nestálost systému.
- Neviditelnost
    - Nelze určit, co chybí v reprezentaci SW produktu.
- Syndrom 90% hotovo
    - Při posuzování hotové části se nevychází z hotového, ale z naplánovaného.

### Problémy, které se nemusí projevit

- Práce v týmu
    - Problémy s organizací, komunikací, plánováním...
- Nízká znovupoužitelnost
    - Málo standartů
    - Neustálé vymýšlení už vymyšleného
    - ...
- Problémy míry
    - Metody použitelné na řešení malých problémů se nedají přizpůsobit na řešení velkých (složitých) problémů.
- Tvorba dokumentace
    - Problémy s udržováním vzhledem ke změnám s úplností a konzistencí.
- Náchylnost SW k chybám
    - Hodně chyb se projeví až při provozu.
- Specifikace požadavků
    - Problém komunikace, nejasnosti a neúplnosti formulace ...
- Přidání dalších pracovníků
    - Přidáním dalších pracovníků do zpožděného projektu se tento projekt ještě více zpozdí.
- Syndrom druhého systému
    - Autor povzbuzen úspěchem prvního systému chce nový systém udělat dokonalý.
    - Nový systém je pak příliš složiý, nepřehledný a neefektivní.
    - Systém není dokonalý, když k němu nelze nic přidat, ale tehdy, když z něho nelze nic odstranit.
- Stárnutí SW
    - Přidávání nových funkcí ve spojení s opravami chyb snižuje spolehlivost systému.

![Křivka stárnutí SW](https://image.prntscr.com/image/3b0E3kAeSUmXHxmvxjV1EA.png "Křivka stárnutí SW")

# Metodiky vývoje softwaru

## Terminologie

- Metoda
    - Postup pro dosažení určitého cíle.
- Metodika
    - Souhrn doporučených praktik a postupů.
- Metodologie
    - Nauka o metodách a jejich tvorbě.
- Program
    - Funkční část produktu.
- SW produkt
    - Sbírka programů, procedur, pravidal a dokumentace (specifikace, popisy návrhu, testovací data, příručky).

### Validace

- Kontrola, zda vyvíjený systém splňuje to, co od něj zákazník očekává.
- Zadal požadavky a zajímá ho, zda to, co dostane, je to, co chce.
- Ověřování, že se vyvíjí to, co má (správný produkt).

### Verifikace

- Kontrola, zda vyvíjený systém vyhovuje specifikacím (návrhu).
- Existuje nějaký model/návrh a podle něj se systém vyvíjel.
- Verifikací se ověřuje, že vyvinutý systém odpovídá návrhu. (produkt se vytváří správně).

---

### Správnost SW (Corectness)

> Do jaké míry SW vyhovuje požadavkům uživatele.

### Spolehlivost SW (Reliability)

> Míra jak moc SW vykonává práci bez neočekávaných chyb.

### Použitelnost SW (Usability / Learnability)

> Míra úsilí a čas vynaložený učením se SW.

### Bezpečnost SW (Security / Safety)

> Míra ochrany dat.

### Přenositelnost SW (Portability)

> Schopnost SW vykonávat stejnou funkcionalitu na jiném prostředí a platformě.

### Znovupoužitelnost SW (Reusability)

> Schopnost kódu být použitelný pro jiný účel.

### Interoperabilita SW (Interoperability)

> Shopnost výměny informací s jinými aplikacemi.

### Udržovatelnost SW (Maintability)

> Schopnost SW reagovat na měnící se potřeby zákazníka.

### Testovatelnost SW (Testability)

> Testování SW funkcionalit by mělo být lehké.

### Modularita SW (Modularity)

> Míra samostatnosti jednotlivých částí systému, které jsou integrovány dohromady.
Pokud jsou samostatné, lze je samostatně testovat a měnit.

### Dokumentovatelnost SW

> Míra, do jaké jsou všechna rozhodnutí při vývoji SW dokumentovaná.

---

### Aktéři při vývoji SW

- Zákazník
    - Sponzoruje vývoj SW.
    - Specifikuje požadavky.
- Dodavatel
    - Vyvíjí systém.
    - Má závazky vůči zákazníkovi.
    - Komunikuje se zákazníkem.
- Uživatel
    - Testuje a používá systém.
    - Upřesňuje požadavky SW.

### Typy SW produktů

- Generické
    - Obecné
    - SW se prodává libovolnému zájemci. `Krabicový SW`
    - Musí být důkladně testován, protože opravy jsou vzhledem k velkému rozšíření drahé.
- Zákaznické
    - SW se vytváří na základě požadavků pro konkrétního zákazníka.
    - Cena je výrazně vyšší.

## Proces vývoje SW

> Definuje, kdo má kdy co dělat, aby byly splněné požadavky.
Jedná se o implementaci `SDLC` (`S`oftware `D`evelopment `L`ife `C`ycle)

# Životní cyklus SW

> Model životního cyklu SW definuje etapy vývoje SW a pro každou etapu dále definuje nutné činnosti a její vstupy a výstupy.

## Jednotlivé etapy cyklu

- Analýza a specifikace požadavků - _8%_
    - Získávání, analýza, definování a specifikace požadavků => Transformace neformálních požadavků uživatele do strukturovaného popisu požadavků.
    - Plánování akceptačního testování.
    - Provedení studie vhodnosti a analýza rizik.
- Architektonický a podrobný návrh - _7%_
    - **Architektonický**
        - `Dekompozice systému`
            - Rozbití na podsystémy.
            - Soustředění pozornosti na jeden podsystém.
            - Prezentovatelnost dílčího problému bez rušivých vlivů.
            - Nezávislý vývoj.
        - Specifikace funkcionality a ohraničení podsystémů.
        - Plánování testování.
        - Plánování nasazení do provozu.
    - **Podrobný**
        - Podrobná specifikace SW součástí.
        - Specifikace algoritmů, rozhraní, struktury.
        - Specifikace požadavků na lidské zdroje.
        - Plán testování a testovacích dat.
- Implementace a testování - _12%_
    - Realizace SW součástí.
    - Vypracování dokumentace.
    - Testování součástí.
    - Školení budoucích uživatelů.
- Integrace a testování - _6%_
    - Akceptační testování.
        - Testování systému uživatelem.
        - Přebírání SW produktu.
        - Školení používání systému.
    - Integrace podsystémů do systému.
    - Testování celého systému.
- Provoz a údržba - _64%_
    - Zabezpečení provozu.
    - Řešení problémů s nasazením a používáním SW.
    - Opravy, rozšiřování, přizpůsobování.
