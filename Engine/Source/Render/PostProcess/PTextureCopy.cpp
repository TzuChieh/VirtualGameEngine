#include "PTextureCopy.h"
#include "Render/RenderCommand/RenderCommand.h"
#include "Render/PostProcess/ShaderProgramLibrary.h"
#include "Render/Shader/Shader.h"
#include "Render/Shader/ShaderProgramRes.h"

#include "Common/ThirdPartyLib/glew.h"

#include <iostream>
#include <memory>

#define FSQ_POSITION_GPU_INDEX 0
#define FSQ_TEXCOORD_GPU_INDEX 1

DEFINE_LOG_SENDER(PTextureCopy);

namespace ve
{

class PRenderCommand final : public RenderCommand
{
public:
	PRenderCommand(const ShaderProgram& program, const Texture2D& source, const Quad2dBrush& fullScreenQuad);
	virtual ~PRenderCommand() override;

	virtual void execute() override;

private:
	ShaderProgram m_shaderProgram;
	Texture2D m_sourceTexture;
	Quad2dBrush m_fullScreenQuad;
};

PRenderCommand::PRenderCommand(const ShaderProgram& program, const Texture2D& source, const Quad2dBrush& fullScreenQuad) :
	m_shaderProgram(program), m_sourceTexture(source), m_fullScreenQuad(fullScreenQuad)
{

}

PRenderCommand::~PRenderCommand()
{

}

void PRenderCommand::execute()
{
	glDisable(GL_DEPTH_TEST);

	m_shaderProgram.use();

	glActiveTexture(GL_TEXTURE0 + 0);
	m_sourceTexture.use();
	m_shaderProgram.updateUniform("u_sourceTextureSampler", 0);

	m_fullScreenQuad.draw();

	//std::cout << "executed" << std::endl;
}

}// end namespace ve;

using namespace ve;

PTextureCopy::PTextureCopy() : 
	m_fullScreenQuad(FSQ_POSITION_GPU_INDEX)
{

}

PTextureCopy::~PTextureCopy()
{

}

void PTextureCopy::create()
{
	Shader vertShader("./Shader/PostProcess/TextureCopy.vs");
	Shader fragShader("./Shader/PostProcess/TextureCopy.fs");
	vertShader.compile();
	fragShader.compile();
	
	m_shaderProgram = ShaderProgram(std::make_shared<ShaderProgramRes>());
	m_shaderProgram.completeProgram(vertShader, fragShader);

	m_fullScreenQuad.load2dTexureCoordinateData(FSQ_TEXCOORD_GPU_INDEX);
}

void PTextureCopy::prepare(const Texture2D& source)
{
	if(m_sourceTexture != source)
	{
		m_sourceTexture = source;

		//std::cout << "prepared" << std::endl;
	}
}

void PTextureCopy::genRenderCommands(std::vector<std::shared_ptr<RenderCommand>>* out_renderCommands) const
{
	const auto& renderCommand = std::make_shared<PRenderCommand>(m_shaderProgram, m_sourceTexture, m_fullScreenQuad);
	out_renderCommands->push_back(renderCommand);
}