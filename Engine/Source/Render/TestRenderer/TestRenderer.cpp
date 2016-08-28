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
#include "Core/EngineProxy.h"
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
	m_gpuGbuffer.attachRenderTarget(albedoBuffer, ETargetTag::COLOR_0);
	

	return true;
}

void TestRenderer::render()
{
	m_mainCamera.update();

	std::vector<std::shared_ptr<RenderCommand>> m_renderCommandBuffer;
	m_testRcGen.genRenderCommands(m_mainCamera, m_staticRenderableContainer, &m_renderCommandBuffer);

	//Framebuffer::bindDefault();
	m_gpuGbuffer.bind();


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto& renderCommand : m_renderCommandBuffer)
	{
		renderCommand->execute();
	}
}

void TestRenderer::decompose()
{
	m_staticRenderableContainer.removeAll();
}

std::shared_ptr<ComponentHandle> TestRenderer::addCamera(const CCamera& camera)
{
	return m_cameraComponents.addComponent(camera);
}

std::shared_ptr<ComponentHandle> TestRenderer::addStaticModelGroup(const CStaticModelGroup& staticModelGroup)
{
	return m_staticModelGroups.addComponent(staticModelGroup);
}