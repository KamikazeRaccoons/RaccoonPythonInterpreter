#include <Python.h>
#include <boost\python.hpp>
#include <rplInterpreter.h>

#include <iostream>

#include "TestClass.h"

int main()
{
	if (rplInterpreter::getInstance()->initialize())
	{
		std::cout << "Initialization success!\n";

		TestClass::registerClass();

		TestClass testClass = TestClass("testClass");

		rplInterpreter::getInstance()->execute("testClass.output()");
	}
	else
	{
		std::cout << "Initialization failed.\n";
	}

	std::cin.get();

	return 0;
}