# Zadání 2016

1. _(4b)_ Nakreslete k připraveným osám jednotkovou krychli pro funkci: `F(a, b, c) = a + b`

    ![Osy](https://image.prntscr.com/image/nmEfS0xBR0_yfLscgC_l1w.png "Osy")
1. _(6b)_ Najděte **všechna** minimální řešení funkce `F(a, b, c, d)` zadané uvedenou mapou. Uvažujte **MNKF** s kritériem minimality nechť je počet písmen proměnných ve výrazu. Smyčky zakreslete do obrázku a vsýledná řešení vypište do volného prostoru vedle obrázku.

    ![Mapa](https://image.prntscr.com/image/TbZrJJrmRV_c-lI1HGDTXA.png "Mapa")
1. _(6b)_ Předpokládejte, že u multiplexoru na obrázku je řídicí vstup C MSB a vstup A je LSB. Jakou log. funkci obvod realizuje? Pozn.: Logickou funkci vyjádřete skrz vrcholy v log. jedničce a log. nule.

    ![Multiplexor](https://image.prntscr.com/image/X0Bc1sZ5QPuopxekXz6O_A.png "Multiplexor") <br />
    Vrcholy v log. jedničce: .............. <br />
    Vrcholy v log. nule: ..............
1. _(5b)_ Z časového diagramu na obrázku rozpoznejte typ klopného obvodu a identifikujte jeho vstupy X1 a X2. U klopných obvodů s jedním excitačním vstupem (T a D) uvažujte i vstup _Clock Enable_.

    ![Diagram](https://image.prntscr.com/image/yOZzXLGXQ52nIUF0YanIOg.png "Diagram")<br />
    Typ KO: ...... <br />
    X1 odpovídá vstupu: ..... <br />
    X2 odpovídá vstupu: .....
1. _(5b)_ V uvedeném slovníku přechodů označte chybné pozice a nahraďte je správnými hodnotami.

    ![Slovník](https://image.prntscr.com/image/_bX6BC0UQkSJvjeIAwqkZA.png "Slovník")
1. _(7b)_ Navrhněte synchronní obousměrný tříbitový čítač, který pracuje dle uvedeného grafu (stavy čítače jsou Q<sub>1</sub>Q<sub>2</sub>Q<sub>3</sub>). Směr čítání určuje signál _Y_. Pokud `Y = 0`, potom čítač čítá dolů (tj 000 -> 010 -> 100 atd.). Pokud `Y = 1`, potom čítač čítá nahoru (tj 000 -> 101 -> 001 atd.). Pro realizaci použijte **KO typu JK**. Odvoďte **MNDF** pouze pro vstup J<sub>1</sub>. Do volného prostoru napište nejen výsledek, ale i postup řešení.

    ![Diagram](https://image.prntscr.com/image/1h6mjcNiQIyDO25jLQJpjA.png "Diagram") <br />
    J<sub>1</sub>= .......
1. _(6b)_ Po sériové lince jsou přijímány zakódované symboly **A, B, C, D, E**, které jsou reprezontovány binárními kódy: **A=00, B=01, C=10, D=110, E=111**, kde bit nejvíce vlevo reprezentuje LSB a bit nejvíce vpravo MSB (jednotlivé bity symbolu tedy přicházejí po sériové lince zleva doprava). Nakreslete graf přechodů Mealyho automatu, který umožní dekódovat na lince uvedené symboly. Vstupní abeceda automatu je tedy `{0,1}`, výstupní abeceda `{A,B,C,D,E,-}`, kde výstup - znamená, že není dekódován žádný symbol. Automat musí být schopen rozpoznat nejen jeden symbol, ale všechny po sobě jdoucí symboly.
1. _(6b)_ Do vyhrazeného prostoru (pod otázkou) nakreslete schéma zapojení 3-bitového posuvného registru realizujícího následující dvě funkce: _rotate right_ a _shift left_. Pozn. pro realici použijte klopné obvody typu D a dvouvstupé multiplexory.
