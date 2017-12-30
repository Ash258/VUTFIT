#!/usr/bin/env python3
"""
Module for polynomial operations.
"""
import re
from functools import reduce
from operator import add


class Polynomial:
    """
    Class represent polynom.
    """
    x = ['', 'x']
    
    def __init__(self, *args, **kwargs):
        """
        Initialize class Polynomial.
        :param args: Arguments for creating.
        :param kwargs: Keywords arguments for creating.
        """
        # List of arguments.
        if args and isinstance(args[0], list):
            self.polynom = args[0]
        # Only arguments.
        elif args:
            self.polynom = args
        # Named arguments.
        else:
            self.polynom = [kwargs.get(x, 0) for x in ['x' + str(i) for i in range(len(kwargs) + 1)]]
        
        # Degree of polynom.
        self.deg = len(self.polynom)
    
    def __str__(self):
        """
        To string.
        :return: String Final polynomial representation.
        """
        # Format
        terms = ['{0:+d}'.format(self.polynom[k]) +
                 ('x^' + str(k) if k > 1 else self.x[k]) for k in range(0, self.deg) if self.polynom[k] != 0]
        # No terms.
        if len(terms) == 0:
            return "0"
        
        return re.sub('[^0-9]1x', ' x', reduce(add, terms[::-1]).replace('+', ' + ').replace('-', ' - ')).lstrip(' + ')
    
    def __eq__(self, other):
        """
        == Operator. Compare each term of both Polynomials.
        :param other: Second polynomial.
        :return: True if both are equal.
        """
        for i in range(1, len(self.polynom)):
            return self.polynom[i] == other.polynom[i]
    
    def __call__(self, x):
        """Evaluates the Polynomial at value of x"""
        
        return reduce(add, [self.polynom[i] * (x ** i) for i in range(self.deg)])
    
    def __add__(self, other):
        """ + operator. Addition two polynomials. """
        
        # Initialize polynom.
        terms = [0] * max(self.deg, other.deg)
        for i in range(self.deg):
            terms[i] = self.polynom[i]
        # Addition each coefficients.
        for i in range(other.deg):
            terms[i] = terms[i] + other.polynom[i]
        
        return Polynomial(terms)
    
    def __mul__(self, other):
        """ * operator. Multiply two Polynomials. """
        
        # Initialize coefficient list of product.
        product = [0] * (self.deg + other.deg + 1)
        for i in range(0, self.deg):
            for j in range(0, other.deg):
                product[i + j] += self.polynom[i] * other.polynom[j]
        
        return Polynomial(product)
    
    def __pow__(self, power):
        """
        ** operator. Power self with given number.
        :param power: Number for powering.
        :return: Powered polynom.
        """
        if power < 0:
            raise ValueError("Power must be a non-negative integer.")
        elif power == 0:
            return Polynomial(1)
        elif power == 1:
            return self
        else:
            result = self
            for i in range(2, power + 1):
                result = result * self
            
            return result
    
    def derivative(self):
        """
        Derivation of polynom.
        :returns Array Result of derivation.
        """
        result = []
        # Iterate through every polynom part.
        for i in range(1, len(self.polynom)):
            result.append(self.polynom[i] * i)
        
        return Polynomial(result)
    
    def at_value(self, x, y=None):
        """
        Value of polynomial for given value.        
        :param x: Value for returning result.
        :param y: Optional second value.
        :return: Value of polynomial on specified value.
        """
        
        return self.__call__(x) if y is None else self.__call__(y) - self.__call__(x)


def test():
    assert str(Polynomial(1, -3, 0, 2)) == "2x^3 - 3x + 1"
    assert str(Polynomial(0, 1, 0, -1, 4, -2, 0, 1, 3, 0)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(Polynomial([1, -3, 0, 2])) == "2x^3 - 3x + 1"
    assert str(Polynomial([-5, 1, 0, -1, 4, -2, 0, 1, 3, 0])) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x - 5"
    assert str(Polynomial(x0=1, x3=2, x1=-3)) == "2x^3 - 3x + 1"
    assert str(Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3=-1, x1=1)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(
            Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3=-1, x1=3)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + 3x"
    assert str(
            Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3=-1, x1=-3)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 - 3x"
    assert str(Polynomial(x7=1, x8=3, x9=0, x0=9, x5=-2, x3=-1, x1=-3)) == "3x^8 + x^7 - 2x^5 - x^3 - 3x + 9"
    assert str(Polynomial(x8=3, x9=0, x0=9, x5=-2, x3=-1, x1=-3)) == "3x^8 - 2x^5 - x^3 - 3x + 9"
    assert str(Polynomial(x8=-3, x9=0, x0=-9, x5=-2, x6=0, x3=-1, x1=-3)) == "- 3x^8 - 2x^5 - x^3 - 3x - 9"
    assert str(Polynomial(x2=0)) == "0"
    assert str(Polynomial(0, 0)) == "0"
    assert str(Polynomial([0])) == "0"
    assert str(Polynomial(x5=0)) == "0"
    assert str(Polynomial(x0=0, x9=-0)) == "0"


if __name__ == '__main__':
    test()
