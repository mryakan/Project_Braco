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
#include <stdio.h>
#include <string.h>
#include "cppunit/TestCase.h"
#include "cppunit/ui/text/TestRunner.h"

using namespace std;

// 1st let's create a template for List Elements
template <typename T>
class MyElement {
public:
    MyElement() : prev(NULL), next(NULL) {}
    MyElement(T &initializer) : prev(NULL), next(NULL), element(initializer) {}
    MyElement(T initializer) : prev(NULL), next(NULL), element(initializer) {}
    ~MyElement() {}
    void setNext(MyElement<T> *ptr) {this->next = ptr;}
    MyElement<T> *getNext(void) {return this->next;}
    void setPrev(MyElement<T> *ptr) {this->prev = ptr;}
    MyElement<T> *getPrev(void) {return this->prev;}
    T *getElemPtr(void) {return &this->element;}
    size_t getElemSize(void) {return sizeof(this->element);}
private:
    MyElement<T> *prev;
    MyElement<T> *next;
    T element;
};

// We need a linked list class template
// Let's start with a simple doubly linked list implementation
template <typename TE>
class MyLinkedList {
public:
	MyLinkedList(MyElement<TE> *elemPtr);
    MyLinkedList(void) : MyLinkedList(NULL) {}
    ~MyLinkedList() {}
    unsigned long long len(void) {return this->numElems;}
    MyElement<TE> *getHead(void) {return this->head;}
    MyElement<TE> *getTail(void) {return this->tail;}
    MyElement<TE> *addElemAtHead(MyElement<TE> *e);
//    MyElement<TE> *addElemAtTail(MyElement<TE> *e);
    //MyElement<TE> *addElemAfterElem(MyElement<TE> *e);
    //MyElement<TE> *addElemBeforeElem(MyElement<TE> *e);
    MyElement<TE> *removeElem(MyElement<TE> *e);
private:
    unsigned long long numElems;
    MyElement<TE> *head, *tail;
};

// Let's start with a simple stack implementation using the list
template <typename SE>
class MyStack {
public:
	MyStack() {this->list = new MyLinkedList<SE>;}
	~MyStack() {delete(this->list);}
	bool push(MyElement<SE> *e) {return (this->list->addElemAtHead(e) == e);}
	MyElement<SE> *pop(void) {return this->list->removeElem(this->list->getHead());}
	unsigned long long getSize(void) {return this->list->len();}
private:
	MyLinkedList<SE> *list;
};

// Fifo using a Two stack implementation (yes very retarted)
template <typename E>
class MyTwoStackFifo {
public:
    MyTwoStackFifo() {this->inStack = new MyStack<E>; this->outStack = new MyStack<E>;}
    ~MyTwoStackFifo() {delete(this->inStack);delete(this->outStack);}
    bool add(MyElement<E> *e);
    MyElement<E> *remove(void);
    unsigned long long getSize(void) {return this->inStack->getSize()+this->outStack->getSize();}
private:
    MyStack<E> *inStack, *outStack;
};


// #############
// MyLinkedList
// #############
template <typename TE>
MyLinkedList<TE>::MyLinkedList(MyElement<TE> *elemPtr) : numElems(0), head(NULL), tail(NULL) {
    this->addElemAtHead(elemPtr);
}

template <typename TE>
MyElement<TE> *
MyLinkedList<TE>::addElemAtHead(MyElement<TE> *e) {
    if (e == NULL) {
        return NULL;
    }
    e->setPrev(NULL);
    MyElement<TE> *ptr = e, *last=NULL;
    // preserve chain if already exist!
    while (ptr) {
        last = ptr;
        ptr = ptr->getNext();
        this->numElems++;
    }
    // prepend new list to old and update tail if necessary
    if (this->head) {
        this->head->setPrev(last);
    }
    last->setNext(this->head);
    this->head = e;
    if (this->tail == NULL) {
        this->tail = last;
    }
    return e;
}

//template <typename TE>
//MyElement<TE> *
//addElemAtTail(MyElement<TE> *e) {
//
//}

template <typename TE>
MyElement<TE> *
MyLinkedList<TE>::removeElem(MyElement<TE> *e) {
    if (e == NULL) {
        return NULL;
    }
    MyElement<TE> *prev = e->getPrev(), *next = e->getNext();
    if (this->head == e) {
        this->head = next;
    }
    if (this->tail == e) {
        this->tail = prev;
    }
    if (prev) {
        prev->setNext(next);
    }
    if (next) {
        next->setPrev(prev);
    }
    e->setPrev(NULL);
    e->setNext(NULL);
    this->numElems--;
    return e;
}

// ###############
// MyTwoStackFifo
// ###############
template <typename E>
bool
MyTwoStackFifo<E>::add(MyElement<E> *e) {
    while (this->outStack->getSize()) {
        this->inStack->push(this->outStack->pop());
    }
    this->inStack->push(e);
    return true;
}

template <typename E>
MyElement<E> *
MyTwoStackFifo<E>::remove(void) {
    if (this->getSize() == 0) {
        return NULL;
    }
    while (this->inStack->getSize()) {
        this->outStack->push(this->inStack->pop());
    }
    return this->outStack->pop();
}



// ##############
// Test Helpers
// ##############
bool  printTestHeader(const string testname){
    cout << endl;
    cout << string(80, '+') << endl;
    cout << "Testing " <<  testname << "..." << endl;
    cout << endl;
    return true;
}

bool  printTestTrailer(const string testname){
    cout << endl;
    cout << "Test End." << endl;
    cout << string(80, '+') << endl;
    return true;
}

// ##################
// MyElementTest
// ##################
class MyElementTest : public CppUnit::TestCase {
public:
    MyElementTest(string name) : CppUnit::TestCase(name) {}
    // Some basic unit testing
    void setUp() {
        printTestHeader(this->getName());
    }
    void runTest() {
        MyElement<int> e0;
        MyElement<char [32]> e1;
        MyElement<unsigned long long> e2;
        CPPUNIT_ASSERT_EQUAL(sizeof(int), e0.getElemSize());
        CPPUNIT_ASSERT_EQUAL(32*sizeof(char), e1.getElemSize());
        CPPUNIT_ASSERT_EQUAL(sizeof(unsigned long long), e2.getElemSize());
        int *x = e0.getElemPtr();
        *x = -1;
        CPPUNIT_ASSERT_EQUAL(-1, *(e0.getElemPtr()));

        char cArray[32] = {'a', 'b', 'c'};
        MyElement<char [32]> e3;
        strncpy((char *)(e3.getElemPtr()), cArray, sizeof(cArray));
        CPPUNIT_ASSERT(strncmp(cArray, *(e3.getElemPtr()), e3.getElemSize()) == 0);
        MyElement<string> e4("Hello World");
        CPPUNIT_ASSERT(e4.getElemPtr()->compare("Hello World") == 0);
    }
    void tearDown() {
        printTestTrailer(this->getName());
    }
};

// ###########
// MyListTest
// ###########
class MyListTest : public CppUnit::TestCase {
public:
    MyListTest(string name) : CppUnit::TestCase(name) {}
    // Some basic unit testing, not comprehensive, only some boundary conditions tested
    void setUp() {
        printTestHeader(this->getName());
    }
    void runTest() {
        MyElement<int> e0(-1);
        CPPUNIT_ASSERT_EQUAL(-1, *(e0.getElemPtr()));
        CPPUNIT_ASSERT_EQUAL((MyElement<int> *)NULL, e0.getPrev());
        CPPUNIT_ASSERT_EQUAL((MyElement<int> *)NULL, e0.getNext());

        MyLinkedList<int> list0(&e0);
        CPPUNIT_ASSERT_EQUAL((unsigned long long)1, list0.len());
        CPPUNIT_ASSERT_EQUAL(&e0, list0.getHead());
        CPPUNIT_ASSERT_EQUAL(&e0, list0.getTail());
        CPPUNIT_ASSERT_EQUAL(-1, *((list0.getHead())->getElemPtr()));
        CPPUNIT_ASSERT_EQUAL(-1, *((list0.getHead())->getElemPtr()));

        MyElement<char> *e1 = new MyElement<char>('a');
        MyElement<char> e2('b');
        CPPUNIT_ASSERT_EQUAL('a', *(e1->getElemPtr()));
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, e1->getPrev());
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, e1->getNext());
        e1->setNext(&e2);
        e2.setPrev(e1);

        // create lits with [e1, e2] and check
        MyLinkedList<char> list1(e1);
        CPPUNIT_ASSERT_EQUAL((unsigned long long)2, list1.len());
        CPPUNIT_ASSERT_EQUAL(e1, list1.getHead());
        CPPUNIT_ASSERT_EQUAL(&e2, list1.getTail());
        MyElement<char> *ptr = list1.getHead();
        CPPUNIT_ASSERT_EQUAL(e1, ptr);
        CPPUNIT_ASSERT_EQUAL('a', *(ptr->getElemPtr()));
        ptr = ptr->getNext();
        CPPUNIT_ASSERT_EQUAL(&e2, ptr);
        CPPUNIT_ASSERT_EQUAL('b', *(ptr->getElemPtr()));
        ptr = ptr->getNext();
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, ptr);
        // Remove current tail and check
        list1.removeElem(&e2);
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, e2.getNext());
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, e2.getPrev());
        CPPUNIT_ASSERT_EQUAL(e1, list1.getHead());
        CPPUNIT_ASSERT_EQUAL(e1, list1.getTail());
        // remove only element & check
        list1.removeElem(e1);
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, e1->getNext());
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, e1->getPrev());
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, list1.getHead());
        CPPUNIT_ASSERT_EQUAL((MyElement<char> *)NULL, list1.getTail());

        delete(e1);
    }
    void tearDown() {
        printTestTrailer(this->getName());
    }
};

// ############
// MyStackTest
// ############
class MyStackTest : public CppUnit::TestCase {
public:
    MyStackTest(string name) : CppUnit::TestCase(name) {}
    // Some basic unit testing
    void setUp() {
        printTestHeader(this->getName());
    }
    void runTest() {
        MyElement<int> int0(-1), int1(0), int2(1);

        MyStack<int> s1;
        unsigned long long numPushed=0;
        cout << "Pushing " << *(int0.getElemPtr()) << "(size = " << int0.getElemSize() << ")" << " onto stack." << endl;
        s1.push(&int0); numPushed++;
        CPPUNIT_ASSERT_EQUAL(numPushed, s1.getSize());
        cout << "Pushing " << *(int1.getElemPtr()) << "(size = " << int1.getElemSize() << ")" << " onto stack." << endl;
        s1.push(&int1); numPushed++;
        CPPUNIT_ASSERT_EQUAL(numPushed, s1.getSize());
        cout << "Pushing " << *(int2.getElemPtr()) << "(size = " << int2.getElemSize() << ")" << " onto stack." << endl;
        s1.push(&int2); numPushed++;
        CPPUNIT_ASSERT_EQUAL(numPushed, s1.getSize());

        MyElement<int> *e;
        e = s1.pop(); numPushed--;
        cout << "Popped " << *(e->getElemPtr()) << "(size = " << e->getElemSize() << ")" << " off the stack." << endl;
        CPPUNIT_ASSERT_EQUAL(&int2, e);
        CPPUNIT_ASSERT_EQUAL(numPushed, s1.getSize());
        e = s1.pop(); numPushed--;
        cout << "Popped " << *(e->getElemPtr()) << "(size = " << e->getElemSize() << ")" << " off the stack." << endl;
        CPPUNIT_ASSERT_EQUAL(&int1, e);
        CPPUNIT_ASSERT_EQUAL(numPushed, s1.getSize());
        e =s1.pop(); numPushed--;
        cout << "Popped " << *(e->getElemPtr()) << "(size = " << e->getElemSize() << ")" << " off the stack." << endl;
        CPPUNIT_ASSERT_EQUAL(&int0, e);
        CPPUNIT_ASSERT_EQUAL(numPushed, s1.getSize());
    }
    void tearDown() {
        printTestTrailer(this->getName());
    }
};

// ###################
// MyTwoStackFifoTest
// ###################
class MyTwoStackFifoTest : public CppUnit::TestCase {
public:
    MyTwoStackFifoTest(string name) : CppUnit::TestCase(name) {}
    // Some basic unit testing
    void setUp() {
        printTestHeader(this->getName());
    }
    void runTest() {
        MyElement<char> c1('a');
        MyElement<char> c2('b');
        MyElement<char> c3('c');
        MyTwoStackFifo<char> f1;
        unsigned long long numAdded=0;
        cout << "Adding " << *(c1.getElemPtr()) << "(size = " << c1.getElemSize() << ")" << " to Fifo." << endl;
        f1.add(&c1); numAdded++;
        CPPUNIT_ASSERT_EQUAL(numAdded, f1.getSize());
        cout << "Adding " << *(c2.getElemPtr()) << "(size = " << c2.getElemSize() << ")" << " to Fifo." << endl;
        CPPUNIT_ASSERT_EQUAL(numAdded, f1.getSize());
        f1.add(&c2); numAdded++;
        cout << "Adding " << *(c3.getElemPtr()) << "(size = " << c3.getElemSize() << ")" << " to Fifo." << endl;
        f1.add(&c3); numAdded++;
        CPPUNIT_ASSERT_EQUAL(numAdded, f1.getSize());

        MyElement<char> *e;
        e = f1.remove(); numAdded--;
        cout << "Removed " << *(e->getElemPtr()) << "(size = " << e->getElemSize() << ")" << " from Fifo." << endl;
        CPPUNIT_ASSERT_EQUAL(&c1, e);
        CPPUNIT_ASSERT_EQUAL(numAdded, f1.getSize());
        e = f1.remove(); numAdded--;
        cout << "Removed " << *(e->getElemPtr()) << "(size = " << e->getElemSize() << ")" << " from Fifo." << endl;
        CPPUNIT_ASSERT_EQUAL(&c2, e);
        CPPUNIT_ASSERT_EQUAL(numAdded, f1.getSize());
        e = f1.remove(); numAdded--;
        cout << "Removed " << *(e->getElemPtr()) << "(size = " << e->getElemSize() << ")" << " from Fifo." << endl;
        CPPUNIT_ASSERT_EQUAL(&c3, e);
        CPPUNIT_ASSERT_EQUAL(numAdded, f1.getSize());
    }
    void tearDown() {
        printTestTrailer(this->getName());
    }
};

// ##################
// Test Suite Runner
// ##################
bool runUnitTests(void) {
    CppUnit::TestSuite *suite = new CppUnit::TestSuite();
    suite->addTest(new MyElementTest("MyElementTest"));
    suite->addTest(new MyListTest("MyListTest"));
    suite->addTest(new MyStackTest("MyStackTest"));
    suite->addTest(new MyTwoStackFifoTest("MyTwoStackFifoTest"));

    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);
    bool success = runner.run();
    return success;
}

// #####
// Main
// #####
int main(int argc, char *argv[]) {
    bool rc = runUnitTests();
       if (!rc) {
           exit(EXIT_FAILURE);
       }
    exit(EXIT_SUCCESS);
}
