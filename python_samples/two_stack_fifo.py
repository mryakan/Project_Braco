#!/usr/bin/python3

#============================================================================
# Name        : two_stack_fifo.py
# Author      : Medhat R. Yakan
# Version     : 1.0
#
# ****************************************************************************
# Copyright   : Copyright (c) 2016 "Medhat R. Yakan" - All Rights Reserved
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
# USE OR OTHER DEALINGS IN THE SOFTWARE.
# ****************************************************************************
#
# Description : See docstring
#
#============================================================================

"""
Using 2 stacks, implement a FIFO
This is a weird way to do it, but this is how the requirement for this coding challenge is framed
"""

import sys
from optparse import OptionParser
#from operator import xor

class MyStack(object):
    """
    basic Stack implementation to use in exercise
    """
    def __init__(self):
        """ Constructor """
        self.__list = []
    def get_size(self):
        """ Get number of elements on the stack """
        return len(self.__list)
    def push(self, element):
        """ Push onto the stack """
        self.__list.insert(0, element)
        return True
    def pop(self):
        """ Pop off the stack """
        if not self.get_size():
            return None
        return self.__list.pop(0)

class MyFifo(object):
    """
    Implementing a Fifo in Python is simple, so let's start with that then subclass the required implementation
    """
    def __init__(self):
        """ Constructor """
        self.__elems = [] # for simple implementation
    def add(self, element):
        """ Add an element """
        self.__elems.append(element)
        return True
    def remove(self):
        """ Remove element in FiFo order """
        if not self.__elems:
            return None
        return self.__elems.pop(0)
    def get_size(self):
        """ Retrieve Size of FIFO """
        return len(self.__elems)

class MyTwoStackFifo(MyFifo):
    """
    According to the requirement, we want to implementa FIFO using 2 stacks
    This subclass of MyFifo does that
    """
    def __init__(self):
        """ Constructor """
        MyFifo.__init__(self)
        self.__instack = MyStack()
        self.__outstack = MyStack()
    def add(self, element):
        """ Add an element """
        # If we still have things on the outstack we need to put back on the instack to maintain FiFO order
        while self.__outstack.get_size():
            self.__instack.push(self.__outstack.pop())
        # Now add to instack
        self.__instack.push(element)
        return True
    def remove(self):
        """ Remove element in FiFo order """
        # To get FiFo order, we need to pop one by one from a and push on outstack to reverse order
        if not self.get_size():
            return None
        while self.__instack.get_size():
            self.__outstack.push(self.__instack.pop())
        return self.__outstack.pop()
    def get_size(self):
        """ Retrieve Size of FIFO """
        return self.__instack.get_size()+self.__outstack.get_size()

def execute():
    """ Main execution function """
    parser = OptionParser(usage="Usage: %prog [options] [element]\n  e.g. %prog -a X -a Y -a Z -r 3")
    parser.add_option('-a', '--add', action='append', dest='add',
                      help='Add element to FIFO', default=[])
    parser.add_option('-r', '--remove', action='store', dest='rem',
                      help='Remove specified number of elements from FIFO', default=0)
    opts, args = parser.parse_args()
    # print(opts.add)
    # print(opts.rem)
    # print(args)
    if not isinstance(args, list):
        args = [args]
    if args:
        print("ERROR: Unexpected argument(s):")
        print(*args, sep=", ")
        parser.print_help()
        return False
    if not opts.add and not opts.rem:
        print("ERROR; Must specify at least one option.")
        parser.print_help()
        return False
    #myfifo = MyFifo()
    myfifo = MyTwoStackFifo()
    for item in opts.add:
        ok = myfifo.add(item)
        print("%s '%s'" % ('Successfully added' if ok else 'Failed to add', item))
    numelems = int(opts.rem)
    if numelems > myfifo.get_size():
        numelems = myfifo.get_size()
        print("ERROR: Not enough elements in fifo. Removing only %s elements." % numelems)
    for n in range(numelems):
        item = myfifo.remove()
        if item:
            print("Removed '%s'" % item)
        else:
            print('Failed to remove item number %s' % n)

    # if not xor(bool(opts.add), bool(opts.rem)):
    #     print("ERROR: Either add or remove must be used exclusively.")
    #     parser.print_help()
    return True

if __name__ == '__main__':
    ret = execute()
    sys.exit(1 if not ret else 0)
