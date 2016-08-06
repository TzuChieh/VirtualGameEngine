#pragma once

#include "Render/Renderer.h"
#include "Resource/Component/TIndexedComponentManager.h"
#include "Render/Component/CCamera.h"
#include "Render/Camera.h"
#include "Render/Component/CStaticMeshGroup.h"

namespace xe
{

class TestRenderer : public Renderer
{
public:
	virtual ~TestRenderer() override;

	virtual void render() override;

	virtual std::shared_ptr<ComponentHandle> addCamera(const CCamera& camera) override;
	virtual std::shared_ptr<ComponentHandle> addStaticMeshGroup(const CStaticMeshGroup& staticMeshGroup) override;

private:
	TIndexedComponentManager<CCamera> m_cameraComponents;
	TIndexedComponentManager<CStaticMeshGroup> m_staticMeshGroups;
	Camera m_mainCamera;

	virtual bool init() override;
	virtual void decompose() override;
};

}