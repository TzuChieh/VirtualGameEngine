#pragma once

#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"
#include "Render/Image/Texture2D.h"
#include "Common/logging.h"

#include <vector>
#include <memory>
#include <initializer_list>
#include <utility>

DECLARE_LOG_SENDER_EXTERN(Framebuffer);

namespace ve
{

enum class ETargetTag : uint32;

class Framebuffer
{
public:
	static void bindDefault();

public:
	Framebuffer();
	~Framebuffer();

	void create(const uint32 widthPx, const uint32 heightPx);

	void bind() const;
	void unbind() const;

	// these are per-framebuffer states; no need to specify them everytime you use
	void disableRead() const;
	void disableWrite() const;
	void enableWriteOn(const std::initializer_list<ETargetTag> targetTags) const;

	void attachRenderTarget(const Texture2D& texture2d, const ETargetTag& targetTag);

private:
	uint32 m_widthPx;
	uint32 m_heightPx;

	std::shared_ptr<GLuint> m_framebufferHandle;
	std::vector<std::pair<ETargetTag, Texture2D>> m_texture2dRenderTargets;

	bool isTargetAttached(const ETargetTag& targetTag) const;

private:
	static std::string getFramebufferStatusInfo(const Framebuffer& framebuffer);
};

enum class ETargetTag : uint32
{
	COLOR_0 = GL_COLOR_ATTACHMENT0,
	COLOR_1 = GL_COLOR_ATTACHMENT1,
	COLOR_2 = GL_COLOR_ATTACHMENT2,
	COLOR_3 = GL_COLOR_ATTACHMENT3,
	COLOR_4 = GL_COLOR_ATTACHMENT4,
	COLOR_5 = GL_COLOR_ATTACHMENT5,

	DEPTH_STENCIL = GL_DEPTH_STENCIL_ATTACHMENT
};

}