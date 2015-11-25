#pragma once

#include "stdafx.h"

#ifdef RPL_EXPORTS
#define RPL_INTERPRETER_API __declspec(dllexport)
#else
#define RPL_INTERPRETER_API __declspec(dllimport)
#endif

using namespace boost::python;

class rplInterpreter
{
private:

	static RPL_INTERPRETER_API rplInterpreter* m_pInstance;

	bool m_initialized;

	object m_mainModule;
	object m_mainNamespace;

	RPL_INTERPRETER_API rplInterpreter();

public:
	
	static RPL_INTERPRETER_API rplInterpreter* getInstance();

	bool RPL_INTERPRETER_API initialize();

	bool RPL_INTERPRETER_API isInitialized();

	void RPL_INTERPRETER_API execute(std::string script);

	bool RPL_INTERPRETER_API registerClass(std::string name, object pythonClass);

	template <typename T>
	bool addObject(std::string name, T* pythonObject)
	{
		if (!m_initialized)
			return false;

		m_mainNamespace[name] = ptr(pythonObject);

		return true;
	}

};