#include "TestRcGen.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/TestRenderer/RenderCommandGenerator/RenderCommand/TestRenderCommand.h"
#include "Render/Renderable/StaticRenderableContainer.h"

using namespace ve;

bool TestRcGen::init(const ShaderProgram& shaderProgram)
{
	m_shaderProgram = shaderProgram;

	// TODO: check shader validity
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

			out_renderCommands->push_back(std::make_shared<TestRenderCommand>(camera, m_shaderProgram, meshMatlPair.first));
		}
	}
}