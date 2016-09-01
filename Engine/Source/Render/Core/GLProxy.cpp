#include "GLProxy.h"
#include "GLStateCache.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Shader/ShaderProgramRes.h"

#include "Common/ThirdPartyLib/glew.h"

DEFINE_LOG_SENDER(GLProxy);

using namespace ve;

GLProxy::GLProxy(GLStateCache* stateCache) : 
	m_stateCache(stateCache)
{
	ENGINE_LOG_IF(stateCache == nullptr, GLProxy, LogLevel::FATAL_ERROR, "specified GLStateCache is null");
}

GLProxy::~GLProxy()
{

}

void GLProxy::useProgram(const ShaderProgram& shaderProgram)
{

	glUseProgram(shaderProgram.getResource()->getGlHandle());
}
