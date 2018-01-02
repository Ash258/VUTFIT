# How to use

- `docker-compose up --build -d`
- `docker exec -ti c_develop bash`
- `../Setup/setup.sh`

# Úvod

Cílem tohoto projektu je si prakticky vyzkoušet typické úlohy spojené s testováním softwareu pomocí tzv. unit testů. Projekt je rozdělen do tří částí, jejichž účelem je otestovat neznámý kód (**black box testy**), otestovat známý kód (**white box testy**), ověřit pokrytí kódy testy (**code coverage**) a implementovat kód na základě testů (**Test drive development**).
Za každou z těchto úloh je možné získat až **6 bodů**, za celý projekt lze tedy získat až **18 bodů**.

## Použité nástroje

Jako implementační jazyk byl zvolen C/C++. (základní znalost by měla být dostatečná). Jako testovací framework je využívána kombinace:

- [GoogleTest](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md "Google test")
- [CMake/CTest](https://cmake.org/documentation/ "CMake/CTest")
- [GCOV](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html "GCOV")

## Hodnocení

Pro hodnocení bude použit server `ivs.fit.vubt.cz` a vaše řešení na tomto serveru tedy závazn2 fungovat.
Tento server také můžete použít pro vyhodnocení pokrytí kódu (viz dále).

## Struktura projektu

- Systém překadu (CMake)
    - Systém pro vygenerování skriptu pro překlad je tvořen soubory (není potřeba je upravovat):
        - `CMakeLists.txt`
        - `CMakeLists.txt.in`
        - `CodeCoverage.cmake`
        - `GoogleTest.cmake`
- Úloha black box testing
    - `blackboxtests.cpp` - Zdrojový soubor, do kterého je třeba doplnit příslušné testy.
    - `blackboxlib.a/.lib` - Knihovna, která obsahuje testovaný kód
    - `redblacktree.h` - Hlavičkový soubor pro binární strom
- Úloha white box testing
    - `whiteboxcode.h` a `whiteboxcode.cpp` - Obsahují testovaný kód.
    - `whiteboxtests.cpp` - Do kterého je třeba doplnit příslušné testy.
- Úloha test driven development
    - `tddcode.h` - Obsahuje definici rozhraní prioritní fronty, kterou je třeba implementovat.
    - `tddcode.cpp` - Implementace prioritní fronty.
    - `tddtest.cpp` - Obsahuje testy prioritní fronty, které musí vaše řešení splnit.
- Odevzdávané soubory
    - Odevzdávají se **POUZE** soubory zabalené do ziparchivu (lze pomocí Cmake)
        - `blackboxtests.cpp`
        - `whiteboxtests.cpp`
        - `tddcode.h`, `tddcode.cpp`

## Prerekvizity a překlad

Projekt je primárně určen pro platformu Linux/GCC, avšak lze jej přeložit a spustit i na Windows (Visual Studio/MSVC). Pod Windows však může být problém použít nástroje pro analýzu pokrytí kódu, které jsou založené na GCC.

### Windows

#### Prerekvizity

- Microsoft Visual Studio 2015
- [CMake 2.8.2+](https://cmake.org "CMake")
- [GoogleTest](https://github.com/google/googletest/archive/master.zip "Google Test")
- [Případně GIT client pro Windows](https://git-for-windows.github.io/ "GIT")
    - Pak si CMake skripty umí GoogleTest stáhnout automaticky z repozitáře.

#### Překlad a spustění

1. Soubor se zadáním projektu rozbatle do libovolného adresáře.
1. Do libovolného adresáře rozbalte [CMake](https://cmake.org/files/v3.7/cmake-3.7.2-win64-x64.zip "CMake")
    - Nebo nainstalujte [CMake](https://cmake.org/files/v3.7/cmake-3.7.2-win64-x64.msi "CMake")
1. Spusťte konzoli a přesuňte se do adresáře `assignment-build`.
    - Pokud používáte zip verzi CMaku, je třeba aktualizovat PATH:
        - `set PATH=%PATH%;cesta\k\cmake.exe;`
        - Toto nastavení je dočasné (do zavření okna konzole)
1. Pokud není dostupný nástroj GIT, je nutné v aktuálním adresáři rozbalit archiv `googletest-master.zip`, tak aby je obsah byl v adresáři: `assignment/build/googletest-master`.
1. Soubory pro překlad je možné vygenerovat příkazem:
    - `cmake ..`
    - Vygeneruje Solution (případně stáhne GoogleTest) a měl by skončit výstupem: **Vuild files have been writeen to: ...**.
    - Tento krok je nutné opakovat po každém přidaném novém testu!
    - Pokud není Cmake nalezen je zřemě špatně nastavená proměnná PATH, nebo je třeba po jeho instalaci restartovat systém.
1. Tím by měl v aktuálním adresáři vzniknout projektový soubor pro Visual Studio `ivs.proj1.sln`, který můžete otevřít a použít pro vypracování úloh.
1. Překlad je možné provést z konzole příkazem:
    - `cmake --build .` nebo ve Visual Studiu.
1. Visual Studio by mělo být schopné spustit jednotlivé testy přímo z textového editoru (tlačítko na řádku s testem v postranní liště vlevo.
    - Jinak je možné testy spouštět z příkazové konzole přes CMake pomocí:
        - `ctest -C Debug`
1. Odevzdávaný archív je možné vytvořit příkazem:
    - `cmake --build . --target pack`
    - Stále v adřesáři `assignment/build`, který vytvoří archív `xlogin.zip`.
    - Archív zkontrolujte a přejmenujte dle svého loginu.
    - Vytvoření archívu je možné pouze s CMake 3.2 a novějším!

### Linux

#### Prerekvizity

- GCC 4.9.0+
    - Mělo by být dostupné v repozitářích pro danou distribuci.
- GCOV
    - Mělo by být dostupné v repozitářích pro danou distribuci.
- LCOV
    - http://downloads.sourceforge.net/ltp/lcov-1.13.tar.gz
    - Nebo v repozitářích
- CMake 2.8.2+
    - Mělo by být dostupné v repozitářích pro danou distribuci.
- [GoogleTest](https://github.com/google/googletest/archive/master.zip "GoogleTest")
- Případně GIT client
    - Mělo by být dostupné v repozitářích pro danou distribuci.
    - Pak si CMake skripty umí GoogleTest stáhnout automaticky z repozitáře.

#### Překlad a spustění

1. Soubor se zadáním projektu rozbalte do libovlného adresáře
    - `unzip ivs_project_1.zip`
1. Pokud nepoužíváte systémovou instalaci LCOV (například na serveru merlin) je nutné rozbalit staženou verzi do adresáře `./assignment`
    - `tar -xvf lcov-1.13.tar.gz`
    - `mv lcov-1.13 lcov`
1. Přesuňte se do adresáře `./assignment/build`, kde budou vytvořeny soubory překladu, výsledné spustitelné soubory a výstupní nástroje pro analýzu pokrytí kódu (GCOV/LCOV).
1. Pokud není dostupný nástroj GIT, je nutné v aktuálním adresáři rozbalit archiv `googletest-master.zip`, tak aby je obsah byl v adresáři: `assignment/build/googletest-master`.
1. Soubory pro překlad je možné vygenerovat příkazem:
    - `cmake ..`
    - Vygeneruje Solution (případně stáhne GoogleTest) a měl by skončit výstupem: **Vuild files have been writeen to: ...**.
    - Tento krok je nutné opakovat po každém přidaném novém testu!
    - Pokud není Cmake nalezen je zřemě špatně nastavená proměnná PATH, nebo je třeba po jeho instalaci restartovat systém.
1. Tím by měl v aktuálním adresáři vzniknout projektový soubor pro Visual Studio `ivs.proj1.sln`, který můžete otevřít a použít pro vypracování úloh.
1. Nyní by mělo být možné přeloži projekt pomocí:
    - `cmake --build .`
    - nebo
    - `make`
1. Testy je možné spustit pomocí:
    - `ctest -C Debug`
    - Nebo každou část projektu oddělené přímo pomocí příslušných spustilených souborů:
        - `./black_box_test`
        - `./white box test`
        - `./tdd test`
1. Odevzdávaný archív je možné vytvořit příkazem:
    - `cmake --build . --target pack`
    - Stále v adřesáři `assignment/build`, který vytvoří archív `xlogin.zip`.
    - Archív zkontrolujte a přejmenujte dle svého loginu.
    - Vytvoření archívu je možné pouze s CMake 3.2 a novějším!

#### Ověření pokrytí kódu

Za předpokaldu, že překlad a spuštění projektu proběhlo bez problémů, je nyní možné přistoupit k ověření pokrytí kódu testy pomocí nástrojů GCOV a LCOV.
Pro tento účel vytváří CMake cíle `white_box_test_coverage` a `tdd_test_coverage`. Analýzu pokrytí kódu je pak možné provést příkazem: <br />
`make white_box_test_coverage`<br />
nebo<br />
`make tdd_test_coverage`<br />
Výsledky analýzy by měly být v adresářích `white_box_test_coverage` nebo `tdd_test_coverage` ve formátu HTML a lze je zobrazit pomocí `index.html` v příslušném adresáři.

## Úlohy

V rámci projektu je třeba vypracovat tři úlohy zamřeneé na testování neznámého kódu (black box), testováním známého kódu (white box) a implementace dle testů (test driven development).

### Black Box Testing (až 6 bodů)

Cílem této úlohy je otestování základních operací nad neznámou implementací [Red-Black tree](viz https://en.wikipedia.org/wiki/Red-black_tree "Red-Black Tree") na základě jejich definice.

#### Red-Black Tree

Red-Black Tree je stromová struktura (binární strom), která umožňuje provedení základních operací (vkládání, mazání a vyhledávání) v logaritmickém čas O(log n).
Struktura stromu je tvořena kolekcí uzlů, které jsou propojeny tak, že každý má maximální dva potomky (levý a pravý)
Každý uzel pak tvoří další podstrom (který může být prázdný). Každý stom má pak právě 1 uzel, který nemá žádného rodiče a nazývá se **kořen/root** (v obrázku má hodnotu 2).

![Red-Black Tree](https://image.prntscr.com/image/HXJBApNzQw64hjojJlnMUw.png "Red-Black Tree")

#### Implementujte testy

#### Hodnocení

### White Box Testing (až 6 bodů)

#### Maticové

#### Implementujte testy

#### Hodnocení

### Test Drive Development (až 6 bodů)

#### Vlastností prioritní fronty

#### Implementujte

#### Hodnocení
