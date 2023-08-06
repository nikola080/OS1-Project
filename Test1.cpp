#include "Thread.h"
#include "Sistem.h"
#include "Semafor.h"
#include <iostream.h>
#include <stdio.h>

/*extern int syncPrintf (const char* format, ... );
Semafor *spavanje =0;
void tick() {}

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
	spavanje->wait(10);
	for(int i = 0; i < 320; i++){dispatch(); for(int j = 0; j < 10000; j++) { for(int k = 0; k < 20; k++);}}
	//spavanje->signal();
}
int userMain(int argc, char** argv)
{
	spavanje = new Semafor(0);
	syncPrintf("User main starts\n");
	TestThread ** t = new TestThread*[50];
	for(int i = 0; i < 50; i++){
		t[i] = new TestThread(i);
		t[i]->start();
	}
	WaitThread** w = new WaitThread*[20];
	for(int j = 0 ; j < 20; ++j){
		w[j] = new WaitThread(t[j],t[(j + 29)]);
		w[j]->start();
	}

	for(int k = 0; k < 50; ++k) {delete t[k];}
	//for(int u = 0; u < 20; ++u) delete w[u];
	syncPrintf("User main ends\n");
	return 0;
}*/

