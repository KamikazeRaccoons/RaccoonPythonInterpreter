#include "Object.h"

namespace rpl
{
	Object::~Object()
	{
		delete m_pMutex;
	}

	void Object::lock()
	{
		m_pMutex->lock();
	}

	void Object::unlock()
	{
		m_pMutex->unlock();
	}

	void Object::destroy() const
	{
		delete this;
	}

	Object::ScopedLock::ScopedLock(Object* parent)
	{
		m_pParent = parent;
		m_pParent->lock();
	}

	Object::ScopedLock::~ScopedLock()
	{
		m_pParent->unlock();
	}
}