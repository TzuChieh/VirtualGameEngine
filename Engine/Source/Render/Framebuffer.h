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

enum class ETargetSlot : uint32;

class FramebufferRes;

class Framebuffer final
{
public:
	static void bindDefaultForRendering(const uint32 renderWidthPx, const uint32 renderHeightPx);

public:
	Framebuffer();
	Framebuffer(const std::shared_ptr<FramebufferRes>& resource);

	void useForRendering() const;

	// these are per-framebuffer states; no need to specify them everytime you use
	void disableRead() const;
	void disableWrite() const;
	void enableWriteOn(const std::initializer_list<ETargetSlot>& targetSlots) const;
	void setRenderWidthPx(const uint32 widthPx);
	void setRenderHeightPx(const uint32 heightPx);
	void setRenderDimensionPx(const uint32 widthPx, const uint32 heightPx);

	// attaching render target to an already occupied slot will simply overwrite the existing one
	void attachRenderTarget(const Texture2D& texture2d, const uint32 targetMipLevel, const ETargetSlot& targetSlot);
	Texture2D getAttachedRenderTarget(const ETargetSlot& targetSlot) const;
	void detachAllRenderTargets();

	uint32 getRenderWidthPx() const;
	uint32 getRenderHeightPx() const;

private:
	std::shared_ptr<FramebufferRes> m_framebufferResource;
};

}