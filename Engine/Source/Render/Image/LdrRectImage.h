#pragma once

#include "Common/type.h"
#include "RectImage.h"
#include "Common/logging.h"

#include <vector>
#include <memory>

DECLARE_LOG_SENDER_EXTERN(LdrRectImage);

namespace xe
{

class LdrRectImage : public RectImage
{
public:
	LdrRectImage();
	virtual ~LdrRectImage() override;

	virtual bool load(const std::string& fullFilename) override;

private:
	std::shared_ptr<std::vector<uint8>> m_imageData;
};

}