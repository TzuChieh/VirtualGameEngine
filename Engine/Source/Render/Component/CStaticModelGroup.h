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

class StaticModel;

class CStaticModelGroup : public Component
{
public:
	CStaticModelGroup() = default;
	virtual ~CStaticModelGroup() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;

	void addStaticModel(const std::string& modelName, std::shared_ptr<StaticModel> staticModel);

private:
	std::unordered_map<std::string, std::shared_ptr<StaticModel>> m_staticModelsNameMap;
};

}