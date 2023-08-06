/*
 * IVTEntry.h
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "Sistem.h"
#include "KEvent.h"
typedef void interrupt (*intrRutine)(...);
typedef unsigned EventIndex;
class KEvent;
class IVTEntry {
public:
	int rb;
	static IVTEntry * IVTTable[256];
	intrRutine oldRutine;
	KEvent* event;
	void signal();
	void callOldInterrupt();
	IVTEntry(EventIndex, intrRutine);
	virtual ~IVTEntry();
};

#endif /* IVTENTRY_H_ */
