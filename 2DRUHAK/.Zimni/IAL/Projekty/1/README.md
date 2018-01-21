# Zadání 2017

## Výsledek hodnocení

### Přiložené soubory

[tests.tar.gz](./Hodnocení/tests.tar.gz "tests.tar.gz") - soubor testovacích programů napsaných v C. S těmito soubory byly Vaše projekty kompilovány.
[template-outputs.tar.gz](./Hodnocení/template-outputs.tar.gz "template-outputs.tar.gz") - vzorové výstupy z testovacích skriptů. S těmito soubory byly porovnávány výstupy z Vašeho programu.
[xlogin00.tar.gz](./Hodnocení/xcaber00.tar.gz "xcaber00.tar.gz") - výstupy Vašich skiptů (\*.output), výsledky porovnávání (\*.results), logy z kompilace (\*.log) a makefily, se kterými byly příklady kompilovány (Makefile.*).

### Bodovací tabulka

Příklady v úloze: c202 až 3 body, c204 až 3 body, c206 až 4 body
Jednotlivé testy:

- c202-test(max\_9\_OK):
    - 0<=pocet_OK<8: 0 b.
    - 8<=pocet_OK<9: 1 b.
    - 9<=pocet_OK: 2 b.
- c202-advanced-test(max\_19\_OK):
    - 0<=pocet_OK<19: 0 b.
    - 19<=pocet_OK: 1 b.
- c204-test(max\_15\_OK):
    - 0<=pocet_OK<13: 0 b.
    - 13<=pocet_OK<15: 1 b.
    - 15<=pocet_OK: 2 b.
- c204-advanced-test(max\_19\_OK):
    - 0<=pocet_OK<19: 0 b.
    - 19<=pocet_OK: 1 b.
- c206-test(max\_18\_OK):
    - 0<=pocet_OK<16: 0 b.
    - 16<=pocet_OK<18: 1 b.
    - 18<=pocet_OK: 2 b.
- c206-advanced-test(max\_58\_OK):
    - 0<=pocet_OK<46: 0 b.
    - 46<=pocet_OK<58: 1 b.
    - 58<=pocet_OK: 2 b.

### Bodové hodnocení pro xcaber00

- c202-test(max\_9\_OK) - počet získaných bodů: 2 (9 sections OK)
- c202-advanced-test(max\_19\_OK) - počet získaných bodů: 1 (19 sections OK)
- c204-test(max\_15\_OK) - počet získaných bodů: 2 (15 sections OK)
- c204-advanced-test(max\_19\_OK) - počet získaných bodů: 1 (19 sections OK)
- c206-test(max\_18\_OK) - počet získaných bodů: 2 (18 sections OK)
- c206-advanced-test(max\_58\_OK) - počet získaných bodů: 0 (0 sections OK)

Celkem: 8 bodů

---

V první domácí úloze, kterou najdete v [Zadání](https://wis.fit.vutbr.cz/FIT/st/course-files-st.php?file=%2Fcourse%2FIAL-IT%2Fprojects%2Fial_2017_du1.tar.gz&cid=12129 "Souborech k předmětům / Algoritmy / Projekty / ial_2017_du1.tar.gz"), na vás čekají následující tři příklady:

- C202: zásobník znaků v poli za 3 body,
- C204: převod infixového výrazu na postfixový 3 body a
- C206: dvousměrně vázaný lineární seznam za 4 body.

Vaším úkolem je v souborech **c202.c**, **c204.c** a **c206.c** doplnit těla funkcí a odevzdat je prostřednictvím IS FIT (nezapakované a s kódováním diakritiky v UTF8). Pozor, v příkladu c204 budete potřebovat zásobník znaků implementovaný v příkladu c202.

Správnost implementace si můžete ověřit pomocí základní testovací aplikace (např. c202-test.c), pro jejíž překlad máte připravený makefile (make all / make clean). Do hlaviček funkcí ani do hlavičkových souborů nezasahujte!

Jestliže implementace daného příkladu dává správné výsledky pro základní testovací aplikaci při překladu a spuštění na serveru eva.fit.vutbr.cz (správné výsledky najdete např. v souboru c202-test.out), získáváte za příklad 2 body. Jestliže Vaše implementace vyhoví i pokročilým testům (ty v zadání domácí úlohy nenajdete), získáváte za příklad i zbývající body (tedy 1 bod za příklad C202 a C204 a 2 body za příklad C206).

Doporučuji Vám proto, abyste si zkusili základní testovací aplikaci rozšířit a odhalit tak co nejvíce chyb ve své implementaci. Upravenou testovací aplikaci ale do IS FIT neodevzdávejte. Pokud se dostanete do časové tísně, nesnažte se řešit všechny příklady najednou v naději, že za částečné řešení něco dostanete. V takovém případě je výhodnější dokončit alespoň jeden či dva příklady pořádně.

## Důležitá upozornění

Domácí úlohy budou hodnoceny automatickými skripty na serveru eva. Nedodržení zadání  (např. zásahy do kostry, přejmenování souborů s řešením, zapakování odevzdaných souborů, ap.) bude mít za následek ztrátu všech bodů za domácí úlohu!

Stejně tak budou 0 body hodnoceny příklady nepřeložitelné a ty, které se nekonečně zacyklí - příklad se se zlou potáže (přesněji řečeno s "kill -9"), pokud bude potřebovat k řešení více jak 15 s.

Domácí úlohu vypracovávejte, prosím, samostatně a své řešení si dobře chraňte! V případě odhalení plagiátorství či nedovolené spolupráce, nebude udělen zápočet a dále bude zváženo zahájení disciplinárního řízení.
