> Do souboru, nazvaného podle konvence isj\_proj04\_xnovak00.py, napište definice následujících funkcí:

- `balanced_paren(parenstr)`
    - Vrátí True, pokud je řetězec, v němž se jako závorky mohou vyskytnout znaky '()[]{}<>', správně uzávorkovaný
          - Jinak False
          - Například
               - Pro řetězce '123', '[{}]', '12<4<[a]b>>5' vrátí True
               - Pro '{1<2(>3)}' False.
- `caesar_list(word, key)`
    - Vrátí vstupní řetězec zakódovaný podle klíče Caesarovou šifrou
    - Vstupní řetězec má být složený výhradně z 26 malých písmen anglické abecedy
    - Pokud tomu tak není, vyvolejte výjimku `ValueError`.
    - Klíč má formu seznamu čísel, udávající posun v abecedě
        - Nnapř. [3,5,7]
    - Použije se cyklicky
    - Pokud tedy bude vstupem 'abc', a klíč [4,5], výsledkem má být 'egg'
    - Můžete využít `itertools.cycle()`
    - Pokud posun "přeteče" přes konec abecedy, začíná se od začátku
        - Pokud tedy bude vstupem 'xyz', a klíč [3,4,5,6,7], výsledkem má být 'ace'
    - Při volání funkce nemusí být parametr key zadán, potom se použije defaultní klíč [1,2,3].
- `caesar_varnumkey`
    - Funguje stejně jako funkce `caesar_list`
    - Klíč se při volání předává jako samostatné parametry
        - `caesar_varnumkey('xyz', 3, 5, 7)`
- Jako první řádek skriptu uveďte tzv. [shebang](https://en.wikipedia.org/wiki/Shebang_%28Unix%29 "shebang")
    - Umožní spuštění skriptu na fakultních serverech, takže např.:
        - `#!/usr/bin/env python3`
- Nezapomeňte na dokumentační řetězce všech funkcí.
- Dále každou logickou část kódu jednotlivých funkcí okomentujte, např.
    - `# checking whether the item can be converted to int - try: int(item)`
