#pragma once

#include "Common/type.h"
#include "GpuMeshRes.h"
#include "Common/logging.h"

#include "Common/ThirdPartyLib/glew.h"

#include <vector>
#include <memory>
#include <array>

DECLARE_LOG_SENDER_EXTERN(GpuMesh);

namespace ve
{

class GpuBuffer;

class GpuMesh
{
public:
	GpuMesh();
	GpuMesh(const std::shared_ptr<GpuMeshRes>& resource);
	virtual ~GpuMesh();

	void draw() const;

	void setIndexData(const GpuBuffer& indexData, const uint32 numIndices);
	void addVertexData(const GpuBuffer& vertexData, const int32 accessId);
	bool isIndexed() const;

	void setDrawingGenre(const EDrawingGenre drawingGenre);
	void setVertexDataLocatorSeparated(const uint32 accessId, const uint32 gpuAccessIndex);
	void setVertexDataLocatorInterleaved(const uint32 accessId, const uint32 gpuAccessIndex, const uint32 numOffsetBytes);

	std::shared_ptr<GpuMeshRes> getResource() const;
	bool hasResource() const;

private:
	std::shared_ptr<GpuMeshRes> m_meshResource;
};

}