# Zadání 2017

## Výsledné hodnocení

### Přiložené soubory:

[tests.tar.gz](./Hodnocení/tests.tar.gz "tests.tar.gz") - soubor testovacích programů napsaných v C. S těmito soubory byly Vaše projekty kompilovány.
[template-outputs.tar.gz](./Hodnocení/template-outputs.tar.gz "template-outputs.tar.gz") - vzorové výstupy z testovacích skriptů. S těmito soubory byly porovnávány výstupy z Vašeho programu.
[xlogin00.tar.gz](./Hodnocení/xcaber00.tar.gz "xcaber00.tar.gz") - výstupy Vašich skiptů ( *.output* soubory ) a výsledky porovnávání ( *.result soubory ), dále logy z kompilace a makefily, se kterými byl projekt kompilován.

### Bodové hodnocení bylo následující

Příklady v úloze: c401(max\_3\_body) c402(max\_4\_body) c016(max\_3\_body)
Jednotlivé testy:

- c401-test(max\_20\_OK):
    - 0<=pocet_OK<10: 0 bodu
    - 10<=pocet_OK<20: 1 bodu
    - 20<pocet_OK: 2 bodu
- c401-advanced-test(max\_30\_OK):
    - 0<=pocet_OK<29: 0 bodu
    - 29<pocet_OK: 1 bodu
- 402-test(max\_20\_OK):
    - 0<=pocet_OK<10: 0 bodu
    - 10<=pocet_OK<20: 1 bodu
    - 20<pocet_OK: 2 bodu
- c402-advanced-test(max\_30\_OK):
    - 0<=pocet_OK<25: 0 bodu
    - 25<=pocet_OK<29: 1 bodu
    - 29<pocet_OK: 2 bodu
- c016-test(max\_12\_OK):
    - 0<=pocet_OK<6: 0 bodu
    - 6<=pocet_OK<12: 1 bodu
    - 12<pocet_OK: 2 bodu
- c016-advanced-test(max\_20\_OK):
    - 0<=pocet_OK<19: 0 bodu
    - 19<pocet_OK: 1 bodu

### Bodové hodnocení pro xcaber00

- c401-test(max\_20\_OK) - pocet pocet ziskanych bodu: 2 ( 20 sections OK )
- c401-advanced-test(max\_30\_OK) - pocet pocet ziskanych bodu: 1 ( 30 sections OK )
- 402-test(max\_20\_OK) - pocet pocet ziskanych bodu: 2 ( 20 sections OK )
- c402-advanced-test(max\_30\_OK) - pocet pocet ziskanych bodu: 2 ( 30 sections OK )
- c016-test(max\_12\_OK) - pocet pocet ziskanych bodu: 2 ( 12 sections OK )
- c016-advanced-test(max\_20\_OK) - pocet pocet ziskanych bodu: 1 ( 20 sections OK )

Celkem : **10** bodu

----------------

V druhé domácí úloze, kterou najdete v [zadání](https://wis.fit.vutbr.cz/FIT/st/course-files-st.php?file=%2Fcourse%2FIAL-IT%2Fprojects%2Fial_2017_du2.tar.gz&cid=12129 "Souborech k předmětům / Algoritmy / Projekty / ial_2017_du2.tar.gz"), na vás čekají následující tři příklady:

- C401: binární strom a operace nad ním implementované rekurzivně za **3 body**
- C402: binární strom a operace nad ním implementované nerekurzivně za **4 body**
- C016: tabulka s rozptýlenými položkami za **3 body**

Vaším úkolem je v souborech **c401.c**, **c402.c** a **c016.c** doplnit těla funkcí a odevzdat je prostřednictvím IS FIT (nekomprimované a s kódováním diakritiky podle UTF-8).

Správnost implementace si můžete ověřit pomocí základní testovací aplikace (např. c401-test.c), pro jejíž překlad máte připravený makefile (make all / make clean). Do hlaviček funkcí ani do hlavičkových souborů nezasahujte!

Jestliže implementace daného příkladu dává správné výsledky pro základní testovací aplikaci při překladu a spuštění na serveru eva.fit.vutbr.cz (správné výsledky najdete např. v souboru c401-test.output), získáváte za příklad 2 body. Jestliže vaše implementace vyhoví i pokročilým testům (ty k dispozici nemáte), získáváte za příklad i zbývající body (tedy 1 bod za příklad C401 a C016 a 2 body za C402).

Doporučujeme vám proto, abyste si zkusili základní testovací aplikaci rozšířit a odhalit tak co nejvíce chyb ve své implementaci. Upravenou testovací aplikaci ale do IS FIT neodevzdávejte! Pokud se dostanete do časové tísně, nesnažte se řešit všechny příklady najednou v naději, že za částečné řešení něco dostanete. V takovém případě je výhodnější dokončit alespoň jeden či dva příklady pořádně.

## DŮLEŽITÁ UPOZORNĚNÍ

Vzhledem ke špatným zkušenostem z minulých let je termín odevzdání **"hard deadline"**, tzn. nebudou akceptována žádná pozdní odevzdání formou e-mailu, apod.

Domácí úlohy budou hodnoceny automatickými skripty na serveru eva. Nedodržení zadání  (např. zásahy do kostry, přejmenování souborů s řešením, zapakování odevzdaných souborů, ap.) bude mít za následek ztrátu všech bodů za domácí úlohu!

Stejně tak budou 0 body hodnoceny příklady nepřeložitelné a ty, které se nekonečně zacyklí - příklad se se zlou potáže (přesněji řečeno s "kill -9"), pokud bude potřebovat k řešení více jak 15 sekund!

Domácí úlohu vypracovávejte, prosím, samostatně a své řešení si dobře chraňte! V případě prokázaného plagiátorství bude bez výjimky odebrán zápočet a bude zváženo zahájení disciplinárního řízení.

Jen v akademickém roce 2014/2015 byl v předmětu IAL kvůli plagiátorství domácích úloh odebrán zápočet 17-ti studentům. U opakujících studentů byl následkem konec studia. V případě časové tísně doporučujeme raději odevzdat částečné řešení než riskovat uvedeným způsobem.
