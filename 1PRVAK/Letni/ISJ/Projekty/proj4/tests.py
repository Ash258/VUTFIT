import unittest

from proj4.isj_proj04_xcaber00 import *


class Test(unittest.TestCase):
    def test_balanced_paren(self):
        self.assertTrue(balanced_paren('123'))
        self.assertTrue(balanced_paren('(123)'))
        self.assertTrue(balanced_paren('[{}]'))
        self.assertTrue(balanced_paren('12<4<[a]b>>5'))
        self.assertTrue(balanced_paren('[a{(1)()}<.>(9)/]'))
        self.assertFalse(balanced_paren('{1<2(>3)}'))
        self.assertFalse(balanced_paren('(1'))
        self.assertFalse(balanced_paren('1)'))

    def test_caesar_list(self):
        self.assertEqual('bdf', caesar_list("abc"))
        self.assertEqual('akz', caesar_list("akz", [0]))
        self.assertEqual('cde', caesar_list("abc", [2]))
        self.assertEqual('ace', caesar_list("xyz", [3, 4, 5, 6, 7]))
        self.assertEqual('egg', caesar_list("abc", [4, 5]))
        self.assertEqual('egg', caesar_list("abc", [4, 5]))
        self.assertRaises(ValueError, caesar_list, "A")
        self.assertRaises(ValueError, caesar_list, "ab1c", [1, 2])
        self.assertRaises(ValueError, caesar_list, "abc", [1, 2, "a"])

    def test_caesar_varnumkey(self):
        self.assertEqual('bdf', caesar_varnumkey("abc"))
        self.assertEqual('bdf', caesar_varnumkey("abc", 1, 2, 3))
        self.assertEqual('akz', caesar_varnumkey("akz", 0))
        self.assertEqual('cde', caesar_varnumkey("abc", 2))
        self.assertEqual('ace', caesar_varnumkey("xyz", 3, 4, 5, 6, 7))
        self.assertEqual('egg', caesar_varnumkey("abc", 4, 5))
        self.assertEqual('egg', caesar_varnumkey("abc", 4, 5))
        self.assertRaises(ValueError, caesar_varnumkey, "A")
        self.assertRaises(ValueError, caesar_varnumkey, "a", 1, "a")
        self.assertRaises(ValueError, caesar_varnumkey, "abc", [])
        self.assertRaises(ValueError, caesar_varnumkey, "abc", [1, 2, 3])
        self.assertRaises(ValueError, caesar_varnumkey, "abc", [1, 2, "a"])
