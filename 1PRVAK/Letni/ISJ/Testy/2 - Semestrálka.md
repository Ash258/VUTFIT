# Semestrálka 2015, 2016, 2017

1. Co vypíše kód. Proč?

    ```python
    def f(a = 1, b = 1, u = 40000):
        while a+b < u:
            yield b
            a,b = b, a+b

    print(list(range(3)))

    print(sum(k**3 +g for k in range(3) for g in f(u = 30) if g%2 and   k!=g))
    _sum = 0
    for g in f(u=30):
        for k in range(3):
            if g%2 and k!=g:
                _sum += k**3+g
    print(_sum)
    ```
1. Napisat dekoracnu funkciu, ktora pre danu funkciu bude drzat statistiky, kolko krat sa s pustala s jednotlivimy parametrami, alebo nieco take...
1. Napsat třídu SparseVector pro ukládání řídkých vektorů (většina hodnot je 0)
    - Použijte dat. strukturu dict nebo odvozené (defaultdict)
    - Proměnná counter, která počítá vytvořené instance (see "class variable")
