#pragma once

#include "Common/type.h"
#include "Common/logging.h"
#include "GpuBufferRes.h"

#include <memory>
#include <vector>

DECLARE_LOG_SENDER_EXTERN(GpuBuffer);

namespace ve
{

class GpuBuffer final
{
public:
	GpuBuffer();
	GpuBuffer(const std::shared_ptr<GpuBufferRes>& resource);

	void loadData(const std::vector<float32>& data, const uint32 numDatumElements);
	void loadData(const std::vector<uint32>& data, const uint32 numDatumElements);

	void use() const;

	std::shared_ptr<GpuBufferRes> getResource() const;
	bool hasResource() const;

	EGpuBufferType     getBufferType()     const;
	EGpuBufferUsage    getBufferUsage()    const;
	EGpuBufferDataType getBufferDataType() const;

private:
	std::shared_ptr<GpuBufferRes> m_bufferResource;
};

}