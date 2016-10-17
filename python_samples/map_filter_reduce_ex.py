#!/usr/bin/python3


#============================================================================
# Name        : map_filter_reduce_ex.py
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
Examples of using map, filter, & reduce
"""
import sys
from functools import reduce

# Example using map
def upperCase(l):
    """ Return a list containing the upper case equivalent of strings passed in input list 'l'"""
    o = list(map(lambda s: s.upper(), l))
    return o

#Helper
def fibonacci(n):
    """Return list containing 1st N fibonacci #s"""
    o = [0, 1]
    for i in range(1, n-1):
        o.append(sum(o[i-1:i+1]))
    return o

# Example using filter
def oddFibonacci(n):
    """
    Return sorted list containing only the odd fibonacci numbers
    for fibonacci sequence up to 'n' without duplicates
    """
    odd = list(filter(lambda x: (x % 2 == 1), fibonacci(n)))
    return sorted(list(set(odd)))

# Example using reduce
def squareSum(l):
    """Return a list containing the sum of squares of integers in 'l'"""
    o = reduce(lambda x, y: x+y**2, l)
    return o


def test():
    """ Run tests for above functions"""
    print(*upperCase(['abc', 'Hello World', 'CaMelCaSe']), sep='\n')
    print(squareSum(range(10)))
    print(fibonacci(15))
    print(oddFibonacci(15))
    return True

if __name__ == '__main__':
    rc = test()
    sys.exit(0 if rc else 1)
