#pragma once

#include "Render/Renderer.h"
#include "Resource/Component/TIndexedComponentManager.h"
#include "Render/Component/CCamera.h"
#include "Render/Camera.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Render/Renderable/StaticRenderableContainer.h"
#include "Render/TestRenderer/RenderCommandGenerator/TestRcGen.h"
#include "Common/logging.h"

DECLARE_LOG_SENDER_EXTERN(TestRenderer);

namespace xe
{

class TestRenderer : public Renderer
{
public:
	virtual ~TestRenderer() override;

	virtual void render() override;

	virtual std::shared_ptr<ComponentHandle> addCamera(const CCamera& camera) override;
	virtual std::shared_ptr<ComponentHandle> addStaticModelGroup(const CStaticModelGroup& staticModelGroup) override;

private:
	TIndexedComponentManager<CCamera> m_cameraComponents;
	TIndexedComponentManager<CStaticModelGroup> m_staticModelGroups;


	StaticRenderableContainer m_staticRenderableContainer;
	TestRcGen m_testRcGen;

	Camera m_mainCamera;

	virtual bool init() override;
	virtual void decompose() override;
};

}