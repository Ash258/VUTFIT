1. _(6b)_
    ```nasm
    MOV AL, 8
    MOV AL, 8
    MOV BL, 17
    MOV CL, AL
    ADD CL, 2
    TEST CL, 7        CL=
    JNZ hop1
    XOR CL, 255

    hop1:
    MOV AH, CL      AX=
    AND CL, 7
    SAR AX, CL        AX=
    XCHG AL, DL
    AND DL, 127     DL=
    ```
1. _(4b)_
    - _(1b)_ Hexa DC6 do desítkové
    - _(1b)_ Dekadické -65 na binární 8bit se znaménkem v doplňkovém kódě
    - _(1b)_ Binární 8bit se znaménkem v přímém kódě 01101011 do dekadické
    - _(1b)_ Binární 8bit bez znaménka 00110000 do hexa
1. _(6b)_ Fragment programu, který zjistí index prvního nenulového bitu zleva v retistri EDX a výsledek uloží do registru BL. Bity se číslují od 0 zprava. Pokud se nenajde nulový bit, BL vrátí libovolnou hodnotu.

>>>
Ďalšie zadania úlohy 3 rôznych skupín (neviem presné znenie): <br />
Fragment programu, který odpočítá počet jednotkových bitů registru EDI od počtu nulových bitů v registru AX a výsledek uloží do registru CH. <br />
Fragment programu, který navzájem vymění obsahy posledních bitů registru DH a CL. <br />
Fragment programu, který zjistí index prvého nenulového bitu zprava.
>>>
