# Skupina D 2016

1. Při běžném provozu auta (dlouhodobější přerušení provozu neuvažujeme) je poškrábání laku nahodilá událost, ke které při jistém chování a stylu jízdy dochází průměrně jednou za 4 roky. Co je pravděpodobnější?:
    - Auto bude takto jezdit 8 let bez škrábance.
    - K poškrábání dojde třikrát za prvních 20 měsíců provozu.
1. Uvažme náhodnou veličinu _Q_, která má standardizované normální rozdělení pravděpodobnosti a náhodnou veličinu _R_, která má Poissonovo rozdělení pravděpodobnosti. Je-li _Q_ diskrétní, položte `a = 1`, jinak položte `a = 12 DQ`. Je-li _R_ diskrétní, položte `b = 3`, jinak položte `b = 6`. Zajistěte konvergenci Gauss-Seidelovy metody, zvolte `x^(0) = (0,0,0)` a proveďte dva kroky Gauss-Seidelovy metody pro soustavu:

    ```text
    ax + 4y + z  = 12
    bx + 3y + 9z = 9
    x  + ay + 5z = 7
    ```
1. V bodech `X_0 = 0; X_1 = 0,4; X_2 = 0,8; X_3 = 1` nahraďte funkci `f(x) = sinx+x^2 - 3x` polynomem `P(x)` a vypočtěte rozdíl `f(0,5) - P(0,5)`
1. Kolega z práce si na oběd dává vždy polévku, hlavní jídlo a salát. Vypozoroval, že vždy platí cca 120 korun. Hlavní jídlo vybírá z nabídky několika položek, které jsou cenově srovnatelné, cena salátu závisí na váze, avšak vybírá si vždy zhruba stejné množství do misky téže velikosti. Cena polévky je konstantní. Tedy předpokládáme, že cenu oběda lze popsat normálním rozdělením se střední hodnotou 120 korun a směrodatnou odchylkou 3 koruny. Průměrná cena deseti posledních obědů byla 124 korun. Na hladině významnosti `a = 0,05` testujte hypotézu, že kolega začal za oběd platit vyšší cenu než dosud.
1. Vypočtěte složenou lichoběžníkovou nebo složenou Simpsonovou metodou s dělením intervalu na 4 dílky, případně pomocí poznatků z teorie pravděpodobnosti. <br />
    ![Integrál](https://image.prntscr.com/image/sT-B364ORGa7gI9J7oeJsg.png "Integrál")
1. Je dána funkce `G(x)`. Určete konstantu `c ∈ R` tak, aby G(x) byla distribuční funkcí nějaké spojité náhodné veličiny _X_. Poté určete střední hodnotu _X_. Pokud taková konstanta _c_ existovat nemůže (zdůvodněte!), desetinným číslem vyjádřete `P(Y ∈ <k/5;5k>)`, kde _Y_ je náhodná veličina, jejíž hustota pravděpodobnosti je `f(x)`. `k ∈ R`. <br />
    ![G](https://image.prntscr.com/image/JRL7u979TTK8eO6WkFTMig.png "G")
    ![F](https://image.prntscr.com/image/ELEJ0mfETWeXG1e3l0L1Yg.png "F")
1. S přesností `ϵ = 0,01` najděte nejmenší z kladných průsečíků funkcí `f(x) = e^(x-3)` a `g(x) = 2 + ln(x-1)`, který je nejdále od nuly. Algoritmus výpočtu spusťte jen tehdy, když nejprve prokážete jeho konvergenci.
