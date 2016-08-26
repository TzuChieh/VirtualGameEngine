#include "StaticRenderableContainer.h"

#include <iostream>

using namespace ve;

void StaticRenderableContainer::add(const StaticRenderable& staticRenderable)
{
	m_staticRenderables.push_back(staticRenderable);
}

// note the current implementation do "NOT" retain renderables' order; also the operation
// is O(N) now
void StaticRenderableContainer::removeByOriginatedModelName(const std::string& originatedModelName)
{
	uint32 index = 0;

	while(index < m_staticRenderables.size())
	{
		if(m_staticRenderables[index].getOriginatedModelName() == originatedModelName)
		{
			// overwrite the target (which is going to remove) renderable with the last renderable
			m_staticRenderables[index] = m_staticRenderables.back();

			// drop the last renderable
			m_staticRenderables.pop_back();

			// no "index++" since we hadn't checked the last renderable yet
			continue;
		}

		index++;
	}
}

void StaticRenderableContainer::removeAll()
{
	m_staticRenderables.clear();
}

uint32 StaticRenderableContainer::numStaticRenderables() const
{
	return m_staticRenderables.size();
}

const StaticRenderable& StaticRenderableContainer::getStaticRenderable(const uint32 index) const
{
	if(index >= m_staticRenderables.size())
	{
		std::cerr << "StaticRenderableContainer Warning: at getStaticRenderable(), index overflow" << std::endl;
	}

	return m_staticRenderables[index];
}