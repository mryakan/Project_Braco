//============================================================================
// Name        : two_stack_fifo.cpp
// Author      : Medhat R. Yakan
// Version     : 1.0
//
// ****************************************************************************
// Copyright   : Copyright (c) 2016 "Medhat R. Yakan" - All Rights Reserved
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
// ****************************************************************************
//
// Description : A coding challenge to create a Fifo using 2 stacks
//
//============================================================================

#include <iostream>
#include <stdlib.h>
#include "cppunit/TestCase.h"
#include "cppunit/ui/text/TestRunner.h"

using namespace std;

// 1st let's create a template for List Elements
template <typename T>
class MyListElement {
public:
    MyListElement() : prev(NULL), next(NULL) {}
    MyListElement(T &initializer) : prev(NULL), next(NULL), element(initializer) {}
    MyListElement(T initializer) : prev(NULL), next(NULL), element(initializer) {}
    ~MyListElement() {}
    void setNext(MyListElement<T> *ptr) {this->next = ptr;}
    MyListElement<T> *getNext(void) {return this->next;}
    void setPrev(MyListElement<T> *ptr) {this->prev = ptr;}
    MyListElement<T> *getPrev(void) {return this->prev;}
    T *getElemPtr(void) {return &this->element;}
    size_t getElemSize(void) {return sizeof(this->element);}
private:
    MyListElement<T> *prev;
    MyListElement<T> *next;
    T element;
};

// We need a linked list class template
// Let's start with a simple doubly linked list implementation
template <typename TE>
class MyLinkedList {
public:
	MyLinkedList(MyListElement<TE> *elemPtr);
    MyLinkedList(void) : MyLinkedList(NULL) {}
    ~MyLinkedList() {/*TBD*/}
    unsigned long long len(void) {return this->numElems;}
    MyListElement<TE> *getHead(void) {return this->head;}
    MyListElement<TE> *getTail(void) {return this->tail;}
    MyListElement<TE> *addElemAtHead(void) {return this->numElems;}
    MyListElement<TE> *addElemAtTail(void) {return this->numElems;}
    //MyListElement<TE> *addElemAfterElem(MyListElement<TE> *e);
    //MyListElement<TE> *addElemBeforeElem(MyListElement<TE> *e);
    bool removeElem(MyListElement<TE> *e);
private:
    unsigned long long numElems;
    MyListElement<TE> *head, *tail;
};

// Let's start with a simple stack of characters
// Also for now let's limit the size to the initial size.
class MyStack {
public:
	MyStack(const unsigned int initial_size=0) : size(initial_size), head(NULL) {}
	bool push(char *element);
	char *pop(void);
	unsigned int get_size(void);
private:
	unsigned int size;
	void *head;
};


// #############
// MyLinkedList
// #############
template <typename TE>
MyLinkedList<TE>::MyLinkedList(MyListElement<TE> *elemPtr) {

    this->numElems = 0;
    this->head = elemPtr;
    if (elemPtr)
        elemPtr->setPrev(NULL); // Element has to be added to front of list
    MyListElement<TE> *ptr = this->head;
    // preserve next if already exist!
    while (ptr) {
        this->tail = ptr;
        ptr = ptr->getNext();
        this->numElems++;
    }
}


// ##################
// MyListElementTest
// ##################
class MyListElementTest : public CppUnit::TestCase {
public:
    MyListElementTest(string name) : CppUnit::TestCase(name) {}
    // Some basic unit testing
    void runTest() {

        MyListElement<int> e0;
        MyListElement<char [32]> e1;
        MyListElement<unsigned long long> e2;
        CPPUNIT_ASSERT_EQUAL(sizeof(int), e0.getElemSize());
        CPPUNIT_ASSERT_EQUAL(32*sizeof(char), e1.getElemSize());
        CPPUNIT_ASSERT_EQUAL(sizeof(unsigned long long), e2.getElemSize());
        int *x = e0.getElemPtr();
        *x = -1;
        CPPUNIT_ASSERT_EQUAL(-1, *(e0.getElemPtr()));
    }
};

// ###########
// MyListTest
// ###########
class MyListTest : public CppUnit::TestCase {
public:
    MyListTest(string name) : CppUnit::TestCase(name) {}
    // Some basic unit testing
    void runTest() {
        MyListElement<int> e0(-1);
        CPPUNIT_ASSERT_EQUAL(-1, *(e0.getElemPtr()));
        CPPUNIT_ASSERT_EQUAL((MyListElement<int> *)NULL, e0.getPrev());
        CPPUNIT_ASSERT_EQUAL((MyListElement<int> *)NULL, e0.getNext());

        MyLinkedList<int> list0(&e0);
        CPPUNIT_ASSERT_EQUAL((unsigned long long)1, list0.len());
        CPPUNIT_ASSERT_EQUAL(&e0, list0.getHead());
        CPPUNIT_ASSERT_EQUAL(&e0, list0.getTail());
        CPPUNIT_ASSERT_EQUAL(-1, *((list0.getHead())->getElemPtr()));
        CPPUNIT_ASSERT_EQUAL(-1, *((list0.getHead())->getElemPtr()));

        MyListElement<char> *e1 = new MyListElement<char>('a');
        MyListElement<char> e2('b');
        CPPUNIT_ASSERT_EQUAL('a', *(e1->getElemPtr()));
        CPPUNIT_ASSERT_EQUAL((MyListElement<char> *)NULL, e1->getPrev());
        CPPUNIT_ASSERT_EQUAL((MyListElement<char> *)NULL, e1->getNext());
        e1->setNext(&e2);

        MyLinkedList<char> list1(e1);
        CPPUNIT_ASSERT_EQUAL((unsigned long long)2, list1.len());
        MyListElement<char> *ptr = list1.getHead();
        CPPUNIT_ASSERT_EQUAL(e1, ptr);
        CPPUNIT_ASSERT_EQUAL('a', *(ptr->getElemPtr()));
        ptr = ptr->getNext();
        CPPUNIT_ASSERT_EQUAL(&e2, ptr);
        CPPUNIT_ASSERT_EQUAL('b', *(ptr->getElemPtr()));
        ptr = ptr->getNext();
        CPPUNIT_ASSERT_EQUAL((MyListElement<char> *)NULL, ptr);
    }
};

// ########
// MyStack
// ########
//unsigned int
//MyStack::get_size(void) {
//	return this->size;
//}

// ######
// Tests
// ######
bool test1(void) {
    cout << "Testing MyListElement..." << endl;
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(new MyListElementTest("MyListElementTest"));
    bool success = runner.run();
    return success;
}

bool test2(void) {
    cout << "Testing MyList..." << endl;
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(new MyListTest("MyListTest"));
    bool success = runner.run();
    return success;
}

// #####
// Main
// #####
int main(int argc, char *argv[]) {
    MyListElement<int> e0;
    MyListElement<char [32]> e1;
    MyListElement<unsigned long long> e2;
//    MyLinkedList list0, list1(10, 10);
//	cout << "List0 has " << list0.len() << " elements each of size " << list0.get_elem_size() << endl;
//    cout << "List0 has " << list1.len() << " elements each of size " << list1.get_elem_size() << endl;
    bool rc = test1();
    if (!rc) {
        exit(EXIT_FAILURE);
    }
    rc = test2();
    if (!rc) {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
