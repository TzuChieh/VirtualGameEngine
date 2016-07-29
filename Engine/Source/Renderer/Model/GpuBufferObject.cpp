#include "GpuBufferObject.h"

#include <iostream>

using namespace xe;

GpuBufferObject::GpuBufferObject()
	: m_gpuBufferType(GpuBufferType::UNKNOWN), 
	  m_gpuBufferUsage(GpuBufferUsage::UNKNOWN)
{

}

GpuBufferObject::~GpuBufferObject()
{
	if(m_bufferHandle.unique())
	{
		glDeleteBuffers(1, m_bufferHandle.get());

		std::cout << "gpu buffer object deleted" << std::endl;
	}
}

bool GpuBufferObject::create(GpuBufferType bufferType, GpuBufferUsage bufferUsage)
{
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
	GLsizeiptr numDataBytes = static_cast<GLsizeiptr>(data.size() * sizeof(float32));

	use();
	glBufferData(static_cast<GLenum>(m_gpuBufferType), 
	             numDataBytes, data.data(), 
	             static_cast<GLenum>(m_gpuBufferUsage));
}

// FIXME: duplicated code
void GpuBufferObject::loadData(const std::vector<uint32>& data)
{
	GLsizeiptr numDataBytes = static_cast<GLsizeiptr>(data.size() * sizeof(float32));

	use();
	glBufferData(static_cast<GLenum>(m_gpuBufferType),
				 numDataBytes, data.data(),
				 static_cast<GLenum>(m_gpuBufferUsage));
}

void GpuBufferObject::use() const
{
	glBindBuffer(static_cast<GLenum>(m_gpuBufferType), *m_bufferHandle);
}