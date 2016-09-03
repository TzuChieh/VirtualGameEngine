#pragma once

#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"
#include "Common/logging.h"
#include "Render/Image/Texture2DRes.h"

#include <vector>
#include <memory>
#include <initializer_list>
#include <utility>

DECLARE_LOG_SENDER_EXTERN(FramebufferRes);

namespace ve
{

enum class ETargetSlot : uint32;

class FramebufferRes final
{
public:
	static void bindDefault();
	static void bindDefaultForRendering(const uint32 renderWidthPx, const uint32 renderHeightPx);

public:
	FramebufferRes(const uint32 renderWidthPx, const uint32 renderHeightPx);
	~FramebufferRes();

	void bind() const;
	void unbind() const;
	void bindForRendering() const;

	// these are per-framebuffer states; no need to specify them everytime you use
	void disableRead() const;
	void disableWrite() const;
	void enableWriteOn(const std::initializer_list<ETargetSlot> targetSlots) const;
	void setRenderWidthPx(const uint32 widthPx);
	void setRenderHeightPx(const uint32 heightPx);
	void setRenderDimensionPx(const uint32 widthPx, const uint32 heightPx);

	// attaching render target to an already occupied slot will simply overwrite the existing one
	void attachRenderTarget(const std::shared_ptr<Texture2DRes>& targetResource, 
	                        const uint32 targetMipLevel, 
	                        const ETargetSlot& targetSlot);
	void detachAllRenderTargets();
	std::shared_ptr<Texture2DRes> getAttachedRenderTarget(const ETargetSlot targetSlot) const;

	uint32 getRenderWidthPx() const;
	uint32 getRenderHeightPx() const;

private:
	GLuint m_framebufferHandle;

	uint32 m_renderWidthPx;
	uint32 m_renderHeightPx;

	std::vector<std::pair<ETargetSlot, std::shared_ptr<Texture2DRes>>> m_texture2dResRenderTargets;

	bool isTargetSlotOccupied(const ETargetSlot& targetSlot) const;

private:
	static std::string getFramebufferResStatusInfo(const FramebufferRes& framebufferRes);
};

enum class ETargetSlot : uint32
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