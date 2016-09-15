#pragma once

#include "Render/Renderer.h"
#include "Resource/World/Component/TIndexedComponentManager.h"
#include "Render/Component/CCamera.h"
#include "Render/Camera.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Render/Renderable/StaticRenderableContainer.h"
#include "Render/TestRenderer/RenderCommandGenerator/TestRcGen.h"
#include "Common/logging.h"
#include "Render/Framebuffer.h"
#include "Render/PostProcess/PostProcessor.h"
#include "Render/PostProcess/PTextureCopy.h"
#include "Core/EngineProxy.h"
#include "Render/TestRenderer/RenderCommandGenerator/GBufferRcGen.h"
#include "Render/Command/GpuCommandQueue.h"
#include "StaticModelGroupProcessor.h"

DECLARE_LOG_SENDER_EXTERN(TestRenderer);

namespace ve
{

class TestRenderer : public Renderer
{
public:
	virtual ~TestRenderer() override;

	virtual void render() override;

private:
	TIndexedComponentManager<CCamera> m_cameraComponents;
	TIndexedComponentManager<CStaticModelGroup> m_staticModelGroups;

	PostProcessor m_postProcessor;
	PTextureCopy m_textureCopyEffect;

	StaticModelGroupProcessor m_staticModelGroupProcessor;
	StaticRenderableContainer m_staticRenderableContainer;
	TestRcGen m_testRcGen;
	GBufferRcGen m_gbufferRcGen;

	Camera m_mainCamera;

	Framebuffer m_gpuGbuffer;
	EngineProxy m_engineProxy;
	Texture2D m_testTexture;

	GpuCommandQueue m_gpuCommandQueue;

	virtual bool init(const EngineProxy& engineProxy) override;
	virtual void decompose() override;
};

}