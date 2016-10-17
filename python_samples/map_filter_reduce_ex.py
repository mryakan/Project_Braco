#!/usr/bin/python3

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
    """Return only the odd fibonacci numbers for fibonacci sequence up to 'n' without duplicates"""
    odd = list(filter(lambda x: (x % 2 == 1), fibonacci(n)))
    return list(set(odd))

# Example using reduce
def squareSum(l):
    """Return a list containing the sum of squares of integers in 'l'"""
    o = reduce(lambda x, y: x+y**2, l)
    return o


def test():
    print(*upperCase(['abc', 'Hello World', 'CaMelCaSe']), sep='\n')
    print(squareSum(range(10)))
    print(oddFibonacci(10))

if __name__ == '__main__':
    rc = test()
    sys.exit(0 if rc else 1)