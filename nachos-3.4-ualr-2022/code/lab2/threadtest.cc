// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(_int code) // encryped code wwwxxxqqq 2024.10.31.19:48
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times priority %d\n", (int) code / 100, num, (int) code % 100);
        currentThread->Yield();
    }
    printf("*** thread %d finishing\n", (int) code / 100);
}

//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest()
{
    DEBUG('t', "Entering SimpleTest");

    Thread *t1 = new Thread("forked thread1", 1);
    Thread *t2 = new Thread("forked thread2", 2);
    Thread *t3 = new Thread("forked thread3", 3);

    t1->Fork(SimpleThread, 100 + t1->getPriority());
    t2->Fork(SimpleThread, 200 + t2->getPriority());
    t3->Fork(SimpleThread, 300 + t3->getPriority());
    SimpleThread(9);
}
