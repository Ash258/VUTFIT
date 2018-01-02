# Platforms

| OS           | Architecture |
| :----------: | :----------: |
| windows 10   | x64 & x86    |
| ubuntu 16.04 | x64 & x86    |

# Authors

| Name & Surname  | Login    |
| :-------------: | :------: |
| Pavel Parma     | xparma02 |
| Vojtěch Bargl   | xbargl01 |
| Jakub Čábera    | xcaber00 |
| Michal Šimončič | xsimon24 |

# Projekt 2

## Zadání

Vytvořte kalkulačku se základními matematickými operacemi (+,-,*,/), faktoriálem, umocňováním s přirozenými exponenty, obecnou odmocninou a jednou další funkcí.

Program lze vytvořit v libovolném programovacím jazyce a bude se skládat ze dvou částí: grafické uživatelské rozhraní a knihovna s matematickými funkcemi. Součástí programu bude i nápověda a k programu bude dodána uživatelská i programová dokumentace (program bude distribuován s otevřenými zdrojovými texty pod licencí GNU GPL v. 1, 2 nebo 3).

V uživatelské dokumentaci bude mimo jiné i postup instalace a odinstalace programu pomocí instalátoru (odinstalátoru). Dále bude uveden návod pro manuální (od)instalaci, tzn. postup překladu ze zdrojových kódů, vytvoření zástupců (ikonek) a dalších akcí, které provádí instalátor.

## Doplňující podmínky

- Preferovanou (ale nikoliv striktně vyžadovanou) platformou je Linux.
- Máte k dispozici virtuální prostředí, na kterých budeme projekt hodnotit (viz níže). Je nutné, aby program alespoň na jednom z nich bez problémů fungoval vč. instalace a odinstalace. V dokumentaci musí být uvedeno, které prostředí jste zvolili a jak zde projekt zprovoznit.
- Pro správu verzí bude využit GIT, Mercurial či Bazaar. Povolené hostingy jsou ivs.fit.vutbr.cz, github.com, gitlab.com, bitbucket.com a merlin.fit.vutbr.cz (mimo sít VUT může být nutné využít VPN; před vytvořením repozitáře čtěte celé pokyny pro odevzdání!). Jiný systém či hosting pro správu verzí pouze po předchozí konzultaci. S CVS či SVN nelze získat plný počet bodů za projekt.
- Testy pro matematickou knihovnu vytváříme dříve než program podle konceptu Test-driven development.
- K matematické knihovně i k celému programu musí být vygenerována programová dokumentace.
- Preferovaný nástroj je Doxygen.
- Součástí bude Makefile pro kompilaci projektu, který bude obsahovat alespoň tyto cíle:
    - all (přeloží projekt)
    - pack (zabalí projekt tak aby mohl být odevzdán)
    - clean (smaže všechny soubory co nemají být odevzdány)
    - test (spustí testy matematické knihovny)
    - doc (spustí generování dokumentace)
    - run (spustí program)
    - Při spuštění make bez uvedení cíle se provede make all.
- Pokud to není nezbytně nutné (např. instalační cesty jako je /usr/bin), Makefile nebude obsahovat absolutní cesty.
- Bude-li to možné, Makefile nebude obsahovat jméno ani jednoho ze zdrojových souborů.
- Na kalkulačce si povinně vyzkoušíte debugging - odevzdáte snímek obrazovky debuggeru v matematické knihovně.
- K programu bude vytvořen mockup uživatelského rozhraní další verze kalkulačky, která bude podporovat vědecký mód, vykreslování grafů a nějakou další potenciálně užitečnou funkci (výpočet BMI, stopky, statistické funkce, …). Musí být jasné, jak bude nová verze vypadat a fungovat, v případě potřeby vytvořte mockupů více.

## Profiling

Pomocí funkcí z Vaší matematické knihovny vytvořte program pro výpočet [směrodatné odchylky](https://cs.wikipedia.org/wiki/Sm%C4%9Brodatn%C3%A1_odchylka) ze souboru čísel (program ji čte ze standardního vstupu, v C např. pomocí funkce scanf). Vzorec pro směrodatnou odchylku:

![Odchylka](https://image.prntscr.com/image/lkvOMLOWQdaxwtJFSFMGEg.png "Odchylka")

Tento program profilujte se vstupy o velikosti 10, 100 a 1000 číselných hodnot. Odevzdejte protokol obsahující výstup profileru a stručné shrnutí - ve kterých místech program tráví nejvíce času a uveďte na co se při optimalizaci kódu nejlépe zaměřit.

## Virtuální prostředí

### Pro testování a hodnocení

- Ubuntu 16.04 - [32bit](http://ivs.fit.vutbr.cz/virtual_machines/IVS%20Ubuntu%2016.04%2032-bit.zip) a [64bit](http://ivs.fit.vutbr.cz/virtual_machines/IVS%20Ubuntu%2016.04%2064-bit.zip)
- Windows 10 - [32bit](http://ivs.fit.vutbr.cz/virtual_machines/IVS%20Win10%2032-bit.zip) a [64bit](http://ivs.fit.vutbr.cz/virtual_machines/IVS%20Win10%2064-bit.zip)

### Pro vývoj ve Windows

Pro vývoj ve Windows jsme Vám připravili ještě virtuální prostředí s MS Visual studio a Qt. Toto prostředí Vám může ušetřit práci s instalací, ale jeho využití je volitelné. Finální instalátor však musí fungovat na jednom z prostředí pro testování určených výše.

- Windows 10 - [32bit](http://ivs.fit.vutbr.cz/virtual_machines/IVS%20Win10%2032-bit%20IDE.zip) a [64bit](http://ivs.fit.vutbr.cz/virtual_machines/IVS%20Win10%2064-bit%20IDE.zip)

~~Všechna virtuální prostředí budou k dispozici do 3 dnů od oficiálního zadání projektu na přednášce (dříve to z technických důvodů není možné). Návod ke stažení bude uveden zde.~~ <br />
[Všechna virtuální prostředí jsou ke stažení zde](http://ivs.fit.vutbr.cz/virtual_machines/)

## Volitelná rozšíření

Především studentům vyšších ročníků doporučujeme zadání rozšířit tak, aby pro ně projekt měl větší přínos.
Příklady rozšíření:

- Výpočty se závorkami (aplikace znalostí z IFJ v praxi).
- Využití více číselných soustav (dvojková, šestnáctková, ...) - dynamické změny rozložení uživatelského
- rozhraní (skrývání a blokování tlačítek).
- Vykreslování grafů.
- Generování náhodných čísel (využívá se pro statistické výpočty).
- ...

Funkcionalita volitelných rozšíření není součástí hodnocení, ale může k ní být přihlédnuto při hodnocení jiné části projekty.

## Tipy pro zlepšení výsledného hodnocení

- Kontrolujte práci ostatních (např. se dohodněte tak, že každý úkol 1 člen týmu plní a 2. kontroluje).
- Doxyfile vytvoří každý člen týmu nezávisle, pak si je porovnáte a nejlepší využijete.
- Na mockupu budou pracovat všichni členové týmu.

## Týmy

- Projekt budou řešit tří až čtyřčlenné týmy. Každý tým si zvolí název (vyhýbejte se názvům známých firem - vyzkoušejte, co pro zvolený název najde Google) a vedoucího, který bude tým zastupovat při komunikaci s vyučujícími.
- Práci na projektu je nutné rozdělit mezi členy týmu (pokud možno rovnoměrně).

## Přihlašování

**Registrace týmu musí být provedena do 10. 3. 2017.**

Přihlašování týmů bude realizováno v IS FIT. Bude-li s přihlášením problém, lze jej provést e-mailem, který vedoucí týmu zašle na adresu dytrych@fit.vutbr.cz:

- předmět (xlogin01 je login vedoucího): "IVS - projekt - xlogin01 xlogin02 xlogin03 xlogin04"
- Obsah:
    - Přihlášení na projekt do IVS
    - Tým: název týmu
    - Vedoucí: Jméno Příjmení xlogin01@stud.fit.vutbr.cz
    - Členové:
    - Jméno Příjmení xlogin01@stud.fit.vutbr.cz
    - Jméno Příjmení xlogin02@stud.fit.vutbr.cz
    - ...

Ostatní členové týmu budou uvedeni také v seznamu příjemců kopie zprávy, aby věděli, že jsou přihlášeni.

## Struktura repozitáře

Kostra repozitáře ke stažení bude k dispozici zde:
root
  ├── mockup/
  │    └── *.png|jpg|svg|pdf
  ├── plan/
  ├── profiling/
  │ ├── vystup.*
  │ └── zprava.txt|pdf
  ├── src/
  │   ├── Zdrojový kód a testy
  │   ├── Makefile
  │   ├── Doxyfile
  │   └── zdrojový kód pro profiling
  ├── debugging.png|jpg|pdf|txt
  ├── dokumentace.pdf
  ├── screenshot.png|jpg
  ├── skutecnost.txt
  ├── hodnoceni.txt
  ├── README.md|txt
  ├── .gitignore
  └── .editorconfig

## Soubor hodnoceni.txt

Soubor hodnoceni.txt bude obsahovat osobní ohodnocení jednotlivých členů týmu v rozsahu 0 - 100% (dle aktivity člena týmu a jeho přínosu pro projekt). Hodnocení musejí odsouhlasit všichni členové týmu. Soubor bude ve formátu (X je počet procent od 0 do 100):

- xlogin01 X (skutečně řešená část projektu)
- xlogin02 X (skutečně řešená část projektu)
- xlogin03 X (skutečně řešená část projektu)
- xlogin04 X (skutečně řešená část projektu)

Tento soubor je zpracováván automaticky, nedodržení struktury může vést na hodnocení nula bodů.

## Soubor README.md nebo README.txt

Soubor bude v patičce povinně obsahovat alespoň následující informace. V části “Prostředí” uveďte pouze jeden řádek dle vybraného prostředí řádky s vybranými prostředími, ve kterých je projekt plně funkční (při hodnocení bude náhodně vybráno jedno z uvedených prostředí).

```markdown
Prostredi
---------
Ubuntu 32bit
Ubuntu 64bit
Windows 32bit
Windows 64bit
Autori
------
Nazev tymu
- xlogin01 jmeno prijmeni
- xlogin02 jmeno prijmeni
- xlogin03 jmeno prijmeni
- xlogin04 jmeno prijmeni
Licence
-------
Tento program je poskytovan...
```

## Odevzdání

**Věnujte prosím pozornost postupu odevzdání a dodržujte názvy souborů a další stanovené podmínky.** Pro desítky projektů není v našich silách za pomoci správce prohledávat domovské adresáře na serveru ivs (častá chyba z předchozích let je odevzdání na toto místo) a jiná umístění, kde by se mohly nacházet odevzdané soubory. Značnou komplikací jsou i nesprávné názvy složek apod.
**Při hodnocení budou využívány i automatické skripty.**

Do **17. 3. 2017** vedoucí týmu v IS FIT odevzdá předběžný plán projektu v souboru xlogin01_xlogin02_xlogin03_xlogin04_plan.txt. Soubor bude obsahovat:

- Stanovené termíny, přidělení úkolů na projektu jednotlivým řešitelům
- Zvolené komunikační kanály pro komunikaci v týmu a stanovená pravidla pro komunikaci (jsou-li nějaká)
- Zvolený systém pro správu verzí a hosting + **informaci, jak do repozitáře mohou nahlédnout vyučující/cvičící (viz níže)**

Alternativně lze odevzdat archiv xlogin01_xlogin02_xlogin03_xlogin04_plan.zip, který bude obsahovat libovolný počet souborů xlogin01_xlogin02_xlogin03_xlogin04_plan* ("*" zastupuje libovolný počet libovolných znaků, tedy např. ".mpp" či "01.jpg"), přičemž plán zde může být vytvořený v MS Projectu či jiném programu (není-li daný program ve škole dostupný, je nutno odevzdat i exportovanou verzi v PDF či jpg).

**Repozitář bude průběžně kontrolován** vyučujícími/cvičícími, aby Vám bylo možné poskytnout zpětnou vazbu, zda jste jej využívali správným způsobem. Máte-li repozitář na serveru ivs.fit.vutbr.cz, vyučující se do něj dostanou bez problémů. Využijete-li **github, gitlab či bitbucket, je třeba přidělit oprávnění pro uživatele ivskontrola** (e-mail má ivs.kontrola@gmail.com, ale na tento e-mail prosím nic nezasílejte - byl vytvořen pouze pro účely vytvoření účtu na výše uvedených serverech).
**Při vytváření repozitáře na serveru merlin.fit.vutbr.cz je nutné k Vašim loginům přidat loginy všech cvičících**: “dytrych, ispanhel, iwiglasz, ibartl, iprivalov, ivaverka”

Do **24. 4. 2017** vedoucí týmu odevzdá:

- Obsah repozitáře projektu (viz struktura výše) - tímto není myšlena pracovní kopie, ale kopie repozitáře (včetně historie)
- Instalátor programu, který kromě samotného programu nainstaluje i odinstalátor
- Vygenerovanou programovou dokumentaci
- Vše bude v jednom adresáři `xlogin01_xlogin02_xlogin03_xlogin04`, který bude sbalený do archivu
- `xlogin01_xlogin02_xlogin03_xlogin04.zip`

Zkontrolujte, zda repozitář obsahuje vše potřebné:

- Uživatelskou příručku v PDF
- Snímek obrazovky programu
- Testy k matematické knihovně
- Snímek obrazovky debuggeru či popis postupu debuggingu
- Mockup(y) další verze kalkulačky
- Informace o provedeném profilingu (v .txt, .pdf či obrázku)
- Soubor skutecnost.txt, který bude obsahovat informace o rozdílech mezi plánem projektu a skutečností
- Soubor hodnoceni.txt (s obsahem viz výše)

### Struktura adresáře v odevzdávaném archivu

```text
xlogin01_xlogin02_xlogin03_xlogin04
  └── xlogin01_xlogin02_xlogin03_xlogin04
        ├── doc/
        │    └── Vygenerovaná programová dokumentace
        ├── install/
        │    └── Instalátory
        └── repo/
            └── Repozitář (musí být pracovní kopie i historie, tedy např. i složka .git)
```

Archiv se odevzdává do adresáře `/ivs-proj2/odevzdane/xlogin01` (kde xlogin01 je login vedoucího týmu) na serveru `ivs.fit.vutbr.cz`.
Odevzdání do jiného adresáře (např. do /home/xlogin01 či /home/xlogin01/ivsproj2/...) bude značně penalizováno.
Je-li vedoucí neaktivní, zvolte si včas nového a oznamte změnu cvičícím, aby mu mohl být vytvořen adresář pro odevzdání.

Do IS FIT uložíte archiv, který bude obsahovat:

- hodnoceni.txt
- Zdrojové soubory programu
- Uživatelskou příručku (nebude-li příliš velká)
- Soubor odevzdani.txt
    - Bude uvedeno datum, čas a způsob odevzdání kompletního archivu
    - Informace o tom, jaké další soubory jsou v něm obsaženy.

Každý člen týmu do **2. 5. 2017** v IS FIT odevzdá soubor xloginNN_problemy.txt, který bude obsahovat seznam problémů, které podle daného člena týmu tým měl, včetně pravděpodobných příčin a navrhovaných řešení (co jste mohli udělat lépe). Pokud tým žádné problémy neměl, budou zde uvedeny pouze návrhy, co by bylo možné při příštím týmovém projektu řešit lépe. Povinně je nutné uvést nejméně 3 problémy či návrhy seřazené od nejdůležitějšího po nejméně důležitý. Zaměřte se při tom na následující oblasti:

- Komunikace v týmu
    - Využili jste vhodné komunikační kanály?
    - Stanovili jste si pravidla a dodržovalije?
    - Komunikovali všichni?
    - ...
- Spolupráce
    - Dělal každý to, co měl?
    - Bylo možné se dohodnout, nebo si někdo prosazoval svoje za každou cenu?
    - ...
- Vedení týmu
    - Dělal vedoucí to, co měl?
    - Měl vedoucí autoritu?
    - ...
- Termíny
    - Naplánovali jste si práci dobře?
    - Začali jste včas?
    - ...
- Aktivita
    - Byla v týmu nějaká iniciativa, nebo všichni čekali, až někdo něco udělá?
- Nástroje
    - Zvolili jste vhodné prostředky pro sdílení dat?
    - Zvolili jste vhodné vývojářské nástroje?
    - Měli jste s něčím problémy?
    - ...

## Obhajoby

- **Obhajoby jsou povinné** a za kvalitně připravenou obhajobu lze získat až 5 bodů. Získáte také zkušenosti s prezentací a zpětnou vazbu k projektu i k prezentaci.
- Přihlašování na obhajoby, které proběhnou ve zkouškovém období, bude přes IS FIT.
    - **Přihlašuje se pouze vedoucí týmu (vedoucí přihlásí celý tým)**.
- K obhajobě bude mít každý tým jednu prezentaci v PDF, kterou odevzdá do IS FIT nejpozději den před
- obhajobou.
    - Název souboru s prezentací musí začínat loginem vedoucího týmu.
    - Jako záložní variantu si přineste prezentaci na obhajobu na USB flash.
- První část prezentace (max. 1,5 min.) bude věnována vytvořenému řešení, následující části budou věnovány získaným zkušenostem při práci v týmu.
    - **Celková doba prezentace nesmí překročit 6 min**.
- Při prezentování se povinně vystřídají všichni členové týmu.
- Při nerovnoměrném hodnocení členů týmu bude prezentace obsahovat krátké zdůvodnění tohoto hodnocení, ke kterému se mohou vyjádřit dotčení členové týmu.
- Po prezentaci následuje krátká diskuse a zhodnocení projektu vyučujícím, při kterém se ihned dozvíte bodové hodnocení.
- **Obhajoby jsou veřejné**. Po skončení obhajob budou diskutovány nejčastější chyby v projektech a případný zbývající čas bude věnován prostoru pro vzájemnou výměnu zkušeností (kdokoliv může dobrovolně prezentovat zkušenosti z práce na projektu, ze kterých plyne ponaučení do dalších projektů).
- **Z obhajob je pořizován záznam** a můžete se tedy podívat, jak Vaše vystoupení působí a co byste měli do budoucna zlepšit.
- Vzhledem ke zveřejnění záznamu je vhodné se v prezentacích vyhnout využití licencovaných fotografií a jiných autorských děl 3. stran.
- Vstupem do obhajovací místnosti souhlasíte s pořízením a zveřejněním záznamu (veřejně přístupný záznam na webu FIT). Nesouhlasíte-li, nevstupujte prosím a e-mailem si dohodněte konzultace, kde individuálně zvolíme náhradní řešení (např. náhradní individuální projekt za 5 bodů, jehož hodnocení bude podmíněno nenulovým hodnocením týmového projektu) - historicky se zatím nikdo takový nenašel.

## Hodnocení projektu

### Části projektu hodnocené pro celý tým dohromady

- 2 body za vytvoření repozitáře a zpřístupnění vyučujícím,
- 25 bodů za funkční a kompletní výsledný produkt (matematická knihovna s testy, program, instalátor, odinstalátor a dokumentace),
- 3 body za naplánování a rozdělení práce,
- 3 body za Makefile,
- 2 body za debugging,
- 3 body za mockup další verze programu,
- 1 bod za vyhodnocení rozdílů mezi plánem projektu a skutečností,
- 4 body za profiling.

Celý tým může získat 43 * počet členů týmu = 129 nebo 172 bodů.

### Hodnocení každého člena týmu

- 2 body za vhodné využívání systému pro správu verzí
- 43 bodů za produkt dle Vašeho hodnocení (`43 * počet % * 0.01`)
- 2 body za zhodnocení práce v týmu (za zamyšlení nad tím, co jste dělali špatně a jak to řešit lépe)
- 5 bodů za obhajobu

**Celkem může každý člen týmu za projekt získat 52b.**

## Dotazy a konzultace

- Pro dotazy přednostně využívejte fórum v IS FIT.
- Dotazy, které nechcete zveřejnit (např. ke konkrétnímu řešení projektu), můžete zaslat i na [e-mail](dytrych@fit.vutbr.cz) nebo můžete přijít na [osobní konzultaci](http://www.fit.vutbr.cz/~dytrych/courses.php).
