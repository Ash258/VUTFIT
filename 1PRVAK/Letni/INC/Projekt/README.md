# Projekt Přístupový terminál

## Zadání

1. Seznamte se s přípravkem FITKit a způsobem připojení jeho periférií, zejména klávesnice a LCD displeje.
1. Prostudujte si zdrojové kódy projektu v jazyce VHDL.
1. Navrhněte řídicí jednotku (konečný automat) jednoduchého přístupového terminálu.
1. Navrženou řídicí jednotku implementujte v jazyce VHDL a ověřte její funkčnost přímo na přípravku FITKit.

## Architektura přístupového terminálu

Přístupový terminál je jednoduché elektronické zařízení, které povoluje oprávněným uživatelům vstup do chráněných objektů. Obvykle je složeno z klávesnice, LCD displeje a řídicí jednotky. Každý uživatel musí před vstupem do objektu vyťukat na klávesnici přístupového terminálu aktivační kód a na jeho základě získá nebo nezíská přístup do objektu.

Cílem tohoto projektu je realizovat takovýto přístupový terminál na přípravku FITKit, kde je k dispozici klávesnice, LCD display a FPGA hradlové pole připojené k oběma těmto perifériím. Úlohou FPGA čipu bude sledovat vstupy klávesnice, vyhodnocovat zadaný vstupní kód a vypisovat příslušné odezvy na LCD displeji. Architektura FPGA čipu je uvedena na následujícím obrázku.

![FPGA](https://i.imgur.com/yVUqVuw.png "FPGA")

### Funkce obvodu je následující

- Vstupy z klávesnice jsou pravidelně testovány pomocí řadiče klávesnice (Keyboard Controller). Jakmile je detekován stisk některé klávesy, nastaví řadič na svém výstupu KEY jeden z 16-ti signálů odpovídající číslu stisknuté klávesy (signály KEY(0..9) odpovídají klávesám 0..9, signály KEY(10..13) odpovídají klávesám A..D, signál KEY(14) odpovídá klávese "*", signál KEY(15) odpovídá klávese "#").
- Výstupní signály z klávesnice jsou dále připojeny ke konečnému automatu (FSM), který ovládá zbývající části obvodu. Automat sleduje posloupnost stisknutých kláves, v průběhu zadávání kódu vypisuje na LCD displeji znak "*" a po potvrzení kódu klávesou "#" vypíše na displej zprávu "Pristup povolen" nebo "Pristup odepren". Opětovným stisknutím klávesy "#" přechází obvod opět do stavu čekajícího na vstupní kód.
- Textové zprávy "Pristup povolen" resp. "Pristup odepren" jsou uloženy ve dvou paměťových modulech typu ROM. Každý z modulů obsahuje 16 osmi-bitových položek obsahujících jednu ze zpráv.
- V okamžiku potvrzení vstupního kódu klávesou "#", aktivuje automat Clock Enable signál 4-bitového čítače (COUNTER), který je připojen na adresové vstupy paměťových modulů a způsobí tak vyčtení jejich obsahu na výstup.
- Výstupy paměťových modulů jsou dále připojeny na dvou-vstupý multiplexor (MX_MEM). V případě, že byl kód správně zadán, potom automat vybere skrze tento multiplexor zprávu "Přístup povolen", v opačném případě vybere zprávu "Pristup odepren".
- Výstup multiplexoru (MX_MEM) je připojen na další dvou-vstupý multiplexor (MX_LCD). Tento multiplexor přepíná na svůj výstup buď zprávu uloženou v paměťových modulech nebo znak "*" podle toho, zda se přístupový terminál nachází ve stavu zadávání kódu nebo ve stavu vypisujícím výstupní zprávu.
- Výstup multiplexoru (MX_LCD) je připojen na datový vstup řadiče LCD displeje (LCD DISPLAY CONTROLLER) a reprezentuje znaky, které se budou zobrazovat na displeji. Řadič je ovládán pomocí dvou signálů WRITE a CLEAR. Aktivace signálu WRITE způsobí zápis znaku na displeji, zatímco aktivace signálu CLEAR displej vymaže a připraví na zápis nové sekvence znaků.

**Architektura FPGA čipu je připravena tak, že vše kromě konečného automatu FSM je již naimplementováno v jazyce VHDL. Cílem toho projektu je proto správně navrhnout a implementovat právě tento automat řídící zbývající části obvodu.**

## Postup práce

1. Pro vypracování projektu a jeho ověření na přípravku FITkit jsou potřeba následující nástroje: MSPGCC (kompilátor zdrojových souboru pro mikrokontrolér MSP430), Xilinx ISE (vývojové prostředí pro syntézu obvodů v jazyce VHDL do čipu FPGA) a QDevKit (prostředí pro práci s přípravkem FITkit).
    - S ohledem na náročnost instalace všech těchto nástrojů byl pro Vás připraven obraz virtuálního stroje, kde jsou všechny tyto nástroje již nainstalovány. Obraz tohoto virtuálního stroje si stáhněte z privátních stránek FITkitu.
    - Pro spuštění tohoto stroje si nainstalujte volně dostupný program VirtualBox.
1. Připojte FITkit k počítači.
1. Spusťte program VirtualBox a připojte obraz virtuálního stroje. V nastavení USB zařízení povolte FTDI Dual RS232 (viz obrázek) a virtuální stroj spusťte.
    - Důležitá poznámka: Používejte VirualBox verze 5 a vyšší. Starší verze nepodporují USB 3.0, a proto pokud máte na svém počítači pouze porty USB 3.0, potom se FITkit nebude korektně propagovat z vašeho systému až do virtuálního stroje.
1. Z informačního systému si stáhněte archív zdrojových souborů projekt.zip a rozbalte si jej do adresáře C:\FitkitSVN\apps\demo\terminal\ (uvnitř virtuálního stroje).
    - Po spuštění aplikace QDevKit by se Vám měla objevit v záložce Demo aplikace nová položka s názvem Přístupový terminál (viz obrázek).
    - Od tohoto okamžiku můžete aplikaci překládat, simulovat, nahrávat do přípravku FITkit a následně spouštět (všechny tyto volby jsou dostupné skrze kontextové menu vyvolané kliknutím pravého tlačítka myši na položku Přístupový terminál).
1. V informačním systému také naleznete soubor kod.txt se seznamem přístupových kódů.
    - Uvnitř tohoto souboru vyhledejte svůj login a u něj naleznete také dva přístupové kódy pro Váš projekt.
1. Prostudujte si zdrojové kódy projektu v jazyce VHDL a způsob zapojení jeho jednotlivých částí.
1. Navrhněte řídicí jednotku (konečný automat) jednoduchého přístupového terminálu.
    - Při návrhu dbejte na následující požadavky:
        - Přístupový terminál musí akceptovat pouze Vaše dva přístupové kódy (tzn. terminál vypíše hlášení „Pristup povolen“, pokud uživatel zadá správně libovolný z obou kódů).
        - Pokud uživatel v průběhu zadávání kódu stiskne špatnou klávesu, nesmí to Váš automat nijak dát najevo, dokud není stisknuta potvrzovací klávesa "#".
        - Identifikujte Mealyho a Moorovy výstupy.
        - Sestavte si graf přechodů automatu.
        - Při sestavování grafu přechodu automatu vzniká obecně velké množství přechodů mezi stavy, neboť je potřeba reagovat na všechny možné stisknuté klávesy (celkem 16 možností).
            - Pro zjednodušení a přehlednost prosím využijte v grafu označení typu KEY=X (pro očekávanou klávesu) a KEY<>X (pro všechny ostatní případy).
        - Při návrhu respektujte rozhraní automatu (tj. názvy vstupních a výstupních signálů), které je připraveno v souboru fsm.vhd.
            - Rovněž zachovejte název proměnných automatu: present_state a next_state.
        - Nezjednodušujte si prosím práci vložením přístupového kódu do proměnné typu pole a jejím cyklickým testováním.
            - Takovéto projekty nebudou hodnoceny.
        - Příklad automatu v souboru fsm.vhd slouží pouze pro inspiraci a v žádném případě nemusí souhlasit s Vámi navrženým automatem.
1. Navržený konečný automat implementujte v jazyce VHDL a uložte do předpřipraveného souboru fsm.vhd v adresáři fpga.
1. Proveďte simulaci VHDL kódu pomocí programu ISIM. Simulaci lze spustit pomocí nástroje qdevkit.
1. Jakmile je ověřena funkce přístupového terminálu v simulacích, je možné přistoupit k testování funkce přímo na FITKitu. Nejprve proveďte překlad zdrojových souborů do binární podoby (pomocí nástroje qdevkit).
1. Vytvořený binární soubor s příponou *.bin nahrajte do FPGA čipu (pomocí nástroje qdevkit).
1. Správnou funkci přístupového terminálu ověřte přímo na FITKitu.

## Výstupy projektu

Výstupem projektu bude:

1. Soubor fsm.vhd se zdrojovým kódem konečného automatu.
1. Soubor accterm.bin, obsahující konfiguraci pro FPGA čip.
    - Tento soubor naleznete v podadresáři build.
1. Soubor **zprava.**pdf s výstupní zprávou (ve formátu PDF) obsahující následující informace:
    - Jméno a příjmení, login, přístupové kódy
    - Graf přechodu konečného automatu
    - Seznam výstupů s identifikací, zda se jedná o Mealyho nebo Moorovy výstupy.
    - Ukázku výstupní zprávy naleznete v příloze č. 1.

**Rozsah zprávy nesmí překročit jednu stranu formátu A4.**

**Všechny tři soubory zabalte do archívu s názvem `login.zip`.**

**Před odevzdáním tohoto archivu do informačního systému si prosím tento archiv otestujte skrze sadu testovacích skriptů dostupných v informačním systému v souboru student_test.zip. Podrobný návod na otestování naleznete v přiloženém README souboru.**

**Otestovaný archiv odevzdejte prostřednictvím informačního systému nejpozději do data uvedeného na wiki stránkách předmětu INC. Pozdější odevzdání projektu nebude bráno v úvahu.**

**Po zkušenostech z minulých let ještě jedno důležité upozornění!**

**Podle Směrnice děkana FIT doplňující Studijní a zkušební řád VUT (Rozhodnutí děkana FIT č. 34/2010), K článku 11, odst. 4:**
**„Veškeré testy, projekty a další hodnocené úlohy vypracovává student samostatně, pokud projekt nebo úloha nebyly výslovně zadány pro stanovenou skupinu studentů.“**

**V případě odhalení plagiátorství nebo nedovolené spolupráce na projektu, bude proto student odměněn neudělením zápočtu z předmětu INC (0 bodů za projekt). Případně i předvoláním před disciplinární komisi podle Disciplinárního řádu pro studenty Fakulty informačních technologií Vysokého učení technického v Brně.**
