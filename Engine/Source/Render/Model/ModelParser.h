#pragma once

namespace ve
{

class StaticModel;
class StaticRenderable;

class ModelParser
{
public:
	virtual ~ModelParser() = 0;

	virtual bool load(const StaticModel& staticModel, StaticRenderable* out_staticRenderable) = 0;
};

}