> Do souboru, nazvaného podle konvence isj\_proj06\_xnovak00.py, implementujte:

- Funkci `first_nonrepeating`
    - Dostane na vstup řetězec
    - Vrátí první neopakující se znak ze vstupního řetězce:
        - tooth -> h, lool -> None
- Funkci `combine4`
    - Dostane čtveřici 4 kladných celých čísel a očekávaný výsledek
    - Vrátí setříděný seznam unikátních řešení matematických hádanek s výsledkem operací **+, -, *, /** nad 4 čísly
        - [Např.](http://blog.plover.com/math/17-puzzle.html "Puzzle")
        - `combine4([6,6,5,2],36)` == `['(2+5)*6-6', '(5+2)*6-6', '6*(2+5)-6', '6*(5+2)-6']`
            - Případně jen `['(2+5)*6-6']`, pokud se vám podaří odstraňovat výrazy kvůli komutativitě sčítání a násobení
            - Ppřípadně i delší seznam, jehož prvky se budou lišit jen uzávorkováním.
