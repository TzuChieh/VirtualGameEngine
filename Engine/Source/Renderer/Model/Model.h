#pragma once

namespace xe
{

class Model
{
public:
	virtual ~Model() = 0;

	virtual bool load() = 0;
};

}