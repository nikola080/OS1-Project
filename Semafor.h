/*
 * Semafor.h
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#ifndef SEMAFOR_H_
#define SEMAFOR_H_
#include "Sistem.h"
#include "KSem.h"
typedef unsigned int Time;

class KSem;
class Semafor {
public:
    Semafor(int init=1);
    virtual ~Semafor ();
    virtual int wait (Time maxTimeToWait);
    virtual int signal(int n=0);
    int val () const; // Returns the current value of the semaphore
private:
    KSem* myImpl;
};

#endif /* SEMAFOR_H_ */
