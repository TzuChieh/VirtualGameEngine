#include "GBufferShadingPass.h"
#include "Render/Command/GpuCommandQueue.h"
#include "Render/Camera.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/Renderable/StaticRenderableContainer.h"

using namespace ve;

void GBufferShadingPass::fetchRequiredData(const Camera& camera, const StaticRenderableContainer& renderables)
{
	Matrix4f vpMatrix(camera.getViewProjectionMatrix());

	//renderables.
}

void GBufferShadingPass::genRenderCommands(GpuCommandQueue* out_renderCommandQueue) const
{

}
