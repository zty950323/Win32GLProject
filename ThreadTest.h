#if 0
#pragma once
class ThreadTest
{
public:
	ThreadTest();
	~ThreadTest();
	void mainThread01();
private:
	void* thread01();
	void* thread02();
};

#endif
