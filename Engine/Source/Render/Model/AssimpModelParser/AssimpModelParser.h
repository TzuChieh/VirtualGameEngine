#pragma once

#include "Render/Model/ModelParser.h"
#include "Math/Matrix4f.h"

#include <assimp/importer.hpp>

#include <string>

namespace ve
{

class AssimpModelParser : public ModelParser
{
public:
	AssimpModelParser();
	virtual ~AssimpModelParser() override;

	virtual bool load(const StaticModel& staticModel, StaticRenderable* out_staticRenderable) override;

private:
	Assimp::Importer m_assimpImporter;

private:
	static Matrix4f genModelMatrix(const StaticModel& staticModel);
};

}