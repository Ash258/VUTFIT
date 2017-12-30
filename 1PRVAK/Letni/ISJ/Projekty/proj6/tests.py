import unittest

from proj6.isj_proj06_xcaber00 import *


class Test(unittest.TestCase):
    def test_first_nonrepeating(self):
        self.assertEquals("h", first_nonrepeating("tooth"))
        self.assertEquals("h", first_nonrepeating("toothc"))
        self.assertEquals("c", first_nonrepeating("tootch"))
        self.assertEquals(None, first_nonrepeating("lool"))
        self.assertEquals("!", first_nonrepeating("113!3"))
        self.assertEquals(" ", first_nonrepeating("!11 303!"))
    
    def test_combine4(self):
        for item in combine4([6, 6, 5, 2], 36):
            self.assertEquals(eval(item), 36)
        
        for item in combine4([6, 6, 5, 2], 17):
            self.assertEquals(eval(item), 17)
        
        for item in combine4([1, 2, 3, 4], 24):
            self.assertEquals(eval(item), 24)
        
        for item in combine4([0, 0, 0, 0], 0):
            self.assertEquals(eval(item), 0)
