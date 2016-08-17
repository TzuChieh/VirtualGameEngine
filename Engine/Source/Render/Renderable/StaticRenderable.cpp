#include "StaticRenderable.h"
#include "Render/Material/Material.h"
#include "Render/Model/GpuMesh.h"

#include <iostream>

using namespace xe;

StaticRenderable::~StaticRenderable()
{

}

void StaticRenderable::addMeshMaterialPair(const GpuMesh& gpuMesh, const std::shared_ptr<Material>& material)
{
	m_meshMaterialPairs.push_back(std::make_pair(gpuMesh, material));
}

const std::pair<GpuMesh, std::shared_ptr<Material>>& StaticRenderable::getMeshMaterialPair(const uint32 index) const
{
	if(index >= m_meshMaterialPairs.size())
	{
		std::cerr << "StaticRenderable Warning: at getMeshMaterialPair(), index overflow" << std::endl;
	}

	return m_meshMaterialPairs[index];
}

uint32 StaticRenderable::numMeshMaterialPairs() const
{
	return m_meshMaterialPairs.size();
}

void StaticRenderable::setOriginatedModelName(const std::string originatedModelName)
{
	m_originatedModelName = originatedModelName;
}

const std::string& StaticRenderable::getOriginatedModelName() const
{
	return m_originatedModelName;
}