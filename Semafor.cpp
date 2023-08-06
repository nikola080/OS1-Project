/*
 * Semafor.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#include "Semafor.h"

Semafor::Semafor(int k) {
	myImpl = new KSem(k);
}

Semafor::~Semafor() {
	lock();
	delete myImpl;
	unlock();
}

int Semafor::wait(Time t){
	lock();
	myImpl->_wait(t);
	unlock();
}

int Semafor::signal(int k){
	lock();
	myImpl->_signal(k);
	unlock();
}

int Semafor::val() const { lock(); this->myImpl->_val(); unlock();}
