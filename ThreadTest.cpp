#if 0
#include "stdafx.h"
#include "ThreadTest.h"
#include <iostream>
#include <thread>
#include <Windows.h>
using namespace std;
static ThreadTest *p_threadT = NULL;
ThreadTest::ThreadTest()
{
	p_threadT = this;
}


ThreadTest::~ThreadTest()
{
}

void ThreadTest::mainThread01()
{
	thread task01(this->thread01);
	thread task02(this->thread02);
	task01.join();
	task02.join();

	for (int i = 0; i < 5; i++)
	{
		cout << "Main thread is working !" << endl;
		Sleep(200);
	}
	system("pause");
}

void* ThreadTest::thread01()
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Thread 01 is working!." << endl;
		Sleep(200);
	}
}

void* ThreadTest::thread02()
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Thread 02 is working!." << endl;
		Sleep(200);
	}
}
#endif