#include "GBufferRcGen.h"
#include "Render/Shader/ShaderProgramRes.h"
#include "Render/Shader/Shader.h"
#include "Render/Model/GpuMesh.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/Renderable/StaticRenderableContainer.h"
#include "Render/Camera.h"
#include "Render/Command/GpuCommandQueue.h"
#include "Render/Command/SortingStrategy.h"

#include <functional>

using namespace ve;

GBufferRcGen::GBufferRcGen() : 
	m_gbufferShaderProgram(std::make_shared<ShaderProgramRes>()), 
	m_commandSorter(ESortingStrategy::PRIORITIED_MATERIAL_ONLY)
{
	Shader vertShader("./Shader/GBuffer.vs");
	Shader fragShader("./Shader/GBuffer.fs");
	vertShader.compile();
	fragShader.compile();

	m_gbufferShaderProgram.completeProgram(vertShader, fragShader);
}

void GBufferRcGen::renderGBuffer(const Camera& camera,
                                 const StaticRenderableContainer& renderables,
                                 GpuCommandQueue* out_commandQueue)
{
	m_commandSorter.clearCommands();

	for(uint32 x = 0; x < renderables.numStaticRenderables(); x++)
	{
		const auto& renderable = renderables.getStaticRenderable(x);
		for(uint32 i = 0; i < renderable.numMeshMaterialPairs(); i++)
		{
			const auto& meshMatlPair = renderable.getMeshMaterialPair(i);
			const auto& renderCommand = [&camera, &renderable, &meshMatlPair, this]()
			{
				m_gbufferShaderProgram.use();

				m_gbufferShaderProgram.updateUniform("u_viewMatrix", camera.getViewMatrix());
				m_gbufferShaderProgram.updateUniform("u_projectionMatrix", camera.getProjectionMatrix());
				m_gbufferShaderProgram.updateUniform("u_modelMatrix", renderable.getModelMatrix());

				meshMatlPair.first.draw();
			};

			RenderCommandInfo commandInfo;
			commandInfo.materialId = 777;
			m_commandSorter.addCommand(renderCommand, commandInfo);
		}
	}

	m_commandSorter.sortCommands();
	m_commandSorter.queueCommands(out_commandQueue);
}