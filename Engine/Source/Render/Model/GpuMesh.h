#pragma once

#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"
#include "GpuBufferObject.h"

#include <vector>
#include <memory>
#include <array>

namespace xe
{

enum class EDrawingGenre : GLenum
{
	UNKNOWN   = 0,
	TRIANGLES = GL_TRIANGLES
};

enum class EGpuMeshProperties : uint32
{
	MAX_INDEX = 20
};

class GpuMesh
{
public:
	GpuMesh();
	~GpuMesh();

	bool create();

	void bind() const;
	void unbind() const;
	void draw() const;

	//void shareGpuBufferWith(GpuMesh* other) const;
	void setIndexData(const GpuBufferObject& indexData, uint32 numIndices);
	void addVertexData(const GpuBufferObject& vertexData, uint32 accessIndex);
	bool isIndexed() const;

	void setDrawingGenre(EDrawingGenre drawingGenre);
	void setVertexDataLocator(uint32 accessIndex, 
	                          uint32 gpuAccessIndex,
							  uint32 numDatumElements,
							  uint32 numVertexBytes,
							  uint32 numOffsetBytes);

private:
	std::shared_ptr<GLuint> m_vertexArrayObjectHandle;

	std::array<GpuBufferObject, static_cast<uint32>(EGpuMeshProperties::MAX_INDEX)> m_gpuBufferObjects;
	GpuBufferObject m_gpuIndexBufferObject;
	uint32 m_numIndices;

	EDrawingGenre m_drawingGenre;
};

}