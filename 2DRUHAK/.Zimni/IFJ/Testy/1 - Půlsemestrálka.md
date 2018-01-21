# Zadání 2017

## Skupina A 11:10

1. Operace A={a,b,c} B={b,c,d} průnik, sjednocení, rozdíl, konkatenace, iterace, pozitvní iterace. Vyber jednu a více operací, které byly použity:
    - `∅`
    - `{ε, a, d, aa, dd, ad, da, ada, ...}`
    - `{b,c}`
    - `{d, ba, da, baa, daa, caaa, baaaa...}`
1. DKA, {a,b,c} nesmí obsahovat řetězec "bc" a |w| musí být sudý.
1. Tabulka prvidel ==> Udělat DKA.
1. Definice Abeceda, Řetězec, Jazyk

## Skupina B

1. Použite jazykové operace, abyste dosáhli cílového jazyka. Jako parametry operací použitjte A, B, ∅.
    `A = {a, b, c}`,
    `B = {b, c, d}`,
    `Σ = {a, b, c, d}`
    - a) `{a, d}`
    - b) `{bb, bc, cb, cc, bbb, bbc, bcb, bcc, cbb, ...}`
    - c) `{Σ}`
    - d) `{da, db, dc, dda, ddb, ddc, ddda, dddb, dddc, ...}`
1. Graficky vytvořte automat pro jazyk `L = {w | w  {a, b, c}+, w obsahuje řetězec bc, |w| je sudé délky}` <br />
    Poznámka: `{a, b, c}+` = pozitivní iterace
1. Je dán automat `M = ({s, p, q, f}, {a, b}, R, s, {f})`. Vytvořte graficky DKA.

    |    | a   | b   |
    |----|:---:|:---:|
    | s  | ∅   | p,q |
    | p  | s   | ∅   |
    | q  | p,f | p,q |
    | f  | ∅   | p   |

1. Formálně definujte konečný automat.

# Zadání 2016

## Skupina A

1. _(5b)_ Jsou dány jazyky A a B `A={a,b,c}` `B={b,c,d}`. Jsou dány operace průnik, sjednocení, konkatenace, rozdíl, iterace, pozitivní iterace. U každého výsledku napište použitím jaké operace by mohl vzniknout. Jako operandy použijte A, B.
    - `{ε,bb,cc,dd,bcd,bdc,bbd,....}`
    - `{a,b,c,d}`
    - `{b,c}`
    - `∅`
    - `{d}`

1. _(6b)_ Navrhněte a graficky znázorněte deterministický konečný automat, který přijímá jednoduchá desetinná čísla. Skládají se z celé části, desetinné části a části pro exponent o nenulových délkách. Po celé části následuje desetinná tečka `.`, po desetinné `e` a po něm `+` nebo `-` a exponent. Místo číslic 0-9 použijte zástupný znak D.

1. _(4b)_ Nechť L1 a L2 jsou jazyky nad Σ.

    ___________ jazyků L1 a L2, L1 ∪ L2, je definováno:<br/>
    L1 ∪ L2 = {x: ___________ }

    Nechť L je jazyk nad Σ.<br/>
    ___________ jazyka L, L̅, je definován:<br/>
    L̅ = ___ - L

1. _(5b)_ Formálně definujte konečný automat.

## Skupina B

1. Operace nad jazyky (sjednocení, průnik, konkatenance, iterace, doplněk, rozdíl, mocnina).

    `A = { a, b, c }`<br/>
    `B = { b, c d }`<br/>
    `abeceda Σ = { a, b, c, d }`

    > Pro dále zadané operace byl vyžadován výpis všech řetězců délky n, kde n <= 2. Pozor na formát výsledků, stačí zpravidla bez závorek pouhý výpis řetězců.

1. Zadán malý automat (tabulkou přechodů) s Σ přechody s požadavkem na sestavení Σ uzávěru. Lze řešit z grafuván nebyl)., nebo formálním algoritmem z přednášek (konkrétní způsob však vyžado

1. Definice mocniny a rozdílu. Postačilo doplnit jen pár chybějících částí.
1. Definovat Regulární výrazy `RV`, které značí regulární jazyky.
