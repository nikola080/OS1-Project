/*
 * Queue.h
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "PCB.h"
#include "Sistem.h"
class Sistem;
class Queue {
public:
	friend class Sistem;
	friend class Thread;
	class Elem{
	public:
		PCB* data;
		Elem* next;
	};
	Elem* front, * rear;
	Queue();
	virtual ~Queue();
	void put(PCB * p);
	PCB* get();
	void deletePCB(int i);
	static PCB* findPCB(int k);
	void decrTimeBlockedOnSem();
};

#endif /* QUEUE_H_ */
