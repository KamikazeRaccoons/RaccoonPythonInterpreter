#include "TestClass.h"
#include <iostream>
#include <rplInterpreter.h>

TestClass::TestClass(std::string name)
{
	rplInterpreter::getInstance()->addObject(name, this);
}

void TestClass::registerClass()
{
	rplInterpreter::getInstance()->registerClass("TestClass", class_<TestClass>("TestClass", no_init).def("output", &TestClass::output));
}

void TestClass::output()
{
	std::cout << "Hello, World!\n";
}