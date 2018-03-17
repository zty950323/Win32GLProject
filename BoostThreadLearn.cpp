#include "stdafx.h"
#include "BoostThreadLearn.h"


BoostThreadLearn::BoostThreadLearn()
{
}


BoostThreadLearn::~BoostThreadLearn()
{
}
#if 1
#if 0
下面的过程，是一个利用boost库进行相关的join类型线程的测试学习。
如果线程采用join方法加入主线程或者其他线程，那么就会产生一个等待的效果，必须等该线程先执行完，主线程或其他才可继续执行。
#endif
void BoostThreadLearn::wait(int seconds)
{
	boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

void thread(void)
{
	for (int i = 0; i < 5; i++)
	{
		BoostThreadLearn::wait(1);
		std::cout << "线程运行中" << i << std::endl;
	}
}

void BoostThreadLearn::mainThreadTest(void)
{
	boost::thread t(thread);
	t.join();

	for (int i = 0;i < 5; i++)
	{
		std::cout << "主线程运行中" << i << std::endl;
	}
}



#endif
#if 1
#if 0
在一个线程对象上调用 interrupt() 会中断相应的线程。 
在这方面，中断意味着一个类型为 boost::thread_interrupted 的异常，它会在这个线程中抛出。 
然后这只有在线程达到中断点时才会发生。
如果给定的线程不包含任何中断点，简单调用 interrupt() 就不会起作用。 
每当一个线程中断点，它就会检查 interrupt() 是否被调用过。
只有被调用过了， boost::thread_interrupted 异常才会相应地抛出。
#endif
void thread_inter(void)
{
	try
	{
		std::cout << "thread_inter id:" <<boost::this_thread::get_id() << std::endl; // 获取线程ID号
		std::cout << "thread_inter hardware_concurrency:" <<boost::thread::hardware_concurrency() << std::endl; \
			// 它能够返回基于CPU数目或者CPU内核数目的刻在同时在物理机器上运行的线程数
		for (int i = 0; i < 5; i++)
		{
			BoostThreadLearn::wait(1);
			std::cout << "线程运行中" << i << std::endl;
		}
	}
	catch (boost::thread_interrupted&)
	{
		std::cout << "线程thread_inter产生中断" << std::endl;
	}
}
void BoostThreadLearn::mainThreadInterTest(void)
{
	boost::thread t(thread_inter);
	wait(3);
	t.interrupt();
	t.join();

	for (int i = 0; i < 5; i++)
	{
		std::cout << "主线程运行中" << i << std::endl;
	}
}



#endif

#if 1
#if 0
下面的代码主要实现一个Boost.Thread的线程同步的学习。
多线程程序使用所谓的互斥对象来同步。
Boost.Thread提供多个的互斥类，boost::mutex是最简单的一个。 
互斥的基本原则是当一个特定的线程拥有资源的时候防止其他线程夺取其所有权。 
一旦释放，其他的线程可以取得所有权。 
这将导致线程等待至另一个线程完成处理一些操作，从而相应地释放互斥对象的所有权。
下面的示例使用一个类型为 boost::mutex 的 mutex 全局互斥对象。
thread() 函数获取此对象的所有权才在 for 循环内使用 lock() 方法写入到标准输出流的。 
一旦信息被写入，使用 unlock() 方法释放所有权。
下面的程序，主线程建立了两个子线程。其中利用 for 循环，每个线程数到5，用一个迭代器写一条消息到标准输出流。 
不幸的是，标准输出流是一个全局性的被所有线程共享的对象。 
该标准不提供任何保证 std::cout 可以安全地从多个线程访问。 
因此，访问标准输出流必须同步：在任何时候，只有一个线程可以访问 std::cout。
由于两个线程试图在写入标准输出流前获得互斥体，实际上只能保证一次只有一个线程访问 std::cout。
不管哪个线程成功调用 lock() 方法，其他所有线程必须等待，直到 unlock() 被调用。
#endif
// 定义一个mutex的共享资源锁
boost::mutex mutex;
void thread_synchronization(void) 
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << "thread_syncharonization id:" << boost::this_thread::get_id() << std::endl; // 获取线程ID号
		std::cout << "thread_syncharonization hardware_concurrency:" << boost::thread::hardware_concurrency() << std::endl;
		BoostThreadLearn::wait(1);
		mutex.lock();
		std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl;
		mutex.unlock();
	}
}
void BoostThreadLearn::mainThread_synchronizationTest(void)
{
	boost::thread t1(thread_synchronization);
	boost::thread t2(thread_synchronization);
	t1.join();
	t2.join();

	std::cout << "主线程结束" << std::endl;
}
#endif

#if 1
#if 0

#endif
#endif