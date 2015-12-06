#pragma once

#include "stdafx.h"
#include "rplInterpreter.h"

#ifdef RPL_EXPORTS
#define RPL_OBJECT_API __declspec(dllexport)
#else
#define RPL_OBJECT_API __declspec(dllimport)
#endif

using namespace boost;

class rplObject
{
private:

	mutex* m_pMutex;

protected:

	class rplScopedLock
	{
	private:

		rplObject* m_pParent;

	protected:

		// Prevent dynamic allocation of an rplScopedLock.
		static void* operator new(std::size_t);
		static void* operator new[](std::size_t);

	public:

		RPL_OBJECT_API rplScopedLock(rplObject* parent);
		RPL_OBJECT_API ~rplScopedLock();

	};

	template<typename T>
	rplObject(std::string name, T* instance)
	{
		m_pMutex = new mutex();
		rplInterpreter::getInstance()->addObject(name, instance);
	}

	RPL_OBJECT_API ~rplObject();

public:

	void RPL_OBJECT_API lock();
	void RPL_OBJECT_API unlock();
	void RPL_OBJECT_API destroy() const;

};