#include "PTextureCopy.h"
#include "Render/RenderCommand/RenderCommand.h"
#include "Render/PostProcess/ShaderProgramLibrary.h"
#include "Render/Shader/Shader.h"

#include "Common/ThirdPartyLib/glew.h"

#include <iostream>

#define FSQ_POSITION_GPU_INDEX 0

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

	m_fullScreenQuad.bind();
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
	
	m_shaderProgram.createProgram();
	m_shaderProgram.completeProgram(vertShader, fragShader);

	m_fullScreenQuad.create();
}

void PTextureCopy::prepare(const Texture2D& source)
{
	if(m_sourceTexture != source)
	{
		m_sourceTexture = source;
	}
}

void PTextureCopy::genRenderCommands(std::vector<std::shared_ptr<RenderCommand>>* out_renderCommands) const
{
	const auto& renderCommand = std::make_shared<PRenderCommand>(m_shaderProgram, m_sourceTexture, m_fullScreenQuad);
	out_renderCommands->push_back(renderCommand);
}