#pragma once

#include "PEffect.h"
#include "Render/Image/Texture2D.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Model/Brush/Quad2dBrush.h"
#include "Common/logging.h"

DECLARE_LOG_SENDER_EXTERN(PTextureCopy);

namespace ve
{

class PTextureCopy final : public PEffect
{
public:
	PTextureCopy();
	virtual ~PTextureCopy() override;

	virtual void create() override;

	void prepare(const Texture2D& source);

private:
	virtual void genRenderCommands(std::vector<std::shared_ptr<RenderCommand>>* out_renderCommands) const override;

	Texture2D m_sourceTexture;

	ShaderProgram m_shaderProgram;
	Quad2dBrush   m_fullScreenQuad;
};

}