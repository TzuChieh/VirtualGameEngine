#pragma once

#include "Model.h"

#include <string>

namespace xe
{

class AssimpModel : public Model
{
public:
	AssimpModel(const std::string& fullFilename);
	virtual ~AssimpModel() override;

	virtual bool load() override;

private:
	std::string m_fullFilename;
};

}