/*
 * Sistem.h
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */
#ifndef SISTEM_H_
#define SISTEM_H_
#include <stdio.h>
#include<dos.h>
#include "Scheduler.h";
#include "Thread.h"
#include "Queue.h"
#include "PCB.h"
#include "IdleTrh.h"
#include "Glavna.h"
#include "KSem.h"
#include "Semafor.h"
#include "Event.h"
#include "IVTEntry.h"
#define lock() {asm{pushf; cli;}}
#define unlock() {asm{popf};}

class Sistem {
public:
	friend class Thread;
	friend class PCB;
	friend class Queue;
	friend class IdleTrh;
	friend class Glavna;
	static volatile PCB* running;
	static volatile Queue* globalPCBQueue;
	static volatile Thread* idleThread;
	static volatile Thread * mainThread;
	static volatile int change_on_demand;
	static volatile int cnt;
	static void interrupt (*oldRutine)(...);
	static void interrupt timer(...);
	static void start();
	static void end();
	static void wrapper();
	Sistem();
	~Sistem();
};

#endif /* SISTEM_H_ */
