#pragma once

#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"

#include <memory>
#include <vector>

namespace xe
{

enum class EGpuBufferType : GLenum;
enum class EGpuBufferUsage : GLenum;
enum class EGpuBufferDataType : GLenum;

class GpuBufferObject
{
public:
	GpuBufferObject();
	~GpuBufferObject();

	bool create(EGpuBufferType bufferType, EGpuBufferUsage bufferUsage);

	void loadData(const std::vector<float32>& data);
	void loadData(const std::vector<uint32>& data);

	void bind() const;
	void unbind() const;

	bool isEmpty() const;

	EGpuBufferType     getBufferType()     const;
	EGpuBufferUsage    getBufferUsage()    const;
	EGpuBufferDataType getBufferDataType() const;

private:
	std::shared_ptr<GLuint> m_bufferHandle;
	EGpuBufferType     m_gpuBufferType;
	EGpuBufferUsage    m_gpuBufferUsage;
	EGpuBufferDataType m_gpuBufferDataType;
};

enum class EGpuBufferType : GLenum
{
	UNKNOWN = 0,
	GENERAL_ARRAY = GL_ARRAY_BUFFER,
	INDEX_ARRAY = GL_ELEMENT_ARRAY_BUFFER
};

enum class EGpuBufferUsage : GLenum
{
	UNKNOWN = 0,
	STATIC = GL_STATIC_DRAW
};

enum class EGpuBufferDataType : GLenum
{
	UNKNOWN = 0,
	FLOAT_32 = GL_FLOAT,
	UNSIGNED_INT_32 = GL_UNSIGNED_INT
};

}