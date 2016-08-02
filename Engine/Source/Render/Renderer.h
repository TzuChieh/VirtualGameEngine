#pragma once

#include "Resource/Component/ComponentHandle.h"

#include <memory>

namespace xe
{

class CCamera;

class Renderer
{
	friend class Engine;

public:
	virtual ~Renderer() = 0;

	virtual void render() = 0;

	virtual std::shared_ptr<ComponentHandle> addCamera(const CCamera& camera) = 0;

private:
	virtual bool init() = 0;
	virtual void decompose() = 0;
};

}