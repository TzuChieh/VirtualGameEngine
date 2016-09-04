#pragma once

#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"
#include "Common/logging.h"

#include <vector>

DECLARE_LOG_SENDER_EXTERN(GpuBufferRes);

namespace ve
{

enum class EGpuBufferType : GLenum;
enum class EGpuBufferUsage : GLenum;
enum class EGpuBufferDataType : GLenum;

class GpuBufferRes final
{
public:
	GpuBufferRes(const EGpuBufferType bufferType, const EGpuBufferUsage bufferUsage);
	~GpuBufferRes();

	// forbid copying
	GpuBufferRes(const GpuBufferRes& other) = delete;
	GpuBufferRes& operator = (const GpuBufferRes& rhs) = delete;

	void loadData(const EGpuBufferDataType type, const uint32 length, const uint32 numDatumElements, const void* data);

	void bind() const;
	void unbind() const;

	EGpuBufferType     getBufferType()     const;
	EGpuBufferUsage    getBufferUsage()    const;
	EGpuBufferDataType getBufferDataType() const;

	uint32 sizeofBufferDataTypeInBytes() const;
	uint32 numDatumElements() const;

	GLuint getGlHandle() const;

private:
	GLuint m_bufferHandle;

	EGpuBufferType     m_gpuBufferType;
	EGpuBufferUsage    m_gpuBufferUsage;
	EGpuBufferDataType m_gpuBufferDataType;

	uint32 m_numDatumElements;

private:
	static uint32 sizeofInBytes(const EGpuBufferDataType type);
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