#pragma once

#include <Python.h>
#include <boost\python.hpp>
#include <boost\thread.hpp>
#include <rplObject.h>

class TestClass : rplObject
{
private:

	int m_counter;

public:

	TestClass(std::string name);

	static void registerClass();

	void output();
	void increment();
};