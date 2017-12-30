1. Všeobecný prehled (6b)
    - Jaké základní 3 nastavení může být v souboru `.editorconfig`?
    - Uvést 3 nástroje na sdílení zdrojů v týmech?
        - Krátký popis, klady, zápory
    - Jak bude vypadat příkaz překladu gcc?
        - Chceme preložit soubor (a) prekladačem (b) při profilovaní pomocí gprof.
1. Doxygen komentáře (6b)
    - Je tam kod a má se doplnit komentáře.
1. Makefile (6b)
    - Vytvořte Makefile pro projekt IVS-2017
        - Máme adresář src(main.c, plus nejaké dalšíe dvě), obj(prázdny), doc(prázdny), include (knihovna.h, asi dvě)
        - Předdefinované byly nějaké adresáře `SRCDIR = src` a `OBJDIR = obj`, a potom obsahy jako `SOURCES` a `OBJECTS`
    - Podúkoly:
        - Makefile bez parametrů přeloží a vytvoří spustitelný soubor.
        - Makefile přeloží zdrojové soubory na objekty.
        - Makefile preloží objekty na spustitelné soubory.
        - Makefile spustí vytvorené soubory pomocí cíle `run`.
        - Makefile vytvoří dokumentáci pomocí cíle `doc`.
            - Pomocí doxygenu
        - Makefile vytvoří zip s určitým názvom pomocí cíle `pack`.
        - Makefile vyčistí projekt pomocí cíle `clean`.
    - Bylo důležité hlavně napsat správně závislosti tak, aby nedocházel k vícenásobnému překládání.
1. GIT (6b)
    - Co to znamená `git head detached state`?
    - `Git merge` a jeho dvě možnosti spojování větví.
    - Co znamená chybové hlášení `git-u non-fast forward updates were rejected`?
    - Struktura repozitáře.
        - Zobrazit pomocí šipek rozděl mezi commitali ste zobraziť (aj pomocou ukazovateľov - šípiek  ) rozdiel medzi commit - issue pre git merge a commit issue pre git rebase. ???
1. ??? (6b)
    - Jaké 4 stupně testování existují.
        - V jakých fázích vývoje se s nimi lze potkat.
    - Metody zabezpečení UNIT testů.
    - Definice `verifikace, validace`.
1. ??? (6b)
    - Uveďte aspoň 3 typy souborů, které není vhodné verzovat.
    - Co by měla obsahovat chybová hláška pro neplatný přístup?
        - Jak má vypadat a jak nemá vypadat
    - Co to znamená viditelnost stavu systému.
    - Rozdíl mezi `mockupom, wireframe, prototypem`.
