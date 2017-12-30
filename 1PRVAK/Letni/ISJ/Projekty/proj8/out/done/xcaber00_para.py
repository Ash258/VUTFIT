#!/usr/bin/env python3
from multiprocessing import Pool


def count(n):
    while n > 0:
        n -= 1


if __name__ == '__main__':
    pool = Pool(processes=2)
    pool.map(count, (10**8, 10**8,))
