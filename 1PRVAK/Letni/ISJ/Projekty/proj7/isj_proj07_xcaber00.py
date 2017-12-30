#!/usr/bin/env python3
import os

"""" Module for seventh project. """


class Log(object):
    """ Logger. """
    
    def __init__(self, file):
        """ Initialize logger and create file field with given {file}. """
        self.file = file
    
    def __enter__(self):
        """ Enter the runtime context related to this object. """
        # Open file stream
        self.fp = open(self.file, "a")
        # Start logging.
        self.logging("Begin")
        
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        """ Exit the runtime context related to this object. """
        # End logging.
        self.logging("End")
        # Close file stream.
        self.fp.close()
    
    def logging(self, text):
        """ Log given text into file. """
        self.fp.write(text + os.linesep)


class TooManyCallsError(Exception):
    """ Specific exception. """
    pass


def limit_calls(max_calls=2, error_message_tail='called too often'):
    """ Limit function call. """
    
    # Define counter (dictionary) for function calling.
    call_counter = dict()
    
    def decorate(func):
        """ Decorate function. """
        
        def wrapper(*args, **kwargs):
            """ Call function with given arguments or raise exception. """
            # Get function name and count calling. => Save to dictionary.
            call = "function \"{}\" - {}".format(func.__name__, error_message_tail)
            call_counter[call] = call_counter.get(call, 0) + 1
            if call_counter[call] > max_calls:
                raise TooManyCallsError(call)
            
            # Call function with its arguments.
            return func(*args, *kwargs)
        
        return wrapper
    
    return decorate


def ordered_merge(*args, **kwargs):
    """ Merge given iterable objects in given order. """
    cosi = list(map(iter, args))
    # Get selector argument or empty array => Iterate through it.
    for i in kwargs.get("selector", []):
        yield next(cosi[i])
