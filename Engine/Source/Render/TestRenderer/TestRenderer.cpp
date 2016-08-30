#include "TestRenderer.h"
#include "Render/Shader/Shader.h"
#include "Common/type.h"
#include "Render/Model/GpuBufferObject.h"
#include "Render/Model/GpuMesh.h"
#include "CameraManagerActionListener.h"
#include "StaticModelGroupProcessor.h"
#include "Render/Image/LdrRectImage.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/RenderCommand/RenderCommand.h"
#include "Render/Image/Texture2D.h"

#include "Common/ThirdPartyLib/glew.h"
#include "Common/ThirdPartyLib/assimp.h"

#include <iostream>

DEFINE_LOG_SENDER(TestRenderer);

using namespace ve;

TestRenderer::~TestRenderer()
{

}

bool TestRenderer::init(const EngineProxy& engineProxy)
{
	m_engineProxy = engineProxy;

	if(!m_postProcessor.init(engineProxy))
	{
		ENGINE_LOG(TestRenderer, LogLevel::FATAL_ERROR, "PostProcessor init failed");
		return false;
	}

	m_textureCopyEffect.create();

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	m_cameraComponents.addActionListener(std::make_shared<CameraManagerActionListener>(&m_mainCamera));
	m_staticModelGroups.addActionListener(std::make_shared<StaticModelGroupProcessor>(&m_staticRenderableContainer));

	if(!m_testRcGen.init())
	{
		ENGINE_LOG(TestRenderer, LogLevel::FATAL_ERROR, "TestRcGen init failed");
		return false;
	}

	LdrRectImage blahImage;
	blahImage.load("./Resource/Image/test.png");


	const uint32 displayWidthPx = engineProxy.getDisplayWidthPx();
	const uint32 displayHeightPx = engineProxy.getDisplayHeightPx();

	Texture2D albedoBuffer;
	albedoBuffer.create(displayWidthPx, displayHeightPx, ETextureDataFormat::RGB_8_BITS_EACH, ETextureFilterMode::LINEAR);

	m_gpuGbuffer.create(displayWidthPx, displayHeightPx);
	m_gpuGbuffer.attachRenderTarget(albedoBuffer, ETargetSlot::COLOR_0);
	m_gpuGbuffer.enableWriteOn({ETargetSlot::COLOR_0});

	LdrRectImage image;
	image.load("./Resource/Image/test.png");
	m_testTexture.create(image);

	return true;
}

void TestRenderer::render()
{
	m_mainCamera.update();

	std::vector<std::shared_ptr<RenderCommand>> m_renderCommandBuffer;
	m_testRcGen.genRenderCommands(m_mainCamera, m_staticRenderableContainer, &m_renderCommandBuffer);

	//Framebuffer::bindDefaultForRendering(m_engineProxy.getDisplayWidthPx(), m_engineProxy.getDisplayHeightPx());
	//m_gpuGbuffer.bind();
	m_gpuGbuffer.bindForRendering();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);

	for(auto& renderCommand : m_renderCommandBuffer)
	{
		renderCommand->execute();
	}

	m_textureCopyEffect.prepare(m_testTexture);
	//m_textureCopyEffect.prepare(m_gpuGbuffer.getAttachedRenderTarget(ETargetSlot::COLOR_0));
	m_postProcessor.renderEffectToDisplay(m_textureCopyEffect);

	//m_textureCopyEffect.prepare(m_gpuGbuffer.getAttachedRenderTarget(ETargetSlot::COLOR_0));
	//m_postProcessor.renderEffectToTexture(m_textureCopyEffect, );
}

void TestRenderer::decompose()
{
	m_staticRenderableContainer.removeAll();
	m_postProcessor.decompose();
}

std::shared_ptr<ComponentHandle> TestRenderer::addCamera(const CCamera& camera)
{
	return m_cameraComponents.addComponent(camera);
}

std::shared_ptr<ComponentHandle> TestRenderer::addStaticModelGroup(const CStaticModelGroup& staticModelGroup)
{
	return m_staticModelGroups.addComponent(staticModelGroup);
}