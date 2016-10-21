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
A collection of functions to solve some string related coding challenges
"""
import sys

def first_nonrepeating_char(somestring):
    """
    Find the 1st non-repeating char in a string (ignore case).
    e.g. for 'tomatoes' it is 'm'; 'potatoes' -> 'p'; 'pepper' -> 'r';
             'seemlessly' -> 'm'; 'tintin' -> None;
    :param somestring: A string
    :return: 1st non repeating chat if any, None otherwise
    """
    char_count = {}
    for character in somestring:
        try:
            char_count[character] += 1
        except KeyError:
            char_count[character] = 1
    for character in somestring:
        if char_count[character] == 1:
            return character
    return None

def reverseSentence(sentence):
    """Reverse a sentence and make sure only 1st letter in sentence is capitalized and it ends with a dot"""
    if not sentence:
        return sentence
    words = list(sentence.lower().strip('.').split(' '))
    words.reverse()
    words[0] = words[0].capitalize()
    return ' '.join(words)+'.'


def test():
    """Some tests for above fns"""
    test_strings = ['tomatoes', 'potatoes', 'pepper', 'seemlessly', 'tintin']
    for astring in test_strings:
        print("First non-repeating char in '%s' is '%s'" %
              (astring, first_nonrepeating_char(astring)))
    print(reverseSentence("We live in interesting times."))
    return True

if __name__ == '__main__':
    rc = test()
    sys.exit(0 if rc else 1)
