# BS

> Binární strom sestává z kořene, neterminálních uzlů, které mají ukazatel na jednoho nebo dva uzly synovské a terminálních uzlů, které nemají žádné syny. <br />
> Každý uzel, který není kořenem stromu je kořenem svého podstromu.

## Výškově vývážený

BS je výškově vyvážřený, když pro všechny je uzly platí, že výška levého a pravého podstromu se rovná, nebo liší o 1.

## Váhové vývážený

BS je váhově vyvážený, když pro všechny jeho uzly platí, že počet uzlů levého a pravého podstromu se rovná, nebo liší o 1.

## BVS Se zpětnými ukazateli

![Zpětné](https://i.imgur.com/drOcY0A.png "Zpětné")

1. Zpětné ukazatele Root a vedlejší diagonály ukazují na `null`.
1. Zpětný ukazatel levého syna ukazuje na svého otce.
1. Zpětný ukazatel pravého syna dědí ukazatele od otce (ukazuje tam kam otec).

## Průchod stromem

### PreOrder

Root, Left, Right

#### Inverzní PreOrder

Root, Right, Left

### InOrder

Left, Root, Right

#### Inverzní InOrder

Right, Root, Left

### PostOrder

Left, Right, Root

#### Inverzní PostOrder

Right, Left, Root
