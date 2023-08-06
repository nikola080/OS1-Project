/*
 * Glavna.cpp
 *
 *  Created on: Sep 8, 2020
 *      Author: OS1
 */

#include "Glavna.h"

Glavna::Glavna() :Thread(defaultStackSize, 1){

}

Glavna::~Glavna() {
	lock();
	waitToComplete();
	delete myPCB;
	unlock();
}

void Glavna::run(){}

