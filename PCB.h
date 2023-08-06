/*
 * PCB.h
 *
 *  Created on: Sep 3, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "Sistem.h"
#include "Thread.h"
#include "Queue.h"
class Queue;
class Thread;
class Sistem;
class PCB {
public:
	static int ID;
	int IDThread;
	volatile int sp;
	volatile int ss;
	volatile int bp;
	unsigned * stack;
	volatile unsigned stackSize;
	Queue* blockedOnThis;
	enum Type {NEW = 0, BLOCKED, READY, FINISHED} ;
	volatile int tip;
	Thread * pcbThread;
	unsigned timeSlice;
	// za semafor
	volatile unsigned timeBlocked;
	volatile int blockedTimeExpired;
	volatile int deleteMe;
	volatile unsigned timeLeftBeforeBlocked;
	// za semafor
	PCB(Thread* t, unsigned tS, unsigned sS);
	void createStack();
	void pokreniNit();
	void flushBlocked();
	~PCB();
};

#endif /* PCB_H_ */
