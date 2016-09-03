#include "GpuMesh.h"
#include "GpuMeshRes.h"
#include "GpuBuffer.h"

#include <iostream>

DEFINE_LOG_SENDER(GpuMesh);

using namespace ve;

GpuMesh::GpuMesh() : 
	m_meshResource(nullptr)
{
	
}

GpuMesh::GpuMesh(const std::shared_ptr<GpuMeshRes>& resource) : 
	m_meshResource(resource)
{
	ENGINE_LOG_IF(!hasResource(), GpuMesh, LogLevel::NOTE_WARNING, "at ctor(), resource is empty");
}

GpuMesh::~GpuMesh() = default;

void GpuMesh::draw() const
{
	if(!hasResource())
	{
		ENGINE_LOG(GpuMesh, LogLevel::NOTE_WARNING, "at draw(), attempting to use an empty resource");
		return;
	}

	m_meshResource->draw();
}

void GpuMesh::setIndexData(const GpuBuffer& indexData, const uint32 numIndices)
{
	if(!hasResource())
	{
		ENGINE_LOG(GpuMesh, LogLevel::NOTE_WARNING, "at setIndexData(), attempting to use an empty resource");
		return;
	}

	m_meshResource->setIndexData(indexData.getResource(), numIndices);
}

void GpuMesh::addVertexData(const GpuBuffer& vertexData, const int32 accessId)
{
	if(!hasResource())
	{
		ENGINE_LOG(GpuMesh, LogLevel::NOTE_WARNING, "at addVertexData(), attempting to use an empty resource");
		return;
	}

	m_meshResource->addVertexData(vertexData.getResource(), accessId);
}

void GpuMesh::setVertexDataLocatorSeparated(const uint32 accessId, const uint32 gpuAccessIndex)
{
	if(!hasResource())
	{
		ENGINE_LOG(GpuMesh, LogLevel::NOTE_WARNING, "at setVertexDataLocatorSeparated(), attempting to use an empty resource");
		return;
	}

	m_meshResource->setVertexDataLocator(accessId, gpuAccessIndex, EDataPackingMode::SEPARATED, 0);
}

void GpuMesh::setVertexDataLocatorInterleaved(const uint32 accessId, const uint32 gpuAccessIndex, const uint32 numOffsetBytes)
{
	if(!hasResource())
	{
		ENGINE_LOG(GpuMesh, LogLevel::NOTE_WARNING, "at setVertexDataLocatorInterleaved(), attempting to use an empty resource");
		return;
	}

	m_meshResource->setVertexDataLocator(accessId, gpuAccessIndex, EDataPackingMode::INTERLEAVED, numOffsetBytes);
}

bool GpuMesh::isIndexed() const
{
	return m_meshResource->hasIndexData();
}

void GpuMesh::setDrawingGenre(const EDrawingGenre drawingGenre)
{
	m_meshResource->setDrawingGenre(drawingGenre);
} 

std::shared_ptr<GpuMeshRes> GpuMesh::getResource() const
{
	return m_meshResource;
}

bool GpuMesh::hasResource() const
{
	return m_meshResource != nullptr;
}