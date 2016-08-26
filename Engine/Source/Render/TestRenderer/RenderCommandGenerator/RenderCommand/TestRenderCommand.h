#pragma once

#include "Render/RenderCommand/RenderCommand.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Model/GpuMesh.h"
#include "Render/Camera.h"

namespace ve
{

class TestRenderCommand : public RenderCommand
{
public:
	TestRenderCommand(const Camera& camera, const ShaderProgram& shaderProgram, const GpuMesh& gpuMesh);
	virtual ~TestRenderCommand() override;

	virtual void execute() override;

private:
	Camera m_camera;
	ShaderProgram m_shaderProgram;
	GpuMesh m_gpuMesh;
};

}