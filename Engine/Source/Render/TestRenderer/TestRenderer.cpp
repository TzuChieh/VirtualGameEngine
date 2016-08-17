#include "TestRenderer.h"
#include "Render/ShaderProgram.h"
#include "Render/Shader.h"
#include "Common/type.h"
#include "Render/Model/GpuBufferObject.h"
#include "Render/Model/GpuMesh.h"
#include "CameraManagerActionListener.h"
#include "StaticModelGroupManagerActionListener.h"
#include "Render/Image/LdrRectImage.h"

#include "Common/ThirdPartyLib/glew.h"
#include "Common/ThirdPartyLib/assimp.h"

#include <iostream>

using namespace xe;

static GpuMesh gpuMesh;
static ShaderProgram* shaderProgram;

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
	m_staticModelGroups.addActionListener(std::make_shared<StaticModelGroupManagerActionListener>(&m_staticRenderableContainer));

	/*glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, positions3d.size() * sizeof(float32), positions3d.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);*/

	Assimp::Importer assimpImporter;
	const aiScene* assimpScene = assimpImporter.ReadFile("./Resource/Model/house.obj", aiProcess_Triangulate);
	if(!assimpScene)
	{
		std::cerr << assimpImporter.GetErrorString() << std::endl;
	}

	std::cout << "numMeshes: " << assimpScene->mNumMeshes << std::endl;
	for(uint32 i = 0; i < assimpScene->mNumMeshes; i++)
	{
		std::cout << "mesh id: " << i << std::endl;
		aiMesh* assimpMesh = assimpScene->mMeshes[i];
	}

	gpuMesh.create();
	gpuMesh.setDrawingGenre(EDrawingGenre::TRIANGLES);

	GpuBufferObject vbo_positions;
	GpuBufferObject vbo_normals;
	GpuBufferObject vbo_indices;
	std::vector<float32> positions;
	std::vector<float32> normals;
	std::vector<uint32> indices;

	aiMesh* mesh = assimpScene->mMeshes[0];

	if(mesh->HasPositions())
	{
		for(int i = 0; i < mesh->mNumVertices; ++i)
		{
			positions.push_back(mesh->mVertices[i].x);
			positions.push_back(mesh->mVertices[i].y);
			positions.push_back(mesh->mVertices[i].z);
			//std::cout << "pos" << std::endl;
		}

		vbo_positions.create(EGpuBufferType::GENERAL_ARRAY, EGpuBufferUsage::STATIC);
		vbo_positions.loadData(positions);

		gpuMesh.addVertexData(vbo_positions, 0);
		gpuMesh.setVertexDataLocator(0, 0, 3, 0, 0);
	}

	if(mesh->HasNormals())
	{
		for(int i = 0; i < mesh->mNumVertices; ++i)
		{
			normals.push_back(mesh->mNormals[i].x);
			normals.push_back(mesh->mNormals[i].y);
			normals.push_back(mesh->mNormals[i].z);
		}

		vbo_normals.create(EGpuBufferType::GENERAL_ARRAY, EGpuBufferUsage::STATIC);
		vbo_normals.loadData(normals);

		gpuMesh.addVertexData(vbo_normals, 1);
		gpuMesh.setVertexDataLocator(1, 1, 3, 0, 0);
	}

	if(mesh->HasFaces())
	{
		for(int i = 0; i < mesh->mNumFaces; ++i)
		{
			indices.push_back(mesh->mFaces[i].mIndices[0]);
			indices.push_back(mesh->mFaces[i].mIndices[1]);
			indices.push_back(mesh->mFaces[i].mIndices[2]);
			//std::cout << "ind" << std::endl;
		}

		vbo_indices.create(EGpuBufferType::INDEX_ARRAY, EGpuBufferUsage::STATIC);
		vbo_indices.loadData(indices);

		gpuMesh.setIndexData(vbo_indices, mesh->mNumFaces * 3);
	}

	shaderProgram = new ShaderProgram;
	/*Shader vertShader("./Shader/testVertShader.vs");
	Shader fragShader("./Shader/testFragShader.fs");*/
	Shader vertShader("./Shader/PhongMaterial.vs");
	Shader fragShader("./Shader/PhongMaterial.fs");
	vertShader.compile();
	fragShader.compile();
	shaderProgram->completeProgram(vertShader, fragShader);

	shaderProgram->registerUniform("u_viewMatrix");
	shaderProgram->registerUniform("u_projectionMatrix");


	LdrRectImage blahImage;
	blahImage.load("./Resource/Image/test.png");

	return true;
}

void TestRenderer::render()
{
	m_mainCamera.update();
	//std::cout << m_mainCamera.getViewProjectionMatrix().toStringFormal() << std::endl;


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	shaderProgram->updateUniform("u_viewMatrix", m_mainCamera.getViewMatrix());
	shaderProgram->updateUniform("u_projectionMatrix", m_mainCamera.getProjectionMatrix());


	gpuMesh.draw();
}

void TestRenderer::decompose()
{
	delete shaderProgram;
	//delete m_mesh;
}

std::shared_ptr<ComponentHandle> TestRenderer::addCamera(const CCamera& camera)
{
	return m_cameraComponents.addComponent(camera);
}

std::shared_ptr<ComponentHandle> TestRenderer::addStaticModelGroup(const CStaticModelGroup& staticModelGroup)
{
	return m_staticModelGroups.addComponent(staticModelGroup);
}