#pragma once

#include "Renderer/Renderer.h"
#include "Resource/Component/TIndexedComponentManager.h"
#include "Renderer/Component/CCamera.h"

namespace xe
{

class TestRenderer : public Renderer
{
public:
	virtual ~TestRenderer() override;

	virtual void render() override;

	virtual std::shared_ptr<ComponentHandle> addCamera(const CCamera& camera) override;

private:
	TIndexedComponentManager<CCamera> m_cameras;

	virtual bool init() override;
	virtual void decompose() override;
};

}