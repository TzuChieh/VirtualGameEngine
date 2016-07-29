#include "TestRenderer.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Shader.h"
#include "Common/type.h"
#include "Core/graphicsApi.h"
#include "Renderer/Model/GpuBufferObject.h"

#include <assimp/importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>

using namespace xe;

static GLuint vao;
static GpuBufferObject vbo_positions;
static GpuBufferObject vbo_normals;
static GpuBufferObject vbo_indices;
static GLuint size;

static ShaderProgram* shaderProgram;

TestRenderer::~TestRenderer()
{

}

bool TestRenderer::init()
{
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

	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

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

		vbo_positions.create(GpuBufferType::GENERAL_ARRAY, GpuBufferUsage::STATIC);
		vbo_positions.loadData(positions);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
	}

	if(mesh->HasNormals())
	{
		for(int i = 0; i < mesh->mNumVertices; ++i)
		{
			normals.push_back(mesh->mNormals[i].x);
			normals.push_back(mesh->mNormals[i].y);
			normals.push_back(mesh->mNormals[i].z);
		}

		vbo_normals.create(GpuBufferType::GENERAL_ARRAY, GpuBufferUsage::STATIC);
		vbo_normals.loadData(normals);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
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

		size = mesh->mNumFaces * 3;

		vbo_indices.create(GpuBufferType::INDEX_ARRAY, GpuBufferUsage::STATIC);
		vbo_indices.loadData(indices);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shaderProgram = new ShaderProgram;
	Shader vertShader("./Resource/Shader/testVertShader.vs");
	Shader fragShader("./Resource/Shader/testFragShader.fs");
	vertShader.compile();
	fragShader.compile();
	shaderProgram->completeProgram(vertShader, fragShader);

	return true;
}

void TestRenderer::render()
{
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

void TestRenderer::decompose()
{
	delete shaderProgram;
	//delete m_mesh;
}