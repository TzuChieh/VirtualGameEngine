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

#include "Common/ThirdPartyLib/glew.h"
#include "Common/ThirdPartyLib/assimp.h"

#include <iostream>

DEFINE_LOG_SENDER(TestRenderer);

using namespace ve;

TestRenderer::~TestRenderer()
{

}

bool TestRenderer::init()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	m_cameraComponents.addActionListener(std::make_shared<CameraManagerActionListener>(&m_mainCamera));
	m_staticModelGroups.addActionListener(std::make_shared<StaticModelGroupProcessor>(&m_staticRenderableContainer));


	ShaderProgram shaderProgram;
	shaderProgram.createProgram();
	/*Shader vertShader("./Shader/testVertShader.vs");
	Shader fragShader("./Shader/testFragShader.fs");*/
	Shader vertShader("./Shader/TestShader.vs");
	Shader fragShader("./Shader/TestShader.fs");
	vertShader.compile();
	fragShader.compile();
	shaderProgram.completeProgram(vertShader, fragShader);

	shaderProgram.registerUniform("u_viewMatrix");
	shaderProgram.registerUniform("u_projectionMatrix");

	if(!m_testRcGen.init(shaderProgram))
	{
		ENGINE_LOG(TestRenderer, LogLevel::FATAL_ERROR, "TestRcGen init failed");
		return false;
	}

	

	LdrRectImage blahImage;
	blahImage.load("./Resource/Image/test.png");

	return true;
}

void TestRenderer::render()
{
	std::vector<std::shared_ptr<RenderCommand>> m_renderCommandBuffer;

	m_testRcGen.genRenderCommands(m_mainCamera, m_staticRenderableContainer, &m_renderCommandBuffer);

	m_mainCamera.update();

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