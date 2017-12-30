#!/usr/bin/env python3
"""
Modul pro 4. projekt.
"""
import itertools
import string


def balanced_paren(parenstr):
    """
    Vrátí True, pokud je řetězec, v němž se jako závorky mohou vyskytnout znaky '()[]{}<>', správně uzávorkovaný,
    jinak False.
    Například pro řetězce '123', '[{}]', '12<4<[a]b>>5' vrátí True, pro '{1<2(>3)}' False.
    
    Parameters
    ---------------
    :parameter parenstr Řetězec ke zkontrolování.
    
    Returns
    --------------------------------
    ":returns True Pokud je řetězec dobře uzávorkován.
    """
    stack = []
    # All supported brackets.
    parentheses = iter('()[]{}<>')
    # Create dictionary with Opening bracket as key and closing bracket as value.
    parenth = dict(zip(parentheses, parentheses))

    for char in parenstr:
        # Get bracket or None
        bracket = parenth.get(char, None)
        # If it's bracket append stack with open bracket
        if bracket: stack.append(bracket)
        # Character is closing bracket.
        elif char in parenth.values():
            # If stack is empty or bracket is different./
            if not stack or char != stack.pop():
                return False

    return not stack


def caesar_list(word, key=(1, 2, 3)):
    """
    Vrátí vstupní řetězec zakódovaný podle klíče Caesarovou šifrou. Vstupní řetězec má být složený výhradně z 26
    malých písmen anglické abecedy. Pokud tomu tak není, vraťte výjimku ValueError. Klíč má formu seznamu čísel,
    udávající posun v abecedě, např. [3,5,7]. Použije se cyklicky. Pokud tedy bude vstupem 'abc', a klíč [4,5],
    výsledkem má být 'egg'. Můžete využít itertools.cycle(). Pokud posun \"přeteče\" přes konec abecedy, začíná se od
    začátku. Pokud tedy bude vstupem 'xyz', a klíč [3,4,5,6,7], výsledkem má být 'ace'. Při volání funkce nemusí být
    parametr key zadán, potom se použije defaultní klíč [1,2,3].
    
    Parameters
    ---------------
    :parameter word Slovo k zašifrování.
    :parameter key Klíč využit při šifrování.
    
    Returns
    --------------------------------
    :returns Zašifrovaný řetězec.
                ValueError pokud byly zadány jiné než základní znaky anglické abecedy.
    
    """
    # All 26 letters in right place.
    letters = string.ascii_lowercase
    encrypted_word = ''
    # Handle non integer values
    for i in key:
        if not isinstance(i, int):
            raise ValueError("Nelze zašifrovat jiné znaky než " + letters + '`')

    # Create generator for cycling through key.
    generator = itertools.cycle(key)

    # Iterate through lowercase word.
    for char in word:
        if char in letters:
            # ENCRYPTED_CHAR = (((CHAR – ‘A’ + SHIFT) % 26) + ‘A’)
            encrypted_word += chr((((ord(char) - ord('a')) + next(generator)) % letters.__len__()) + ord('a'))
        else:
            raise ValueError("Nelze zašifrovat jiné znaky než " + letters + '`')

    return encrypted_word


def caesar_varnumkey(word, *argv):
    """"
    Funguje stejně jako funkce caesar_list, jen klíč se při volání předává jako samostatné parametry, tedy např.
    caesar_varnumkey('xyz', 3, 5, 7).
    
    Returns
    --------------------------------
    :returns Zašifrovaný řetězec.
                ValueError pokud byly zadány jiné než základní znaky anglické abecedy.
    
    """

    # Call function with word argument, and list of remaining arguments.
    if not argv:
        argv = [1, 2, 3]

    return caesar_list(word, argv)
