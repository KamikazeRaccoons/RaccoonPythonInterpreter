#pragma once

#include "stdafx.h"

#ifdef RPL_EXPORTS
#define RPL_INTERPRETER_API __declspec(dllexport)
#else
#define RPL_INTERPRETER_API __declspec(dllimport)
#endif

using namespace boost;

class rplInterpreter
{
private:

	static RPL_INTERPRETER_API rplInterpreter* m_pInstance;

	bool m_initialized;
	
	python::object m_mainModule;
	python::object m_mainNamespace;

	thread m_executingThread;

	RPL_INTERPRETER_API rplInterpreter();

	static int RPL_INTERPRETER_API quitExec(void*);

public:
	
	static RPL_INTERPRETER_API rplInterpreter* getInstance();

	bool RPL_INTERPRETER_API initialize();

	bool RPL_INTERPRETER_API isInitialized();

	void RPL_INTERPRETER_API execute(std::string script, bool multithreaded);

	void RPL_INTERPRETER_API terminate();

	bool RPL_INTERPRETER_API registerClass(std::string name, python::object pythonClass);

	template <typename T>
	bool addObject(std::string name, T* pythonObject)
	{
		if (!m_initialized)
			return false;

		m_mainNamespace[name] = python::ptr(pythonObject);

		return true;
	}

};