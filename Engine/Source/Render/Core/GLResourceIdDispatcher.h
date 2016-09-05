#pragma once

#include "Common/type.h"
#include "Common/logging.h"
#include "GLResourceId.h"

#include <vector>

DECLARE_LOG_SENDER_EXTERN(GLResourceIdDispatcher);

namespace ve
{

class GLResourceIdDispatcher
{
public:
	GLResourceIdDispatcher() = default;

	GLResourceId acquireId();
	void returnId(const GLResourceId id);

	// forbid copying
	GLResourceIdDispatcher(const GLResourceIdDispatcher& other) = delete;
	GLResourceIdDispatcher& operator = (const GLResourceIdDispatcher& rhs) = delete;

private:
	std::vector<GLResourceId> m_availableIds;
	std::vector<bool> m_isIdDispatched;
};

}