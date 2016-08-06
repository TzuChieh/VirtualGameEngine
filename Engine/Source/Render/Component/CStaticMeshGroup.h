#pragma once

#include "Common/type.h"
#include "Resource/Component/Component.h"
//#include "Render/Model/StaticModel.h"

#include <unordered_map>
#include <memory>
#include <string>

#include <memory>

namespace xe
{

class StaticMesh;

class CStaticMeshGroup : public Component
{
public:
	CStaticMeshGroup() = default;
	virtual ~CStaticMeshGroup() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;

	void addStaticMesh(const std::string& meshName, std::shared_ptr<StaticMesh> staticMesh);

private:
	std::unordered_map<std::string, std::shared_ptr<StaticMesh>> m_staticMeshesNameMap;
};

}