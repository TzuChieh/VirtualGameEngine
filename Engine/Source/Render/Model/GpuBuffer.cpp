#include "GpuBuffer.h"

#include <iostream>

DEFINE_LOG_SENDER(GpuBuffer);

using namespace ve;

GpuBuffer::GpuBuffer() : 
	m_bufferResource(nullptr)
{

}

GpuBuffer::GpuBuffer(const std::shared_ptr<GpuBufferRes>& resource) : 
	m_bufferResource(resource)
{
	ENGINE_LOG_IF(!hasResource(), GpuBuffer, LogLevel::NOTE_WARNING, "at ctor(), resource is empty");
}

void GpuBuffer::loadData(const std::vector<float32>& data, const uint32 numDatumElements)
{
	m_bufferResource->loadData(EGpuBufferDataType::FLOAT_32, data.size(), numDatumElements, data.data());
}

void GpuBuffer::loadData(const std::vector<uint32>& data, const uint32 numDatumElements)
{
	m_bufferResource->loadData(EGpuBufferDataType::UNSIGNED_INT_32, data.size(), numDatumElements, data.data());
}

void GpuBuffer::use() const
{
	m_bufferResource->bind();
}

std::shared_ptr<GpuBufferRes> GpuBuffer::getResource() const
{
	return m_bufferResource;
}

bool GpuBuffer::hasResource() const
{
	return m_bufferResource != nullptr;
}

EGpuBufferType GpuBuffer::getBufferType() const
{
	return m_bufferResource->getBufferType();
}

EGpuBufferUsage GpuBuffer::getBufferUsage() const
{
	return m_bufferResource->getBufferUsage();
}

EGpuBufferDataType GpuBuffer::getBufferDataType() const
{
	return m_bufferResource->getBufferDataType();
}