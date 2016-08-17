#pragma once

#include "StaticRenderable.h"

#include <vector>

namespace xe
{

class StaticRenderableContainer
{
public:
	void add(const StaticRenderable& staticRenderable);
	void removeByOriginatedModelName(const std::string& originatedModelName);

private:
	std::vector<StaticRenderable> m_staticRenderables;
};

}