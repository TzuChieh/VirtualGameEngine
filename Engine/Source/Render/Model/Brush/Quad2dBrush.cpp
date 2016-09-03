#include "Quad2dBrush.h"
#include "Render/Model/GpuBuffer.h"
#include "Render/Model/GpuBufferRes.h"

#include <vector>
#include <iostream>
#include <memory>

DEFINE_LOG_SENDER(Quad2dBrush);

using namespace ve;

Quad2dBrush::Quad2dBrush(const uint32 positionGpuAccessIndex) : 
	Brush(), 
	m_positionGpuAccessIndex(positionGpuAccessIndex)
{
	loadPositionData();
}

Quad2dBrush::~Quad2dBrush() = default;

bool Quad2dBrush::loadPositionData()
{
	std::vector<float32> positions { 1,  1, // (0) upper-right
	                                -1,  1, // (1) upper-left
	                                -1, -1, // (2) lower-left
	                                 1, -1};// (3) lower-right

	// CCW order, 2 triangles
	std::vector<uint32> indices {0, 1, 2, 0, 2, 3};

	GpuBuffer positionBuffer(std::make_shared<GpuBufferRes>(EGpuBufferType::GENERAL_ARRAY, EGpuBufferUsage::STATIC));
	GpuBuffer indexBuffer(std::make_shared<GpuBufferRes>(EGpuBufferType::INDEX_ARRAY, EGpuBufferUsage::STATIC));

	positionBuffer.loadData(positions, 2);
	indexBuffer.loadData(indices, 1);

	setIndexData(indexBuffer, indices.size());
	addVertexData(positionBuffer, m_positionGpuAccessIndex);
	setVertexDataLocatorSeparated(m_positionGpuAccessIndex, m_positionGpuAccessIndex);

	setDrawingGenre(EDrawingGenre::TRIANGLES);\

	return true;
}

bool Quad2dBrush::load2dTexureCoordinateData(const uint32 texCoordGpuAccessIndex)
{
	if(texCoordGpuAccessIndex == m_positionGpuAccessIndex)
	{
		ENGINE_LOG(Quad2dBrush, LogLevel::NOTE_WARNING, 
		           "at load2dTexureCoordinateData(), specified texCoord index is the same as position's");
	}

	std::vector<float32> texCoords {1, 1, // (0) upper-right
	                                0, 1, // (1) upper-left
	                                0, 0, // (2) lower-left
	                                1, 0};// (3) lower-right

	GpuBuffer texCoordBuffer(std::make_shared<GpuBufferRes>(EGpuBufferType::GENERAL_ARRAY, EGpuBufferUsage::STATIC));

	texCoordBuffer.loadData(texCoords, 2);

	addVertexData(texCoordBuffer, texCoordGpuAccessIndex);
	setVertexDataLocatorSeparated(texCoordGpuAccessIndex, texCoordGpuAccessIndex);

	return true;
}