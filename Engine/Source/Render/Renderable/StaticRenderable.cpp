#include "StaticRenderable.h"
#include "Render/Material/Material.h"
#include "Render/Model/GpuMesh.h"

#include <iostream>

DEFINE_LOG_SENDER(StaticRenderable);

using namespace ve;

StaticRenderable::StaticRenderable()
{
	m_modelMatrix.initIdentity();
}

StaticRenderable::~StaticRenderable()
{
	// debug
	/*for(uint32 i = 0; i < m_meshMaterialPairs.size(); i++)
	{
		std::cerr << m_meshMaterialPairs[i].first.isIndexed() << std::endl;
		std::cerr << m_meshMaterialPairs[i].second.unique() << std::endl;
	}*/
}

void StaticRenderable::addMeshMaterialPair(const GpuMesh& gpuMesh, const std::shared_ptr<Material>& material)
{
	if(!gpuMesh.hasResource())
	{
		ENGINE_LOG(StaticRenderable, LogLevel::NOTE_WARNING, "at addMeshMaterialPair(), gpuMesh has no resource");
		return;
	}

	m_meshMaterialPairs.push_back(std::make_pair(gpuMesh, material));
}

const std::pair<GpuMesh, std::shared_ptr<Material>>& StaticRenderable::getMeshMaterialPair(const uint32 index) const
{
	if(index >= m_meshMaterialPairs.size())
	{
		ENGINE_LOG(StaticRenderable, LogLevel::NOTE_WARNING, "at getMeshMaterialPair(), index overflow");
	}

	return m_meshMaterialPairs[index];
}

uint32 StaticRenderable::numMeshMaterialPairs() const
{
	return m_meshMaterialPairs.size();
}

void StaticRenderable::setOriginatedModelName(const std::string& originatedModelName)
{
	m_originatedModelName = originatedModelName;
}

const std::string& StaticRenderable::getOriginatedModelName() const
{
	return m_originatedModelName;
}

void StaticRenderable::clearAll()
{
	m_originatedModelName = std::string();
	m_meshMaterialPairs.clear();
}

void StaticRenderable::setModelMatrix(const Matrix4f modelMatrix)
{
	m_modelMatrix = modelMatrix;
}

const Matrix4f& StaticRenderable::getModelMatrix() const
{
	return m_modelMatrix;
}