#!/usr/bin/env python3

from threading import Thread

def count(n):
    while n > 0:
        n -= 1

t1 = Thread(target=count,args=(10**8,))
t1.start()
t2 = Thread(target=count,args=(10**8,))
t2.start()
t1.join(); t2.join()
