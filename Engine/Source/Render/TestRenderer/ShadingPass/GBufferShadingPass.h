#pragma once

#include "Render/Shader/ShaderProgram.h"
#include "Render/Command/RenderCommandSorter.h"
#include "Render/Command/RenderCommandInfo.h"
#include "Render/Command/GpuCommand.h"
#include "Math/Matrix4f.h"

#include <vector>

namespace ve
{

class GpuCommandQueue;
class Camera;
class StaticRenderableContainer;

class GBufferShadingPass
{
public:

	void fetchRequiredData(const Camera& camera, const StaticRenderableContainer& renderables);
	void genRenderCommands(GpuCommandQueue* out_renderCommandQueue) const;

private:
	std::vector<Matrix4f> m_mvpMatrices;
};

}