# IFJ Semestrálka

## SA

### Zdola - nahoru

Ukončující znak (#), shiftovací, redukční pravidla

konečný stav `#Ss -> f` <br />
sa -> as, ... <br />
Původním pravidlům se prohodí strany (`S -> AaBbCc` == `AaBbCcs -> Ss`; `B -> ε` == `s -> Bs`)

### Shora - dolu

Expandující, porovná vací pravidla, prázdná množina jako konečný stav (výstup je prázdný zásobník)

asa -> s, ... <br />
Pravá strana je stejná, levá reverzovaná (`S -> AaBbCc` == `Ss -> cCbBaAas`; `B -> ε` == `Bs -> s`)

- Expanduje se reverzovanou pravou stranou
- Na začátek se vloží `Ss`
- `Ss` se nahradí reverzovanou pravou stranou pravidla pro `Ss`
- nahrazení nebo porovnání pro zbytek řetězec

## LL

### Množina Empty

Obsahuje `ε`, pokud x derivuje ε <br />
jinak je `∅`

### Množina First

Obsahuje symboly, které z aktuálního neterminálu mohou být aktuálně nejlevěji vyderivovány.

### Množina Follow

Množina všech terminálů, které se mohou vyskytovat vpravo od neterminálu A ve větné formě.

#### Pravidla (Algritmus)

- Follow(S) = `{$}`
- Každé pravidlo má tvar `A -> xBy`
    - Pokud je `y != ε`. Vše z Firts(y) se přidá do Follow(B)
    - Pokud `Empty(y) == {ε}`. Vše z Follow(A) se přidá do Follow(B)

### Množina Predict

Všechny terminály, které mohou být aktuálně nejlevěji vygenerovány (patří do First), pokud pro libovolnou větnou formu použijeme pravidlo `A -> x`

#### Pravidla

- Pokud `Empty(x) == {ε}`. Predict(`A -> x`) = First(x) a Follow(A)
- Pokud `Empty(x) == ∅`. Predict(`A -> x`) = First(x)

## Precedenční tabulka

- \> == redukce, < == shift
- Levě asociativní oprátory lze vyhodnotit (redukovat)
- Pravě asociativní oprátory == čekat (shift)

## Vstupy / Výstupy
