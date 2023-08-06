/*
 * Thread.cpp
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "Sistem.h"

Thread::Thread(StackSize stackSize , Time timeSlice ){
	lock();
	myPCB = new PCB(this,stackSize, timeSlice);
	Sistem::globalPCBQueue->put(myPCB);
	unlock();
}

void Thread::waitToComplete(){
	lock();
	if(myPCB->tip == PCB::NEW || myPCB->tip == PCB::FINISHED) {unlock(); return;}
	if(this->myPCB == Sistem::running){ unlock(); return;}
	if(Sistem::idleThread->myPCB == this->myPCB) {unlock(); return;}
	if(this->myPCB == Sistem::mainThread->myPCB){ unlock(); return;}
	Sistem::running->tip = PCB::BLOCKED;
	Sistem::running->timeLeftBeforeBlocked = Sistem::cnt;
	this->myPCB->blockedOnThis->put((PCB*)Sistem::running);
	dispatch();
	unlock();
}

void Thread::start(){
	lock();
	if(myPCB->tip == PCB::NEW){
		myPCB->createStack();
		myPCB->tip = PCB::READY;
		Scheduler::put(myPCB);
	}
	unlock();
}
Thread::~Thread() {
	lock();
	waitToComplete();
	if(this != Sistem::mainThread->myPCB) delete myPCB;
	unlock();
}

void dispatch(){
	lock();
	Sistem::change_on_demand  = 1;
	Sistem::timer();
	Sistem::change_on_demand = 0;
	unlock();
}

ID Thread::getRunningId(){
	lock();
	int id = Sistem::running->IDThread;
	unlock();
	return id;
}

ID Thread::getId(){
	lock();
	int id = myPCB->IDThread;
	unlock();
	return id;

}

Thread * Thread::getThreadById(ID id){
	lock();
	Queue::Elem *pok = Sistem::globalPCBQueue->rear;
	while(pok){
		if(pok->data->IDThread == id) {unlock();return pok->data->pcbThread;}
		pok = pok->next;
	}
	unlock();
	return 0;
}
