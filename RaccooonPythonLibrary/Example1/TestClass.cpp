#include "TestClass.h"
#include <iostream>
#include <rplInterpreter.h>

TestClass::TestClass(std::string name)
	: m_counter(0)
{
	m_mutex = new mutex();
	rplInterpreter::getInstance()->addObject(name, this);
}

TestClass::~TestClass()
{
	delete m_mutex;
}

void TestClass::registerClass()
{
	rplInterpreter::getInstance()->registerClass("TestClass", python::class_<TestClass>("TestClass", python::no_init)
		.def("output", &TestClass::output)
		.def("increment", &TestClass::increment));
}

void TestClass::output()
{
	m_mutex->lock();
	std::cout << m_counter << std::endl;
	m_mutex->unlock();
}

void TestClass::increment()
{
	m_mutex->lock();
	m_counter++;
	m_mutex->unlock();
}