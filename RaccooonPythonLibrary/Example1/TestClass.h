#pragma once

#include <Python.h>
#include <boost\python.hpp>
#include <boost\thread.hpp>

class TestClass
{
private:

	boost::mutex* m_mutex;

	int m_counter;

public:

	TestClass(std::string name);
	~TestClass();

	static void registerClass();

	void output();
	void increment();
};