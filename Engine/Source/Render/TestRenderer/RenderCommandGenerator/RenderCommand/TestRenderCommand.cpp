#include "TestRenderCommand.h"

using namespace xe;

TestRenderCommand::TestRenderCommand(const ShaderProgram& shaderProgram, const GpuMesh& gpuMesh) : 
	m_shaderProgram(shaderProgram), m_gpuMesh(gpuMesh)
{

}

TestRenderCommand::~TestRenderCommand()
{

}

void TestRenderCommand::execute()
{
	m_shaderProgram.use();
	m_gpuMesh.bind();
	m_gpuMesh.draw();
}