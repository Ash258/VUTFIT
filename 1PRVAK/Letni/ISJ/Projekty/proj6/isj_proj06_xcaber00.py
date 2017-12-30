#!/usr/bin/env python3
""" Module for sixth project. """
import itertools


def first_nonrepeating(string):
    """
    Function analyze string and return first non repeating character.
    :param string: String for analyzing. 
    :return: First non-repeating character.
    """
    var = []
    for i in string:  # Get all character in string. Right order. (Could use set, but set return in some goofy way
        # order.)
        if i not in var:
            var.append(i)

    cosi = {}  # Empty dictionary for results.
    for i in var:  # Iterate in characters and count occurrences for each character.
        cosi[i] = string.count(i)
        if cosi[i] == 1:
            return i


# region Combine4
used_comm = []


class Node(object):
    """ Tree representation of math operators and operands. """

    def __init__(self, operator=None, operand=None, left=None, right=None):
        self.operator = operator
        self.operand = operand
        self.left = left
        self.right = right

    def __str__(self) -> str:
        return Node.build(self)[1:-1]

    @staticmethod
    def build_operator(node):
        """ Build operator into representable string. """
        return "({}{}{})".format(Node.build(node.left), node.operator, Node.build(node.right))

    @staticmethod
    def build(node):
        """ Build node into representable string. """
        return Node.build_operator(node) if node.operator else str(node.operand)


class Interpreter(object):
    """ Math interpreter for evaluation. """

    @staticmethod
    def evaluate_operator(node):
        """ Evaluate node operator and its operands """
        if node.operator == "+":
            return Interpreter.evaluate(node.left) + Interpreter.evaluate(node.right)
        elif node.operator == "-":
            return Interpreter.evaluate(node.left) - Interpreter.evaluate(node.right)
        elif node.operator == "*":
            return Interpreter.evaluate(node.left) * Interpreter.evaluate(node.right)
        elif node.operator == "/":
            right = Interpreter.evaluate(node.right)
            if right == 0:
                raise ZeroDivisionError
            return Interpreter.evaluate(node.left) / right

    @staticmethod
    def evaluate(node):
        """ Node evaluating. """
        return Interpreter.evaluate_operator(node) if node.operator else node.operand


def generate_nodes(operands, operators):
    """ Generate nodes from operands and operators """
    commutative_operators = ['+', '*']
    if operators[2] in commutative_operators and already_used(operands, operators):
        return

    node = Node(  # Left oriented tree.
            operator=operators[0],
            right=Node(operand=operands[0]),
            left=Node(
                    operator=operators[1],
                    right=Node(operand=operands[1]),
                    left=Node(
                            operator=operators[2],
                            right=Node(operand=operands[2]),
                            left=Node(operand=operands[3])
                    )
            )
    )
    yield node

    swap_sides(node.left)  # Half left oriented tree.
    if node.left.operator not in commutative_operators:
        yield node

    swap_sides(node)  # Right oriented tree.
    if node.left.operator not in commutative_operators:
        yield node

    swap_sides(node.right)  # Half right oriented tree.
    if node.left.operator not in commutative_operators:
        yield node

    node.left, node.right.left = node.right.left, node.left  # Half right and half left oriented.
    if node.operator not in commutative_operators or node.left.operator not in commutative_operators or \
                    node.right.operator in commutative_operators:
        yield node


def already_used(operands, operators):
    """ Check if given operands and operators have been already used. """
    commutative_part = ''.join(sorted(str(x) for x in list(operands[-2:]) + list(operators[-1:]))) + ''.join(
            str(x) for x in list(operands[:-2]) + list(operators[:-1]))
    if commutative_part not in used_comm:
        used_comm.append(commutative_part)
        return False

    return True


def swap_sides(node):
    """ Swap sides of node. """
    node.left, node.right = node.right, node.left


def combine4(args, expected):
    """
    Combine list of integers with selected math operators and brackets. 
    :param args: List of integers for combining.
    :param expected: Result of combination
    :return: List of all possible combinations.
    """
    for i in args:
        if not (isinstance(i, int) or isinstance(expected, int) or i >= 0 or expected >= 0):  # Validation.
            raise ValueError("Values must be positive integers.")

    results = []
    used_comm.clear()
    for operands_combination in itertools.permutations(args):  # Iterate in permutations of arguments.
        for operators_combination in itertools.product(["+", "-", "*", "/"], repeat=3):
            for node in generate_nodes(operands_combination, operators_combination):
                try:
                    if Interpreter.evaluate_operator(node) == expected:
                        results.append(str(node))
                except: pass

    return list(set(results))


# endregion

print(combine4([2, 5, 6, 6], 17))
