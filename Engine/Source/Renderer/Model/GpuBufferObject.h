#pragma once

#include "Common/type.h"
#include "Core/graphicsApi.h"

#include <memory>
#include <vector>

namespace xe
{

enum class GpuBufferType : GLenum
{
	UNKNOWN       = 0,
	GENERAL_ARRAY = GL_ARRAY_BUFFER,
	INDEX_ARRAY   = GL_ELEMENT_ARRAY_BUFFER
};

enum class GpuBufferUsage : GLenum
{
	UNKNOWN = 0,
	STATIC  = GL_STATIC_DRAW
};

class GpuBufferObject
{
public:
	GpuBufferObject();
	~GpuBufferObject();

	bool create(GpuBufferType bufferType, GpuBufferUsage bufferUsage);
	void loadData(const std::vector<float32>& data);
	void loadData(const std::vector<uint32>& data);
	void use() const;

private:
	std::shared_ptr<GLuint> m_bufferHandle;
	GpuBufferType  m_gpuBufferType;
	GpuBufferUsage m_gpuBufferUsage;
};

}