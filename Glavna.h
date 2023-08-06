/*
 * Glavna.h
 *
 *  Created on: Sep 8, 2020
 *      Author: OS1
 */

#ifndef GLAVNA_H_
#define GLAVNA_H_
#include "Sistem.h";
#include "Thread.h"
class Thread;
class Glavna: public Thread {
public:
	Glavna();
	virtual void run();
	virtual ~Glavna();
};

#endif /* GLAVNA_H_ */
