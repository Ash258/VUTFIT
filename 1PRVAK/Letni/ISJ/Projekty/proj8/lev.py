#!/usr/bin/env python3
import cProfile

def lev(a, b):
    """Recursively calculate the Levenshtein edit distance between two strings,
    a and b.
    Returns the edit distance.
    """
    if("" == a):
        return len(b)   # returns if a is an empty string
    if("" == b):
        return len(a)   # returns if b is an empty string
    return min(lev(a[:-1], b[:-1])+(a[-1] != b[-1]), lev(a[:-1], b)+1, lev(a, b[:-1])+1)

# print(lev('abracadabra', 'abba'))
cProfile.run("lev('abracadabra', 'abba')")