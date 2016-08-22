#include "StaticModelLoader.h"
#include "ModelParser.h"

DEFINE_LOG_SENDER(StaticModelLoader);

using namespace xe;

bool StaticModelLoader::init(const std::shared_ptr<ModelParser>& modelParser)
{
	if(!modelParser)
	{
		ENGINE_LOG(StaticModelLoader, LogLevel::SEVERE_ERROR, "at init(), modelParser is null");
		return false;
	}

	m_modelParser = modelParser;
	
	return true;
}

bool StaticModelLoader::load(const StaticModel& staticModel, StaticRenderable* out_staticRenderable) const
{
	return m_modelParser->load(staticModel, out_staticRenderable);
}
