#pragma once

#include "Interpreter.h"

#include <Python.h>
#include <boost\python.hpp>
#include <boost\thread.hpp>

using namespace boost;

namespace rpl
{
	class Object
	{
	private:

		mutex* m_pMutex;

	protected:

		class ScopedLock
		{
		private:

			Object* m_pParent;

		protected:

			// Prevent dynamic allocation of an rplScopedLock.
			static void* operator new(std::size_t) { }
			static void* operator new[](std::size_t) { }

		public:

			ScopedLock(Object* parent);
			~ScopedLock();

		};

		template<typename T>
		Object(std::string name, T* instance)
		{
			m_pMutex = new mutex();
			Interpreter::get()->addObject(name, instance);
		}

		~Object();

	public:

		void lock();
		void unlock();
		void destroy() const;

	};
}
