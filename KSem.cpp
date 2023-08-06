/*
 * KSem.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#include "KSem.h"
KSem::KSem(int v){
	head = 0;
	tail = 0;
	value = v;
}
KSem::KSem() {
	KSem(0);
}

KSem::~KSem() {
	lock();
	if(head){
		Elem* pok1 = head;
		Elem* pok2;
		while(pok1){
			pok2 = pok1;
			pok1 = pok1->next;
			delete pok2;
		}
	}
	unlock();
}

void KSem::insertIntoBlocked(PCB* p){
	if(!head){
		head = new Elem();
		head->data = p;
		head->next = 0;
		head->prev = 0;
		tail = head;
	}
	else{
		tail->next = new Elem();
		tail->next->prev = tail;
		tail = tail->next;
		tail->data = p;
		tail->next = 0;
	}
}

void KSem::removeFromBlocked(Elem * pok){

	if(!pok) return;
	if((head == tail) && head && tail){
		head = 0;
		tail = 0;
		delete pok;
		return;
	}

	if(pok == head){
		head = head->next;
		head->prev = 0;
		delete pok;
		return;
	}

	if(pok == tail){
		tail = tail->prev;
		tail->next = 0;
		delete pok;
		return;
	}

	pok->prev->next = pok->next;
	pok->next->prev = pok->prev;
	delete pok;
}

int KSem::_wait(int k){
	int ret = 1;
	if(k < 0) {return ret;}
	if(--value < 0){
		Sistem::running->tip = PCB::BLOCKED;
		Sistem::running->timeLeftBeforeBlocked = Sistem::cnt;
		insertIntoBlocked((PCB*)Sistem::running);
		Sistem::running->timeBlocked = k;
		dispatch();
		if(Sistem::running->blockedTimeExpired) {
			ret = 0;
			if(Sistem::running->deleteMe == 1){
				Elem* pok = head;
				while(pok->data != Sistem::running) pok = pok->next;
				pok->data->deleteMe = 0;
				removeFromBlocked(pok);
			}
		}
		Sistem::running->blockedTimeExpired = 0;
	}
	return ret;
}

int KSem::_signal(int k){
	int ret = 0;
	if(k < 0) return ret;
	if(value >= 0) {if(!k) value+=1; else value+= k; return ret;}
	if(value < 0) {
		if(!k) k = 1;
		value += k;
		Elem* pok1 = head;
		Elem* pom = 0;
		volatile int n = 0;
		while((n < k) && (pok1 != 0)){
			if(pok1->data->timeBlocked == 0){
				if(pok1->data->deleteMe == 1){
				pom = pok1;
				pok1->data->deleteMe = 0;
				pok1 = pok1->next;
				removeFromBlocked(pom);
				continue;
				}
				Scheduler::put(pok1->data);
				pok1->data->tip = PCB::READY;
				pom = pok1;
				pok1 = pok1->next;
				removeFromBlocked(pom);
				++n;
			}
			else pok1 = pok1->next;
		}
		if(n < k){
			Elem* pok2 = head;
			while((pok2 != 0)){
				if(pok2->data->timeBlocked > 0){
					pok2->data->blockedTimeExpired = 1;
					Scheduler::put(pok2->data);
					pok2->data->tip = PCB::READY;
					pom = pok2;
					pok2 = pok2->next;
					++n;
					removeFromBlocked(pom);
				}
				else pok2 = pok2->next;
			}
		}
		ret = n;
	}
	return ret;
}

int KSem::_val() const {  return value; }

