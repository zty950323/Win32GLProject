#pragma once
#include "../packages/boost.1.66.0.0/lib/native/include/boost/thread.hpp"
#include <iostream>
namespace Learn 
{
	class BoostThreadLearn;
}
class BoostThreadLearn
{
public:
	BoostThreadLearn();
	~BoostThreadLearn();
	//************************************
	// Method:    wait 设置线程等待时间
	// FullName:  BoostThreadLearn::wait
	// Access:    public static 
	// Returns:   void
	// Qualifier:
	// Parameter: int seconds
	//************************************
	static void wait(int seconds);
	static void mainThreadTest(void);
	static void mainThreadInterTest(void);
	static void mainThread_synchronizationTest(void);
};

