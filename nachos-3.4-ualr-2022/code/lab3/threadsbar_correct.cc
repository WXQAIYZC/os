#include <iostream>
#include <vector>
#include <climits>
#include "copyright.h"
#include "system.h"
#include "synch.h"
#include "thread.h"

using namespace std;


const int n = 10;
vector<Thread*> threads;
int count = 0;
Lock* mutex;
Semaphore* barrier;

void MakeTicks(int ticks) {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    for(int i = 0; i < ticks; ++i) {
    	interrupt->SetLevel(IntOff);
	    interrupt->SetLevel(IntOn);
    }
    interrupt->SetLevel(oldLevel);
}

void BarThread(_int which) {
    MakeTicks(1000);
    cout << "Thread " << (int)which << " rendezvous" << endl;
    
    mutex->Acquire();
    count++;
    
    MakeTicks(10);
    if(count == n) {
        cout << "Thread " << which << " is the last" << endl;
        barrier->V();
    }
    mutex->Release();

    barrier->P();
    barrier->V();

    cout << "Thread " << (int)which << " critical point" << endl;
}

void ThreadsBarrier() {
    mutex = new Lock("mutex");
    barrier = new Semaphore("barrier", 0);
    threads.resize(n);

    for(int i = 0; i < n; ++i) {
        threads[i] = new Thread("i");
        threads[i]->Fork(BarThread, i);
    }
}
