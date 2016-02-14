#pragma once

#include <Python.h>
#include <boost\python.hpp>
#include <boost\thread.hpp>

using namespace boost;

namespace rpl
{
	class Interpreter
	{
	private:

		static Interpreter* m_pInstance;

		bool m_initialized;

		python::object m_mainModule;
		python::object m_mainNamespace;

		thread m_executingThread;

		Interpreter();

		static int quitExec(void*);

	public:

		static Interpreter* get();

		bool initialize();
		void reset();

		bool isInitialized();

		std::string execute(std::string script, bool multithreaded);
		void terminate();

		bool registerClass(std::string name, python::object pythonClass);

		template <typename T>
		bool addObject(std::string name, T* pythonObject)
		{
			if (!m_initialized)
				return false;

			m_mainNamespace[name] = python::ptr(pythonObject);

			return true;
		}

	};
}