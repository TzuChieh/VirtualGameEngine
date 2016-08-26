#include "TestRenderCommand.h"

using namespace ve;

TestRenderCommand::TestRenderCommand(const Camera& camera, const ShaderProgram& shaderProgram, const GpuMesh& gpuMesh) : 
	m_camera(camera), m_shaderProgram(shaderProgram), m_gpuMesh(gpuMesh)
{

}

TestRenderCommand::~TestRenderCommand()
{

}

void TestRenderCommand::execute()
{
	m_shaderProgram.use();
	m_shaderProgram.updateUniform("u_viewMatrix", m_camera.getViewMatrix());
	m_shaderProgram.updateUniform("u_projectionMatrix", m_camera.getProjectionMatrix());

	m_gpuMesh.bind();
	m_gpuMesh.draw();
}