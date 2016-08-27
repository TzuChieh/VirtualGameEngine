#include "TestRcGen.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/Renderable/StaticRenderableContainer.h"
#include "Render/Shader/Shader.h"
#include "Render/RenderCommand/RenderCommand.h"
#include "Render/Camera.h"
#include "Render/Shader/ShaderUniformUpdater.h"

#include <functional>

namespace ve
{

class TestRenderCommand : public RenderCommand
{
public:
	TestRenderCommand(const std::function<void(ShaderProgram&)>& uniformUpdater,
	                  const ShaderProgram& shaderProgram,
	                  const GpuMesh& gpuMesh);
	virtual ~TestRenderCommand() override;

	virtual void execute() override;

private:
	std::function<void (ShaderProgram&)> m_uniformUpdater;
	ShaderProgram m_shaderProgram;
	GpuMesh m_gpuMesh;
};

}

using namespace ve;

TestRenderCommand::TestRenderCommand(const std::function<void(ShaderProgram&)>& uniformUpdater,
                                     const ShaderProgram& shaderProgram,
                                     const GpuMesh& gpuMesh) : 
	m_uniformUpdater(uniformUpdater), m_shaderProgram(shaderProgram), m_gpuMesh(gpuMesh)
{

}

TestRenderCommand::~TestRenderCommand()
{

}

void TestRenderCommand::execute()
{
	m_shaderProgram.use();

	m_uniformUpdater(m_shaderProgram);

	m_gpuMesh.bind();
	m_gpuMesh.draw();
}

bool TestRcGen::init()
{
	m_shaderProgram.createProgram();

	Shader vertShader("./Shader/TestShader.vs");
	Shader fragShader("./Shader/TestShader.fs");
	vertShader.compile();
	fragShader.compile();

	m_shaderProgram.completeProgram(vertShader, fragShader);

	m_shaderProgram.registerUniform("u_viewMatrix");
	m_shaderProgram.registerUniform("u_projectionMatrix");
	m_shaderProgram.registerUniform("u_modelMatrix");

	return true;
}

void TestRcGen::genRenderCommands(const Camera& camera, 
                                  const StaticRenderableContainer& renderables,
                                  std::vector<std::shared_ptr<RenderCommand>>* out_renderCommands) const
{
	for(uint32 x = 0; x < renderables.numStaticRenderables(); x++)
	{
		const auto& renderable = renderables.getStaticRenderable(x);
		for(uint32 i = 0; i < renderable.numMeshMaterialPairs(); i++)
		{
			const auto& meshMatlPair = renderable.getMeshMaterialPair(i);
			const auto& uniformUpdater = [&camera, &renderable](ShaderProgram& shaderProgram)
			{
				shaderProgram.updateUniform("u_viewMatrix", camera.getViewMatrix());
				shaderProgram.updateUniform("u_projectionMatrix", camera.getProjectionMatrix());
				shaderProgram.updateUniform("u_modelMatrix", renderable.getModelMatrix());
			};

			const auto& renderCommand = std::make_shared<TestRenderCommand>(uniformUpdater, m_shaderProgram, meshMatlPair.first);
			out_renderCommands->push_back(renderCommand);
		}
	}
}