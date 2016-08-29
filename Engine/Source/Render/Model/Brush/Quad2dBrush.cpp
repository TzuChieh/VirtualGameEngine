#include "Quad2dBrush.h"
#include "Render/Model/GpuBufferObject.h"

#include <vector>
#include <iostream>

DEFINE_LOG_SENDER(Quad2dBrush);

using namespace ve;

Quad2dBrush::Quad2dBrush(const uint32 positionGpuAccessIndex) : 
	m_positionGpuAccessIndex(positionGpuAccessIndex)
{

}

Quad2dBrush::~Quad2dBrush()
{

}

bool Quad2dBrush::loadBrushData()
{
	std::vector<float32> positions { 1,  1, // (0) upper-right
	                                -1,  1, // (1) upper-left
	                                -1, -1, // (2) lower-left
	                                 1, -1};// (3) lower-right

	// CCW order, 2 triangles
	std::vector<uint32> indices {0, 1, 2, 0, 2, 3};

	GpuBufferObject positionBuffer;
	GpuBufferObject indexBuffer;

	if(!positionBuffer.create(EGpuBufferType::GENERAL_ARRAY, EGpuBufferUsage::STATIC))
	{
		ENGINE_LOG(Quad2dBrush, LogLevel::RECOVERABLE_ERROR, "position buffer creation failed");
		return false;
	}

	if(!indexBuffer.create(EGpuBufferType::INDEX_ARRAY, EGpuBufferUsage::STATIC))
	{
		ENGINE_LOG(Quad2dBrush, LogLevel::RECOVERABLE_ERROR, "index buffer creation failed");
		return false;
	}

	positionBuffer.loadData(positions);
	indexBuffer.loadData(indices);

	setIndexData(indexBuffer, indices.size());
	addVertexData(positionBuffer, m_positionGpuAccessIndex);
	setVertexDataLocator(m_positionGpuAccessIndex, m_positionGpuAccessIndex, 2, 0, 0);

	setDrawingGenre(EDrawingGenre::TRIANGLES);

	//std::cout << "Quad2dBrush loading complete" << std::endl;

	return true;
}