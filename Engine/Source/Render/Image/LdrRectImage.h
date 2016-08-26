#pragma once

#include "Common/type.h"
#include "RectImage.h"
#include "Common/logging.h"

#include <vector>
#include <memory>
#include <string>

DECLARE_LOG_SENDER_EXTERN(LdrRectImage);

namespace ve
{

class LdrRectImage : public RectImage
{
public:
	LdrRectImage();
	virtual ~LdrRectImage() override;

	virtual bool load(const std::string& fullFilename) override;
	virtual std::string getName() const override;

	bool isDataValid() const;
	const uint8* getImageData() const;

private:
	std::shared_ptr<std::vector<uint8>> m_imageData;
	std::string m_name;
};

}