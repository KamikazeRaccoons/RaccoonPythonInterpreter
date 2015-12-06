#include "TestClass.h"
#include <iostream>
#include <rplInterpreter.h>

TestClass::TestClass(std::string name)
	: rplObject(name, this), m_counter(0)
{
}

void TestClass::registerClass()
{
	rplInterpreter::getInstance()->registerClass("TestClass",
		python::class_<TestClass>("TestClass", python::no_init)
		.def("output", &TestClass::output)
		.def("increment", &TestClass::increment));
}

void TestClass::output()
{
	rplScopedLock lock(this);
	std::cout << m_counter << std::endl;
}

void TestClass::increment()
{
	rplScopedLock lock(this);
	m_counter++;
}