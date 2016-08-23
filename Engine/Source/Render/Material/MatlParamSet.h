#pragma once

namespace xe
{

class MatlParamSet
{
public:
	virtual ~MatlParamSet() = 0;

	virtual void reset() = 0;
};

}