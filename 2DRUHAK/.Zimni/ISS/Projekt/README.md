# ISS Projekt 2017/2018

## Cíl

Cílem projektu je provést analýzu signálu. Jako vstup použijte dodaný zvukový soubor **xlogin.wav**. Projek tje možno řešit v Matlabu, jazyce C nebo libovolném jiném programovacím nebo skriptovacím jazyce. Je možné použít libovolné knihovny. Projekt není zaměřen na "krásu programování", není tedy nutné mít vše úhledně zabalené do okomentovaných funkcí, atd. - napři. soubor v Matlabu, ze kterého copy-pastujete příkazy do příkazové řádky, napraosto stačí. Důležitý je výsledek.

## Odevzdání

Odevzdat 2 soubory do WISU.

1. xlogin00.pdf
    - Protokol s řešením
    - V záhlaví prosím uveďte své jméno, příjmení a login.
    - Pak budou následovat odpovědi na jednotlivé otázky (obrázky, hodnoty, komentáře).
    - U každé otázky uveďte stručný postup.
        - Kousek okomentovaného kódu, komentovanou rovnici nebo text.
        - Není nutné kopírovat do protokolu celý zdrojový kód.
        - Není nutné opisovat zadání či teorii, sousttřeďte se přímo na řešení.
        - Pokud využijete zdroje mimo standardních materiálů (přednášky, cvičení a studijní etapa projektu ISS), prosím uveďte, odkud jste čerpali.
        - Protokol je možné psát v libovolném systému, můžete jej psát dokonce i čitelně rukou, dolepit do něj obrázky a pak oskenovat.
        - Protokol může být česky, anglicky nebo slovensky.
        - Doporučená délka protokolu je max. 2 stránky, případně 3, pokud se rozhodnete řešit bonusový úkol.
1. soubor se zdrojovými kódy.
    - Může se jednat o soubor nebo o ZIP archiv, pokud bude více souborů.
    - Do tohototo souboru není třeba přikládat vygenerované obrázky.
    - Projekt je samostatný (== plagiátorství, kontrola, ...)

## Zadání

1. [x] **_[0.5b]_** Načtěte váš osobní signál ze souboru. Napište vzorkovací frekvenci signálu a jeho délku ve vzorcích a v sekundách.
1. [x] **_[0.5b]_** Vypočítejte spektrum signálu pomocí diskrétní Fourierovy transofmarce. Do protokolu vložte obrázek modulu spektra v závislosti na frekvenci. Frekvenční osa musí být v Hz a pouze od 0 do poloviny vzorkovací frekvence.
1. [x] **_[0.5b]_** Určete a napište, na které frekvenci v Hz je maximum modulu spektra.
1. [x] **_[0.5b]_** Pro další zpracování je dán IIR filtr s následujícími koeficienty:
    - `b0 = 0.2324`
    - `b1 = -0.4112`
    - `b2 = 0.2324`
    - `a1 = 0.2289`
    - `a2 = 0.4462`
    - Do protokolu vložte obrázek s nulami a póly přenosové funkce tohoto filtru a uveďte, zda je filtr stabilní.
1. [x] **_[0.5b]_** Do protokolu vložte obrázek s modulem kmitočtové charakteristiky tohoto filtru (frekvenční osa musí být v Hz a pouze od 0 do poloviny vzorkovací frekvence) a uveďte, jakého je filtr typu (dolní propust / horní propust / pásmová propusť / pásmová zádrž ).
1. [x] **_[0.5b]_** Filtrujte načtený signál tímto filtrem. Z výsledného signálu vypočítejte spektrum signálu pomocí diskrétní Fourierovy transformace. Do protokolu vložte obrázek modulu spektra v závislosti na frekvenci. Frekvenční osa musí být v Hz a pouze od 0 do poloviny vzorkovací frekvence.
1. [x] **_[0.5b]_** Určete a napište, na které frekvenci v Hz je maximum modulu spektra filtrovaného signálu.
1. [ ] **_[0.5b]_** **Od tohoto cvičení se bude pracovat s původním signálem, ne s filtrovaným.** Do signálu bylo přimícháno 20 ms obdélníkových impulsů se střední hodnotou nula a střídou 50% na frekvenci 4kHz. Tedy 80 sekvencí [h h -h -h] (kde h je kladné číslo) za sebou.
    - Najděte kde jsou - napište čas ve vzorcích a sekundách.
    - **Pomůcka:**
        - Uvažte přizpůsobený filtr, výrobu spektra této sekvence a jeho hledání ve spektru signálu rozděleného po 20ti ms, posled, atd.
        - Cílem není matematická čistota, ale vyřešení úkolu.
1. [x] **_[0.5b]_** Spočítejte a do protokolu vložte obrázek autokorelačních koeficientů R[k] pro `k ∈ -50 ... 50`. Použijte vychýlený odhad koeficientů podle vztahu: <br />
    ![Vztah](https://image.prntscr.com/image/ssCBf3PzTk6wWbZdVB1hNw.png "Vztah")
1. [x] **_[0.5b]_** Napište hodnotu koeficientu **R[10]**.
1. [ ] **_[2b]_** Proveďte časový odhad sdružené funkce hustoty rozdělení pravděpodobnosti p(x1,x2, 10) mezi vzorky n a n + 10.
    - Do protokolu vložte 3-D obrázek těchto hodnot.
    - Můžete použít barevnou mapu, odstíny šedi, projekci 3D a 2D.
    - Můžete využít, vykuchat, chytře zavolat dodanou funkci [hist2opt.m](https://www.fit.vutbr.cz/study/courses/ISS/public/proj_studijni_etapa/5_random/hist2opt.m "hist2opt.m")
1. [x] **_[2b]_** Ověřte, že se jedná o správnou sdruženou funkci hustoty rozdělení pravděpodobnosti, tedy že: <br />
    ![Rovnice](https://image.prntscr.com/image/i_mKKlNRRxWfHBaJ8rrNDw.png "Rovnice")
1. [ ] **_[2b]_** Vypočtěte z této odhadnuté funkce hustoty rozdělení pravděpodobnosti autokorelační koeficient R[10]:
    - Srovnejte s hodnotou vypočítanou v příkladu 10 a komentujte výsledek. <br />
    ![Rovnice](https://image.prntscr.com/image/spntg_yNQsmVGQcaiZR2zg.png "Rovnice")

---

### Bonus

Navrhněte prediktor, který dokáže odhadnou hodnotu vzorku x[n] z hodnot 5 předcházejících vzorků pomocí jednoduchého FIR filtru: <br />
    ![Filtr](https://image.prntscr.com/image/G4ANC1gHTZW3m-rdXNWh3g.png "Filtr") <br/>
kde x^ je odhadnutý vzorek.

Jako metriku pro určení kvality prediktoru použijte energii chyby predikce, Chyba predikce je definována jako rozdíl skutečných a předpovězených vzorků: <br />
    ![Rozdíl](https://image.prntscr.com/image/w9LYLASpS2aFCyJXW32_pw.png "Rozdíl") <br />
a její energie je dána zcela tradičně jako: <br />
    ![Energie](https://image.prntscr.com/image/ojWNepTWSqy2BYV6a5Z-1A.png "Energie")

Určete nejlepší možný prediktro pro Váš signál (původní). Prediktor je plně dán hodnotami koeficientů b1 ... b5. Vyhodnoťte také kvalitu prediktoru pmocí energie chyby predikce E a srovnejte Váš prediktor s několika "blbými", např.

- Prediktor generující pouze nuly: `x[n] = 0`
- Prediktor opakující minulý prvek `x[n[ = x[n-1]`
- Prediktor průměrující dva minulé vzorky `x[n] = 0.5x[n-1] + 0.5x[n-2]`

Důležitý je opět výsledek. Lze odvozovat, hledat, použít hotové odvozené řešení, použít libovolnou techniku strojového učení, zkusit určit koeficienty ručně, atd.
