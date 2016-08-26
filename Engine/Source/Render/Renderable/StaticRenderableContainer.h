#pragma once

#include "Common/type.h"
#include "StaticRenderable.h"

#include <vector>

namespace ve
{

class StaticRenderableContainer
{
public:
	void add(const StaticRenderable& staticRenderable);

	void removeByOriginatedModelName(const std::string& originatedModelName);
	void removeAll();

	uint32 numStaticRenderables() const;
	const StaticRenderable& getStaticRenderable(const uint32 index) const;

private:
	std::vector<StaticRenderable> m_staticRenderables;
};

}