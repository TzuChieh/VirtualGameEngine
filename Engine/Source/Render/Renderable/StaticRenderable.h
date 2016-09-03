#pragma once

#include "Common/type.h"
#include "Renderable.h"
#include "Render/Model/GpuMesh.h"
#include "Math/Matrix4f.h"
#include "Common/logging.h"

#include <vector>
#include <utility>
#include <memory>
#include <string>

DECLARE_LOG_SENDER_EXTERN(StaticRenderable);

namespace ve
{

class Material;

class StaticRenderable : public Renderable
{
public:
	StaticRenderable();
	virtual ~StaticRenderable() override;

	void addMeshMaterialPair(const GpuMesh& gpuMesh, const std::shared_ptr<Material>& material);
	void setOriginatedModelName(const std::string& originatedModelName);
	void setModelMatrix(const Matrix4f modelMatrix);

	uint32 numMeshMaterialPairs() const;

	const std::string& getOriginatedModelName() const;
	const std::pair<GpuMesh, std::shared_ptr<Material>>& getMeshMaterialPair(const uint32 index) const;
	const Matrix4f& getModelMatrix() const;

	void clearAll();

private:
	std::string m_originatedModelName;
	std::vector<std::pair<GpuMesh, std::shared_ptr<Material>>> m_meshMaterialPairs;

	Matrix4f m_modelMatrix;
};

}