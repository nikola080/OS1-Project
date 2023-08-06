/*
 * KEvent.h
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */

#ifndef KEVENT_H_
#define KEVENT_H_

#include "IVTEntry.h"
typedef unsigned char ivtNum;
class KEvent {
public:
	ivtNum ivtNo;
	PCB* owner;
	volatile int value;
	void wait();
	void signal();
	KEvent(ivtNum);
	virtual ~KEvent();
};

#endif /* KEVENT_H_ */
