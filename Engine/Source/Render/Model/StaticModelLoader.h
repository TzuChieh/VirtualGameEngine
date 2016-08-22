#pragma once

#include "Common/logging.h"

#include <memory>

DECLARE_LOG_SENDER_EXTERN(StaticModelLoader);

namespace xe
{

class ModelParser;
class StaticModel;
class StaticRenderable;

// TODO: threading
class StaticModelLoader
{
public:
	bool init(const std::shared_ptr<ModelParser>& modelParser);

	bool load(const StaticModel& staticModel, StaticRenderable* out_staticRenderable) const;

private:
	std::shared_ptr<ModelParser> m_modelParser;
};

}