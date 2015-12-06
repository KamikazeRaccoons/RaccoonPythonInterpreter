#include <Python.h>
#include <boost\python.hpp>
#include <boost\thread.hpp>
#include <rplInterpreter.h>

#include <iostream>

#include "TestClass.h"

using namespace boost;

int main()
{
	if (rplInterpreter::getInstance()->initialize())
	{
		std::cout << "Initialization success!\n";
		
		TestClass::registerClass();
		
		TestClass* testClass = new TestClass("testClass");

		rplInterpreter::getInstance()->execute("while True:\n\ttestClass.output()", true);

		for (int i = 0; i < 500000; i++)
			testClass->increment();

		rplInterpreter::getInstance()->terminate();

		delete testClass;
	}
	else
	{
		std::cout << "Initialization failed.\n";
	}

	std::system("PAUSE"); // Pause after execution is complete.

	return 0;
}