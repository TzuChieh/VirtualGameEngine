#pragma once

#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"
#include "GpuBufferRes.h"
#include "Common/logging.h"

#include <vector>
#include <memory>
#include <array>
#include <utility>

DECLARE_LOG_SENDER_EXTERN(GpuMeshRes);

namespace ve
{

enum class EDrawingGenre : uint32;
enum class EDataPackingMode : uint32;

class GpuMeshRes final
{
public:
	GpuMeshRes();
	~GpuMeshRes();

	// forbid copying
	GpuMeshRes(const GpuMeshRes& other) = delete;
	GpuMeshRes& operator = (const GpuMeshRes& rhs) = delete;

	void bind() const;
	void unbind() const;
	void draw() const;

	void setIndexData(const std::shared_ptr<GpuBufferRes>& indexData, const uint32 numIndices);
	void addVertexData(const std::shared_ptr<GpuBufferRes>& vertexData, const int32 accessId);
	bool hasIndexData() const;

	void setDrawingGenre(const EDrawingGenre drawingGenre);
	void setVertexDataLocator(const uint32 accessId, const uint32 gpuAccessIndex, 
	                          const EDataPackingMode packingMode, 
	                          uint32 numOffsetBytes);

	std::shared_ptr<GpuBufferRes> getVertexData(const int32 accessId) const;

private:
	GLuint m_vertexArrayHandle;

	std::vector<std::pair<int32, std::shared_ptr<GpuBufferRes>>> m_gpuVertexResources;
	std::shared_ptr<GpuBufferRes> m_gpuIndexResource;

	uint32 m_numIndices;
	EDrawingGenre m_drawingGenre;

	bool isVertexDataAccessIdUsed(const int32 accessId) const;
};

enum class EDrawingGenre : uint32
{
	TRIANGLES = GL_TRIANGLES
};

enum class EDataPackingMode : uint32
{
	SEPARATED, 
	INTERLEAVED
};

}