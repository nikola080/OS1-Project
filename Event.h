/*
 * Event.h
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Sistem.h"

#define PREPAREENTRY(ivtno,old) \
void interrupt routine##ivtno(...); \
IVTEntry ent##ivtno(ivtno,routine##ivtno); \
void interrupt routine##ivtno(...) { \
	if (old) ent##ivtno.callOldInterrupt(); \
	ent##ivtno.signal(); \
	dispatch(); \
}

typedef unsigned char IVTNo;
class KEvent;

class Event {
public:
      Event (IVTNo ivtNo);
      ~Event ();
      void wait ();
protected:
      friend class KEvent;
      void signal(); // can call KernelEv
private:
      KEvent* myImpl;
};


#endif /* EVENT_H_ */
