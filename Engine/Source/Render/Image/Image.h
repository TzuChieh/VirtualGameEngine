#pragma once

#include <string>

namespace ve
{

class Image
{
public:
	virtual ~Image();

	virtual bool load(const std::string& fullFilename) = 0;
	virtual std::string getName() const = 0;
};

}