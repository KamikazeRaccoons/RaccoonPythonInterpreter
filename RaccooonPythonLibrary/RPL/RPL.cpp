// RPL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "rplInterpreter.h"
#include <iostream>

// rplInterpreter

rplInterpreter* rplInterpreter::m_pInstance = 0;

rplInterpreter::rplInterpreter()
	: m_initialized(false)
{
}

rplInterpreter* rplInterpreter::getInstance()
{
	if (m_pInstance == 0)
		m_pInstance = new rplInterpreter();

	return m_pInstance;
}

bool rplInterpreter::initialize()
{
	if (m_initialized)
		return false;

	if (!Py_IsInitialized())
		Py_Initialize();

	m_mainModule = import("__main__");
	m_mainNamespace = m_mainModule.attr("__dict__");

	return m_initialized = Py_IsInitialized();
}

bool rplInterpreter::isInitialized()
{
	return m_initialized;
}

void rplInterpreter::execute(std::string script)
{
	exec(str(script), m_mainNamespace);
}

bool rplInterpreter::registerClass(std::string name, object pythonClass)
{
	if (!m_initialized)
		return false;

	m_mainNamespace[name] = pythonClass;
	
	return true;
}