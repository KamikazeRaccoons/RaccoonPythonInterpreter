#include <Python.h>
#include <boost\python.hpp>
#include <boost\thread.hpp>
#include <rplInterpreter.h>

#include <iostream>

#include "TestClass.h"

using namespace boost;

int main()
{
	try
	{
		if (rplInterpreter::getInstance()->initialize())
		{
			std::cout << "Initialization success!\n";
		
			TestClass::registerClass();
		
			TestClass* testClass = new TestClass("testClass");
		
			rplInterpreter::getInstance()->execute("while True:\n\ttestClass.output()", true);

			while (true)
				testClass->increment();
		}
		else
		{
			std::cout << "Initialization failed.\n";
		}
	}
	catch (python::error_already_set) // must be single-threaded for debugging to work.
	{
		PyObject *pType, *pValue, *pTraceback;
		PyErr_Fetch(&pType, &pValue, &pTraceback);

		if (pValue != NULL && pTraceback != NULL && pValue != NULL)
			std::cout << std::string(python::extract<std::string>(pValue)) << std::endl;
		else
			std::cout << "An unexpected error has occurred (check syntax).\n";
	}

	std::cin.get(); // Pause after execution is complete.

	return 0;
}