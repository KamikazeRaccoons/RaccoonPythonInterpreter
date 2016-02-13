#include "TestClass.h"
#include <iostream>

TestClass::TestClass(std::string name)
	: rpl::Object(name, this), m_counter(0)
{
}

void TestClass::registerClass()
{
	rpl::Interpreter::getInstance()->registerClass("TestClass",
		python::class_<TestClass>("TestClass", python::no_init)
		.def("output", &TestClass::output)
		.def("increment", &TestClass::increment));
}

void TestClass::output()
{
	ScopedLock lock(this);
	std::cout << m_counter << std::endl;
}

void TestClass::increment()
{
	ScopedLock lock(this);
	m_counter++;
}