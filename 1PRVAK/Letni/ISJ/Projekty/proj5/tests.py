import unittest

from proj5.isj_proj05_xcaber00 import Polynomial


class TestPoint(unittest.TestCase):
    def setUp(self):
        pass
    
    def test(self):
        assert str(Polynomial(0, 1, 0, -1, 4, -2, 0, 1, 3, 0)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
        assert str(Polynomial([-5, 1, 0, -1, 4, -2, 0, 1, 3, 0])) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x - 5"
        assert str(Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3=-1, x1=1)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
        assert str(Polynomial(x2=0)) == "0"
        assert str(Polynomial(x0=0)) == "0"
        assert Polynomial(x0=2, x1=0, x3=0, x2=3) == Polynomial(2, 0, 3)
        assert Polynomial(x2=0) == Polynomial(x0=0)
        assert str(Polynomial(x0=1) + Polynomial(x1=1)) == "x + 1"
        assert str(Polynomial([-1, 1, 1, 0]) + Polynomial(1, -1, 1)) == "2x^2"
        pol1 = Polynomial(x2=3, x0=1)
        pol2 = Polynomial(x1=1, x3=0)
        assert str(pol1 + pol2) == "3x^2 + x + 1"
        assert str(pol1 + pol2) == "3x^2 + x + 1"
        assert str(Polynomial(x0=-1, x1=1) ** 1) == "x - 1"
        assert str(Polynomial(x0=-1, x1=1) ** 2) == "x^2 - 2x + 1"
        pol3 = Polynomial(x0=-1, x1=1)
        assert str(pol3 ** 4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
        assert str(pol3 ** 4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
        assert str(Polynomial(x0=2).derivative()) == "0"
        assert str(Polynomial(x3=2, x1=3, x0=2).derivative()) == "6x^2 + 3"
        assert str(Polynomial(x3=2, x1=3, x0=2).derivative().derivative()) == "12x"
        pol4 = Polynomial(x3=2, x1=3, x0=2)
        assert str(pol4.derivative()) == "6x^2 + 3"
        assert str(pol4.derivative()) == "6x^2 + 3"
        assert Polynomial(-2, 3, 4, -5).at_value(0) == -2
        assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3) == 20
        assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3, 5) == 44
        pol5 = Polynomial([1, 0, -2])
        assert pol5.at_value(-2.4) == -10.52
        assert pol5.at_value(-2.4) == -10.52
        assert pol5.at_value(-1, 3.6) == -23.92
        assert pol5.at_value(-1, 3.6) == -23.92
