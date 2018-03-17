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

#endif
#endif