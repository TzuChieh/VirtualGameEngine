#include "AssimpModelParser.h"
#include "Render/Model/StaticModel.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/Material/PhongMaterial.h"

#include "Common/ThirdPartyLib/assimp.h"

#include <iostream>

using namespace ve;

AssimpModelParser::AssimpModelParser()
{

}

AssimpModelParser::~AssimpModelParser()
{

}

bool AssimpModelParser::load(const StaticModel& staticModel, StaticRenderable* out_staticRenderable)
{
	const aiScene* assimpScene = m_assimpImporter.ReadFile(staticModel.getFullFilename(), aiProcess_Triangulate);
	if(!assimpScene)
	{
		std::cerr << m_assimpImporter.GetErrorString() << std::endl;
		return false;
	}

	out_staticRenderable->clearAll();

	out_staticRenderable->setOriginatedModelName(staticModel.getFullFilename());
	out_staticRenderable->setModelMatrix(AssimpModelParser::genModelMatrix(staticModel));

	GpuMesh         gpuMesh;
	GpuBufferObject vbo_positions;
	GpuBufferObject vbo_normals;
	GpuBufferObject vbo_indices;

	gpuMesh.create();
	gpuMesh.setDrawingGenre(EDrawingGenre::TRIANGLES);
	
	std::vector<float32> positions;
	std::vector<float32> normals;
	std::vector<uint32>  indices;

	// FIXME: mMeshes[N]
	const aiMesh* mesh = assimpScene->mMeshes[0];

	// TODO: interleaved buffer data

	if(mesh->HasPositions())
	{
		for(int i = 0; i < mesh->mNumVertices; ++i)
		{
			positions.push_back(mesh->mVertices[i].x);
			positions.push_back(mesh->mVertices[i].y);
			positions.push_back(mesh->mVertices[i].z);
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
		}

		vbo_indices.create(EGpuBufferType::INDEX_ARRAY, EGpuBufferUsage::STATIC);
		vbo_indices.loadData(indices);

		// size of indices = mesh->mNumFaces * 3

		gpuMesh.setIndexData(vbo_indices, indices.size());
	}

	out_staticRenderable->addMeshMaterialPair(gpuMesh, std::make_shared<PhongMaterial>());

	return true;
}

Matrix4f AssimpModelParser::genModelMatrix(const StaticModel& staticModel)
{
	Matrix4f translationMatrix;
	Matrix4f rotationMatrix;
	Matrix4f scaleMatrix;

	translationMatrix.initTranslation(staticModel.getPosition());
	rotationMatrix.initRotation(staticModel.getOrientation());
	scaleMatrix.initScale(staticModel.getScale());

	return translationMatrix.mul(rotationMatrix).mul(scaleMatrix);
}