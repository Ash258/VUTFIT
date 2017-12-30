#!/usr/bin/env python3

import collections

# for task 1, 2, 3
eskymo = ['do', 'pre', 'du', 'du', 'do', 'za', 'du', 'du']


def first_task():
    # number of all distinct strings in the eskymo list
    vocabulary_size_eskymo = len(set(eskymo))
    # test
    return vocabulary_size_eskymo == 4


def second_task():
    # for the next test
    prepos = ['do', 'za', 'pred']

    # all distinct strings in both the lists
    in_both_eskymo_prepos = set(prepos).intersection(eskymo)
    # test
    in_both_str = ';'.join(in_both_eskymo_prepos)
    return in_both_str == 'do;za' or in_both_str == 'za;do'


def third_task():
    # what strings and how many times appeared in the eskymo list
    wordfreq_eskymo = collections.Counter(eskymo)
    # test
    return ''.join(word + str(freq) for (word, freq) in wordfreq_eskymo.items()) == 'do2pre1du4za1'


def fourth_task():
    # for the next test
    udubutubudu = 'u dubu tu budu.'

    # the udubutubudu string without the last character, backwards
    backward_except_last = udubutubudu[:-1][::-1]
    # test
    return backward_except_last == 'udub ut ubud u'


def fifth_task():
    # for the next test
    hymn_st_john = 'Hymn of St. John: Ut queant laxis re sonare fibris mi ra gestorum fa muli tuorum sol ve polluti ' \
                   'la bii reatum SI Sancte Iohannes'

    # the hymn as a list of strings separated by ' '
    hymn_list = hymn_st_john.split(' ')
    # the list starting from the fifth string, skipping always two strings
    skip2 = hymn_list[4::3]
    # the skip2 list as a string, ', ' as a separator
    skip2_str = ', '.join(skip2)
    # test
    return skip2_str == 'Ut, re, mi, fa, sol, la, SI'


if first_task():
    print('funguje')
else:
    print('nefunguje')
if second_task():
    print('funguje')
else:
    print('nefunguje')
if third_task():
    print('funguje')
else:
    print('nefunguje')
if fourth_task():
    print('funguje')
else:
    print('nefunguje')
if fifth_task():
    print('funguje')
else:
    print('nefunguje')
