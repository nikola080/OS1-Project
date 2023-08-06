/*
 * Queue.cpp
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */

#include "Queue.h"

Queue::Queue() {
	front = 0;
	rear = 0;
}

Queue::~Queue() {
	if(rear != 0){
		Elem * pok = rear;
		while(pok){
			Elem* pokk = pok;
			pok = pok->next;
			delete pokk;
		}
	}

}


void Queue::put(PCB* p){
	if(rear == 0){
		rear = new Elem();
		rear->data = p;
		rear->next = 0;
		front = rear;
	}
	else{
		front->next = new Elem();
		front = front->next;
		front->data = p;
		front->next = 0;
	}
}

PCB* Queue::get(){
	if(rear == 0) return 0;
	else{
		PCB * ret = rear->data;
		Elem* pokk = rear;
		rear = rear->next;
		delete pokk;
		if(!rear) { rear = 0;front = 0;}
		return ret;
	}
}


PCB* Queue::findPCB(int k){
	Queue::Elem *pok = Sistem::globalPCBQueue->rear;
	while(pok && pok->data->IDThread != k) pok = pok->next;
	if(!pok) return 0;
	return pok->data;
}

void Queue::deletePCB(int i){
	if(rear == 0) return;
	Elem * pok1 = rear;
	Elem * pok2 = 0;
	while(pok1 && pok1->data->IDThread != i) {
		pok1 = pok1->next;
		pok2 = pok1;
	}
	if(!pok1) return;
	if(pok1 == rear){
		rear = rear->next;
		delete pok1;
	}
	else{
		if(!pok1->next){
			pok2->next = 0;
			front = pok2;
			delete pok1;
		}
		else{
			pok2->next = pok1->next;
			delete pok1;
		}
	}
}

void Queue::decrTimeBlockedOnSem(){
	if(rear == 0) return;
	else{
		Elem* pok = rear;
		while(pok){
			if(pok->data->timeBlocked > 0){
				--pok->data->timeBlocked;
				if(pok->data->timeBlocked == 0) {
					pok->data->blockedTimeExpired = 1;
					pok->data->deleteMe = 1;
					pok->data->tip = PCB::READY;
					Scheduler::put(pok->data);
				}
			}
			pok = pok->next;
		}
	}
}
