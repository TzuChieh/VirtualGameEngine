#include "StaticModelLoader.h"
#include "ModelParser.h"
#include "StaticModel.h"

DEFINE_LOG_SENDER(StaticModelLoader);

using namespace ve;

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
	ENGINE_LOG(StaticModelLoader, LogLevel::NOTE_MESSAGE, "loading <" + staticModel.getFullFilename() + ">");

	return m_modelParser->load(staticModel, out_staticRenderable);
}
