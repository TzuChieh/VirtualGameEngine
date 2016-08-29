#include "GpuBufferObject.h"

#include <iostream>

using namespace ve;

GpuBufferObject::GpuBufferObject() : 
	m_gpuBufferType(EGpuBufferType::UNKNOWN), 
	m_gpuBufferUsage(EGpuBufferUsage::UNKNOWN),
	m_gpuBufferDataType(EGpuBufferDataType::UNKNOWN)
{

}

GpuBufferObject::~GpuBufferObject()
{
	// debug
	//std::cerr << "GpuBufferObject dtor called" << std::endl;

	if(m_bufferHandle.unique())
	{
		glDeleteBuffers(1, m_bufferHandle.get());

		std::cout << "gpu buffer object deleted" << std::endl;
	}
}

bool GpuBufferObject::create(EGpuBufferType bufferType, EGpuBufferUsage bufferUsage)
{
	if(m_bufferHandle)
	{
		std::cerr << "GpuBufferObject Error: at create(), GpuBufferObject has already created" << std::endl;
		return false;
	}

	GLuint bufferHandle;
	glGenBuffers(1, &bufferHandle);
	m_bufferHandle = std::make_shared<GLuint>(bufferHandle);

	m_gpuBufferType  = bufferType;
	m_gpuBufferUsage = bufferUsage;

	// FIXME: check error
	return true;
}

// FIXME: duplicated code
void GpuBufferObject::loadData(const std::vector<float32>& data)
{
	m_gpuBufferDataType = EGpuBufferDataType::FLOAT_32;
	GLsizeiptr numDataBytes = static_cast<GLsizeiptr>(data.size() * sizeof(float32));

	bind();
	glBufferData(static_cast<GLenum>(m_gpuBufferType), 
	             numDataBytes, data.data(), 
	             static_cast<GLenum>(m_gpuBufferUsage));
}

// FIXME: duplicated code
void GpuBufferObject::loadData(const std::vector<uint32>& data)
{
	m_gpuBufferDataType = EGpuBufferDataType::UNSIGNED_INT_32;
	GLsizeiptr numDataBytes = static_cast<GLsizeiptr>(data.size() * sizeof(float32));

	bind();
	glBufferData(static_cast<GLenum>(m_gpuBufferType),
	             numDataBytes, data.data(),
	             static_cast<GLenum>(m_gpuBufferUsage));
}

void GpuBufferObject::bind() const
{
	glBindBuffer(static_cast<GLenum>(m_gpuBufferType), *m_bufferHandle);
}

void GpuBufferObject::unbind() const
{
	glBindBuffer(static_cast<GLenum>(m_gpuBufferType), 0);
}

bool GpuBufferObject::isEmpty() const
{
	return m_bufferHandle.use_count() == 0L;
}

EGpuBufferType GpuBufferObject::getBufferType() const
{
	return m_gpuBufferType;
}

EGpuBufferUsage GpuBufferObject::getBufferUsage() const
{
	return m_gpuBufferUsage;
}

EGpuBufferDataType GpuBufferObject::getBufferDataType() const
{
	return m_gpuBufferDataType;
}