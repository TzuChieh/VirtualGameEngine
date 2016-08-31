#include "Texture2D.h"
#include "LdrRectImage.h"
#include "Texture2DRes.h"

DEFINE_LOG_SENDER(Texture2D);

using namespace ve;

Texture2D::Texture2D() : 
	m_textureResource(nullptr)
{

}

Texture2D::Texture2D(const std::shared_ptr<Texture2DRes>& resource) : 
	m_textureResource(resource)
{
	ENGINE_LOG_IF(m_textureResource == nullptr, Texture2D, LogLevel::NOTE_WARNING,
	              "at ctor(), specified resource is null");
}

bool Texture2D::load(const LdrRectImage& ldrRectImage)
{
	ENGINE_LOG(Texture2D, LogLevel::NOTE_MESSAGE, "loading image (" + ldrRectImage.getName() + ")");

	if(!hasResource())
	{
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR, "resource is empty");
		return false;
	}

	if(!ldrRectImage.isDataValid())
	{
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR, "image (" + ldrRectImage.getName() + ") data is invalid");
		return false;
	}

	EDataFormat dataFormat;
	ETextureDataFormat textureDataFormat;

	if(ldrRectImage.getNumComponents() == 3)
	{
		dataFormat = EDataFormat::RGB_8_BITS_EACH;
		textureDataFormat = ETextureDataFormat::RGB_8_BITS_EACH;
	}
	else if(ldrRectImage.getNumComponents() == 4)
	{
		dataFormat = EDataFormat::RGBA_8_BITS_EACH;
		textureDataFormat = ETextureDataFormat::RGBA_8_BITS_EACH;
	}
	else
	{
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR,
		           "image (" + ldrRectImage.getName() + ") pixel data have " +
		           std::to_string(ldrRectImage.getNumComponents()) +
		           " components which is unsupported");
		return false;
	}
	
	const bool isLoadingSuccess = m_textureResource->loadData(ldrRectImage.getWidthPx(), ldrRectImage.getHeightPx(), 
	                                                          dataFormat, ldrRectImage.getImageData(),
	                                                          0, textureDataFormat);

	if(!isLoadingSuccess)
	{
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR,
		           "image (" + ldrRectImage.getName() + ") loading failed");
	}

	return isLoadingSuccess;
}

bool Texture2D::create(const uint32 widthPx, const uint32 heightPx, const ETextureDataFormat dataFormat)
{
	ENGINE_LOG(Texture2D, LogLevel::NOTE_MESSAGE, "creating render target");

	if(!hasResource())
	{
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR, "resource is empty");
		return false;
	}

	if(!m_textureResource->asRenderTarget(widthPx, heightPx, dataFormat))
	{
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR, "creation failed");
		return false;
	}

	return true;
}

void Texture2D::use() const
{
	m_textureResource->bind();
}

uint32 Texture2D::getWidthPx() const
{
	return m_textureResource->getWidthPx();
}

uint32 Texture2D::getHeightPx() const
{
	return m_textureResource->getHeightPx();
}

std::shared_ptr<Texture2DRes> Texture2D::getResource() const
{
	return m_textureResource;
}

bool Texture2D::hasResource() const
{
	return m_textureResource != nullptr;
}

void Texture2D::setFilterMode(const ETextureFilterMode filterMode)
{
	m_textureResource->setTextureFilterMode(filterMode);
}

bool Texture2D::operator == (const Texture2D& other) const
{
	if(!hasResource() || !other.hasResource())
	{
		return false;
	}

	return (*m_textureResource) == (*other.m_textureResource);
}

bool Texture2D::operator != (const Texture2D& other) const
{
	return !(*this == other);
}