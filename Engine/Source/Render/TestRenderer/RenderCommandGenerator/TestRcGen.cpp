#include "TestRcGen.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/TestRenderer/RenderCommandGenerator/RenderCommand/TestRenderCommand.h"

using namespace xe;

TestRcGen::TestRcGen(const ShaderProgram& shaderProgram) :
	m_shaderProgram(shaderProgram)
{

}

//void TestRcGen::genRenderCommands(const std::vector<StaticRenderable>& renderables,
//                                  std::vector<RenderCommand>* out_renderCommands) const
//{
//	for(const auto& renderable : renderables)
//	{
//		for(uint32 i = 0; i < renderable.numMeshMaterialPairs(); i++)
//		{
//			// TODO
//
//			const auto& meshMatlPair = renderable.getMeshMaterialPair(i);
//
//			out_renderCommands->push_back(TestRenderCommand(m_shaderProgram, meshMatlPair.first));
//		}
//	}
//}