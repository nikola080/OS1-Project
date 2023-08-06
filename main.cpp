/*
 * main.cpp
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */
#include<iostream.h>
#include "Sistem.h"
#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
int userMain(int argc, char** argv);

int main(int argc, char** argv){
	Sistem::start();
	int value = userMain(argc, argv);
	Sistem::end();
	return value;
}

/*int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
	lock();
	va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	unlock();
	return res;
}
class TestThread : public Thread
{
public:

	TestThread(int id): Thread(4096, 2), myID(id) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:
	int myID;
	void run();

};

class WaitThread: public Thread
{
public:
	WaitThread(TestThread *t1, TestThread *t2): Thread()
	{
		t1_ = t1;
		t2_ = t2;
	};

	~WaitThread()
		{
			waitToComplete();
		}

protected:
	void run()
	{
		syncPrintf("Starting tests...\n");
		t1_->waitToComplete();
		syncPrintf("Test 1 completed!\n");
		t2_->waitToComplete();
		syncPrintf("Test 2 completed!\n");
	}
private:
	TestThread *t1_,*t2_;
};

void TestThread::run()
{
	syncPrintf("Thread %d adresa:%p: loop1 starts\n", getId(), this);

	for(long i=0;i<8000;i++) {	for (long j = 0; j < 32000; j++);}
	//Thread::sleep(myID*20);

	syncPrintf("Thread %d: loop1 ends, dispatch\n",myID);

	dispatch();

	syncPrintf("Thread %d: loop2 starts\n", getId());

	for (int k = 0; k < 8000; k++) { for (long j = 0; j < 32000; j++); }
	//Thread::sleep(myID*20);

	syncPrintf("Thread %d: loop2 ends\n", getId());

}

int main(){
	Sistem::start();
	syncPrintf("User main starts\n");
		TestThread *t1 = new TestThread(1),
				*t2 = new TestThread(2),
				*t3 = new TestThread(3);

		WaitThread *w = new WaitThread(t1,t2);
		t1->start();
		t2->start();
		t3->start();
		w->start();
		for (long k=0; k<5; k++) {
			for(long i=0;i<8000;i++) { for (long j = 0; j < 32000; j++);}
			//Thread::sleep(10);

			syncPrintf("Usermain %d running!\n", Thread::getRunningId());
			Thread *t = Thread::getThreadById(0);
			syncPrintf("%p\n", t);
			dispatch();
		}
		delete t1;
		delete t2;
		delete t3;
		delete w;
		syncPrintf("User main ends\n");
	Sistem::end();
}*/


