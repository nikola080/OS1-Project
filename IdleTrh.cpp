/*
 * IdleTrh.cpp
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */

#include "IdleTrh.h"

IdleTrh::IdleTrh():Thread(defaultStackSize,1) {

}

IdleTrh::~IdleTrh() {
	lock();
	delete myPCB;
	unlock();
}

void IdleTrh::run(){
	while(1);//{printf("idle\n");}
}

