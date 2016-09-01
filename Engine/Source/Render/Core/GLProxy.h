#pragma once

#include "Common/Logger.h"


DECLARE_LOG_SENDER_EXTERN(GLProxy);

namespace ve
{

class GLStateCache;
class ShaderProgram;

class GLProxy final
{
public:
	GLProxy(GLStateCache* stateCache);
	~GLProxy();

	// disallow copying
	GLProxy(const GLProxy& other) = delete;
	GLProxy& operator = (const GLProxy& other) = delete;

	void useProgram(const ShaderProgram& shaderProgram);

private:
	GLStateCache* m_stateCache;
};

}