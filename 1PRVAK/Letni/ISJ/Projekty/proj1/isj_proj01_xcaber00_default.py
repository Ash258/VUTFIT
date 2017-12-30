#!/usr/bin/env python3

import re


def first_task():
    # trivialni ukol 1 - 1 bod
    objects = 'Mars Jupiter Uran Neptun Pluto'
    tests1 = ['Neptun']
    for test in tests1:
        if re.search(r'^.*\b(Jupiter|Mars|Neptun|Uran)\b.*$', objects).group(1) == test:
            assert True
        else:
            assert False


def second_task():
    # trivialni ukol 2 - 1 bod
    tests2 = ['987==987', '666==666']
    for test in tests2:
        if re.search(r'([987]{3}|[654]{3})==\1', test):
            assert True
        else:
            assert False


def third_task():
    # mene trivialni ukol - 3 body
    punct = re.compile(r'''(?<=(?<!\d)[,.]  # after a full stop or comma
                            (?=[^\d]     # ...
                            ))''', re.X)
    assert punct.sub(' ',
                     'Hello,John.I bought 192.168.0.1 for 100,000 bitcoins') == 'Hello, John. I bought 192.168.0.1 for 100,000 bitcoins'


first_task()
second_task()
third_task()
