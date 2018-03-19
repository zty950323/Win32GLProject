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
����Ĺ��̣���һ������boost�������ص�join�����̵߳Ĳ���ѧϰ��
����̲߳���join�����������̻߳��������̣߳���ô�ͻ����һ���ȴ���Ч��������ȸ��߳���ִ���꣬���̻߳������ſɼ���ִ�С�
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
		std::cout << "�߳�������" << i << std::endl;
	}
}

void BoostThreadLearn::mainThreadTest(void)
{
	boost::thread t(thread);
	t.join();

	for (int i = 0;i < 5; i++)
	{
		std::cout << "���߳�������" << i << std::endl;
	}
}



#endif
#if 1
#if 0
��һ���̶߳����ϵ��� interrupt() ���ж���Ӧ���̡߳� 
���ⷽ�棬�ж���ζ��һ������Ϊ boost::thread_interrupted ���쳣������������߳����׳��� 
Ȼ����ֻ�����̴߳ﵽ�жϵ�ʱ�Żᷢ����
����������̲߳������κ��жϵ㣬�򵥵��� interrupt() �Ͳ��������á� 
ÿ��һ���߳��жϵ㣬���ͻ��� interrupt() �Ƿ񱻵��ù���
ֻ�б����ù��ˣ� boost::thread_interrupted �쳣�Ż���Ӧ���׳���
#endif
void thread_inter(void)
{
	try
	{
		std::cout << "thread_inter id:" <<boost::this_thread::get_id() << std::endl; // ��ȡ�߳�ID��
		std::cout << "thread_inter hardware_concurrency:" <<boost::thread::hardware_concurrency() << std::endl; \
			// ���ܹ����ػ���CPU��Ŀ����CPU�ں���Ŀ�Ŀ���ͬʱ��������������е��߳���
		for (int i = 0; i < 5; i++)
		{
			BoostThreadLearn::wait(1);
			std::cout << "�߳�������" << i << std::endl;
		}
	}
	catch (boost::thread_interrupted&)
	{
		std::cout << "�߳�thread_inter�����ж�" << std::endl;
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
		std::cout << "���߳�������" << i << std::endl;
	}
}



#endif

#if 1
#if 0
����Ĵ�����Ҫʵ��һ��Boost.Thread���߳�ͬ����ѧϰ��
���̳߳���ʹ����ν�Ļ��������ͬ����
Boost.Thread�ṩ����Ļ����࣬boost::mutex����򵥵�һ���� 
����Ļ���ԭ���ǵ�һ���ض����߳�ӵ����Դ��ʱ���ֹ�����̶߳�ȡ������Ȩ�� 
һ���ͷţ��������߳̿���ȡ������Ȩ�� 
�⽫�����̵߳ȴ�����һ���߳���ɴ���һЩ�������Ӷ���Ӧ���ͷŻ�����������Ȩ��
�����ʾ��ʹ��һ������Ϊ boost::mutex �� mutex ȫ�ֻ������
thread() ������ȡ�˶��������Ȩ���� for ѭ����ʹ�� lock() ����д�뵽��׼������ġ� 
һ����Ϣ��д�룬ʹ�� unlock() �����ͷ�����Ȩ��
����ĳ������߳̽������������̡߳��������� for ѭ����ÿ���߳�����5����һ��������дһ����Ϣ����׼������� 
���ҵ��ǣ���׼�������һ��ȫ���Եı������̹߳���Ķ��� 
�ñ�׼���ṩ�κα�֤ std::cout ���԰�ȫ�شӶ���̷߳��ʡ� 
��ˣ����ʱ�׼���������ͬ�������κ�ʱ��ֻ��һ���߳̿��Է��� std::cout��
���������߳���ͼ��д���׼�����ǰ��û����壬ʵ����ֻ�ܱ�֤һ��ֻ��һ���̷߳��� std::cout��
�����ĸ��̳߳ɹ����� lock() ���������������̱߳���ȴ���ֱ�� unlock() �����á�
#endif
// ����һ��mutex�Ĺ�����Դ��
boost::mutex mutex;
void thread_synchronization(void) 
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << "thread_syncharonization id:" << boost::this_thread::get_id() << std::endl; // ��ȡ�߳�ID��
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

	std::cout << "���߳̽���" << std::endl;
}



#endif

#if 1
#if 0
boost::lock_guard �����ڲ���������������ֱ��Զ����� lock() �� unlock() �� ���ʹ�����Դ����Ҫͬ���ģ���Ϊ����ʾ�ر������������á�
����boost::mutex �� boost::lock_guard ֮�⣬Boost.ThreadҲ�ṩ��������֧�ָ���ͬ���� 
����һ����Ҫ�ľ��� boost::unique_lock ����Ƚ� boost::lock_guard ���ԣ����ṩ������õķ�����
#endif
void thread_lock_grard(void)
{
	for (int i = 0; i < 5; i++)
	{
		BoostThreadLearn::wait(1);
		boost::lock_guard<boost::mutex> lock(mutex); // ��֤��ͬ���̵߳����д���
		std::cout << "Thread_lock_grand id:" << boost::this_thread::get_id() << " : " << i << std::endl;
	}
}

void BoostThreadLearn::mainThread_lock_grandTest(void)
{
	boost::thread t1(thread_lock_grard);
	boost::thread t2(thread_lock_grard);
	t1.join();
	t2.join();

	std::cout << "���߳̽���" << std::endl;
}


#if 0
������Ӿ���Ϊ����ʾ boost::unique_lock �ṩ�Ĺ��ܡ���Ȼ�ˣ���Щ���ܵ��÷��Ը������龰��һ�����á�
boost::unique_lock ͨ��������캯�����ṩ��ͬ�ķ�ʽ��û����塣 ���������û�����ĺ����򵥵ص����� lock() ������һֱ�ȵ������������塣 ����������Ϊ�� boost::lock_guard ���Ǹ���һ���ġ�
����ڶ�����������һ�� boost::try_to_lock ���͵�ֵ����Ӧ�Ĺ��캯���ͻ���� try_lock() ������ 
����������� bool �͵�ֵ������ܹ���û������򷵻�true�����򷵻� false ��
��� lock() ������try_lock() ���������أ������ڻ�û�����֮ǰ���ᱻ������
������ boost::unique_lock �Ĺ��캯���ĵڶ�����������boost::try_to_lock�� 
Ȼ��ͨ�� owns_lock() ���Լ���Ƿ�ɻ�û����塣
������ܣ� owns_lock() ���� false�� 
��Ҳ�õ� boost::unique_lock �ṩ������һ�������� timed_lock() �ȴ�һ����ʱ���Ի�û����塣 
�����ĳ���ȴ�����1�룬Ӧ���㹻��ʱ������ȡ����Ļ��⡣
��ʵ���������ʾ������������ȡһ�������壺lock() ��һֱ�ȴ���ֱ�����һ�������塣
try_lock() �򲻻�ȴ����������ֻ���ڻ�������õ�ʱ����ܻ�ã����򷵻� false ��
���timed_lock() ��ͼ�����һ����ʱ���ڻ�ȡ�����塣 �� try_lock() һ��������bool ���͵�ֵ��ζ�ųɹ��Ƿ�
��Ȼ boost::mutex �ṩ�� lock() �� try_lock() �������������� boost::timed_mutex ֻ֧�� timed_lock() �����������ʾ����ôʹ�õ�ԭ��
������� timed_lock() �Ļ���Ҳ��������ǰ������������ boost::mutex��
���� boost::lock_guard һ���� boost::unique_lock ����������Ҳ����Ӧ���ͷŻ�������
���⣬�����ֶ����� unlock() �ͷŻ�������Ҳ���������������������ͨ������ release() ���boost::unique_lock �ͻ�����֮��Ĺ�����
Ȼ������������£�������ʽ�ص��� unlock() �������ͷŻ���������Ϊ boost::unique_lock ����������������������顣
boost::unique_lock �����ν�Ķ�ռ����ζ��һ��������ͬʱֻ�ܱ�һ���̻߳�ȡ��
�����̱߳���ȴ���ֱ���������ٴα��ͷš� ���˶�ռ�������зǶ�ռ����
Boost.Thread���и� boost::shared_lock �����ṩ�˷Ƕ�ռ����
������������ӣ���������� boost::shared_mutex �͵Ļ�����һ��ʹ�á�
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

	std::cout << "���߳̽���" << std::endl;
}
#endif

