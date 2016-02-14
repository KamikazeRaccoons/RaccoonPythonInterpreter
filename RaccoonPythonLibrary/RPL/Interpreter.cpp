#include "Interpreter.h"

#include <string>

namespace rpl
{
	Interpreter* Interpreter::m_pInstance = 0;

	Interpreter::Interpreter()
		: m_initialized(false)
	{
	}

	int Interpreter::quitExec(void*)
	{
		PyErr_SetString(PyExc_KeyboardInterrupt, "Process has been terminated.");
		return -1;
	}

	Interpreter* Interpreter::get()
	{
		if (m_pInstance == 0)
			m_pInstance = new Interpreter();

		return m_pInstance;
	}

	bool Interpreter::initialize()
	{
		if (m_initialized)
			return false;

		if (!Py_IsInitialized())
			Py_Initialize();

		m_mainModule = python::import("__main__");
		m_mainNamespace = m_mainModule.attr("__dict__");

		return m_initialized = Py_IsInitialized();
	}

	void Interpreter::reset()
	{
		m_mainNamespace = python::object();
		m_mainModule = python::object();

		m_initialized = false;
	}

	bool Interpreter::isInitialized()
	{
		return m_initialized;
	}

	std::string Interpreter::execute(std::string script, bool multithreaded)
	{
		std::string result;

		try
		{
			if (multithreaded)
				m_executingThread = thread(boost::bind(&Interpreter::execute, this, script, false));
			else
				python::exec(python::str(script), m_mainNamespace);

			result = "Execution successful.";
		}
		catch (python::error_already_set)
		{
			PyObject *pType, *pValue, *pTraceback;
			PyErr_Fetch(&pType, &pValue, &pTraceback);

			if (pType != NULL && pValue != NULL && pTraceback != NULL)
				result = std::string(python::extract<std::string>(pValue));
			else
				result = "An unexpected error has occurred (check syntax).\n";
		}

		return result;
	}

	void Interpreter::terminate()
	{
		Py_AddPendingCall(&Interpreter::quitExec, NULL);
		m_executingThread.join();
	}

	bool Interpreter::registerClass(std::string name, python::object pythonClass)
	{
		if (!m_initialized)
			return false;

		m_mainNamespace[name] = pythonClass;

		return true;
	}
}