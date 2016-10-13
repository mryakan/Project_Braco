#!/usr/bin/python3

"""
Using 2 stakcs, implement a FIFO
"""

import sys
from optparse import OptionParser
#from operator import xor

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
        self.__size = 0
    def add(self, element):
        """ Add an element """
        return True
    def remove(self):
        """ Remove element in FiFo order """
        return None
    def get_size(self):
        """ Retrieve Size of FIFO """
        return self.__size

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
