// RPL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "rplInterpreter.h"
#include "rplObject.h"
#include <iostream>

// rplInterpreter

rplInterpreter* rplInterpreter::m_pInstance = 0;

rplInterpreter::rplInterpreter()
	: m_initialized(false)
{
}

int rplInterpreter::quitExec(void*)
{
	PyErr_SetString(PyExc_KeyboardInterrupt, "Process has been terminated.");
	return -1;
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

	m_mainModule = python::import("__main__");
	m_mainNamespace = m_mainModule.attr("__dict__");
	
	return m_initialized = Py_IsInitialized();
}

bool rplInterpreter::isInitialized()
{
	return m_initialized;
}

void rplInterpreter::execute(std::string script, bool multithreaded)
{
	try
	{
		if (multithreaded)
			m_executingThread = thread(boost::bind(&rplInterpreter::execute, this, script, false));
		else
			python::exec(python::str(script), m_mainNamespace);
	}
	catch (python::error_already_set)
	{
		PyObject *pType, *pValue, *pTraceback;
		PyErr_Fetch(&pType, &pValue, &pTraceback);

		if (pType != NULL && pValue != NULL && pTraceback != NULL)
			std::cout << std::string(python::extract<std::string>(pValue)) << std::endl;
		else
			std::cout << "An unexpected error has occurred (check syntax).\n";
	}
}

void rplInterpreter::terminate()
{
	Py_AddPendingCall(&rplInterpreter::quitExec, NULL);
	m_executingThread.join();
}

bool rplInterpreter::registerClass(std::string name, python::object pythonClass)
{
	if (!m_initialized)
		return false;

	m_mainNamespace[name] = pythonClass;
	
	return true;
}

// rplObject

rplObject::~rplObject()
{
	delete m_pMutex;
}

void rplObject::lock()
{
	m_pMutex->lock();
}

void rplObject::unlock()
{
	m_pMutex->unlock();
}

void rplObject::destroy() const
{
	delete this;
}

rplObject::rplScopedLock::rplScopedLock(rplObject* parent)
{
	m_pParent = parent;
	m_pParent->lock();
}

rplObject::rplScopedLock::~rplScopedLock()
{
	m_pParent->unlock();
}