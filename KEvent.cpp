/*
 * KEvent.cpp
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */

#include "KEvent.h"

KEvent::KEvent(ivtNum i) {
	lock();
	if(IVTEntry::IVTTable[i] != 0){
	owner = (PCB*)Sistem::running;
	value = 0;
	ivtNo = i;
	IVTEntry::IVTTable[i]->event = this;
	}
	unlock();
}

KEvent::~KEvent() {
	lock();
	IVTEntry::IVTTable[this->ivtNo] = 0;
	unlock();
}

void KEvent::wait(){
	lock();
	if(Sistem::running != owner) {unlock(); return;}
	if(value) {
		--value;
		unlock();
	}
	else{
		Sistem::running->timeLeftBeforeBlocked = Sistem::cnt;
		Sistem::running->tip = PCB::BLOCKED;
		dispatch();
		unlock();
	}

}
void KEvent::signal(){
	lock();
	if(value){
		unlock();
	}
	else{
		owner->tip = PCB::READY;
		Scheduler::put(owner);
		++value;
		unlock();
	}
}

