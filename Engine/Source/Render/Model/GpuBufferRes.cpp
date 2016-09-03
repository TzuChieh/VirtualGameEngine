#include "GpuBufferRes.h"

#include <iostream>

#define OPENGL_DEFAULT_BUFFER_HANDLE 0

DEFINE_LOG_SENDER(GpuBufferRes);

using namespace ve;

GpuBufferRes::GpuBufferRes(EGpuBufferType bufferType, EGpuBufferUsage bufferUsage) :
	m_gpuBufferType(bufferType),
	m_gpuBufferUsage(bufferUsage),
	m_gpuBufferDataType(EGpuBufferDataType::UNKNOWN)
{
	glGenBuffers(1, &m_bufferHandle);
}

GpuBufferRes::~GpuBufferRes()
{
	glDeleteBuffers(1, &m_bufferHandle);
}

void GpuBufferRes::loadData(const EGpuBufferDataType type, const uint32 length, const uint32 numDatumElements, const void* data)
{
	m_gpuBufferDataType = type;
	m_numDatumElements = numDatumElements;

	GLsizeiptr numDataBytes = static_cast<GLsizeiptr>(length * sizeofInBytes(type));

	bind();
	glBufferData(static_cast<GLenum>(m_gpuBufferType),
	             numDataBytes, data,
	             static_cast<GLenum>(m_gpuBufferUsage));
	unbind();
}

void GpuBufferRes::bind() const
{
	glBindBuffer(static_cast<GLenum>(m_gpuBufferType), m_bufferHandle);
}

void GpuBufferRes::unbind() const
{
	glBindBuffer(static_cast<GLenum>(m_gpuBufferType), OPENGL_DEFAULT_BUFFER_HANDLE);
}

EGpuBufferType GpuBufferRes::getBufferType() const
{
	return m_gpuBufferType;
}

EGpuBufferUsage GpuBufferRes::getBufferUsage() const
{
	return m_gpuBufferUsage;
}

EGpuBufferDataType GpuBufferRes::getBufferDataType() const
{
	return m_gpuBufferDataType;
}

uint32 GpuBufferRes::sizeofBufferDataTypeInBytes() const
{
	return GpuBufferRes::sizeofInBytes(m_gpuBufferDataType);
}

uint32 GpuBufferRes::numDatumElements() const
{
	return m_numDatumElements;
}

GLuint GpuBufferRes::getGlHandle() const
{
	return m_bufferHandle;
}

uint32 GpuBufferRes::sizeofInBytes(const EGpuBufferDataType type)
{
	switch(type)
	{
	case EGpuBufferDataType::FLOAT_32:        return 4;
	case EGpuBufferDataType::UNSIGNED_INT_32: return 4;

	default:
		ENGINE_LOG(GpuBufferRes, LogLevel::NOTE_WARNING, "at sizeofInBytes(), specified data type is unknown, 0 is returned");
		return 0;
	}
}