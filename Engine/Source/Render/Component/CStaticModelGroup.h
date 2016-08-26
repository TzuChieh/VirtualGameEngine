#pragma once

#include "Common/type.h"
#include "Resource/Component/Component.h"
#include "Render/Model/StaticModel.h"

#include <unordered_map>
#include <memory>
#include <string>
#include <queue>

namespace ve
{

class CStaticModelGroup : public Component
{
public:
	CStaticModelGroup() = default;
	virtual ~CStaticModelGroup() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;

	void queueForLoading(const std::string& modelName, const StaticModel& staticModel);
	bool dequeueToLoad(StaticModel* out_staticModel);

private:
	std::queue<StaticModel> m_queueForLoadingStaticModels;
	std::unordered_map<std::string, std::shared_ptr<StaticModel>> m_staticModelsNameMap;
};

}