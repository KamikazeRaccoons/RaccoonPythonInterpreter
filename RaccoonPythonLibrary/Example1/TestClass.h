#pragma once

#include <RPL.h>

class TestClass : rpl::Object
{
private:

	int m_counter;

public:

	TestClass(std::string name);

	static void registerClass();

	void output();
	void increment();
};