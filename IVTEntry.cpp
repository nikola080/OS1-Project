/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"

IVTEntry *IVTEntry::IVTTable[256]= {0};
IVTEntry::IVTEntry(EventIndex i,intrRutine nova) {
	lock();
	event = 0;
#ifndef BCC_BLOCK_IGNORE
	oldRutine = getvect(i);
	setvect(i, nova);
	IVTEntry::IVTTable[i] = this;
#endif
	rb = i;
	unlock();
}

IVTEntry::~IVTEntry() {
	lock();
	oldRutine();
#ifndef BCC_BLOCK_IGNORE
	setvect(rb,oldRutine);
#endif
	unlock();
}

void IVTEntry::signal(){
	lock();
	if(event) event->signal();
	unlock();

}

void IVTEntry::callOldInterrupt(){
	oldRutine();
}

