from proj7.isj_proj07_xcaber00 import *
import unittest

class Test(unittest.TestCase):
    @limit_calls(1)
    def nop(self):
        pass
    
    def test_limit_calls(self):
        self.nop()
        self.assertRaises(TooManyCallsError, self.nop)
    
    def test_ordered_merge(self):
        expected = [3.0, 11, 'a', 1, 22, 2]
        actual = list(ordered_merge('abcde', [1, 2, 3], (3.0, 3.14, 3.141), range(11, 44, 11), selector=[2, 3, 0, 1, 3, 1]))

        self.assertListEqual(expected, actual)
    
    def test_logger(self):
        with self.assertRaises(ZeroDivisionError) as context:
            with Log("test.log") as logger:
                logger.logging('Test1')
                logger.logging('Test2')
                a = 1 / 0
                logger.logging('Test3')