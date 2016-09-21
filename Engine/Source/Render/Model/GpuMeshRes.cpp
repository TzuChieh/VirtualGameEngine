#include "GpuMeshRes.h"

#include <iostream>

#define OPENGL_DEFAULT_VERTEX_ARRAY_HANDLE 0

DEFINE_LOG_SENDER(GpuMeshRes);

using namespace ve;

GpuMeshRes::GpuMeshRes() : 
	m_drawingGenre(EDrawingGenre::TRIANGLES)
{
	glGenVertexArrays(1, &m_vertexArrayHandle);
}

GpuMeshRes::~GpuMeshRes()
{
	glDeleteVertexArrays(1, &m_vertexArrayHandle);
}

void GpuMeshRes::draw() const
{
	bind();

	if(hasIndexData())
	{
		glDrawElements(static_cast<GLenum>(m_drawingGenre),
		               static_cast<GLsizei>(m_numIndices),
		               static_cast<GLenum>(m_gpuIndexResource->getBufferDataType()), 0);
	}
	else
	{
		std::cerr << "GpuMesh Warning: in draw(), not implemented yet!" << std::endl;
	}
}

void GpuMeshRes::setIndexData(const std::shared_ptr<GpuBufferRes>& indexData, const uint32 numIndices)
{
	if(indexData->getBufferType() != EGpuBufferType::INDEX_ARRAY)
	{
		std::cerr << "GpuMeshRes Warning: in addIndexData(), non-index data is specified" << std::endl;
		return;
	}

	m_gpuIndexResource = indexData;
	m_numIndices = numIndices;

	bind();
	m_gpuIndexResource->bind();
}

void GpuMeshRes::addVertexData(const std::shared_ptr<GpuBufferRes>& vertexData, const int32 accessId)
{
	if(isVertexDataAccessIdUsed(accessId))
	{
		ENGINE_LOG(GpuMeshRes, LogLevel::NOTE_WARNING, "access ID duplicated");
	}

	m_gpuVertexResources.push_back(std::make_pair(accessId, vertexData));
}

void GpuMeshRes::setVertexDataLocator(const uint32 accessId, const uint32 gpuAccessIndex,
                                      const EDataPackingMode packingMode,
                                      uint32 numOffsetBytes)
{
	if(!isVertexDataAccessIdUsed(accessId))
	{
		ENGINE_LOG(GpuMeshRes, LogLevel::NOTE_WARNING, "at setVertexDataLocator(), access ID refers to nothing");
		return;
	}

	bind();

	const auto& vertexData = getVertexData(accessId);
	vertexData->bind();

	GLsizei numDatumBytes;
	if(packingMode == EDataPackingMode::SEPARATED)
	{
		numDatumBytes = 0;
		numOffsetBytes = 0;
	}
	else
	{
		numDatumBytes = vertexData->numDatumElements() * vertexData->sizeofBufferDataTypeInBytes();
	}

	glEnableVertexAttribArray(static_cast<GLenum>(gpuAccessIndex));
	glVertexAttribPointer(static_cast<GLuint>(gpuAccessIndex),
	                      static_cast<GLint>(vertexData->numDatumElements()),
	                      static_cast<GLenum>(vertexData->getBufferDataType()),
	                      GL_FALSE,
	                      static_cast<GLsizei>(numDatumBytes),
	                      static_cast<char*>(0) + numOffsetBytes);
}

bool GpuMeshRes::hasIndexData() const
{
	return m_gpuIndexResource != nullptr;
}

void GpuMeshRes::setDrawingGenre(const EDrawingGenre drawingGenre)
{
	m_drawingGenre = drawingGenre;
}

void GpuMeshRes::bind() const
{
	glBindVertexArray(m_vertexArrayHandle);
}

void GpuMeshRes::unbind() const
{
	glBindVertexArray(OPENGL_DEFAULT_VERTEX_ARRAY_HANDLE);
}

std::shared_ptr<GpuBufferRes> GpuMeshRes::getVertexData(const int32 accessId) const
{
	for(const auto& vertexResourcePair : m_gpuVertexResources)
	{
		if(vertexResourcePair.first == accessId)
		{
			return vertexResourcePair.second;
		}
	}

	ENGINE_LOG(GpuMeshRes, LogLevel::NOTE_WARNING, "at getVertexData(), access ID refers to nothing");

	return nullptr;
}

bool GpuMeshRes::isVertexDataAccessIdUsed(const int32 accessId) const
{
	for(const auto& vertexResourcePair : m_gpuVertexResources)
	{
		if(vertexResourcePair.first == accessId)
		{
			return true;
		}
	}

	return false;
}