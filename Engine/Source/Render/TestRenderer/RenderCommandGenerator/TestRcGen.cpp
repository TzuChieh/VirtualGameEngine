#include "TestRcGen.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/Renderable/StaticRenderableContainer.h"
#include "Render/Shader/Shader.h"
#include "Render/RenderCommand/RenderCommand.h"
#include "Render/Camera.h"
#include "Render/Shader/ShaderUniformUpdater.h"

namespace ve
{

class TestRenderCommand : public RenderCommand
{
public:
	TestRenderCommand(const std::shared_ptr<ShaderUniformUpdater>& uniformUpdater,
	                  const ShaderProgram& shaderProgram,
	                  const GpuMesh& gpuMesh);
	virtual ~TestRenderCommand() override;

	virtual void execute() override;

private:
	std::shared_ptr<ShaderUniformUpdater> m_uniformUpdater;
	ShaderProgram m_shaderProgram;
	GpuMesh m_gpuMesh;
};

class TestUniformUpdater : public ShaderUniformUpdater
{
public:
	TestUniformUpdater(const Camera& camera, const Matrix4f& modelMatrix);
	virtual ~TestUniformUpdater() override;

	virtual void updateUniforms(ShaderProgram& shaderProgram) const override;

private:
	Camera m_camera;
	Matrix4f m_modelMatrix;
};

}

using namespace ve;

TestRenderCommand::TestRenderCommand(const std::shared_ptr<ShaderUniformUpdater>& uniformUpdater, 
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

	m_uniformUpdater->updateUniforms(m_shaderProgram);

	m_gpuMesh.bind();
	m_gpuMesh.draw();
}

TestUniformUpdater::TestUniformUpdater(const Camera& camera, const Matrix4f& modelMatrix) : 
	m_camera(camera), m_modelMatrix(modelMatrix)
{

}

TestUniformUpdater::~TestUniformUpdater()
{

}

void TestUniformUpdater::updateUniforms(ShaderProgram& shaderProgram) const
{
	shaderProgram.updateUniform("u_viewMatrix", m_camera.getViewMatrix());
	shaderProgram.updateUniform("u_projectionMatrix", m_camera.getProjectionMatrix());
	shaderProgram.updateUniform("u_modelMatrix", m_modelMatrix);
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

			out_renderCommands->push_back(std::make_shared<TestRenderCommand>(std::make_shared<TestUniformUpdater>(camera, renderable.getModelMatrix()),
			                              m_shaderProgram,
			                              meshMatlPair.first));
		}
	}
}