/*
 * Event.cpp
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */

#include "Event.h"

Event::Event(IVTNo ivtNo) {
	lock();
	myImpl = new KEvent(ivtNo);
	unlock();

}

Event::~Event() {
	lock();
	delete myImpl;
	unlock();
}

void Event::signal(){
	lock();
	myImpl->signal();
	unlock();
}

void Event::wait(){
	lock();
	myImpl->wait();
	unlock();
}

