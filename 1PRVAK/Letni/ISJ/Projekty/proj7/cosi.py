#!/usr/bin/env python3


class TooManyCallsError(Exception):
    pass

calls = dict()


def limit_calls(max_calls=2, error_message_tail='called too often'):
    def decorate(func):
        def wrapper(*args, **kwargs):
            calls[func.__name__] = calls.get(func.__name__, 0) + 1
            if calls[func.__name__] > max_calls:
                raise TooManyCallsError(error_message_tail)

            return func(*args, *kwargs)
        return wrapper
    return decorate


def ordered_merge(*args, **kwargs):
    indexes = dict()
    for list_index in kwargs.get("selector", []):
        indexes[list_index] = indexes.get(list_index, -1) + 1
        yield args[list_index][indexes[list_index]]


class Log(object):
    def __init__(self, file):
        self.file = file

    def __enter__(self):
        self.fp = open(self.file, "a")
        self.logging("Begin")

        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.logging("End")
        self.fp.close()

    def logging(self, text):
        self.fp.write(text + "\n")
