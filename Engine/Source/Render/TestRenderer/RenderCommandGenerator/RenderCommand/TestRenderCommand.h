#pragma once

#include "Render/RenderCommand/RenderCommand.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Model/GpuMesh.h"

namespace xe
{

class TestRenderCommand : public RenderCommand
{
public:
	TestRenderCommand(const ShaderProgram& shaderProgram, const GpuMesh& gpuMesh);
	virtual ~TestRenderCommand() override;

	virtual void execute() override;

private:
	ShaderProgram m_shaderProgram;
	GpuMesh m_gpuMesh;
};

}