#pragma once

#include <Python.h>
#include <boost\python.hpp>

class TestClass
{
public:
	TestClass(std::string name);

	static void registerClass();

	void output();
};