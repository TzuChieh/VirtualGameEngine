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

class Framebuffer
{
public:
	static void bindDefault();
	static void bindDefaultForRendering(const uint32 renderWidthPx, const uint32 renderHeightPx);

public:
	Framebuffer();
	~Framebuffer();

	void create(const uint32 widthPx, const uint32 heightPx);
	void create();

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
		void attachRenderTarget(const Texture2D& texture2d, const ETargetSlot& targetSlot);

		void detachAllRenderTargets();

	uint32 getRenderWidthPx() const;
	uint32 getRenderHeightPx() const;

	Texture2D getAttachedRenderTarget(const ETargetSlot& targetSlot) const;

private:
	uint32 m_renderWidthPx;
	uint32 m_renderHeightPx;

	std::shared_ptr<GLuint> m_framebufferHandle;
	std::vector<std::pair<ETargetSlot, Texture2D>> m_texture2dRenderTargets;

	bool isTargetSlotOccupied(const ETargetSlot& targetSlot) const;

private:
	static std::string getFramebufferStatusInfo(const Framebuffer& framebuffer);
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