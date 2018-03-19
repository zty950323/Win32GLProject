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
boost::lock_guard 在其内部构造和析构函数分别自动调用 lock() 和 unlock() 。 访问共享资源是需要同步的，因为它显示地被两个方法调用。
除了boost::mutex 和 boost::lock_guard 之外，Boost.Thread也提供其他的类支持各种同步。 
其中一个重要的就是 boost::unique_lock ，相比较 boost::lock_guard 而言，它提供许多有用的方法。
#endif
void thread_lock_grard(void)
{
	for (int i = 0; i < 5; i++)
	{
		BoostThreadLearn::wait(1);
		boost::lock_guard<boost::mutex> lock(mutex); // 保证了同类线程的运行次序。
		std::cout << "Thread_lock_grand id:" << boost::this_thread::get_id() << " : " << i << std::endl;
	}
}

void BoostThreadLearn::mainThread_lock_grandTest(void)
{
	boost::thread t1(thread_lock_grard);
	boost::thread t2(thread_lock_grard);
	t1.join();
	t2.join();

	std::cout << "主线程结束" << std::endl;
}


#if 0
这个例子就是为了演示 boost::unique_lock 提供的功能。当然了，这些功能的用法对给定的情景不一定适用。
boost::unique_lock 通过多个构造函数来提供不同的方式获得互斥体。 这个期望获得互斥体的函数简单地调用了 lock() 方法，一直等到获得这个互斥体。 所以它的行为跟 boost::lock_guard 的那个是一样的。
如果第二个参数传入一个 boost::try_to_lock 类型的值，对应的构造函数就会调用 try_lock() 方法。 
这个方法返回 bool 型的值：如果能够获得互斥体则返回true，否则返回 false 。
相比 lock() 函数，try_lock() 会立即返回，而且在获得互斥体之前不会被阻塞。
程序向 boost::unique_lock 的构造函数的第二个参数传入boost::try_to_lock。 
然后通过 owns_lock() 可以检查是否可获得互斥体。
如果不能， owns_lock() 返回 false。 
这也用到 boost::unique_lock 提供的另外一个函数： timed_lock() 等待一定的时间以获得互斥体。 
给定的程序等待长达1秒，应较足够的时间来获取更多的互斥。
其实这个例子显示了三个方法获取一个互斥体：lock() 会一直等待，直到获得一个互斥体。
try_lock() 则不会等待，但如果它只会在互斥体可用的时候才能获得，否则返回 false 。
最后，timed_lock() 试图获得在一定的时间内获取互斥体。 和 try_lock() 一样，返回bool 类型的值意味着成功是否。
虽然 boost::mutex 提供了 lock() 和 try_lock() 两个方法，但是 boost::timed_mutex 只支持 timed_lock() ，这就是上面示例那么使用的原因。
如果不用 timed_lock() 的话，也可以像以前的例子那样用 boost::mutex。
就像 boost::lock_guard 一样， boost::unique_lock 的析构函数也会相应地释放互斥量。
此外，可以手动地用 unlock() 释放互斥量。也可以像上面的例子那样，通过调用 release() 解除boost::unique_lock 和互斥量之间的关联。
然而在这种情况下，必须显式地调用 unlock() 方法来释放互斥量，因为 boost::unique_lock 的析构函数不再做这件事情。
boost::unique_lock 这个所谓的独占锁意味着一个互斥量同时只能被一个线程获取。
其他线程必须等待，直到互斥体再次被释放。 除了独占锁，还有非独占锁。
Boost.Thread里有个 boost::shared_lock 的类提供了非独占锁。
正如下面的例子，这个类必须和 boost::shared_mutex 型的互斥量一起使用。
#endif
boost::timed_mutex time_mutex;
void thread_unique_lock(void) 
{
	std::cout << "Thread_unique_lock id:" << boost::this_thread::get_id() << std::endl;
	for (int i = 0; i < 5; i++)
	{
		BoostThreadLearn::wait(1);
		boost::unique_lock<boost::timed_mutex> lock(time_mutex, boost::try_to_lock);
		if (!lock.owns_lock())
		{
			lock.timed_lock(boost::get_system_time() + boost::posix_time::seconds(1));
			std::cout << "Thread_unique_lock id:" << boost::this_thread::get_id() << ": " << i << std::endl;
			boost::timed_mutex *m = lock.release();
			m->unlock();
		}
	}
}

void BoostThreadLearn::mainThead_unique_lockTest(void)
{
	boost::thread t1(thread_unique_lock);
	boost::thread t2(thread_unique_lock);
	t1.join();
	t2.join();

	std::cout << "主线程结束" << std::endl;
}
#endif

