/*
 * PCB.cpp
 *
 *  Created on: Sep 3, 2020
 *      Author: OS1
 */

#include "PCB.h"
class Sistem;
int PCB::ID = 0;

PCB::PCB(Thread * t,unsigned sS, unsigned tS){
	IDThread = ID++;
	pcbThread  = t;
	timeSlice = tS;
	stackSize = sS;
	ss = 0;
	sp = 0;
	bp = 0;
	stack = 0;
	tip = NEW;
	timeLeftBeforeBlocked = 0;
	timeBlocked = 0;      // vreme kojim je blokirana nit na semaforu ako se zvao wait(value > 0)
	blockedTimeExpired = 0;    // u slucaju da signal izbacuje nit iz lsite blokiranih ako nema niti koje su blokirane na neodredjeno vreme / vracanje na nulu posle vracanja u waitu
	deleteMe = 0; // brisanje u signalu
	blockedOnThis = new Queue();
}

void PCB::createStack(){
	lock();
	if(stackSize > 65535) stackSize = 65535;
	stackSize /= sizeof(unsigned);
	stack = new unsigned[stackSize];
	blockedOnThis = new Queue();
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-1] = 0x200;
	stack[stackSize-2] = FP_SEG(&(Sistem::wrapper));
	stack[stackSize-3] = FP_OFF(&(Sistem::wrapper));
	sp = FP_OFF(stack + stackSize - 12);
	ss = FP_SEG(stack + stackSize - 12);
	bp = FP_OFF(stack + stackSize - 12);
#endif
	unlock();
}

void PCB::pokreniNit(){
	pcbThread->run();
}

void PCB::~PCB(){
	delete stack;
	delete blockedOnThis;
}

void PCB::flushBlocked(){
	PCB* pok = blockedOnThis->get();
	while(pok){
		if(pok->tip != FINISHED){ // za slucaj ako se nit koja je obrisana blokirala na nekoj drugoj niti koja se brise trenutno!
		   pok->tip = READY;
		   Scheduler::put(pok);
		   pok = blockedOnThis->get();
		}
	}
}
