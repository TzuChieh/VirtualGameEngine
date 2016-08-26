#include "LdrRectImage.h"

#include "Common/ThirdPartyLib/stbImage.h"

#include <iostream>

DEFINE_LOG_SENDER(LdrRectImage);

using namespace ve;

LdrRectImage::LdrRectImage() : 
	m_imageData(nullptr)
{

}

LdrRectImage::~LdrRectImage()
{

}

bool LdrRectImage::load(const std::string& fullFilename)
{
	ENGINE_LOG(LdrRectImage, LogLevel::NOTE_MESSAGE, "loading image (" + fullFilename + ")");

	m_name = fullFilename;

	// variables to retrieve image info from stbi_load()
	int widthPx;
	int heightPx;
	int numComponents;

	// the last parameter is "0" since we want the actual components the image has;
	// replace "0" with "1" ~ "4" to force that many components per pixel
	stbi_uc* data = stbi_load(fullFilename.c_str(), &widthPx, &heightPx, &numComponents, 0);

	if(data == NULL)
	{
		ENGINE_LOG(LdrRectImage, LogLevel::RECOVERABLE_ERROR, stbi_failure_reason());
		return false;
	}

	const uint32 dataSize = widthPx * heightPx * numComponents;
	m_imageData = std::make_shared<std::vector<uint8>>(dataSize, 0);

	for(uint32 i = 0; i < dataSize; i++)
	{
		(*m_imageData)[i] = static_cast<uint8>(data[i]);
	}

	setDimensionPx(widthPx, heightPx, numComponents);

	return true;
}

bool LdrRectImage::isDataValid() const
{
	return m_imageData != nullptr;
}

std::string LdrRectImage::getName() const
{
	return m_name;
}

const uint8* LdrRectImage::getImageData() const
{
	return m_imageData->data();
}
