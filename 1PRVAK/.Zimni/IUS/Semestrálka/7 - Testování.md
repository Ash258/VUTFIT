# Testování

## Rozdělení testování

### Funkcionální

> Testuje funkčnost komponent a systému. (`Vstupně výstupní testování`)

### Strukturální

> Testuje strukturu nebo komponenty. (Nutná znalost implementace)

## Strategie testování

### Zdola-nahoru (Bottom-up)

> Testují se komponenty na nižší úrovni, poté se integrují komponenty vyšší úrovně.

### Shora-dolů (Top-down)

> Testují se integrované moduly nejvyšší úrovně, poté submoduly.

### Sendvičové

- Moduly se rozdělí so skupin:
    - **Logické**
        - Řízení rozhodování. (`top-down`)
    - **Funkční**
        - Vykonávání požadovaných funkcí. (`bottom-up`)

### Jednofázové

> Jednotlivé moduly jsou integrovány naráz a poté testovány jako celek.

## Druhy testování

### Akceptance (Akceptační testování)

- Verifikace systému na reálných datech.

### Blackbox (Černá skříňka)

- Testování bez znalosti implementace / struktury.
- Je zapotřebí pouze znalost požadovaného chování.

### Whitebox (Bílá skříňka)

> Testování se znalostmi vnitřní struktury / implementace.

### Smoke

- Abstraktní testování, které slouží k rozhodnutí, zda by se měly provést důslednější testy.
- Základní testy, které mohou například zamítnout vydání systému.
    - Zda systém spustit, ...

### Alfa

> Testování obvykle členy týmu před vydáním. (blackbox, whitebox)

### Beta

> Testování skutečnými uživateli. (Limitovaná skupina lidí, kteří se nepodíleli na vývoji)

## SLA (Service Level Agreement)

- Dojednaná dohoda mezi zákazníkem a poskytovatelem služeb o dostupnosti a kvalitě.
- Obsahuje popis služeb, cenu, odpovědnost, správu změn, záruku.

## OLA (Operation Level Agreement)

- Dohoda mezi interními skupinami, které dohromady dodržují SLA.
- Zabývá se údržbou služeb, dostupností služeb a dalšími službami.
