#include "TestGameProgram.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Common/type.h"
#include "Core/GraphicsApi.h"

#include <iostream>
#include <vector>

using namespace xe;

TestGameProgram::~TestGameProgram() {
	delete m_shaderProgram;
	delete m_mesh;
}

bool TestGameProgram::init() {
	m_shaderProgram = new ShaderProgram;
	m_mesh = new Mesh;

	Shader vertShader("./Resource/Shader/testVertShader.vs");
	Shader fragShader("./Resource/Shader/testFragShader.fs");
	vertShader.compile();
	fragShader.compile();
	m_shaderProgram->completeProgram(vertShader, fragShader);

	std::vector<float32> positions3d = {0.0f, 0.5f, 0.0f,
	                                    -0.5f, -0.5f, 0.0f,
	                                    0.5f, -0.5f, 0.0f};
	m_mesh->loadData(positions3d);

	return true;
}

void TestGameProgram::update() {
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shaderProgram->use();
	m_mesh->draw();

	//std::cout << "updated" << std::endl;
}