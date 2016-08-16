#pragma once

#include <string>

namespace xe
{

class Image
{
public:
	virtual ~Image();

	virtual bool load(const std::string& fullFilename) = 0;
};

}