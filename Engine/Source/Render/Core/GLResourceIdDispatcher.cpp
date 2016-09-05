#include "GLResourceIdDispatcher.h"

DEFINE_LOG_SENDER(GLResourceIdDispatcher);

using namespace ve;

GLResourceId GLResourceIdDispatcher::acquireId()
{
	if(m_availableIds.empty())
	{
		m_isIdDispatched.push_back(true);

		return m_isIdDispatched.size() - 1;
	}
	else
	{
		const GLResourceId id = m_availableIds.back();
		m_availableIds.pop_back();
		m_isIdDispatched[id] = true;

		return id;
	}
}

void GLResourceIdDispatcher::returnId(const GLResourceId id)
{
	if(m_isIdDispatched[id])
	{
		m_isIdDispatched[id] = false;
		m_availableIds.push_back(id);
	}
	else
	{
		ENGINE_LOG(GLResourceIdDispatcher, LogLevel::NOTE_WARNING, "returned ID <" + std::to_string(id) + "> is invalid");
	}
}