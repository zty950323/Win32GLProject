// Win32GLProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DDADrawLine.h"

#include <iostream>
#include "../packages/boost.1.66.0.0/lib/native/include/boost/lexical_cast.hpp"
#include "BoostThreadLearn.h"

void boostTest(void) 
{
	using boost::lexical_cast;
	int a = boost::lexical_cast<int>("123456");
	std::cout << a << std::endl;
	double b = boost::lexical_cast<double>("123.12");
	std::cout << b << std::endl;
	long double c = lexical_cast<long double>("123.11");
	std::cout << c << std::endl;
}

int main(int argc, char **argv)
{
	DDADrawLine::DDATest(argc, argv);
//	BoostThreadLearn::mainThreadTest();
//	BoostThreadLearn::mainThreadInterTest();
//	BoostThreadLearn::mainThread_synchronizationTest();
	system("pause");
    return 0;
}

