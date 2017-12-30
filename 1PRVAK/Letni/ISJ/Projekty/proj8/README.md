1. S využitím modulu cProfile zjistěte, kolikrát je volána funkce lev() ve [skriptu](./lev.py "lev.py").
    - Výsledek uložte do souboru **lev.cProfile_output**.
1. Pomocí `time` zjistěte, jak dlouho běží [skript](./words/nonpalindrom_words_existing_reversed.py "reversed.py") na [souboru](./words/words30000.txt "Words30000").
    - Upravte skript tak, aby se daný čas co možná nejvíc zkrátil a aby bylo možné zpracovat i podstatně větší [soubor](./words/words.txt "words")
    - Upravený skript pojmenujte ve formatu `login_nonpalindrom_words_existing_reversed.py` a odevzdejte
1. Výstup z **time ./ id -u -n`\_nonpalindrom\_words\_existing\_reversed.py words.txt** odevzdejte jako **words.time\_output**.
1. Změřte čas běhu skriptů [1](./time/sekv.py "1") a [2](./time/para.py "2")
    - Odevzdejte je jako **sekv.time\_output** a **para.time\_output**
1. Do souboru **why.txt** napište třípísmennou zkratku, která vysvětlí, proč se reálný čas běhu paralelní verze neblíží polovině běhu sekvenční verze.    - Odevzdejte.
1. Upravte skript para.py tak, aby reálný čas zpracování odpovídal zhruba polovině času běhu sekvenční verze.
    - Upravenou verzi pojmenujte ve formatu **login\_para.py**
    - Odevzdejte.
