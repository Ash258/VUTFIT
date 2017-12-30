> Do souboru, nazvaného podle konvence isj\_proj07\_xnovak00.py, implementujte:

1. dekorátor `@limit_calls` s parametry `max_calls` a `error_message_tail` (defaultní hodnoty 2 a `'called too often'`) pro obecné funkce tak, aby např.:
    ```python
    import math
    @limit_calls(1, 'that is too much')
    def pyth(a,b):
        c = math.sqrt(a**2 + b ** 2)
        return c
    print(pyth(3,4))
    print(pyth(6,8))
    ```

    Vypsalo např:

    ```python
    5.0
    Traceback (most recent call last):
      File "isj_proj07_xnovak01.py", line 43, in <module>
        print(pyth(6,8))
      File "isj_proj07_xnovak01.py", line 14, in wrapper
        raise TooManyCallsError(specific_error_message)
    __main__.TooManyCallsError: function "pyth" - that is too much
    ```

1. Generátorovou funkci `ordered_merge`, která bude moci být volána s libovolným počtem iterovatelných objektů a parametrem `selector`, udávajícím, z kterého iterovatelného objektu má prvek na dané pozici být, a bude vybírat prvky v zadaném pořadí (první iterovatelný objekt má v selector index 0).
    Například tedy:

    `print(list(ordered_merge('abcde', [1, 2, 3], (3.0, 3.14, 3.141), range(11, 44, 11), selector = [2,3,0,1,3,1])))`

    vypíše: `[3.0, 11, 'a', 1, 22, 2]`
1. třídu Log tak, aby po vrácení chyby z kódu:

    ```python
    with Log('mylog.txt') as logfile:
        logfile.logging('Test1')
        logfile.logging('Test2')
        a = 1/0
        logfile.logging('Test3')
    ```

    bylo v souboru mylog.txt:

    ```text
    Begin
    Test1
    Test2
    End
    ```
