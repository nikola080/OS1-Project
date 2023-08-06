/*
 * System.cpp
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */

#include "Sistem.h"
#include "Thread.h"
class Thread;
class Glavna;
void interrupt (*Sistem::oldRutine)(...) = 0;

volatile int Sistem::change_on_demand = 0;
volatile PCB* Sistem::running = 0;
volatile Thread*  Sistem::idleThread = 0;
volatile Thread* Sistem::mainThread = 0;
volatile Queue* Sistem::globalPCBQueue = 0;
volatile int Sistem::cnt = 0;
void tick();

void interrupt Sistem::timer(...){
	globalPCBQueue->decrTimeBlockedOnSem();
	if(!change_on_demand && running->timeSlice) --cnt;
	if(!change_on_demand) asm int 0x45;
	if(change_on_demand || (!cnt && running->timeSlice)){
		running->sp = _SP;
		running->ss = _SS;
		if(running->tip == PCB::READY && running->pcbThread != Sistem::idleThread) {running->timeLeftBeforeBlocked = 0;Scheduler::put((PCB*)running);}
		running = Scheduler::get();
		if(!running) running = Sistem::idleThread->myPCB;
		_SS = running->ss;
		_SP = running->sp;
		if(!running->timeSlice) cnt = 0;
		else{
			if(running->timeLeftBeforeBlocked > 0) cnt = running->timeLeftBeforeBlocked;
			else cnt = running->timeSlice;
		}
	}
	change_on_demand = 0;
}

void Sistem::start(){
	lock();
	Sistem::globalPCBQueue = new Queue();
	mainThread = new Glavna();
	idleThread = new IdleTrh();
	mainThread->myPCB->createStack();
	mainThread->myPCB->tip = PCB::READY;
	running = mainThread->myPCB;
	idleThread->start();
	Sistem::cnt = 1;
	change_on_demand = 0;
#ifndef BCC_BLOCK_IGNORE
	oldRutine = getvect(0x8);
	setvect(0x8,timer);
	setvect(0x45,oldRutine);
#endif
	unlock();
}

void Sistem::end(){
	lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8,oldRutine);
#endif
	delete Sistem::globalPCBQueue;
	delete idleThread;
	delete mainThread;
	unlock();
}

void Sistem::wrapper(){
	running->pokreniNit();
	lock();
	running->tip = PCB::FINISHED;
	running->flushBlocked();
	dispatch();
}
