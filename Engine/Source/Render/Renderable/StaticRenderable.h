#pragma once

#include "Common/type.h"
#include "Renderable.h"
#include "Render/Model/GpuMesh.h"

#include <vector>
#include <utility>
#include <memory>
#include <string>

namespace ve
{

class Material;

class StaticRenderable : public Renderable
{
public:
	virtual ~StaticRenderable() override;

	void addMeshMaterialPair(const GpuMesh& gpuMesh, const std::shared_ptr<Material>& material);
	const std::pair<GpuMesh, std::shared_ptr<Material>>& getMeshMaterialPair(const uint32 index) const;

	uint32 numMeshMaterialPairs() const;

	void setOriginatedModelName(const std::string& originatedModelName);
	const std::string& getOriginatedModelName() const;

	void clearAll();

private:
	std::string m_originatedModelName;
	std::vector<std::pair<GpuMesh, std::shared_ptr<Material>>> m_meshMaterialPairs;
};

}