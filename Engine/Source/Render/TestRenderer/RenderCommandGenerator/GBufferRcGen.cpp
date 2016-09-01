#include "GBufferRcGen.h"
#include "Render/Shader/ShaderProgramRes.h"
#include "Render/Shader/Shader.h"
#include "Render/Model/GpuMesh.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/Renderable/StaticRenderableContainer.h"
#include "Render/Camera.h"

#include <functional>

namespace ve
{

class GBufferRc : public RenderCommand
{
public:
	GBufferRc(const std::function<void(ShaderProgram&)>& uniformUpdater, 
	          const ShaderProgram& shaderProgram,
	          const GpuMesh& gpuMesh) :
		m_uniformUpdater(uniformUpdater), m_shaderProgram(shaderProgram), m_gpuMesh(gpuMesh)
	{

	}

	virtual ~GBufferRc() override
	{

	}

	virtual void execute() override
	{
		m_shaderProgram.use();

		m_uniformUpdater(m_shaderProgram);

		m_gpuMesh.bind();
		m_gpuMesh.draw();
	}

private:
	std::function<void(ShaderProgram&)> m_uniformUpdater;
	ShaderProgram m_shaderProgram;
	GpuMesh m_gpuMesh;
};

}

using namespace ve;

GBufferRcGen::GBufferRcGen() : 
	m_gbufferShaderProgram(std::make_shared<ShaderProgramRes>())
{
	Shader vertShader("./Shader/GBuffer.vs");
	Shader fragShader("./Shader/GBuffer.fs");
	vertShader.compile();
	fragShader.compile();

	m_gbufferShaderProgram.completeProgram(vertShader, fragShader);
}

void GBufferRcGen::genRenderCommands(const Camera& camera,
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

			const auto& renderCommand = std::make_shared<GBufferRc>(uniformUpdater, m_gbufferShaderProgram, meshMatlPair.first);
			out_renderCommands->push_back(renderCommand);
		}
	}
}