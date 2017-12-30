#!/usr/bin/env python3

import fileinput

words = set()
palindroms = set()
for line in fileinput.input():
    cosi = line.rstrip()
    words.add(cosi)
    if cosi == cosi[::-1]: palindroms.add(cosi)

result = [w for w in words if w not in palindroms and w[::-1] in words]

print(sorted(result))
