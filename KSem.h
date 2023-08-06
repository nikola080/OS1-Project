/*
 * KSem.h
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#ifndef KSEM_H_
#define KSEM_H_
#include "Sistem.h"
class KSem {
public:
	class Elem{
	public:
		PCB	* data;
		Elem* next;
		Elem* prev;
	};

	Elem* head;
	Elem* tail;
	void insertIntoBlocked(PCB*);
	void removeFromBlocked(Elem *);
	int value;
	int _val() const;
	int _wait(int = 0);
	int _signal(int = 0);
	KSem();
	KSem(int);
	virtual ~KSem();
};

#endif /* KSEM_H_ */
