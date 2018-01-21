# Zadání 2017

> Navrhněte obvod a vytvořte jeho syntetizovatelný popis ve VHDL, který realizuje statické zobrazení iniciálů Vašeho jména a příjmení na maticovém displeji LED 8x8 externě připojeném k FPGA na FITkitu. Zvolte si zobrazení každého iniciálu tak, aby byly znaky jasně čitelné. V případě pocitu nedostatku místa na displeji můžete sdílet vybrané linie obou znaků, jak je vidět na příkladu v obr. 1. Uvažujte specifikaci obvodu dle obrázku 2 (povinně dodržte název entity a signálů rozhraní).

Vlastní řešení si můžete ověřit v CVT v učebně M105. K dispozici je několik identických přípravků s kompletním zapojením maticového displeje, jak je uvedeno na obr. 1, včetně konektoru pro připojení k FITkitu. **Přípravek bude využit i při hodnocení projektu!** Doneste si FITkit, USB kabel a řešení projektu na NB.

![Obr. 1](https://image.prntscr.com/image/IspmwI0dRlWPTpEKH2ckVw.png "Obr. 1")
![Obr. 2](https://image.prntscr.com/image/jkWjHNsiSvqvT8IXkH2Nqg.png "Obr. 2")

## Charakteristika systému

Maticový displej je standardní zobrazovací součástka, která bude externě připojena k FITkitu prostřednictvím vybraných pinů sběrnice X na rozhraní JP10. Na poskytnutém přípravku je použit displej KINGBRIGHT TC23-11SRWA (zájemci naleznou další podrobnosti o něm např [zde](http://www.farnell.com/datasheets/1683574.pdf "zde")).
Jelikož anody diod v každém řádku displeje sdílejí jediný vodič, je nutné provádět řízení displeje dynamicky v tzv. časovém multiplexu, což znamená, že v každém okamžiku je aktivní právě jeden řádek a periodická aktivace všech řádků v čase s rozumnou frekvencí vytváří dojem celkového obrazu na displeji. Příliš vysoká frekvence snižuje intenzitu LED, příliš nízká však způsobuje viditelné blikání displeje. Na FITkitu můžeme použít frekvenci SMCLK/256, na které bude probíhat přepínání aktivity jednotlivých řádků (tj. každý řádek je aktivní 256 period SMCLK). Podle pozice (indexu) každého řádku pomocí dekodéru určíme, co má řádek zobrazit (které jeho LED rozsvítit).

**Pro jednoznačnou orientaci uvažujte, že je-li přípravek připojen k FITkitu v poloze dle obr. 1, jsou řádky displeje indexovány shora dolů (aktivovány signály r0, r1 atd.) a sloupce zleva doprava (signály c0, c1 atd.).**

## Pokyny k vypracování projektu

1. Doplňte kód dle výše uvedené specifikace obvodu do souboru **ledc8x8.vhd**.
1. Doplňte mapování výstupních signálů ROW a LED do souboru **ledc8x8.ucf** tak, aby tyto signály byly přivedeny na příslušné bity sběrnice X, jak je uvedeno na obr. 2.

Fyzicky budou na všech verzích FITkitu namapovány na spodní řadu 16-ti pinů zcela vpravo na rozhraní JP10. Inspirujte se tím, co je již v tomto souboru uvedeno a ze schématu FITkitu určete mapování zbývajících signálů ([viz](http://merlin.fit.vutbr.cz/FITkit/hardware.html "merlin")). Ve schématu [FITKIT-INPUT/OUTPUT INTERFACE](./Input%20-%20Output%20interface.pdf "I/O Interface") je uvedena struktura rozhraní JP10, kde naleznete, které piny sběrnice X je třeba použít a podle toho pak ze schématu [FITKIT-FPGA INTERFACE](./FPGA%20Interface.pdf "FPGA Interface") určíte čísla pinů FPGA, na které je třeba v souboru ledc8x8.ucf namapovat signály ROW a LED z entity obvodu.

Pro ty, kteří si budou chtít obvod odsimulovat v prostředí Xilinx ISIM, byl vytvořen jednoduchý test-bench ledc8x8_tb.vhd, generující hodinový signál SMCLK a inicializační RESET, a skript isim.tcl pro spuštění simulace a sestavení časového diagramu. Oba tyto soubory se nacházejí v adresáři fpga/sim. Zadáním make isim z příkazového řádku v kořenovém adresáři projektu (nebo volbou Spustit simulaci (ISIM) z kontextového menu projektu v QdevKitu) se spustí simulátor ISIM a zobrazí se průběh sledovaných signálů. Pro potřeby ladění si vhodně přizpůsobte čas simulace u příkazu run ve skriptu isim.tcl, případně provizorně upravte frekvenci přepínání iniciálů či aktivity řádků, abyste zjistili, zda obvod korektně realizuje předepsanou činnost. Ačkoliv je možné pomocí simulátoru projekt vyřešit, velmi doporučujeme ověřit jeho funkci na přípravku v CVT.

## Odevzdání, hodnocení

Doplněné řešení odevzdejte do IS v jediném archivu .zip nebo .tar.gz **se stejnou strukturou, jak jste si jej stáhli (závisí na tom automatizovaný překlad pro hodnocení**). Archiv i adresář v něm pojmenujte vaším loginem.

Jednou z podmínek pro získání plného počtu bodů je bezchybná kompilace VHDL kódu i syntéza konfigurace pro FPGA (tj. žádný warning nebo error!).

**Zkontrolujte si, zda opravdu odevzdáváte všechny správné soubory v archivu s danou strukturou. Pokud bude projekt z jakéhokoliv důvodu nepřeložitelný, bude JEDNOU umožněno odevzdání opravené verze mailem s komentářem k opravě a bodovou ztrátou úměrnou rozsahu/závažnosti opravy.**

**U opakovaně problematických či nenapravených řešení bude hodnocení 0 bodů, stejně tak jako v případě zjištěného plagiátorství, v takovém případě navíc s případným postihem dle platného Disciplinárního řádu FIT VUT v Brně.**

### Struktura

```text
xcaber00.zip
  └── xcaber00
        ├── fpga
        │    ├── sim
        │    │    ├── isim.tcl
        │    │    └── ledc8x8_tb.vhd
        │    ├── ledx8x8.ucf
        │    └── ledc8x8.vhd
        ├── mcu
        │    └── main.c
        └── project.xml
```
