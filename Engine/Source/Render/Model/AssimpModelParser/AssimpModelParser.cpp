#include "AssimpModelParser.h"
#include "Render/Model/StaticModel.h"
#include "Render/Renderable/StaticRenderable.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace xe;

AssimpModelParser::AssimpModelParser()
{

}

AssimpModelParser::~AssimpModelParser()
{

}

bool AssimpModelParser::load(const StaticModel& staticModel, StaticRenderable* out_staticRenderable)
{
	return true;
}