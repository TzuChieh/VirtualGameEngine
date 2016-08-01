#include "GpuMesh.h"

#include <iostream>

using namespace xe;

GpuMesh::GpuMesh()
	: m_drawingGenre(EDrawingGenre::UNKNOWN)
{
	
}

GpuMesh::~GpuMesh()
{
	if(m_vertexArrayObjectHandle.unique())
	{
		glDeleteVertexArrays(1, m_vertexArrayObjectHandle.get());

		std::cout << "gpu vertex array object deleted" << std::endl;
	}
}

bool GpuMesh::create()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	m_vertexArrayObjectHandle = std::make_shared<GLuint>(vao);

	// TODO: check error
	return true;
}

void GpuMesh::draw() const
{
	bind();

	if(isIndexed())
	{
		glDrawElements(static_cast<GLenum>(m_drawingGenre),
		               static_cast<GLsizei>(m_numIndices),
		               static_cast<GLenum>(m_gpuIndexBufferObject.getBufferDataType()), 0);
	}
	else
	{
		std::cerr << "GpuMesh Warning: in draw(), not implemented!" << std::endl;
	}

	unbind();
}

//void GpuMesh::shareGpuBufferWith(GpuMesh* other) const
//{
//	other->m_gpuBufferObjectIndexMap = m_gpuBufferObjectIndexMap;
//}

void GpuMesh::setIndexData(const GpuBufferObject& indexData, uint32 numIndices)
{
	if(indexData.getBufferType() != EGpuBufferType::INDEX_ARRAY)
	{
		std::cerr << "MeshResource Warning: in addIndexData(), non-index data is specified" << std::endl;
		return;
	}

	m_gpuIndexBufferObject = indexData;
	m_numIndices = numIndices;

	bind();
	m_gpuIndexBufferObject.bind();
	unbind();

	m_gpuIndexBufferObject.unbind();
}

void GpuMesh::addVertexData(const GpuBufferObject& vertexData, uint32 accessIndex)
{
	m_gpuBufferObjects[accessIndex] = vertexData;
}

void GpuMesh::setVertexDataLocator(uint32 accessIndex,
                                   uint32 gpuAccessIndex,
                                   uint32 numDatumElements,
                                   uint32 numVertexBytes,
                                   uint32 numOffsetBytes)
{
	if(m_gpuBufferObjects[accessIndex].isEmpty())
	{
		std::cerr << "GpuMesh Warning: in setVertexDataLocator(), target GpuBufferObject is empty" << std::endl;
		return;
	}

	bind();
	m_gpuBufferObjects[accessIndex].bind();

	glEnableVertexAttribArray(static_cast<GLenum>(gpuAccessIndex));
	glVertexAttribPointer(static_cast<GLenum>(gpuAccessIndex),
	                      static_cast<GLenum>(numDatumElements),
	                      static_cast<GLenum>(m_gpuBufferObjects[accessIndex].getBufferDataType()),
	                      GL_FALSE,
	                      static_cast<GLenum>(numVertexBytes),
	                      static_cast<char*>(0) + numOffsetBytes);

	unbind();

	m_gpuBufferObjects[accessIndex].unbind();
}

bool GpuMesh::isIndexed() const
{
	return !m_gpuIndexBufferObject.isEmpty();
}

void GpuMesh::setDrawingGenre(EDrawingGenre drawingGenre)
{
	m_drawingGenre = drawingGenre;
}

void GpuMesh::bind() const
{
	glBindVertexArray(*m_vertexArrayObjectHandle);
}

void GpuMesh::unbind() const
{
	glBindVertexArray(0);
}