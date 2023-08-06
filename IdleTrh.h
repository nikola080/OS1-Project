/*
 * IdleTrh.h
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */

#ifndef IDLETRH_H_
#define IDLETRH_H_
#include"Thread.h"
#include "Sistem.h"
#include "PCB.h"
class PCB;
class Thread;
class Sistem;
class IdleTrh: public Thread{
public:
	IdleTrh();
	virtual ~IdleTrh();
	void run();
};

#endif /* IDLETRH_H_ */
